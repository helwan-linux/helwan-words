#ifndef HELWAN_WORDS_ABOUT_H
#define HELWAN_WORDS_ABOUT_H

#include <gtk/gtk.h>

static inline void show_about_dialog(GtkWindow *parent) {
    GtkWidget *dialog = gtk_about_dialog_new();
    gtk_window_set_transient_for(GTK_WINDOW(dialog), parent);
    
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "Helwan Words");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "1.0");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "A multilingual word guessing game designed for Helwan Linux.");
    gtk_about_dialog_set_translator_credits(GTK_ABOUT_DIALOG(dialog), "Saeed Badreldin");
    
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

#endif
