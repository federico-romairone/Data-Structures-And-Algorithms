#ifndef _ITEM
#define _ITEM

#include <stdio.h>
#include <string.h>
#include "Utilities.h"

typedef struct item* ITEM;
typedef int VALUE;
typedef char* KEY;

#define MAX_KEY_LEN 256

// Memory handling

/**
 * @brief Allocates and initializes a new dynamic array in the container.
 * @param[out]  array_pnt   Pointer to the container to initialize.
 * @param[in]   size        Number of elements to allocate.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_create(ITEM *item_pnt);

/**
 * @brief Deallocates a dynamic array and its container.
 * @param[in] array The array container to deallocate.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_destroy(ITEM item);

// Getters

/**
 * @brief Copies the key of the given item into a pointed variable.
 * @param[in]   item    The item selected.
 * @param[out]  key     The pointer to the variable where copy the item's key.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_get_key(ITEM item, KEY key);

/**
 * @brief Copies the value of the given item into a pointed variable.
 * @param[in]   item    Selected item.
 * @param[out]  value   Pointer to the variable where copy the item's variable.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_get_value(ITEM item, VALUE value);

// Input

/**
 * @brief Reads item data from a file.
 * @param[in] item  Selected item.
 * @param[in] fin   Pointer to the file.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_fill_from_file(ITEM item, FILE *fin);

/**
 * @brief Reads item data from a keyboard (user input).
 * @param[in] item  Selected item.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_fill_from_keyboard(ITEM item);

// Output

/**
 * @brief Writes an item on a file.
 * @param[in] item Selected item.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_write_out(ITEM item, FILE *fout);


#endif