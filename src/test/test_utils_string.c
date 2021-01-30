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
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "soboutils/utils_string.h"


int main (int argc, char **argv)
{
    char * test_string1 = "Alice has a cat"; 
    char * test_string2 = "/usr/local/bin/";
    char test_string2a[] = "usr/local/bin";
    char * test_string_out2;

    char * test_string3 = "usr/local/bin";
    char * test_string3a = "usr/local/bin";
    char * test_string_out3;

    char * test_string4 = "     \t \n   usr/local/bin  \r  \t\t    ";
    char * test_string4a = "usr/local/bin";
    char * test_string_out4;

    printf("\ntest_utils_string has started...\n");
    printf("\nChecking whether strpos of 'ice' in the string '%s' == 2...",
        test_string1);
    assert(strpos(test_string1, "ice") == 2);
    printf(" - OK!\n");


    printf("\nChecking whether the string %s will be properly trimmed \n"
           "on both sides. Slashes should also be removed...",
           test_string2);
    test_string_out2 = trim(test_string2, "/");
    assert(strcmp(test_string_out2, test_string2a) == 0);
    printf(" - OK!\n");
    printf("\n- Trimmed string: %s\n- Original string %s \n\n", 
        test_string_out2, test_string2);


    printf("\nChecking whether the string '%s', in which there is nothing"
           " to trim will be properly handled (ie. left alone)...",
           test_string2);
    test_string_out3 = trim(test_string3, "/");
    assert(strcmp(test_string_out3, test_string3a) == 0);
    printf(" - OK!\n");
    printf("\n- Trimmed string: %s\n- Original string %s \n\n", 
        test_string_out3, test_string3);

    printf("\nChecking whether the string '%s',\nwhich has only whitespace"
           "around (no extra chars) will be properly trimmed...",
           test_string4);
    test_string_out4 = trim(test_string4, "");
    assert(strcmp(test_string_out4, test_string4a) == 0);
    printf(" - OK!\n");
    printf("\n- Trimmed string: %s\n- Original string %s \n\n", 
        test_string_out4, test_string4);

    printf("\ntest_utils_string has finished...\n");

}