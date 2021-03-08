#ifndef ERROR_HELPERS_H
#define ERROR_HELPERS_H 1

#include <gtk/gtk.h>

enum FieldTypes {
    FT_TEXT_ENTRY = 0,
    FT_TEXT_VIEW
};

typedef struct {
    char *field_id;
    int field_type; 
    char **ptr_to_char;
    bool **ptr_to_bool;
    int error_code;
    char *error_msg;
} FieldInfo;


bool check_str_not_empty(char *text);
bool check_str_is_unsigned_int_numeric(char *text);

void show_error(char *field_id, char *error_msg, GtkWindow *window);
void hide_error(char *field_id, GtkWindow *window);

FieldInfo *find_field_by_id(char *field_id, FieldInfo *first_field_in_array,
    int nitems);


#endif
