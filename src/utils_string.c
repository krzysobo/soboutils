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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>  /* for isspace */
#include "soboutils/common.h"


/**
 * @brief  checks whether a char is trimmable
 * @note
 * @param  x:
 * @param  *extra_chars:
 * @retval 1 (true) or 0 (false)
 */
int is_trimmable(char x, char *extra_chars)
{
    if (isspace(x) || (extra_chars && strchr(extra_chars, x))) {
        return 1;
    }

    return 0;
}


/**
 * @brief  trims the string on the left
 * @note
 * @param  *text:
 * @param  *extra_chars: extra characters to be trimmed
 * @retval trimmed string
 */
char *ltrim(char *text, char *extra_chars)
{
    if (!text || !strlen(text)) {
        return text;
    }

    while (is_trimmable(*text, extra_chars))
        text++;

    return text;
}


/**
 * @brief  trims the string on the right
 * @note
 * @param  *text:
 * @param  *extra_chars: extra characters to be trimmed
 * @retval trimmed string
 */
char *rtrim(char *text, char *extra_chars)
{
    char *text_out;
    char *end_pos;
    int new_string_size;
    if (!text || !strlen(text)) {
        return text;
    }

    end_pos = text + strlen(text);
    while (is_trimmable(*end_pos, extra_chars)) {
        --end_pos;
    }

    new_string_size = end_pos - text + 1;
    text_out = calloc(new_string_size + 1, 1);
    memcpy(text_out, text, new_string_size);
    text_out[new_string_size] = 0;

    return text_out;
}


/**
 * @brief trims the string on both sides
 * @note
 * @param  *text:
 * @param  *extra_chars: extra characters to be trimmed
 * @retval trimmed string
 */
char *trim(char *text, char *extra_chars)
{
    return rtrim(ltrim(text, extra_chars), extra_chars);
}


/**
 * @brief
 * @note
 * @param  *haystack:
 * @param  *needle:
 * @retval int - -1 if not found, >= 0 if otherwise
 */
int strpos(char *haystack, char *needle)
{
    char *ptr_found;
    int pos;

    ptr_found = strstr(haystack, needle);
    if (!ptr_found) {
        return -1;
    }
    pos = ptr_found - haystack;

    return pos;
}


/**
 * @brief
 * @note
 * @param  *haystack:
 * @param  *needle:
 * @retval
 */
int number_of_substrings(char *haystack, char *needle)
{
    char *p = NULL;
    int n_items = 0;
    if ((haystack == NULL) || (strlen(haystack) < 1) ||
        (needle == NULL) || (strlen(needle) < 1)) {
        return -1;
    }

    p = haystack;
    while ((p = strstr(p, needle))) {
        n_items++;
        p++;
    }

    return n_items;
}

int split_string(char *string_in, char *sep_in, char ***strings_out)
{
    char *sep = NULL;
    char *p = NULL, *old_p = NULL;
    int sep_size = 0;
    int n_parts = 1, part_i = 0;
    bool going = true;
    unsigned long len_string_in = 0, len_part = 0;
    char **all_parts;

    if ((string_in == NULL) || (strlen(string_in) < 1))
        return -1;

    if ((sep_in != NULL) && (strlen(sep_in) >= 1)) {
        sep = sep_in;
    } else {
        sep = calloc(1 + 1, 1);
        strncpy(sep, ",", 1);
    }

    sep_size = strlen(sep);
    string_in = trim(string_in, "\n");
    len_string_in = strlen(string_in);

    n_parts = number_of_substrings(string_in, sep) + 1;
    all_parts = calloc(n_parts + 1, sizeof(char *));

    p = string_in;
    while (going) {
        old_p = p;
        p = strstr(p, sep);
        if ((p == NULL) || (p > string_in + len_string_in - 1)) {
            p = string_in + len_string_in;
            len_part = p - old_p;
            going = false;
        } else {
            len_part = p - old_p;
            p += sep_size;
        }

        all_parts[part_i] = calloc(len_part + 1, 1);
        memcpy(all_parts[part_i], old_p, len_part);
        /*         printf("\n PART_NUM: %d, PART: '%s' strlen part: %lu \n\n",
                    part_i + 1, all_parts[part_i],
                    strlen(all_parts[part_i]));
         */
        all_parts[part_i][len_part] = 0;
        part_i++;
    };

    *strings_out = all_parts;
    free(p); free(sep);

    return n_parts;
}

/**
 * @brief
 * @note
 * @param  *items[]:
 * @param  nitems:
 * @param  is_quoted:
 * @param  *sep_in:
 * @param  **str_out:
 * @retval
 */
unsigned long join_strings(char *items[], int nitems, bool is_quoted,
    char *sep_in, char **str_out)
{
    int i, d_chars_item;
    unsigned long total_strlen_strs = 0;
    int sep_size = 0;
    char *sep;
    char *quoted_strs_dump;

    if ((items == NULL) || (nitems < 1)) {
        return 0;
    }

    if ((sep_in != NULL) && (strlen(sep_in) >= 1)) {
        sep = sep_in;
    } else {
        sep = calloc(1 + 1, 1);
        strncpy(sep, ",", 1);
    }

    /*     printf("\n SEP IN IS: '%s'...SEP OUT IS: '%s'... \n\n",
            sep_in, sep); */

    sep_size = strlen(sep);

    if (is_quoted)
        d_chars_item = 2 + sep_size; /* for quotes and comma */
    else
        d_chars_item = sep_size; /* for comma only */

    for (i = 0; i < nitems; i++) {
        total_strlen_strs += strlen(items[i]) + d_chars_item;
        /* for quotes and comma (I know it gives one extra place on the end
         * but that's no problem)
         */
    }
    quoted_strs_dump = calloc(total_strlen_strs + 2, 1);

    for (i = 0; i < nitems; i++) {
        if (is_quoted) {
            strncat(quoted_strs_dump, "\"", 1);
            strncat(quoted_strs_dump, items[i], strlen(items[i]));
            strncat(quoted_strs_dump, "\"", 1);
        } else {
            strncat(quoted_strs_dump, items[i], strlen(items[i]));
        }

        if ((nitems > 1) && (i < nitems - 1)) {
            strncat(quoted_strs_dump, sep, strlen(sep));
        }
    }
    quoted_strs_dump[total_strlen_strs] = 0;
    /* printf("\nquoted strs dump %s len: %lu, total: %lu", quoted_strs_dump,
        strlen(quoted_strs_dump), total_strlen_strs); */

    *str_out = quoted_strs_dump;
    free(sep);
    return total_strlen_strs;
}


/**
 * @brief
 * @note
 * @param  **str:
 * @param  *str_size:
 * @param  *part:
 * @retval
 */
int add_to_string(char **str, size_t *str_size, char *part)
{
    char *str_tmp;
    if (*str == NULL) {
        return -1;
    }
    if (strlen(*str) + strlen(part) > *str_size) {
        *str_size += strlen(part);
        str_tmp = realloc(*str, *str_size + 1);
        if (str_tmp == NULL) {
            return -1;
        }
        *str = str_tmp;
    }
    strncat(*str, part, strlen(part));

    return 0;
}


/**
 * @brief
 * @note
 * @param  *text:
 * @param  offset:
 * @param  limit:
 * @param  *part:
 * @param  part_size:
 * @retval
 */
int substr(char *text, size_t offset, size_t limit, char *part,
    size_t part_size)
{
    size_t len_text;

    if (text == NULL)
        return -1; /* non-initialized text */

    if (part == NULL)
        return -1; /* non-initialized part */

    len_text = strlen(text);
    if (len_text < 1)
        return -2; /* empty text */

    if (offset >= len_text)
        return -3;  /* out of range */

    if (part_size < limit)
        return -3; /* out of range */

    if (offset + limit >= len_text)  /* offset + limit too long, trimming */
        limit = len_text - offset;

    memcpy(part, text + offset, limit);
    part[part_size] = 0;

    return 0;
}


/**
 * @brief
 * @note
 * @param  *dst:
 * @param  *src:
 * @param  s_len:
 * @param  s_from:
 * @retval
 */
int char_array_slice(char *dst, char *src, int s_len, int s_from)
{
    int len_src = 0;

    len_src = strlen(src);
    memset(dst, 0, (s_len + 1));
    if (s_from >= len_src)          /* wrong data */
        return RES_WRONG_PARAMS;

    /* if from + length to cut is bigger than string length, cut it
       to the max. length */
    if (s_from + s_len > len_src) {
        s_len = len_src - s_from;
    }
    memcpy(dst, src + s_from, s_len);

    return RES_OK;
}


/**
 * @brief
 * @note
 * @param  *src:
 * @param  page_size:
 * @retval
 */
int get_char_array_slice_number(char *src, int page_size)
{
    /* printf("get_char_array_slice_number str: %s page_size %d", src, page_size); */
    int len_src = strlen(src);
    int part_no = len_src / page_size;
    int part_remn = len_src % page_size;
    /* printf("\nlen_src: %d part_no: %d part_remn: %d", len_src, part_no, part_remn); */
    if (part_remn) {
        part_no++;
    }
    /* printf("\n final part_no %d", part_no); */
    return part_no;
}
