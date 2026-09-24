//game.c
#include "game.h"

static GPtrArray *load_word_file(const gchar *filename)
{
    gchar *contents = NULL;
    gsize length = 0;

    if (!g_file_get_contents(filename, &contents, &length, NULL))
        return NULL;

    GPtrArray *words = g_ptr_array_new_with_free_func(g_free);
    gchar **lines = g_strsplit(contents, "\n", -1);

    for (gint i = 0; lines[i] != NULL; i++) {
        gchar *word = g_strdup(lines[i]);

        g_strstrip(word);

        if (*word == '\0') {
            g_free(word);
            continue;
        }

        if (!g_utf8_validate(word, -1, NULL)) {
            g_free(word);
            continue;
        }

        g_ptr_array_add(words, word);
    }

    g_strfreev(lines);
    g_free(contents);

    return words;
}

static gchar *normalize_letter(const gchar *letter)
{
    if (!letter || !*letter)
        return NULL;

    gunichar ch = g_utf8_get_char(letter);
    ch = g_unichar_tolower(ch);

    gchar buffer[8];
    gint len = g_unichar_to_utf8(ch, buffer);
    buffer[len] = '\0';

    return g_strdup(buffer);
}

static void update_display_word(Game *game)
{
    if (!game || !game->word)
        return;

    GString *display = g_string_new(NULL);
    const gchar *p = game->word;

    while (*p) {
        gunichar ch = g_utf8_get_char(p);

        gchar letter[8];
        gint len = g_unichar_to_utf8(
            g_unichar_tolower(ch),
            letter
        );

        letter[len] = '\0';

        if (g_hash_table_contains(
                game->guessed_letters,
                letter)) {
            g_string_append(display, letter);
        } else {
            g_string_append(display, "_");
        }

        p = g_utf8_next_char(p);

        if (*p)
            g_string_append_c(display, ' ');
    }

    g_free(game->display_word);
    game->display_word = g_string_free(display, FALSE);
}

static gboolean all_letters_found(Game *game)
{
    if (!game || !game->word)
        return FALSE;

    const gchar *p = game->word;

    while (*p) {
        gunichar ch = g_utf8_get_char(p);

        gchar letter[8];
        gint len = g_unichar_to_utf8(
            g_unichar_tolower(ch),
            letter
        );

        letter[len] = '\0';

        if (!g_hash_table_contains(
                game->guessed_letters,
                letter)) {
            return FALSE;
        }

        p = g_utf8_next_char(p);
    }

    return TRUE;
}

Game *game_new(GameLanguage language)
{
    Game *game = g_new0(Game, 1);

    game->language = language;
    game->state = GAME_PLAYING;
    game->max_wrong_guesses = INITIAL_MAX_WRONG_GUESSES;
    game->score = 0;

    game->guessed_letters = g_hash_table_new_full(
        g_str_hash,
        g_str_equal,
        g_free,
        NULL
    );

    return game;
}

void game_free(Game *game)
{
    if (!game)
        return;

    g_free(game->word);
    g_free(game->display_word);

    if (game->guessed_letters)
        g_hash_table_destroy(game->guessed_letters);

    if (game->all_words)
        g_ptr_array_free(game->all_words, TRUE);

    g_free(game);
}

gboolean game_load_words(Game *game, const gchar *filename)
{
    if (!game || !filename)
        return FALSE;

    if (game->all_words) {
        g_ptr_array_free(game->all_words, TRUE);
        game->all_words = NULL;
    }

    game->all_words = load_word_file(filename);

    if (!game->all_words || game->all_words->len == 0)
        return FALSE;

    return game_next_round(game);
}

gboolean game_next_round(Game *game)
{
    if (!game || !game->all_words || game->all_words->len == 0)
        return FALSE;

    guint index = g_random_int_range(
        0,
        game->all_words->len
    );

    gchar *selected = g_strdup(
        g_ptr_array_index(game->all_words, index)
    );

    if (!selected || *selected == '\0') {
        g_free(selected);
        return FALSE;
    }

    g_free(game->word);
    game->word = selected;

    g_hash_table_remove_all(game->guessed_letters);

    game->wrong_guesses = 0;
    game->correct_guesses = 0;
    game->state = GAME_PLAYING;

    update_display_word(game);

    return TRUE;
}

gboolean game_guess(Game *game, const gchar *letter)
{
    if (!game || !letter || !*letter)
        return FALSE;

    if (game->state != GAME_PLAYING)
        return FALSE;

    if (g_utf8_strlen(letter, -1) != 1)
        return FALSE;

    gchar *normalized = normalize_letter(letter);

    if (!normalized)
        return FALSE;

    if (g_hash_table_contains(
            game->guessed_letters,
            normalized)) {
        g_free(normalized);
        return FALSE;
    }

    g_hash_table_add(
        game->guessed_letters,
        normalized
    );

    gboolean found = FALSE;
    const gchar *p = game->word;
    gunichar guess_char = g_utf8_get_char(normalized);

    while (*p) {
        gunichar word_char = g_utf8_get_char(p);

        if (g_unichar_tolower(word_char) ==
            g_unichar_tolower(guess_char)) {
            found = TRUE;
            break;
        }

        p = g_utf8_next_char(p);
    }

    if (found)
        game->correct_guesses++;
    else
        game->wrong_guesses++;

    update_display_word(game);

    if (all_letters_found(game)) {
        game->state = GAME_WON;
        game->score += 2;
    } else if (game->wrong_guesses >= game->max_wrong_guesses) {
        game->state = GAME_LOST;
    }

    return TRUE;
}

gboolean game_letter_was_guessed(
    const Game *game,
    const gchar *letter
)
{
    if (!game || !letter)
        return FALSE;

    gchar *normalized = normalize_letter(letter);

    if (!normalized)
        return FALSE;

    gboolean result = g_hash_table_contains(
        game->guessed_letters,
        normalized
    );

    g_free(normalized);

    return result;
}

gboolean game_is_complete(const Game *game)
{
    if (!game)
        return FALSE;

    return game->state != GAME_PLAYING;
}

const gchar *game_get_display_word(const Game *game)
{
    if (!game)
        return NULL;

    return game->display_word;
}

const gchar *game_get_word(const Game *game)
{
    if (!game)
        return NULL;

    return game->word;
}

guint game_get_wrong_guesses(const Game *game)
{
    if (!game)
        return 0;

    return game->wrong_guesses;
}

guint game_get_remaining_guesses(const Game *game)
{
    if (!game)
        return 0;

    if (game->wrong_guesses >= game->max_wrong_guesses)
        return 0;

    return game->max_wrong_guesses -
           game->wrong_guesses;
}

guint game_get_score(const Game *game)
{
    if (!game)
        return 0;

    return game->score;
}

guint game_get_extra_attempts(const Game *game)
{
    if (!game)
        return 0;

    if (game->max_wrong_guesses <=
        INITIAL_MAX_WRONG_GUESSES)
        return 0;

    return game->max_wrong_guesses -
           INITIAL_MAX_WRONG_GUESSES;
}

gboolean game_buy_extra_attempt(Game *game)
{
    if (!game)
        return FALSE;

    if (game->score < 10)
        return FALSE;

    game->score -= 10;
    game->max_wrong_guesses++;

    return TRUE;
}

GameState game_get_state(const Game *game)
{
    if (!game)
        return GAME_LOST;

    return game->state;
}
