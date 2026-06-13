#include <stdio.h>
#include <stdlib.h>
#include "Array.h"

/**
 * @struct array
 * @brief Dynamic container for generic ITEM elements
 * 
 * Manages a dynamically allocated array of generic pointers (ITEM).
 */
struct array { 
    ITEM *items;    // Array of pointers to elements
    int size;       // Number of allocated elements
}; 

/**
 * @brief Allocates and initializes a new dynamic array in the container.
 * 
 * Creates an array struct and allocates memory for 'size' ITEM elements.
 * The container is initialized via item_create() for each element.
 * 
 * @param[out]  array_pnt   Pointer to the container to initialize
 * @param[in]   size        Number of elements to allocate
 * 
 * @return The type of error occurred, SUCCESS if none.
 */
err array_create(ARRAY *array_pnt, int size) {
    err e = SUCCESS;
    ARRAY array;
    int i;

    if (array_pnt == NULL) e = INVALID_INPUT;
    else {
        // allocate the container
        array = (ARRAY)malloc(sizeof(struct array));
        if (array == NULL) e = OUT_OF_MEMORY;

        // allocate the array
        if (e == SUCCESS) {
            array->items = (ITEM*)malloc(size * sizeof(ITEM));
            if (array->items == NULL) e = OUT_OF_MEMORY;
        }

        // fill the array
        for (i = 0; i < size && e == SUCCESS; i++) 
            e = item_create(&(array->items[i]));

        // return "by value" (by pointer)
        if (e == SUCCESS) {
            array->size = size;
            *array_pnt = array;
        }
    }   

    return e;
}

/**
 * @brief Deallocates a dynamic array and its container.
 * 
 * Frees memory of each ITEM element via item_destroy(),
 * then frees the array and the container itself.
 * 
 * @param[in]   array   The array container to deallocate
 * 
 * @return The type of error occurred, SUCCESS if none.
 */
err array_destroy(ARRAY array) {
    err e = SUCCESS;
    int i;

    if (array == NULL) e = INVALID_INPUT;
    else {
        for (i = 0; i < array->size && e == SUCCESS; i++) 
            e = item_destroy(array->items[i]);
        free(array->items);
        free(array);
    }

    return e;
}

err array_get_size(ARRAY array, int *size_pnt) {
    err e = SUCCESS;

    if (array == NULL) e = INVALID_INPUT;
    else *size_pnt = array->size;

    return e;
}

err array_get_first_element_pointer(ARRAY array, ITEM **items_pnt) {
    err e = SUCCESS;

    if (array == NULL) e = INVALID_INPUT;
    else *items_pnt = array->items;

    return e;
}