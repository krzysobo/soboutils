#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sobologger/logger.h"
#include "misc/include/common.h"


int char_array_slice(char *dst, char *src, int s_len, int s_from)
{
    bzero(dst,sizeof(char) * (s_len + 1));
    // printf("\nchar_array_slice - zeroed dst\n\n\n ");
    int len_src = strlen(src);
    // printf("\n char_array_slice - len_src: %d s_from: %d", len_src, s_from);

    if(s_from >= len_src) { // wrong data
        return RES_WRONG_PARAMS;
    }

    // if from + length to cut is bigger than string length, cut it
    // to the max. length
    if (s_from + s_len > len_src) {
        s_len = len_src - s_from;
    }

    // printf("\n\n char_array_slice - s_len: %d \n\n\n", s_len);
    memcpy(dst, src + s_from, s_len);

    return RES_OK;
}


int get_char_array_slice_number(char *src, int page_size)
{
    // printf("get_char_array_slice_number str: %s page_size %d", src, page_size);
    int len_src = strlen(src);
    int part_no = len_src / page_size;
    int part_remn = len_src % page_size;
    // printf("\nlen_src: %d part_no: %d part_remn: %d", len_src, part_no, part_remn);
    if(part_remn) {
        part_no++;
    }
    // printf("\n final part_no %d", part_no);
    return part_no;
}


void raise_char_array_slice(int res_code)
{
    switch(res_code) {
        case RES_OK: 
            break;
        case RES_WRONG_PARAMS:
            logger("Wrong parameters in char_array_slice.", LOG_ERROR);
            exit(EXIT_FAILURE);
            break;
        default:
            logger("Unknown error occured in char_array_slice.", LOG_ERROR);
            exit(EXIT_FAILURE);
            break;
    }
}


void raise_extend_item_list(int res_code) {
    switch(res_code) {
        case RES_OK: 
            break;
        case RES_FAILED:
            logger("Could not expand list - error in raise_extend_item_list.", LOG_ERROR);
            exit(EXIT_FAILURE);
            break;
        default:
            logger("Unknown error occured in raise_extend_item_list.", LOG_ERROR);
            exit(EXIT_FAILURE);
            break;
    }
}


void raise_fi_negative(int res_code, const char * func_name)
{
    switch(res_code) {
        case RES_OK: 
            break;
        case RES_FAILED:
        default:
            logger("fi was negative in function %s.", LOG_ERROR, func_name);
            exit(EXIT_FAILURE);
            break;
    }
}


int check_fi_non_negative(int fi) 
{
    if (fi < 0) {
        return RES_FAILED;
    }
    return RES_OK;
}


int check_user_list_extended_fi(int fi) 
{
    return check_fi_non_negative(fi);
}