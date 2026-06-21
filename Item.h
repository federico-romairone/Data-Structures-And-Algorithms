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
 * @brief Allocates and initializes a new dynamic item.
 * @param[out]  item_pnt    Pointer to the item to initialize.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_create(ITEM *item_pnt);

/**
 * @brief Allocates and initializes a new dynamic void item.
 * @param[out]  item_pnt    Pointer to the item to initialize.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_create_void(ITEM *item_pnt);

/**
 * @brief Deallocates a dynamic item.
 * @param[in] item The item to deallocate.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_destroy(ITEM item);

// Input

/**
 * @brief Reads item data from a file.
 * @param[in] item  Selected item.
 * @param[in] fin   Pointer to the file.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_insert_from_file(ITEM item, FILE *fin);

/**
 * @brief Reads item data from a keyboard (user input).
 * @param[in] item  Selected item.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_insert_from_keyboard(ITEM item);

// Output

/**
 * @brief Writes an item on a file.
 * @param[in] item Selected item.
 * @return The type of error occurred, SUCCESS if none.
 */
status item_write_out(ITEM item, FILE *fout);


#endif