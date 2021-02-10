#include <gtk/gtk.h>
#include "soboutils/utils_gtk.h"


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
