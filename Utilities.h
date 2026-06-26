#ifndef _UTILITIES
#define _UTILITIES

#include <stdlib.h>

/**
 * @typedef status
 * @brief Status code for operations
 */
typedef enum {
    SUCCESS,
    FAILURE,
    OUT_OF_MEMORY,
    INVALID_INPUT,
    FILE_NOT_FOUND,
    INVALID_FILE_FORMAT,
    END_OF_FILE,
    NOT_FOUND
} status;

/**
 * @typedef boolean
 * @brief Boolean variable
 */
typedef enum {
    FALSE,
    TRUE
} boolean;

#endif