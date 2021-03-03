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

#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include "soboutils/utils_time.h"


int main (int argc, char **argv)
{
    char time_buff[30];
    char time_buff_test[30];
    const char *format = "%Y-%m-%d %H:%M:%S";
    struct tm *tm;
    time_t now;

    printf("\ntest_utils_time has started...\n");
    printf("\nTime format for tests: %s", format);

    get_formatted_local_time(time_buff, 30, format);
    printf("\nformatted local time: %s \n\n", time_buff);

    time(&now);
    tm = localtime(&now);
    
    printf("\nParsing the generated time string with strptime...\n");
    strptime(time_buff, format, tm);

    printf("\nRe-creating the original formatted time string...\n");
    strftime(time_buff_test, 30, format, tm);

    printf("\nChecking whether both time strings:\n%s\nand\n%s\n"
          "are identical - if yes, it means that the created time "
          "string is valid and complies with the format...",
          time_buff, time_buff_test);
    assert(strcmp(time_buff, time_buff_test) == 0);
    printf(" - OK!\n\n");

    printf("\ntest_utils_time has finished...\n");
    
    return 0;
}
