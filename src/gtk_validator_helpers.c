#include <stdbool.h>
#include <ctype.h> /* isnumber etc... */
#include <gtk/gtk.h>
#include "soboutils/utils_gtk.h"
#include "soboutils/gtk_validator_helpers.h"


/**
 * @brief  
 * @note   
 * @param  *text: 
 * @retval 
 */
bool check_str_not_empty(char *text)
{
    if ((text == NULL) || (strlen(text) < 1))
        return false;

    return true;
}

/**
 * @brief  checks whether the string is unsigned integer/long 
 *         (non-float, ie. without decimal part)
 * @note   
 * @param  *text: 
 * @retval true or false
 */
bool check_str_is_unsigned_int_numeric(char *text)
{
    int i = 0;
    size_t len_text;

    if (!check_str_not_empty(text))
        return false;

    len_text = strlen(text);
    for (i = 0; i < len_text; i++)
    {
        if (!isnumber(text[i]))
            return false;
    }

    return true;
}

/**
 * @brief  
 * @note   
 * @param  *field_id: 
 * @retval None
 */
void show_error(char *field_id, char *error_msg, GtkWindow *window)
{
    char *error_label_prefix = "error_";
    char *error_label_id = NULL;
    GtkWidget *widget = NULL;

    error_label_id = calloc(strlen(field_id) +
                                strlen(error_label_prefix) + 1,
                            1);

    sprintf(error_label_id, "%s%s", error_label_prefix, field_id);

    widget = get_widget_by_name(error_label_id, window);
    gtk_label_set_text(GTK_LABEL(widget), error_msg);
    gtk_widget_set_visible(widget, true);

    free(error_label_id);
}

/**
 * @brief  
 * @note   
 * @param  *field_id: 
 * @retval None
 */
void hide_error(char *field_id, GtkWindow *window)
{
    char *error_label_prefix = "error_";
    char *error_label_id = NULL;
    GtkWidget *widget = NULL;

    error_label_id = calloc(strlen(field_id) +
                                strlen(error_label_prefix) + 1,
                            1);
    sprintf(error_label_id, "%s%s", error_label_prefix, field_id);

    widget = get_widget_by_name(error_label_id, window);
    gtk_label_set_text(GTK_LABEL(widget), "");
    gtk_widget_set_visible(widget, false);
    free(error_label_id);
}

/**
 * @brief  
 * @note   
 * @param  *field_id: 
 * @param  *first_field_in_array: 
 * @param  nitems: 
 * @retval 
 */
FieldInfo *find_field_by_id(char *field_id, FieldInfo *first_field_in_array,
                            int nitems)
{
    int i = 0;
    FieldInfo *f_i;
    f_i = first_field_in_array;

    for (i = 0; i < nitems; i++)
    {
        if (strcmp(f_i->field_id, field_id) == 0)
        {
            return f_i;
        }
        f_i++;
    }

    return NULL;
}
