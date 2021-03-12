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
    if (buffer == NULL)
        return -1;

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
int get_gtk_entry_text_by_name(gchar *name, GtkWindow *window,
    char **text_out)
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
    if (buffer == NULL)
        return -1;
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
 * @brief
 * @note
 * @param  *tv:
 * @param  **text_out:
 * @retval
 */
int get_gtk_tv_text(GtkTextView *tv, char **text_out)
{
    GtkTextBuffer *buffer = NULL;
    GtkTextIter start, end;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
    if (buffer == NULL) {
        return -1;
    }
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    *text_out = gtk_text_buffer_get_text(buffer, &start, &end, true);

    return 0;
}

/**
 * @brief
 * @note
 * @param  *name:
 * @param  *window:
 * @param  **text_out:
 * @retval
 */
int get_gtk_tv_text_by_name(gchar *name, GtkWindow *window, char **text_out)
{
    GtkTextView *tv = NULL;
    if ((name == NULL) || (strlen(name) < 1))
        return -1;
    tv = GTK_TEXT_VIEW(get_widget_by_name(name, window));
    if (tv == NULL)
        return -1;

    return get_gtk_tv_text(tv, text_out);
}

/**
 * @brief
 * @note
 * @param  *tv:
 * @param  *text:
 * @retval
 */
int set_gtk_tv_text(GtkTextView *tv, gchar *text)
{
    GtkTextBuffer *buffer;
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
    if (buffer == NULL)
        return -1;
    gtk_text_buffer_set_text(buffer, text, strlen(text));

    return 0;
}

/**
 * @brief
 * @note
 * @param  *name:
 * @param  *window:
 * @param  *text:
 * @retval
 */
int set_gtk_tv_text_by_name(gchar *name, GtkWindow *window, gchar *text)
{
    GtkTextView *tv = NULL;
    if ((name == NULL) || (strlen(name) < 1))
        return -1;
    tv = GTK_TEXT_VIEW(get_widget_by_name(name, window));
    if (tv == NULL)
        return -1;
    return set_gtk_tv_text(tv, text);
}

/**
 * @brief
 * @note
 * @param  *tv:
 * @param  *text:
 * @retval
 */
int add_gtk_tv_text(GtkTextView *tv, gchar *text)
{
    GtkTextBuffer *buffer;
    GtkTextIter start, end;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
    if (buffer == NULL)
        return -1;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    gtk_text_buffer_insert(buffer, &end, text, strlen(text));

    return 0;
}

/**
 * @brief
 * @note
 * @param  *name:
 * @param  *window:
 * @param  *text:
 * @retval
 */
int add_gtk_tv_text_by_name(gchar *name, GtkWindow *window, gchar *text)
{
    GtkTextView *tv = NULL;
    if ((name == NULL) || (strlen(name) < 1))
        return -1;
    tv = GTK_TEXT_VIEW(get_widget_by_name(name, window));
    if (tv == NULL)
        return -1;

    return add_gtk_tv_text(tv, text);
}

/**
 * @brief
 * @note
 * @param  *name:
 * @retval
 */
gboolean get_gtk_checkbtn_active_by_name(gchar *name, GtkWindow *window)
{
    GtkCheckButton *chb = NULL;
    if ((name == NULL) || (strlen(name) < 1))
        return false;
    chb = GTK_CHECK_BUTTON(get_widget_by_name(name, window));
    if (chb == NULL)
        return false;

    return gtk_check_button_get_active(chb);
}

/**
 * @brief
 * @note
 * @param  *name:
 * @retval
 */
int set_gtk_checkbtn_active_by_name(gchar *name, GtkWindow *window,
    gboolean active)
{
    GtkCheckButton *chb = NULL;
    if ((name == NULL) || (strlen(name) < 1))
        return -1;

    chb = GTK_CHECK_BUTTON(get_widget_by_name(name, window));
    if (chb == NULL)
        return -1;

    gtk_check_button_set_active(chb, active);

    return 0;
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

/**
 * @brief toggle N boxes by visibility as in the case of a "radio button":
 *        a selected box gets visible, while other boxes from the list
 *        do disappear.
 * @note
 * @param  *box_name: name of the currently selected box
 * @param  **boxes:  an array of switchable box names
 * @param  n_box_names:  number of items in the above array
 * @param  *window: GtkWindow object
 * @retval None
 */
void switch_visible_boxes(char *box_name, char **boxes, int n_box_names,
    GtkWindow *window)
{
    int i = 0;
    GtkWidget *widget = NULL;

    for (i = 0; i < n_box_names; i++) {
        widget = get_widget_by_name(boxes[i], window);
        if (strcmp(boxes[i], box_name) == 0)
            gtk_widget_set_visible(widget, true);
        else
            gtk_widget_set_visible(widget, false);
    }
}

/**
 * @brief
 * @note
 * @param  *child_id:
 * @param  *parent_id:
 * @param  *builder:
 * @retval
 */
int connect_object_with_parent(const char *child_id, const char *parent_id,
    GtkBuilder *builder)
{
    GObject *child, *parent;
    child = gtk_builder_get_object(builder, child_id);
    if (child == NULL)
        return -1;

    parent = gtk_builder_get_object(builder, parent_id);
    if (parent == NULL)
        return -1;

    gtk_widget_set_parent(GTK_WIDGET(child), GTK_WIDGET(parent));

    return 0;
}


/**
 * @brief
 * @note
 * @param  **child_parent_pairs[]:
 * @param  nitems:
 * @param  *builder:
 * @retval
 */
int connect_objects_with_parents(const char **child_parent_pairs[],
    int nitems, GtkBuilder *builder)
{
    int i = 0;
    int res = 0;

    for (i = 0; i < nitems; i++) {
        res = connect_object_with_parent(child_parent_pairs[i][0],
            child_parent_pairs[i][1], builder);
        if (res != 0)
            return -1;
    }
    return res;
}