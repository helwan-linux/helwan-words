#ifndef HELWAN_WORDS_GAME_H
#define HELWAN_WORDS_GAME_H

#include <glib.h>

#define MAX_WRONG_GUESSES 6
#define MAX_WORD_LENGTH 128

typedef enum {
    GAME_LANG_AR,
    GAME_LANG_EN,
    GAME_LANG_ES
} GameLanguage;

typedef enum {
    GAME_PLAYING,
    GAME_WON,
    GAME_LOST
} GameState;

typedef struct {
    gchar *word;
    gchar *display_word;

    GHashTable *guessed_letters;

    guint wrong_guesses;
    guint correct_guesses;

    GameLanguage language;
    GameState state;
} Game;

Game *game_new(GameLanguage language);
void game_free(Game *game);

gboolean game_load_words(Game *game, const gchar *filename);

gboolean game_new_round(Game *game);

gboolean game_guess(Game *game, const gchar *letter);

gboolean game_letter_was_guessed(const Game *game,
                                 const gchar *letter);

gboolean game_is_complete(const Game *game);

const gchar *game_get_display_word(const Game *game);
const gchar *game_get_word(const Game *game);

guint game_get_wrong_guesses(const Game *game);
guint game_get_remaining_guesses(const Game *game);

GameState game_get_state(const Game *game);

#endif
