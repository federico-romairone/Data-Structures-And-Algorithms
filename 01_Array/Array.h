#ifndef _ARRAY
#define _ARRAY

#include "../Item.h"
#include "../Utilities.h"

#define INITIAL_SIZE 1

typedef struct array *ARRAY;

// Memory handling

/**
 * @brief Allocates and initializes a new dynamic array in the container.
 * @param[out] array_pnt Pointer to the container to initialize.
 * @return The type of error occurred, SUCCESS if none.
 */
status array_create(ARRAY *array_pnt);

/**
 * @brief Deallocates a dynamic array and its container.
 * @param[in] array The array container to deallocate.
 * @return The type of error occurred, SUCCESS if none.
 */
status array_destroy(ARRAY array);

// Getters

/**
 * @brief Gets the size of the given array.
 * @param[in]   array       The array container.
 * @param[out]  size_pnt    Pointer to the integer where the size is copied.
 * @return The type of error occurred, SUCCESS if none.
 */
status array_get_size(ARRAY array, int *size_pnt);

/**
 * @brief Gets the cardinality of the given array.
 * @param[in]   array           The array container.
 * @param[out]  cardinality_pnt Pointer to the integer where the cardinality is copied.
 * @return The type of error occurred, SUCCESS if none.
 */
status array_get_cardinality(ARRAY array, int *cardinality_pnt);

/**
 * @brief Gets the pointer to the first element of the given array.
 * @param[in]   array       The array container.
 * @param[out]  items_pnt   Pointer to a vector of items where the address of the first element is copied.
 * @return The type of error occurred, SUCCESS if none.
 */
status array_get_first_element_pointer(ARRAY array, ITEM **items_pnt);

// Input

/**
 * @brief Fills the array with items from a file.
 * @param[in] array Selected array.
 * @param[in] fin   Pointer to the file.
 * @return The type of error occurred, SUCCESS if none.
 */
status array_fill_from_file(ARRAY array, char *fname);

/**
 * @brief Fills the array with items from a keyboard (user input).
 * @param[in] array Selected array.
 * @return The type of error occurred, SUCCESS if none.
 */
status array_fill_from_keyboard(ARRAY array);

// Output

/**
 * @brief Writes an array on a file.
 * @param[in] array Selected array.
 * @return The type of error occurred, SUCCESS if none.
 */
status array_write_out(ARRAY array, FILE *fout);

#endif