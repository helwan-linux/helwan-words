#ifndef HELWAN_WORDS_UI_H
#define HELWAN_WORDS_UI_H

#include <gtk/gtk.h>
#include "game.h"

typedef struct {
    GtkWidget *window;
    GtkWidget *language_combo;
    GtkWidget *penguin_image;

    GtkWidget *word_label;
    GtkWidget *status_label;
    GtkWidget *attempts_label;
    GtkWidget *score_label;
    GtkWidget *buy_attempt_button;

    GtkWidget *letters_grid;
    GtkWidget *new_game_button;
    GtkWidget *help_button;
    GtkWidget *about_button;

    Game *game;
    GameLanguage language;
} AppUI;

void ui_create(GtkApplication *app);

#endif
