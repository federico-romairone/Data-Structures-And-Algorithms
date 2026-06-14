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
    int n;          // Number of elements
    int size;       // Number of allocated elements
}; 


// Memory handling

status array_create(ARRAY *array_pnt) {
    status result = SUCCESS;
    ARRAY array;
    int i, size = INITIAL_SIZE;

    if (array_pnt == NULL) result = INVALID_INPUT;
    else {
        // allocate the container
        array = (ARRAY)malloc(sizeof(struct array));
        if (array == NULL) result = OUT_OF_MEMORY;

        // allocate the array
        if (result == SUCCESS) {
            array->items = (ITEM*)malloc(size * sizeof(ITEM));
            if (array->items == NULL) result = OUT_OF_MEMORY;
        }

        // fill the array with empty items
        for (i = 0; i < size && result == SUCCESS; i++) 
            result = item_create(&(array->items[i]));

        // return "by value" (by pointer)
        if (result == SUCCESS) {
            array->size = size;
            array->n = 0;
            *array_pnt = array;
        }
    }

    return result;
}

status array_destroy(ARRAY array) {
    status result = SUCCESS;
    int i;

    if (array == NULL) result = INVALID_INPUT;
    else {
        for (i = 0; i < array->size && result == SUCCESS; i++) 
            result = item_destroy(array->items[i]);
        if (array->items != NULL) free(array->items);
        free(array);
    }

    return result;
}

// Getters

status array_get_size(ARRAY array, int *size_pnt) {
    status result = SUCCESS;

    if (array == NULL) result = INVALID_INPUT;
    else *size_pnt = array->size;

    return result;
}

status array_get_cardinality(ARRAY array, int *cardinality_pnt) {
    status result = SUCCESS;

    if (array == NULL) result = INVALID_INPUT;
    else *cardinality_pnt = array->n;

    return result;
}

status array_get_first_element_pointer(ARRAY array, ITEM **items_pnt) {
    status result = SUCCESS;

    if (array == NULL) result = INVALID_INPUT;
    else *items_pnt = array->items;

    return result;
}

// Input 

status array_fill_from_file(ARRAY array, char *fname) {
    FILE *fin;
    status result = SUCCESS;
    int i, old_size;

    if (array == NULL || fname == NULL) result = INVALID_INPUT;
    else {
        fin = fopen(fname, "r");
        if (fin == NULL) result = FILE_NOT_FOUND; 
        else {
            do {
                // array is full
                if (array->n == array->size) {
                    // reallocate
                    old_size = array->size;
                    array->size *= 2;
                    array->items = (ITEM*)realloc(array->items, array->size * sizeof(ITEM));
                    if (array->items == NULL) { result = OUT_OF_MEMORY; break; }
                    else {
                        for (i = old_size; i < array->size && result == SUCCESS; i++)
                            result = item_create(&(array->items[i]));
                    }
                }
                if (result == SUCCESS) {
                    result = item_fill_from_file(array->items[array->n], fin);
                    if (result == SUCCESS) (array->n)++;
                    else if (result == END_OF_FILE) result = SUCCESS;
                }
            } while (result == SUCCESS && !feof(fin));
            fclose(fin);
        }
    }

    return result;
}

status array_fill_from_keyboard(ARRAY array) {
    status result = SUCCESS;
    boolean user_stop = FALSE;
    char buffer[100];
    int i;

    do {
        // array is full
        if (array->n == array->size) {
            // reallocate
            array->size *= 2;
            array->items = (ITEM*)realloc(array->items, array->size * sizeof(ITEM));
            if (array->items == NULL) { result = OUT_OF_MEMORY; break; }
            else {
                for (i = 0; i < array->size && result == SUCCESS; i++)
                    result = item_create(&(array->items[i]));
            }
        }
        result = item_fill_from_keyboard(array->items[array->n]);
        if (result == SUCCESS) {
            (array->n)++;
            printf("Do you want to insert a new item?\nType 'y' for 'yes' ore everything else for 'no': ");
            // clean input in case user digits more then one char (no thrash in buffer for next scan)
            fgets(buffer, sizeof(buffer), stdin);
            if ('y' != buffer[0]) user_stop = TRUE;
        }
    } while (result == SUCCESS && !user_stop && !feof(stdin));

    return result;
}

// Output

status array_write_out(ARRAY array, FILE *fout) {
    status result = SUCCESS;
    int i;

    if (array == NULL || fout == NULL) result = INVALID_INPUT;
    else {
        fprintf(fout, "--- Array ---\n");
        for (i = 0; i < array->n; i++) {
            fprintf(fout, "Item %d: ", i);
            item_write_out(array->items[i], fout);
            fprintf(fout, "\n");
        } 
        fprintf(fout, "-------------\n");
    }

    return result;
}
