```c
#ifndef HELWAN_WORDS_ABOUT_H
#define HELWAN_WORDS_ABOUT_H

#include <gtk/gtk.h>

#define ABOUT_INSTALLED_ICON_PATH \
    "/usr/share/icons/hicolor/512x512/apps/helwan-words.png"

#define ABOUT_LOCAL_ICON_PATH \
    "data/icons/helwan-words.png"

static inline void show_about_dialog(GtkWindow *parent)
{
    GtkWidget *dialog =
        gtk_about_dialog_new();

    gtk_window_set_transient_for(
        GTK_WINDOW(dialog),
        parent
    );

    gtk_about_dialog_set_program_name(
        GTK_ABOUT_DIALOG(dialog),
        "Helwan Words"
    );

    gtk_about_dialog_set_version(
        GTK_ABOUT_DIALOG(dialog),
        "1.0"
    );

    gtk_about_dialog_set_comments(
        GTK_ABOUT_DIALOG(dialog),
        "A multilingual word guessing game designed for Helwan Linux."
    );

    gtk_about_dialog_set_translator_credits(
        GTK_ABOUT_DIALOG(dialog),
        "Saeed Badreldin"
    );

    GError *error = NULL;
    GdkPixbuf *logo = NULL;

    if (g_file_test(
            ABOUT_LOCAL_ICON_PATH,
            G_FILE_TEST_IS_REGULAR)) {

        logo =
            gdk_pixbuf_new_from_file(
                ABOUT_LOCAL_ICON_PATH,
                &error
            );

    } else if (g_file_test(
                   ABOUT_INSTALLED_ICON_PATH,
                   G_FILE_TEST_IS_REGULAR)) {

        logo =
            gdk_pixbuf_new_from_file(
                ABOUT_INSTALLED_ICON_PATH,
                &error
            );
    }

    if (logo) {

        gtk_about_dialog_set_logo(
            GTK_ABOUT_DIALOG(dialog),
            logo
        );

        /*
         * The About dialog keeps its own reference.
         */
        g_object_unref(logo);

    } else if (error) {

        g_warning(
            "Could not load About logo: %s",
            error->message
        );

        g_error_free(error);
    }

    /*
     * Also set the dialog window icon directly.
     */
    if (g_file_test(
            ABOUT_LOCAL_ICON_PATH,
            G_FILE_TEST_IS_REGULAR)) {

        gtk_window_set_icon_from_file(
            GTK_WINDOW(dialog),
            ABOUT_LOCAL_ICON_PATH,
            NULL
        );

    } else if (g_file_test(
                   ABOUT_INSTALLED_ICON_PATH,
                   G_FILE_TEST_IS_REGULAR)) {

        gtk_window_set_icon_from_file(
            GTK_WINDOW(dialog),
            ABOUT_INSTALLED_ICON_PATH,
            NULL
        );
    }

    gtk_dialog_run(
        GTK_DIALOG(dialog)
    );

    gtk_widget_destroy(dialog);
}

#endif
```
