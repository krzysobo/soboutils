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
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "soboutils/utils_file.h"


int main (int argc, char **argv)
{
    FILE *fp;
    char * test_file_path = "./testfile.txt";
    char * test_string = "Hello Test"; 

    printf("\ntest_utils_file started...\n");

    if(!file_exists(test_file_path)) {
        printf("\nThe test file %s already existed - trying to remove...",
            test_file_path);
        remove(test_file_path);
        assert(!file_exists(test_file_path));
        printf(" - OK!\n");
    }

    printf("\nCreating the test file %s...\n", test_file_path);
    fp = fopen(test_file_path, "wb");
    fputs(test_string, fp);
    fclose(fp);

    printf("\nChecking whether the test file %s exists...", test_file_path);
    assert(file_exists(test_file_path));
    printf(" - OK!\n");


    printf("\nChecking whether the test file %s exists...", test_file_path);
    assert(file_exists(test_file_path));
    printf(" - OK!\n");


    printf("\nChecking whether the test file %s is %lu bytes long...", 
        test_file_path, (unsigned long)strlen(test_string));
    assert(get_file_size(test_file_path) == strlen(test_string));
    printf(" - OK!\n");


    printf("\nChecking whether the test file %s contains the word 'Hello'...", 
        test_file_path);
    assert(check_file_contains(test_file_path, "Hello"));
    printf(" - OK!\n");


    printf("\nTrying to remove the test file %s...", test_file_path);
    remove(test_file_path);
    assert(!file_exists(test_file_path));
    printf(" - OK!\n");


    printf("\ntest_utils_file finished...\n");   

    return 0;
}
