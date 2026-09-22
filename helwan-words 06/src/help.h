#ifndef HELWAN_WORDS_HELP_H
#define HELWAN_WORDS_HELP_H

#include <gtk/gtk.h>

static inline void show_help_dialog(GtkWindow *parent) {
    GtkWidget *dialog = gtk_message_dialog_new(
        parent,
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Helwan Words - Help & Instructions\n\n"
        "1. Game Objective:\n"
        "   - Guess the letters of the secret word before the penguin runs out of attempts.\n\n"
        "2. Continuous Gameplay:\n"
        "   - Once you win the current word, the game automatically transitions to a new word.\n\n"
        "3. Scoring & Shop System:\n"
        "   - Each winning word grants you 2 points (+2 points).\n"
        "   - For every 10 points collected, you can buy an extra wrong attempt to help you with difficult words.\n\n"
        "4. Supported Languages:\n"
        "   - Arabic, English, and Spanish."
    );
    gtk_window_set_title(GTK_WINDOW(dialog), "Game Instructions");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

#endif
