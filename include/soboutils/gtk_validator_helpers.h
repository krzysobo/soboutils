/*  
*  Copyright (c) 2020-2021 Krzysztof Sobolewski <krzysztof.sobolewski@gmail.com>
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:

*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.

*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
*/


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
