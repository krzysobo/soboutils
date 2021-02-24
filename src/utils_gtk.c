#include <gtk/gtk.h>
#include "soboutils/utils_gtk.h"


/**
 * @brief  
 * @note   
 * @param  *entry: 
 * @param  **text_out: 
 * @retval 
 */
int get_gtk_entry_text(GtkEntry *entry, char **text_out)
{
    GtkEntryBuffer *buffer;
    const char *text;
    
    buffer = gtk_entry_get_buffer(entry);
    if (buffer == NULL) {
        return -1;
    }
    text = gtk_entry_buffer_get_text(buffer);
    *text_out = (char *)text;

    return 0;
}


/**
 * @brief  
 * @note   
 * @param  *entry: 
 * @param  **text_out: 
 * @retval 
 */
int get_gtk_entry_text_by_name(gchar *name, GtkWindow *window, char **text_out)
{
    GtkEntry *entry = NULL;
    if ((name == NULL) || (strlen(name) < 1))
        return -1;
    entry = GTK_ENTRY(get_widget_by_name(name, window));
    if (entry == NULL)
        return -1;

    return get_gtk_entry_text(entry, text_out);
}


/**
 * @brief  
 * @note   
 * @param  *entry: 
 * @param  **text_out: 
 * @retval 
 */
int set_gtk_entry_text(GtkEntry *entry, gchar *text)
{
    GtkEntryBuffer *buffer;
    
    buffer = gtk_entry_get_buffer(entry);
    if (buffer == NULL) {
        return -1;
    }
    
    gtk_entry_buffer_set_text(buffer, text, strlen(text));

    return 0;
}


/**
 * @brief  
 * @note   
 * @param  *entry: 
 * @param  **text_out: 
 * @retval 
 */
int set_gtk_entry_text_by_name(gchar *name, GtkWindow *window, gchar *text)
{
    GtkEntry *entry = NULL;
    if ((name == NULL) || (strlen(name) < 1))
        return -1;
    entry = GTK_ENTRY(get_widget_by_name(name, window));
    if (entry == NULL)
        return -1;

    return set_gtk_entry_text(entry, text);
}

/**
 * @brief  calls g_object_set_data on 
 * @note   
 * @param  *window: 
 * @param  *builder: 
 * @param  *key: 
 * @retval None
 */
void set_widget_data_in_window(GtkWindow *window, GtkBuilder *builder,
    const gchar *key)
{
    GtkWidget *widget;
    widget = (GtkWidget *)gtk_builder_get_object(builder, key);
    g_object_set_data(G_OBJECT(window), key, widget);
}


/**
 * @brief  "expose" the widgets to be searchable by name
 * @note   
 * @param  *window: 
 * @param  *builder: 
 * @param  *widget_names: 
 * @retval None
 */
void set_widgets_data_in_window(GtkWindow *window, GtkBuilder *builder, 
    gchar *widget_names[], int nitems)
{
    int i;
    for (i = 0; i < nitems; i++) {
        set_widget_data_in_window(window, builder, widget_names[i]);
    }
}


/**
 * @brief  
 * @note   
 * @param  *name: 
 * @param  *window: 
 * @retval 
 */
GtkWidget *get_widget_by_name(gchar *name, GtkWindow *window)
{
    return GTK_WIDGET(g_object_get_data(G_OBJECT(window), name));
}


/**
 * @brief  
 * @note   
 * @param  *name: 
 * @param  *signal: 
 * @param  cb: 
 * @param  *window: 
 * @retval None
 */
void connect_widget_by_name(gchar *name, gchar *signal, 
    GCallback cb, GtkWindow *window)
{
    g_signal_connect(get_widget_by_name(name, window), signal, 
        G_CALLBACK(cb), window);
}


/**
 * @brief  
 * @note   
 * @param  *window: 
 * @retval None
 */
void init_tags(GtkWindow *window)
{
    GtkTextBuffer *buffer;
    GtkWidget *tv_output;
    tv_output = GTK_WIDGET(g_object_get_data(G_OBJECT(window),
        "tv_output"));
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv_output));

    tag_bold = gtk_text_buffer_create_tag(buffer, "bold", 
        "weight", PANGO_WEIGHT_BOLD, NULL);    
}
