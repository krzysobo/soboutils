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
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "soboutils/utils_string.h"


int main (int argc, char **argv)
{
    int i = 0;
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

    char *test_string_5_array[] = {
        "abc",
        "def"
    };

    char *test_string_5_joined;
    char *test_string_5_joined_no_quotes;
    char *test_string_5_for_test = "\"abc\",\"def\"";
    char *test_string_5_for_test_no_quotes = "abc,def";
    int test_string_5_len = 0;
    int test_string_5_len_no_quotes = 0;

    char *test_string_6_a = "abc";
    char *test_string_6_b = "def";
    char *test_string_6_for_test = "abcdef";
    char *test_string_6_added;
    size_t test_string_6_len;

    char * test_string7 = "Alice has a cat";
    char * test_string7_for_test_a = "Alice";
    char * test_string7_for_test_b = "cat";
    char * test_string7_a;
    char * test_string7_b;
    int test_res7_a;
    int test_res7_b;
    unsigned long test_part_size7_a = 10;
    unsigned long test_part_size7_b = 100;
    unsigned long test_string7_len;

    char *test_string_8 = "Alice\nBob\nJenna\nJack Blah Blah\nDonna Doe";
    char **test_array_8_out;
    int test_8_n_parts = 5;
    int res_8;

    char *test_string_9 = "\n\n\n\n\n\t\t\tAlice\r\nBob\r\nJenna\r\nJack Blah Blah\r\nDonna Doe\n\n\n\t\t\t\n\n";
    char **test_array_9_out;
    int test_9_n_parts = 5;
    int res_9;
    

    char *test_string_10 = "Alice and Bob";
    char **test_array_10_out;
    int test_10_n_parts = 1;
    int res_10;


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


    test_string_5_len = join_strings(test_string_5_array, 2, true, NULL, 
        &test_string_5_joined);
    printf("\nTesting join_strings() with quotes - checking if length > 0...");
    assert(test_string_5_len > 0);
    printf(" - OK!\n");

    printf("\nTesting join_strings() with quotes - checking if result is joined well...");
    assert(strcmp(test_string_5_for_test, test_string_5_joined) == 0);
    printf(" - OK!\n");
    printf("\nthe joined string with quotes: %s\n", test_string_5_joined);


    test_string_5_len_no_quotes = join_strings(test_string_5_array, 2, false, NULL, &test_string_5_joined_no_quotes);
    printf("\nTesting join_strings() WITHOUT quotes - checking if length > 0...");
    assert(test_string_5_len_no_quotes > 0);
    printf(" - OK!\n");
    printf("\nTesting join_strings() WITHOUT quotes - checking if result is joined well...");
    assert(strcmp(test_string_5_for_test_no_quotes, test_string_5_joined_no_quotes) == 0);
    printf(" - OK!\n");
    printf("\nthe joined string WITHOUT quotes: %s\n", test_string_5_joined_no_quotes);

    
    test_string_6_len = 3;
    test_string_6_added = calloc(test_string_6_len, 1);

    add_to_string(&test_string_6_added, &test_string_6_len, test_string_6_a);
    printf("\nTesting add_to_string() - checking whether %s added "
        "to empty string... ", test_string_6_a);
    assert(strcmp(test_string_6_added, test_string_6_a) == 0);
    printf(" - OK!\n");
    printf("\nSTRLEN of the resulting string: %lu ", 
        (unsigned long)strlen(test_string_6_added)); 

    add_to_string(&test_string_6_added, &test_string_6_len, test_string_6_b);
    printf("\nTesting add_to_string() - checking whether string == %s... ", 
        test_string_6_for_test);
    assert(strcmp(test_string_6_added, test_string_6_for_test) == 0);
    printf(" - OK!\n");

    printf("\nSTRLEN of the resulting string: %lu \n\n", 
        (unsigned long)strlen(test_string_6_added));


    /* substr */
    test_string7_a = calloc(test_part_size7_a + 1, 1);
    test_string7_b = calloc(test_part_size7_b + 1, 1);
    test_string7_len = strlen(test_string7);
 
    test_res7_a =  substr(test_string7, 0, 5, test_string7_a, test_part_size7_a);
    printf("\nchecking if first result (%d) == 0...", test_res7_a);
    assert(test_res7_a == 0);
    printf(" - OK!\n");
    printf("\nchecking if first substr ('%s') is 'Alice'...", test_string7_a);
    assert(strcmp(test_string7_a, test_string7_for_test_a) == 0);
    printf(" - OK!\ndisplaying: '%s'\n", test_string7_a);
    printf("\nchecking if first substr ('Alice') len == 5...");
    assert(strlen(test_string7_a) == 5);
    printf(" - OK!\n"); 


    test_res7_b = substr(test_string7, 12, 3, test_string7_b, test_part_size7_b);
    printf("\nchecking if second result (%d) == 0...", test_res7_b);
    assert(test_res7_b == 0);
    printf(" - OK!\n");
    printf("\nchecking if second substr ('%s') is 'cat'...", test_string7_b);
    assert(strcmp(test_string7_b, test_string7_for_test_b) == 0);
    printf(" - OK!\n");
    printf("\nchecking if second substr ('cat') len == 3...");
    assert(strlen(test_string7_b) == 3);
    printf(" - OK!\n");


    /* second result - limit exceeding string bounds MUST be cut but it
     * MUST NOT exceed the part size
     */
    test_res7_b = substr(test_string7, 12, 60, 
        test_string7_b, test_part_size7_b);
    printf("\nchecking if limit %lu exceeding the string size %lu BUT NOT "
        "exceeding the 'part' container size %lu is automatically cut and "
        "the result is correct -> second result (%d) == 0...", 
        60L, test_string7_len, test_part_size7_b, test_res7_b);
    assert(test_res7_b == 0);
    printf(" - OK!\n");
    printf("\nchecking if second substr ('%s') is 'cat'...", 
        test_string7_b);
    assert(strcmp(test_string7_b, test_string7_for_test_b) == 0);
    printf(" - OK!\n");
    printf("\nchecking if second substr ('cat') len == 3...");
    assert(strlen(test_string7_b) == 3);
    printf(" - OK!\n");


    /* second result - limit exceeding part size MUST RETURN AN ERROR -3 */
    test_res7_b = substr(test_string7, 12, 101, 
        test_string7_b, test_part_size7_b);
    printf("\nchecking if limit %lu exceeding the part size %lu "
        "returns the error -3: %d",
        101L, test_part_size7_b, test_res7_b);
    assert(test_res7_b == -3);
    printf(" - OK!\n\n");


    res_8 = split_string(test_string_8, "\n", &test_array_8_out);
    printf("\n\n RES8: %d", res_8);
    printf("\n checking whether number of parts in test 8 == %d...", test_8_n_parts);
    assert(res_8 == test_8_n_parts);
    printf(" - OK!\n\n");
    
    res_9 = split_string(test_string_9, "\r\n", &test_array_9_out);
    printf("\n\n RES9: %d", res_9);
    printf("\n checking whether number of parts in test 9 == %d and trimming works...", test_9_n_parts);
    assert(res_9 == test_9_n_parts);
    printf(" - OK!\n\n");

    for(i = 0; i < res_9; i++) {
        printf("\nPART I: %d OF %d: '%s' \n\n", i + 1, res_9, test_array_9_out[i]);
    }

    res_10 = split_string(test_string_10, "\n", &test_array_10_out);
    printf("\n\n RES10: %d", res_10); 
    printf("\n checking whether number of parts in test 10 == %d and the function works where there are NO SEARCHED SEPARATORS as well (should return the full string)...", test_10_n_parts);
    assert(res_10 == test_10_n_parts);
    printf(" - OK!\n\n");

    return 0;
}
