#ifndef _ERROR
#define _ERROR

#include <stdlib.h>

/**
 * @typedef Error
 * @brief Status code for operations
 */
typedef enum { 
    SUCCESS, 
    FAILURE,
    OUT_OF_MEMORY, 
    INVALID_INPUT
} err;

#endif