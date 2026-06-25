#ifndef _ARRAY
#define _ARRAY

#include "../Item.h"
#include "../Utilities.h"

typedef struct list* LIST;

// Memory handling

/**
 * @brief Allocates and initializes a new dynamic list container.
 * @param[out] list_pnt Pointer to the container to initialize.
 * @return The type of error occurred, SUCCESS if none.
 */
status list_create(LIST *list_pnt);

/**
 * @brief Deallocates a dynamic list and its container.
 * @param[in] list The list container to deallocate.
 * @return The type of error occurred, SUCCESS if none.
 */
status list_destroy(LIST list);

// Search, insert, delete

/**
 * @brief Searches an item in a list.
 * @param[in]   list      The list on which the insertion is done.
 * @param[in]   key       Search key to find the item.
 * @param[out]  item_pnt  Where to save the searched item (void if not found).
 * @return The type of error occurred, SUCCESS if none.
 */
status list_search(LIST list, KEY key, ITEM *item_pnt);

/**
 * @brief Inserts an item in head list.
 * @param[in] list The list on which the insertion is done.
 * @param[in] item The item inserted.
 * @return The type of error occurred, SUCCESS if none.
 */
status list_insert_head(LIST list, ITEM item);

/**
 * @brief Inserts an item in tail list.
 * @param[in] list The list on which the insertion is done.
 * @param[in] item The item inserted.
 * @return The type of error occurred, SUCCESS if none.
 */
status list_insert_tail(LIST list, ITEM item);

status list_delete_head(LIST list, boolean extract, ITEM *item_pnt);

status list_delete_position(LIST list, int index, boolean extract, ITEM *item_pnt);

status list_delete_key(LIST list, KEY key, boolean extract, ITEM *item_pnt);

// Setters and status

/**
 * @brief Checks whether the list is empty or not.
 * @param[in]   list    The list to check.
 * @param[out]  result  The check's result.
 * @return The type of error occurred, SUCCESS if none.
 */
status list_empty(LIST list, boolean *empty_pnt);

// Output

status list_write_out(LIST list, FILE *fout); // ricorsivo

#endif