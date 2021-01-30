// Copyright (c) 2020-2021 Krzysztof Sobolewski <krzysztof.sobolewski@gmail.com>

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // for isspace


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
    if(!text || !strlen(text)) {
        return text;
    }

    while(is_trimmable(*text, extra_chars))
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
    if(!text || !strlen(text)) {
        return text;
    }

    char *end_pos = text + strlen(text);
    while (is_trimmable(*end_pos, extra_chars)) {
        --end_pos;
    }

    int new_string_size = end_pos - text + 1;
    text_out = calloc(new_string_size + 1, 1);
    strncpy(text_out, text, new_string_size);
 
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
