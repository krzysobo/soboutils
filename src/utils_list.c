#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sobologger/logger.h"
#include "misc/include/common.h"


void init_list(int max_items, void **list, size_t item_size)
{
    *list = calloc (max_items, item_size);
}


int find_first_free_item_index(void *list, int max_items, 
    int (is_free_fun)(void*, int))
{
    for (int i = 0; i< max_items; i++) {
        if(is_free_fun(list, i)) {
            return i;
        }
    }
    // NO FREE ITEMS FOUND - WILL BE EXTENDING THE LIST
    return -1;
}


int extend_list(void **list, int *current_max_num_items, 
    int extra_max_num_items, size_t item_size)
{
    (*current_max_num_items) += (extra_max_num_items + 1);
    
    int new_size = (*current_max_num_items) * item_size;
    void * tmp = realloc (*list, new_size);
    if (tmp == NULL) {
        free(list);
        raise_extend_item_list(RES_FAILED);
    }

    *list = tmp;
    return RES_OK;
}


int find_or_create_free_item_index(
    void **list,
    int *current_max_num_items,
    int extra_max_num_items,
    size_t item_size,
    int (is_free_fun)(void*, int))
{
    int fi = find_first_free_item_index(*list, *current_max_num_items, 
        is_free_fun);
    // free place not found - must add via realloc
    if (fi < 0) {
        int res_afu = extend_list(list, current_max_num_items,
            extra_max_num_items, item_size);
        raise_extend_item_list(res_afu);

        fi = find_first_free_item_index(*list, *current_max_num_items, 
            is_free_fun);
        res_afu = check_fi_non_negative(fi);
        raise_extend_item_list(res_afu);
    }

    return fi;
}


void update_num_items(void *list, 
    int *ptr_max_num_items, 
    int *ptr_num_items,
    int (is_free_fun)(void*, int))
{
    (*ptr_num_items) = 0;
    for (int i = 0; i < (*ptr_max_num_items); i++) {
        if(!is_free_fun(list, i)) {  // item has been set (is not "free")
            (*ptr_num_items)++; // braces are very important here; without them 
                            // we would increase the pointer, not the value
        }
    }
    logger("NUM ITEMS AFTER UPDATING: %d MAX NUM ITEMS: %d", 
        LOG_INFO, *ptr_num_items, *ptr_max_num_items);
}
