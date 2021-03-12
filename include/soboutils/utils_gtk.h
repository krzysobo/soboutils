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


#ifndef UTL_GTK_H
#define UTL_GTK_H 1

#include <gtk/gtk.h>

GtkTextTag *tag_bold;

int get_gtk_entry_text(GtkEntry *entry, char **text_out);
int get_gtk_entry_text_by_name(gchar *name, GtkWindow *window,
    char **text_out);

int set_gtk_entry_text(GtkEntry *entry, gchar *text);
int set_gtk_entry_text_by_name(gchar *name, GtkWindow *window, gchar *text);

int get_gtk_tv_text(GtkTextView *tv, char **text_out);
int get_gtk_tv_text_by_name(gchar *name, GtkWindow *window, char **text_out);


int set_gtk_tv_text(GtkTextView *tv, gchar *text);
int set_gtk_tv_text_by_name(gchar *name, GtkWindow *window, gchar *text);

int add_gtk_tv_text(GtkTextView *tv, gchar *text);
int add_gtk_tv_text_by_name(gchar *name, GtkWindow *window, gchar *text);

gboolean get_gtk_checkbtn_active_by_name(gchar *name, GtkWindow *window);
int set_gtk_checkbtn_active_by_name(gchar *name, GtkWindow *window,
    gboolean active);


void set_widget_data_in_window(GtkWindow *window, GtkBuilder *builder,
    const gchar *key);

void set_widgets_data_in_window(GtkWindow *window, GtkBuilder *builder,
    gchar *widget_names[], int nitems);

GtkWidget *get_widget_by_name(gchar *name, GtkWindow *window);

void connect_widget_by_name(gchar *name, gchar *signal,
    GCallback cb, GtkWindow *window);

void init_tags(GtkWindow *window);

void switch_visible_boxes(char *box_name, char **boxes, int n_box_names,
    GtkWindow *window);

int connect_object_with_parent(const char *child_id, const char *parent_id,
    GtkBuilder *builder);

int connect_objects_with_parents(const char **child_parent_pairs[],
    int nitems, GtkBuilder *builder);

#endif
