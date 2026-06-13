/**
 * Item is an integer.
 */

#include "Item.h"

struct item {
    int n;
};

err item_create(ITEM *item_pnt) {
    ITEM item;
    err e = SUCCESS;

    item = (ITEM)malloc(sizeof(struct item));
    if (item == NULL) e = OUT_OF_MEMORY;
    else *item_pnt = item;

    return e;
}

err item_destroy(ITEM item) {
    err e = SUCCESS;

    if (item == NULL) e = INVALID_INPUT;
    else free(item);

    return e;
}