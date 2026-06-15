#include <stdio.h>
#include <stdlib.h>
#include "Array.h"

/**
 * TEST HELPER FUNCTIONS
 */

// Counter for passed/failed tests
static int tests_run = 0;
static int tests_passed = 0;

#define TEST_ASSERT(condition, test_name) \
    tests_run++; \
    if (condition) { \
        tests_passed++; \
        printf("✓ PASS: %s\n", test_name); \
    } else { \
        printf("✗ FAIL: %s\n", test_name); \
    }


/**
 * TEST SUITE: array_create()
 */

// Create array successfully
void test_array_create_success() {
    ARRAY array = NULL;
    int size, cardinality;
    ITEM *items = NULL;
    status result = array_create(&array);

    TEST_ASSERT(result == SUCCESS, "array_create returns SUCCESS");
    TEST_ASSERT(array != NULL, "array_create allocates the container structure");

    array_get_size(array, &size);
    TEST_ASSERT(size == 1, "array_create initialize size correctly");

    array_get_cardinality(array, &cardinality);
    TEST_ASSERT(cardinality == 0, "array_create initialize cardinality correctly");

    array_get_first_element_pointer(array, &items);
    TEST_ASSERT(items != NULL, "array_create allocates item's vector");
    
    array_destroy(array);
}

// Create array with NULL pointer (invalid input)
void test_array_create_null_pointer() {
    status result = array_create(NULL);
    
    TEST_ASSERT(result == INVALID_INPUT, 
                    "array_create returns INVALID_INPUT for NULL array_pnt");
}


/**
 * TEST SUITE: array_destroy()
 */

// Destroy valid array
void test_array_destroy_success() {
    ARRAY array = NULL;
    status result;

    array_create(&array);
    result = array_destroy(array);
    
    TEST_ASSERT(result == SUCCESS, "array_destroy returns SUCCESS");
}

// Destroy NULL array (should fail gracefully)
void test_array_destroy_null() {
    status result = array_destroy(NULL);
    
    TEST_ASSERT(result == INVALID_INPUT, 
                    "array_destroy returns INVALID_INPUT for NULL array_pnt");
}

// Create and destroy in sequence
void test_array_create_destroy_sequence() {
    ARRAY array = NULL;
    status create_result = array_create(&array);
    status destroy_result = array_destroy(array);
    
    TEST_ASSERT(create_result == SUCCESS, "create succeeds");
    TEST_ASSERT(destroy_result == SUCCESS, "destroy succeeds");
}


/**
 * TEST SUITE: array_fill_from_file()
 */

// Read all items from a valid file; reaching EOF is normal and must return SUCCESS.
void test_array_fill_from_file_success() {
    ARRAY array = NULL;
    status result;
    int size, cardinality;

    array_create(&array);
    result = array_fill_from_file(array, "01_Array/input_6in.txt");
    TEST_ASSERT(result == SUCCESS,
                "array_fill_from_file returns SUCCESS after reading all items");
    
    array_get_size(array, &size);
    TEST_ASSERT(size == 8, 
                "array_fill_from_file allocates the correct number of elements");

    array_get_cardinality(array, &cardinality);
    TEST_ASSERT(cardinality == 6, 
                "array_fill_from_file reads the correct number of elements");

    array_write_out(array, stdout);

    array_destroy(array);
}

// File that does not exist
void test_array_fill_from_file_not_found() {
    ARRAY array = NULL;
    status result;
    
    array_create(&array);
    result = array_fill_from_file(array, "nonexistent.txt");
    TEST_ASSERT(result == FILE_NOT_FOUND,
                "array_fill_from_file returns FILE_NOT_FOUND for missing file");

    array_destroy(array);
}

// Empty file: EOF on the very first read is still SUCCESS (0 items read).
void test_array_fill_from_file_empty() {
    ARRAY array = NULL;
    status result;
    int size, cardinality; 

    array_create(&array);
    result = array_fill_from_file(array, "01_Array/test_empty.txt");
    TEST_ASSERT(result == SUCCESS,
                "array_fill_from_file returns SUCCESS for empty file (0 items, EOF)");
    
    array_get_size(array, &size);
    TEST_ASSERT(size == 1, 
                "array_fill_from_file allocates the correct number of elements");
    
    array_get_cardinality(array, &cardinality);
    TEST_ASSERT(cardinality == 0, 
                "array_fill_from_file reads the correct number of elements");

    array_write_out(array, stdout);

    array_destroy(array);
}

// File with malformed content (no space-separated pair) must return INVALID_FILE_FORMAT.
void test_array_fill_from_file_invalid_format() {
    ARRAY array = NULL;
    FILE *fin = NULL;
    status result;
    
    array_create(&array);

    fin = fopen("01_Array/test_bad_format.txt", "w");
    fprintf(fin, "not a valid item\n");
    fclose(fin);

    result = array_fill_from_file(array, "01_Array/test_bad_format.txt");

    TEST_ASSERT(result == INVALID_FILE_FORMAT,
                "array_fill_from_file returns INVALID_FILE_FORMAT for malformed content");

    array_destroy(array);
}


/**
 * TEST SUITE: array_fill_from_keyboard()
 */

// One item, then 'n' to stop → expected SUCCESS
void test_array_fill_from_keyboard_single_item() {
    ARRAY array = NULL;
    status result = SUCCESS;
    int size, cardinality;

    printf("Instructions: type one item, then 'n' to stop → expected SUCCESS\n");
    array_create(&array);
    result = array_fill_from_keyboard(array);
    array_get_size(array, &size);
    array_get_cardinality(array, &cardinality);
    printf("size='%d' n='%d'\n", size, cardinality);
    TEST_ASSERT(result == SUCCESS,
                "array_fill_from_keyboard returns SUCCESS after reading one item");
    
    array_write_out(array, stdout);

    array_destroy(array);
}

// More than one item separated by 'y', then 'n' to stop → expected SUCCESS
void test_array_fill_from_keyboard_multiple_items() {
    ARRAY array = NULL;
    status result = SUCCESS;
    int size, cardinality;

    printf("Instructions: type more items, then 'n' to stop → expected SUCCESS\n");
    array_create(&array);
    result = array_fill_from_keyboard(array);
    array_get_size(array, &size);
    array_get_cardinality(array, &cardinality);
    printf("size='%d' n='%d'\n", size, cardinality);
    TEST_ASSERT(result == SUCCESS,
                "array_fill_from_keyboard returns SUCCESS after reading one item");
    
    array_write_out(array, stdout);
    
    array_destroy(array);
}

/**
 * MAIN TEST RUNNER
 */

int main() {
    printf("========================================\n");
    printf("  ARRAY DATA STRUCTURE TEST SUITE\n");
    printf("========================================\n\n");
    
    // Run all tests
    printf("Testing array_create()...\n");
    test_array_create_success();
    test_array_create_null_pointer();
    
    printf("\nTesting array_destroy()...\n");
    test_array_destroy_success();
    test_array_destroy_null();
    test_array_create_destroy_sequence();

    printf("\nTesting array_fill_from_file()...\n");
    test_array_fill_from_file_success();
    test_array_fill_from_file_not_found();
    test_array_fill_from_file_empty();
    test_array_fill_from_file_invalid_format();

    printf("\nTesting array_fill_from_keyboard()...\n");
    test_array_fill_from_keyboard_single_item();
    test_array_fill_from_keyboard_multiple_items();

    
    // Print summary
    printf("\n========================================\n");
    printf("  TEST RESULTS: %d/%d passed\n", tests_passed, tests_run);
    printf("========================================\n");
    
    return 0;
}
