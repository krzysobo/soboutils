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


#ifndef UTL_LST_H
#define UTL_LST_H 1

#include <stdint.h>
#include <ctype.h>

void init_list(int max_items, void **list, size_t item_size);

int find_first_free_item_index(void *list, int max_items,
    int (is_free_fun)(void *, int));

int extend_list(void **list, int *current_max_num_items,
    int extra_max_num_items, size_t item_size);

int find_or_create_free_item_index(
    void **list,
    int *current_max_num_items,
    int extra_max_num_items,
    size_t item_size,
    int (is_free_fun)(void *, int));

void update_num_items(void *list,
    int *ptr_max_num_items,
    int *ptr_num_items,
    int (is_free_fun)(void *, int));

#endif
