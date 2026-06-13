#ifndef _ITEM
#define _ITEM

#include "Error.h"

typedef struct item *ITEM;

err item_create(ITEM *item_pnt);
err item_destroy(ITEM item);

#endif