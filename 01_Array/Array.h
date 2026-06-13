#ifndef _ARRAY
#define _ARRAY

#include "../Item.h"
#include "../Error.h"

typedef struct array *ARRAY;

// Memory handling
err array_create(ARRAY *array_pnt, int size);
err array_destroy(ARRAY array);

// Getters
err array_get_size(ARRAY array, int *size);
err array_get_first_element_pointer(ARRAY array, ITEM **items);

#endif