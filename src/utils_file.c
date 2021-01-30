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
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "soboutils/utils_file.h"


/**
 * @brief  checks if the file exists
 * @note   
 * @param  *file_path:
 * @retval 1 (true) or 0 (false)
 */
int file_exists(char *file_path)
{
    struct stat stat_buffer;
    int res;
    res = (stat(file_path, &stat_buffer) == 0);

    return res;
}


/**
 * @brief  gets the file size if it exists
 * @note   
 * @param  *file_path: 
 * @retval int (0 or higher)
 */
int get_file_size(char *file_path)
{
    FILE *fp;
    int fsize;

    if (!file_exists(file_path)) {
        return 0;
    }

    fp = fopen(file_path, "r");
    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    fclose(fp);

    return fsize;
}


/**
 * @brief  checks whether the file contains a phrase
 * @note   
 * @param  *file_path: 
 * @param  *phrase: 
 * @retval int - 1 (true) or 0 (false)
 */
int check_file_contains(char *file_path, char *phrase)
{
    FILE *fp;
    char *buff;
    int fsize;
    int res;
    int read_size;

    fp = fopen(file_path, "rb");
    fsize = get_file_size(file_path);
    if (!fsize) {
        return 0;
    }
    buff = calloc(fsize + 1, 1);
    
    read_size = fread(buff, 1, fsize, fp);
    if(!read_size) {
        return 0;
    }

    fclose(fp);

    res = (strstr(buff, phrase) != NULL);

    free(buff);

    return res;
}
