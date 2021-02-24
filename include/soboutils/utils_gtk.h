#include <gtk/gtk.h>

GtkTextTag *tag_bold;

int get_gtk_entry_text(GtkEntry *entry, char **text_out);
int get_gtk_entry_text_by_name(gchar *name, GtkWindow *window, char **text_out);

int set_gtk_entry_text(GtkEntry *entry, gchar *text);
int set_gtk_entry_text_by_name(gchar *name, GtkWindow *window, gchar *text);

void set_widget_data_in_window(GtkWindow *window, GtkBuilder *builder,
    const gchar *key);

void set_widgets_data_in_window(GtkWindow *window, GtkBuilder *builder, 
    gchar *widget_names[], int nitems);

GtkWidget *get_widget_by_name(gchar *name, GtkWindow *window);

void connect_widget_by_name(gchar *name, gchar *signal, 
    GCallback cb, GtkWindow *window);

void init_tags(GtkWindow *window);
