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

#define TEST_ASSERT_ERR(actual, expected, test_name) \
    TEST_ASSERT(actual == expected, test_name)


/**
 * TEST SUITE: array_create()
 */

// Create array successfully with valid size
void test_array_create_success(int n) {
    ARRAY array = NULL;
    int size;
    ITEM *items = NULL;
    err result = array_create(&array, n);
    
    printf("Testing array creation with size %d...\n", n);

    TEST_ASSERT_ERR(result, SUCCESS, "array_create returns SUCCESS");
    TEST_ASSERT(array != NULL, "array_create allocates array pointer");

    array_get_size(array, &size);
    TEST_ASSERT(size == 10, "array_create sets size correctly");

    array_get_first_element_pointer(array, &items);
    TEST_ASSERT(items != NULL, "array_create allocates items");
    
    array_destroy(array);
}

// Create array with size 0
void test_array_create_size_zero() {
    ARRAY array = NULL;
    int size;
    ITEM *items = NULL;
    err result = array_create(&array, 0);
    
    TEST_ASSERT_ERR(result, SUCCESS, "array_create returns SUCCESS with size 0");
    TEST_ASSERT(array != NULL, "array_create allocates array pointer with size 0");
    
    array_destroy(array);
}

// Create array with NULL pointer (invalid input)
void test_array_create_null_pointer() {
    err result = array_create(NULL, 10);
    
    TEST_ASSERT_ERR(result, INVALID_INPUT, 
                    "array_create returns INVALID_INPUT for NULL array_pnt");
}

// Create multiple arrays
void test_array_create_multiple() {
    ARRAY array1 = NULL;
    ARRAY array2 = NULL;
    int size1 = -1, size2 = -1;
    
    err result1 = array_create(&array1, 5);
    err result2 = array_create(&array2, 15);
    
    TEST_ASSERT_ERR(result1, SUCCESS, "first array_create succeeds");
    TEST_ASSERT_ERR(result2, SUCCESS, "second array_create succeeds");

    array_get_size(array1, &size1);
    TEST_ASSERT(size1 == 5, "first array has correct size");
   
    array_get_size(array2, &size2);
    TEST_ASSERT(size2 == 15, "second array has correct size");

    TEST_ASSERT(array1 != array2, "arrays are different objects");
    
    array_destroy(array1);
    array_destroy(array2);
}


/**
 * TEST SUITE: array_destroy()
 */

// Destroy valid array
void test_array_destroy_success() {
    ARRAY array = NULL;
    array_create(&array, 10);
    
    err result = array_destroy(array);
    
    TEST_ASSERT_ERR(result, SUCCESS, "array_destroy returns SUCCESS");
    // Note: Don't access array after this - it's freed!
}

// Destroy NULL array (should fail gracefully)
void test_array_destroy_null() {
    err result = array_destroy(NULL);
    
    TEST_ASSERT_ERR(result, INVALID_INPUT, 
                    "array_destroy returns INVALID_INPUT for NULL");
}

// Create and destroy in sequence
void test_array_create_destroy_sequence() {
    ARRAY array = NULL;
    
    err create_result = array_create(&array, 20);
    err destroy_result = array_destroy(array);
    
    TEST_ASSERT_ERR(create_result, SUCCESS, "create succeeds");
    TEST_ASSERT_ERR(destroy_result, SUCCESS, "destroy succeeds");
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
    test_array_create_success(10);
    test_array_create_size_zero();
    test_array_create_null_pointer();
    test_array_create_multiple();
    
    printf("\nTesting array_destroy()...\n");
    test_array_destroy_success();
    test_array_destroy_null();
    test_array_create_destroy_sequence();
    
    // Print summary
    printf("\n========================================\n");
    printf("  TEST RESULTS: %d/%d passed\n", tests_passed, tests_run);
    printf("========================================\n");
    
    return 0;
}
