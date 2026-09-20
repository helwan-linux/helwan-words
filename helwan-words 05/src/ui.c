#include "ui.h"
#include "help.h"
#include "about.h"

#define DATA_DIR "/usr/share/helwan-words/data"
#define ICON_PATH "/usr/share/helwan-words/icons/helwan-words.png"
#define CSS_PATH "/usr/share/helwan-words/helwan-words.css"

static const gchar *english_letters =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const gchar *spanish_letters =
"ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";

static const gchar *arabic_letters[] = {
"ا", "ب", "ت", "ث", "ج", "ح", "خ",
"د", "ذ", "ر", "ز", "س", "ش", "ص",
"ض", "ط", "ظ", "ع", "غ", "ف", "ق",
"ك", "ل", "م", "ن", "ه", "و", "ي"
};

static void load_css(void)
{
GtkCssProvider *provider =
gtk_css_provider_new();

```
GError *error = NULL;

gtk_css_provider_load_from_path(
    provider,
    CSS_PATH,
    &error
);

if (error) {
    g_warning(
        "Could not load CSS: %s",
        error->message
    );

    g_error_free(error);
}

gtk_style_context_add_provider_for_screen(
    gdk_screen_get_default(),
    GTK_STYLE_PROVIDER(provider),
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
);

g_object_unref(provider);


}

static gchar *get_word_file(
GameLanguage language)
{
switch (language) {
case GAME_LANG_AR:
return g_build_filename(
DATA_DIR,
"ar.txt",
NULL
);

    case GAME_LANG_EN:
        return g_build_filename(
            DATA_DIR,
            "en.txt",
            NULL
        );

    case GAME_LANG_ES:
        return g_build_filename(
            DATA_DIR,
            "es.txt",
            NULL
        );
}

return NULL;

}

static void set_language_direction(
AppUI *ui)
{
if (ui->language == GAME_LANG_AR) {
gtk_widget_set_direction(
ui->window,
GTK_TEXT_DIR_RTL
);
} else {
gtk_widget_set_direction(
ui->window,
GTK_TEXT_DIR_LTR
);
}
}

static void update_ui(AppUI *ui);
static void create_letter_buttons(AppUI *ui);

static void on_letter_clicked(
GtkButton *button,
gpointer user_data)
{
AppUI *ui = user_data;

const gchar *letter =
    gtk_button_get_label(button);

if (!letter ||
    !*letter ||
    !ui->game)
    return;

if (!game_guess(
        ui->game,
        letter))
    return;

gtk_widget_set_sensitive(
    GTK_WIDGET(button),
    FALSE
);

update_ui(ui);

if (game_get_state(ui->game) ==
    GAME_WON) {

    while (gtk_events_pending())
        gtk_main_iteration();

    g_usleep(700000);

    if (game_next_round(ui->game)) {
        create_letter_buttons(ui);
        update_ui(ui);
    }
}


}

static void clear_letter_buttons(
AppUI *ui)
{
GList *children =
gtk_container_get_children(
GTK_CONTAINER(ui->letters_grid)
);

for (GList *item = children;
     item;
     item = item->next) {

    gtk_widget_destroy(
        GTK_WIDGET(item->data)
    );
}

g_list_free(children);

}

static void add_letter_button(
AppUI *ui,
const gchar *letter,
gint position)
{
GtkWidget *button =
gtk_button_new_with_label(letter);


gtk_widget_set_size_request(
    button,
    42,
    42
);

gtk_grid_attach(
    GTK_GRID(ui->letters_grid),
    button,
    position % 9,
    position / 9,
    1,
    1
);

g_signal_connect(
    button,
    "clicked",
    G_CALLBACK(on_letter_clicked),
    ui
);

gtk_widget_show(button);

}

static void create_letter_buttons(
AppUI *ui)
{
clear_letter_buttons(ui);

gint position = 0;

if (ui->language == GAME_LANG_AR) {

    for (guint i = 0;
         i < G_N_ELEMENTS(arabic_letters);
         i++) {

        add_letter_button(
            ui,
            arabic_letters[i],
            position++
        );
    }

} else {

    const gchar *letters =
        ui->language == GAME_LANG_EN
            ? english_letters
            : spanish_letters;

    for (gint i = 0;
         letters[i] != '\0';
         i++) {

        gchar letter[2];

        letter[0] = letters[i];
        letter[1] = '\0';

        add_letter_button(
            ui,
            letter,
            position++
        );
    }
}


}

static void new_game(AppUI *ui)
{
gchar *filename =
get_word_file(ui->language);

if (!filename)
    return;

if (ui->game)
    game_free(ui->game);

ui->game =
    game_new(ui->language);

gboolean loaded =
    game_load_words(
        ui->game,
        filename
    );

g_free(filename);

create_letter_buttons(ui);

gtk_widget_set_sensitive(
    ui->new_game_button,
    TRUE
);

if (!loaded) {

    gtk_label_set_text(
        GTK_LABEL(ui->word_label),
        "No words available"
    );

    gtk_label_set_text(
        GTK_LABEL(ui->status_label),
        "Please add words to the selected language file."
    );

    gtk_label_set_text(
        GTK_LABEL(ui->attempts_label),
        ""
    );

    gtk_label_set_text(
        GTK_LABEL(ui->score_label),
        "Score: 0 | Extra Attempts: 0"
    );

    gtk_widget_set_sensitive(
        ui->buy_attempt_button,
        FALSE
    );

    return;
}

update_ui(ui);
```

}

static void on_new_game_clicked(
GtkButton *button,
gpointer user_data)
{
(void)button;

```
AppUI *ui = user_data;

new_game(ui);
```

}

static void on_buy_attempt_clicked(
GtkButton *button,
gpointer user_data)
{
(void)button;

```
AppUI *ui = user_data;

if (game_buy_extra_attempt(ui->game))
    update_ui(ui);
```

}

static void on_help_clicked(
GtkButton *button,
gpointer user_data)
{
(void)button;

```
AppUI *ui = user_data;

show_help_dialog(
    GTK_WINDOW(ui->window)
);
```

}

static void on_about_clicked(
GtkButton *button,
gpointer user_data)
{
(void)button;

```
AppUI *ui = user_data;

show_about_dialog(
    GTK_WINDOW(ui->window)
);
```

}

static void on_language_changed(
GtkComboBoxText *combo,
gpointer user_data)
{
AppUI *ui = user_data;

```
gint active =
    gtk_combo_box_get_active(
        GTK_COMBO_BOX(combo)
    );

if (active == 0)
    ui->language = GAME_LANG_AR;
else if (active == 1)
    ui->language = GAME_LANG_EN;
else
    ui->language = GAME_LANG_ES;

set_language_direction(ui);
new_game(ui);
```

}

static void set_penguin_image(AppUI *ui)
{
GError *error = NULL;

```
GdkPixbuf *pixbuf =
    gdk_pixbuf_new_from_file_at_scale(
        ICON_PATH,
        220,
        220,
        TRUE,
        &error
    );

if (pixbuf) {

    gtk_image_set_from_pixbuf(
        GTK_IMAGE(ui->penguin_image),
        pixbuf
    );

    g_object_unref(pixbuf);
    return;
}

if (error)
    g_error_free(error);

gtk_image_set_from_icon_name(
    GTK_IMAGE(ui->penguin_image),
    "face-smile",
    GTK_ICON_SIZE_DIALOG
);
```

}

static void update_penguin_position(
AppUI *ui)
{
guint wrong =
game_get_wrong_guesses(ui->game);

```
gchar *markup = NULL;

if (wrong == 0) {
    markup = g_strdup(
        "🐧   🏁"
    );
} else if (wrong == 1) {
    markup = g_strdup(
        "🐧  →  🏁"
    );
} else if (wrong == 2) {
    markup = g_strdup(
        "🐧 →  →  🏁"
    );
} else if (wrong == 3) {
    markup = g_strdup(
        "🐧 → →  →  🏁"
    );
} else if (wrong == 4) {
    markup = g_strdup(
        "🐧 → → →  → 🏁"
    );
} else if (wrong == 5) {
    markup = g_strdup(
        "🐧 → → → → → 🏁"
    );
} else {
    markup = g_strdup(
        "🐧     ❌"
    );
}

gtk_label_set_text(
    GTK_LABEL(ui->status_label),
    markup
);

g_free(markup);
```

}

static void update_ui(AppUI *ui)
{
if (!ui || !ui->game)
return;

```
const gchar *display =
    game_get_display_word(ui->game);

if (display) {
    gtk_label_set_text(
        GTK_LABEL(ui->word_label),
        display
    );
}

guint remaining =
    game_get_remaining_guesses(
        ui->game
    );

gchar *attempts =
    g_strdup_printf(
        "Attempts remaining: %u",
        remaining
    );

gtk_label_set_text(
    GTK_LABEL(ui->attempts_label),
    attempts
);

g_free(attempts);

guint score =
    game_get_score(ui->game);

guint extra_attempts =
    game_get_extra_attempts(ui->game);

gchar *score_text =
    g_strdup_printf(
        "Score: %u | Extra Attempts: %u (Buy: 10 pts)",
        score,
        extra_attempts
    );

gtk_label_set_text(
    GTK_LABEL(ui->score_label),
    score_text
);

g_free(score_text);

if (score >= 10 &&
    game_get_state(ui->game) ==
        GAME_PLAYING) {

    gtk_widget_set_sensitive(
        ui->buy_attempt_button,
        TRUE
    );

} else {

    gtk_widget_set_sensitive(
        ui->buy_attempt_button,
        FALSE
    );
}

GameState state =
    game_get_state(ui->game);

if (state == GAME_WON) {

    gtk_label_set_text(
        GTK_LABEL(ui->status_label),
        "🎉 Correct! Next word..."
    );

} else if (state == GAME_LOST) {

    gchar *message =
        g_strdup_printf(
            "Game over! Word: %s",
            game_get_word(ui->game)
        );

    gtk_label_set_text(
        GTK_LABEL(ui->status_label),
        message
    );

    g_free(message);

} else {

    update_penguin_position(ui);
}

if (state == GAME_LOST) {

    GList *children =
        gtk_container_get_children(
            GTK_CONTAINER(ui->letters_grid)
        );

    for (GList *item = children;
         item;
         item = item->next) {

        gtk_widget_set_sensitive(
            GTK_WIDGET(item->data),
            FALSE
        );
    }

    g_list_free(children);
}
```

}

static GtkWidget *create_title(void)
{
GtkWidget *label =
gtk_label_new(NULL);

```
gtk_label_set_markup(
    GTK_LABEL(label),
    "<span size='xx-large' weight='bold'>Helwan Words</span>"
);

gtk_widget_set_halign(
    label,
    GTK_ALIGN_CENTER
);

return label;
```

}

static GtkWidget *create_language_combo(
AppUI *ui)
{
GtkWidget *combo =
gtk_combo_box_text_new();

```
gtk_combo_box_text_append_text(
    GTK_COMBO_BOX_TEXT(combo),
    "العربية"
);

gtk_combo_box_text_append_text(
    GTK_COMBO_BOX_TEXT(combo),
    "English"
);

gtk_combo_box_text_append_text(
    GTK_COMBO_BOX_TEXT(combo),
    "Español"
);

gtk_combo_box_set_active(
    GTK_COMBO_BOX(combo),
    0
);

g_signal_connect(
    combo,
    "changed",
    G_CALLBACK(on_language_changed),
    ui
);

return combo;
```

}

static GtkWidget *create_main_layout(
AppUI *ui)
{
GtkWidget *outer =
gtk_box_new(
GTK_ORIENTATION_VERTICAL,
8
);

```
gtk_widget_set_margin_start(
    outer,
    20
);

gtk_widget_set_margin_end(
    outer,
    20
);

gtk_widget_set_margin_top(
    outer,
    15
);

gtk_widget_set_margin_bottom(
    outer,
    15
);

GtkWidget *title =
    create_title();

gtk_box_pack_start(
    GTK_BOX(outer),
    title,
    FALSE,
    FALSE,
    0
);

GtkWidget *language =
    create_language_combo(ui);

gtk_widget_set_halign(
    language,
    GTK_ALIGN_CENTER
);

gtk_box_pack_start(
    GTK_BOX(outer),
    language,
    FALSE,
    FALSE,
    0
);

ui->language_combo =
    language;

ui->penguin_image =
    gtk_image_new();

gtk_widget_set_halign(
    ui->penguin_image,
    GTK_ALIGN_CENTER
);

gtk_widget_set_size_request(
    ui->penguin_image,
    180,
    180
);

gtk_box_pack_start(
    GTK_BOX(outer),
    ui->penguin_image,
    FALSE,
    FALSE,
    0
);

GtkWidget *path_label =
    gtk_label_new(
        "🐧 → → → → → 🏁"
    );

gtk_widget_set_halign(
    path_label,
    GTK_ALIGN_CENTER
);

gtk_box_pack_start(
    GTK_BOX(outer),
    path_label,
    FALSE,
    FALSE,
    0
);

ui->status_label =
    path_label;

ui->word_label =
    gtk_label_new("_ _ _ _");

gtk_widget_set_name(
    ui->word_label,
    "word-label"
);

gtk_widget_set_halign(
    ui->word_label,
    GTK_ALIGN_CENTER
);

gtk_box_pack_start(
    GTK_BOX(outer),
    ui->word_label,
    FALSE,
    FALSE,
    3
);

ui->score_label =
    gtk_label_new(
        "Score: 0 | Extra Attempts: 0 (Buy: 10 pts)"
    );

gtk_widget_set_halign(
    ui->score_label,
    GTK_ALIGN_CENTER
);

gtk_box_pack_start(
    GTK_BOX(outer),
    ui->score_label,
    FALSE,
    FALSE,
    0
);

ui->buy_attempt_button =
    gtk_button_new_with_label(
        "Buy Extra Attempt (+1)"
    );

gtk_widget_set_halign(
    ui->buy_attempt_button,
    GTK_ALIGN_CENTER
);

gtk_widget_set_size_request(
    ui->buy_attempt_button,
    210,
    32
);

gtk_widget_set_sensitive(
    ui->buy_attempt_button,
    FALSE
);

gtk_box_pack_start(
    GTK_BOX(outer),
    ui->buy_attempt_button,
    FALSE,
    FALSE,
    0
);

g_signal_connect(
    ui->buy_attempt_button,
    "clicked",
    G_CALLBACK(on_buy_attempt_clicked),
    ui
);

ui->attempts_label =
    gtk_label_new("");

gtk_widget_set_halign(
    ui->attempts_label,
    GTK_ALIGN_CENTER
);

gtk_box_pack_start(
    GTK_BOX(outer),
    ui->attempts_label,
    FALSE,
    FALSE,
    0
);

ui->letters_grid =
    gtk_grid_new();

gtk_grid_set_row_spacing(
    GTK_GRID(ui->letters_grid),
    4
);

gtk_grid_set_column_spacing(
    GTK_GRID(ui->letters_grid),
    4
);

gtk_widget_set_halign(
    ui->letters_grid,
    GTK_ALIGN_CENTER
);

gtk_box_pack_start(
    GTK_BOX(outer),
    ui->letters_grid,
    FALSE,
    FALSE,
    2
);

GtkWidget *bottom_box =
    gtk_box_new(
        GTK_ORIENTATION_HORIZONTAL,
        10
    );

gtk_widget_set_halign(
    bottom_box,
    GTK_ALIGN_CENTER
);

ui->help_button =
    gtk_button_new_with_label("Help");

gtk_widget_set_size_request(
    ui->help_button,
    90,
    35
);

gtk_box_pack_start(
    GTK_BOX(bottom_box),
    ui->help_button,
    FALSE,
    FALSE,
    0
);

g_signal_connect(
    ui->help_button,
    "clicked",
    G_CALLBACK(on_help_clicked),
    ui
);

ui->new_game_button =
    gtk_button_new_with_label("New Game");

gtk_widget_set_size_request(
    ui->new_game_button,
    130,
    35
);

gtk_box_pack_start(
    GTK_BOX(bottom_box),
    ui->new_game_button,
    FALSE,
    FALSE,
    0
);

g_signal_connect(
    ui->new_game_button,
    "clicked",
    G_CALLBACK(on_new_game_clicked),
    ui
);

ui->about_button =
    gtk_button_new_with_label("About");

gtk_widget_set_size_request(
    ui->about_button,
    90,
    35
);

gtk_box_pack_start(
    GTK_BOX(bottom_box),
    ui->about_button,
    FALSE,
    FALSE,
    0
);

g_signal_connect(
    ui->about_button,
    "clicked",
    G_CALLBACK(on_about_clicked),
    ui
);

gtk_box_pack_start(
    GTK_BOX(outer),
    bottom_box,
    FALSE,
    FALSE,
    5
);

return outer;
```

}

static void on_window_destroy(
GtkWidget *widget,
gpointer user_data)
{
(void)widget;

```
AppUI *ui = user_data;

if (ui->game)
    game_free(ui->game);

g_free(ui);
```

}

void ui_create(GtkApplication *app)
{
AppUI *ui = g_new0(AppUI, 1);

```
ui->language =
    GAME_LANG_AR;

ui->window =
    gtk_application_window_new(app);

gtk_window_set_title(
    GTK_WINDOW(ui->window),
    "Helwan Words"
);

gtk_window_set_default_size(
    GTK_WINDOW(ui->window),
    760,
    850
);

gtk_window_set_resizable(
    GTK_WINDOW(ui->window),
    TRUE
);

GtkWidget *layout =
    create_main_layout(ui);

gtk_container_add(
    GTK_CONTAINER(ui->window),
    layout
);

load_css();
set_penguin_image(ui);

g_signal_connect(
    ui->window,
    "destroy",
    G_CALLBACK(on_window_destroy),
    ui
);

gtk_widget_show_all(ui->window);

set_language_direction(ui);
new_game(ui);

}
