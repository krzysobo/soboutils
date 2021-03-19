#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sobologger/logger.h"
#include "soboutils/common.h"


/**
 * @brief  
 * @note   
 * @param  res_code: 
 * @retval None
 */
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


/**
 * @brief  
 * @note   
 * @param  res_code: 
 * @retval None
 */
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


/**
 * @brief  
 * @note   
 * @param  res_code: 
 * @param  func_name: 
 * @retval None
 */
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


/**
 * @brief  
 * @note   
 * @param  fi: 
 * @retval 
 */
int check_fi_non_negative(int fi) 
{
    if (fi < 0) {
        return RES_FAILED;
    }
    return RES_OK;
}


/**
 * @brief  
 * @note   
 * @param  fi: 
 * @retval 
 */
int check_user_list_extended_fi(int fi) 
{
    return check_fi_non_negative(fi);
}
