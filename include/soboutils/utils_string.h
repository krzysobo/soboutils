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


#ifndef UTL_STR_H
#define UTL_STR_H 1

#include <stdbool.h>
#include <ctype.h>

int is_trimmable(char x, char *extra_chars);
char *ltrim(char *text, char *extra_chars);
char *rtrim(char *text, char *extra_chars);
char *trim(char *text, char *extra_chars);

int number_of_substrings(char *haystack, char *needle);

int strpos(char *haystack, char *needle);

int split_string(char *string_in, char *sep_in, char ***strings_out);


unsigned long join_strings(char *items[], int nitems, bool is_quoted,
    const char *sep_in, char **str_out);

int add_to_string(char **str, size_t *str_size, char *part);

int substr(char *text, size_t offset, size_t limit, char *part,
    size_t part_size);

/* string/char array functions */
int char_array_slice(char *dst, char *src, int s_len, int s_from);
int get_char_array_slice_number(char *src, int page_size);

#endif
