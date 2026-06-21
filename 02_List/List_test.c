#include <stdio.h>
#include <stdlib.h>
#include "List.h"

/**
 * TEST HELPER FUNCTIONS
 */

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
 * TEST SUITE: list_create()
 */

void test_list_create_success() {
    LIST list = NULL;
    status result = list_create(&list);

    TEST_ASSERT(result == SUCCESS, "list_create returns SUCCESS");
    TEST_ASSERT(list != NULL, "list_create allocates the container structure");

    list_destroy(list);
}

void test_list_create_null_pointer() {
    status result = list_create(NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_create returns INVALID_INPUT for NULL list_pnt");
}

void test_list_create_empty_on_creation() {
    LIST list = NULL;
    boolean empty;
    status result;

    list_create(&list);
    result = list_empty(list, &empty);

    TEST_ASSERT(result == SUCCESS, "list_empty returns SUCCESS on new list");
    TEST_ASSERT(empty == TRUE, "list_create initializes an empty list");

    list_destroy(list);
}


/**
 * TEST SUITE: list_destroy()
 */

void test_list_destroy_empty_list() {
    LIST list = NULL;
    status result;

    list_create(&list);
    result = list_destroy(list);

    TEST_ASSERT(result == SUCCESS, "list_destroy returns SUCCESS on empty list");
}

void test_list_destroy_null_list() {
    status result = list_destroy(NULL);

    TEST_ASSERT(result == SUCCESS,
                "list_destroy returns SUCCESS for NULL list (no-op)");
}


/**
 * TEST SUITE: list_insert_head() + list_insert_tail()
 */
/*
static ITEM make_item() {
    ITEM item = NULL;
    item_create(&item);
    return item;
}

void test_list_insert_head_single() {
    LIST list = NULL;
    boolean empty;

    list_create(&list);
    ITEM item = make_item();
    status result = list_insert_head(list, item);

    TEST_ASSERT(result == SUCCESS, "list_insert_head returns SUCCESS");

    list_empty(list, &empty);
    TEST_ASSERT(empty == FALSE, "list is not empty after insert_head");

    list_destroy(list);
}

void test_list_insert_head_null_list() {
    ITEM item = make_item();
    status result = list_insert_head(NULL, item);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_insert_head returns INVALID_INPUT for NULL list");

    item_destroy(item);
}

void test_list_insert_head_null_item() {
    LIST list = NULL;

    list_create(&list);
    status result = list_insert_head(list, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_insert_head returns INVALID_INPUT for NULL item");

    list_destroy(list);
}

void test_list_insert_tail_single() {
    LIST list = NULL;
    boolean empty;

    list_create(&list);
    ITEM item = make_item();
    status result = list_insert_tail(list, item);

    TEST_ASSERT(result == SUCCESS, "list_insert_tail returns SUCCESS");

    list_empty(list, &empty);
    TEST_ASSERT(empty == FALSE, "list is not empty after insert_tail");

    list_destroy(list);
}

void test_list_insert_tail_null_list() {
    ITEM item = make_item();
    status result = list_insert_tail(NULL, item);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_insert_tail returns INVALID_INPUT for NULL list");

    item_destroy(item);
}

void test_list_insert_tail_null_item() {
    LIST list = NULL;

    list_create(&list);
    status result = list_insert_tail(list, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_insert_tail returns INVALID_INPUT for NULL item");

    list_destroy(list);
}

void test_list_insert_multiple_and_destroy() {
    LIST list = NULL;

    list_create(&list);
    for (int i = 0; i < 5; i++) {
        ITEM item = make_item();
        list_insert_tail(list, item);
    }
    status result = list_destroy(list);

    TEST_ASSERT(result == SUCCESS,
                "list_destroy returns SUCCESS after inserting multiple items");
}
*/

/**
 * TEST SUITE: list_empty()
 */
/*
void test_list_empty_on_empty_list() {
    LIST list = NULL;
    boolean empty;

    list_create(&list);
    status result = list_empty(list, &empty);

    TEST_ASSERT(result == SUCCESS, "list_empty returns SUCCESS");
    TEST_ASSERT(empty == TRUE, "list_empty returns TRUE on empty list");

    list_destroy(list);
}

void test_list_empty_after_insert() {
    LIST list = NULL;
    boolean empty;
    ITEM item = make_item();

    list_create(&list);
    list_insert_head(list, item);
    list_empty(list, &empty);

    TEST_ASSERT(empty == FALSE, "list_empty returns FALSE after an insert");

    list_destroy(list);
}

void test_list_empty_null_list() {
    boolean empty;
    status result = list_empty(NULL, &empty);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_empty returns INVALID_INPUT for NULL list");
}

void test_list_empty_null_result() {
    LIST list = NULL;

    list_create(&list);
    status result = list_empty(list, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_empty returns INVALID_INPUT for NULL result pointer");

    list_destroy(list);
}
*/

/**
 * TEST SUITE: list_delete_head()
 */
/*
void test_list_delete_head_with_extract() {
    LIST list = NULL;
    ITEM item = make_item();
    ITEM extracted = NULL;
    boolean empty;

    list_create(&list);
    list_insert_head(list, item);
    status result = list_delete_head(list, TRUE, &extracted);

    TEST_ASSERT(result == SUCCESS,
                "list_delete_head returns SUCCESS with extract=TRUE");
    TEST_ASSERT(extracted != NULL,
                "list_delete_head extracts the item when extract=TRUE");

    list_empty(list, &empty);
    TEST_ASSERT(empty == TRUE, "list is empty after deleting the only element");

    item_destroy(extracted);
    list_destroy(list);
}

void test_list_delete_head_without_extract() {
    LIST list = NULL;
    ITEM item = make_item();
    boolean empty;

    list_create(&list);
    list_insert_head(list, item);
    status result = list_delete_head(list, FALSE, NULL);

    TEST_ASSERT(result == SUCCESS,
                "list_delete_head returns SUCCESS with extract=FALSE");

    list_empty(list, &empty);
    TEST_ASSERT(empty == TRUE, "list is empty after deleting the only element");

    list_destroy(list);
}

void test_list_delete_head_empty_list() {
    LIST list = NULL;

    list_create(&list);
    status result = list_delete_head(list, FALSE, NULL);

    TEST_ASSERT(result != SUCCESS,
                "list_delete_head fails on empty list");

    list_destroy(list);
}

void test_list_delete_head_null_list() {
    status result = list_delete_head(NULL, FALSE, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_delete_head returns INVALID_INPUT for NULL list");
}
*/

/**
 * TEST SUITE: list_search()
 */
/*
void test_list_search_existing_key() {
    LIST list = NULL;
    ITEM item = NULL;
    ITEM found = NULL;

    list_create(&list);
    item_create(&item);

    FILE *tmp = tmpfile();
    fprintf(tmp, "42 hello");
    rewind(tmp);
    item_insert_from_file(item, tmp);
    fclose(tmp);

    list_insert_head(list, item);
    status result = list_search(list, "hello", &found);

    TEST_ASSERT(result == SUCCESS, "list_search returns SUCCESS for existing key");
    TEST_ASSERT(found != NULL, "list_search finds the item");

    list_destroy(list);
}

void test_list_search_missing_key() {
    LIST list = NULL;
    ITEM found = NULL;

    list_create(&list);
    status result = list_search(list, "ghost", &found);

    TEST_ASSERT(result != SUCCESS, "list_search fails for missing key");

    list_destroy(list);
}

void test_list_search_null_list() {
    ITEM found = NULL;
    status result = list_search(NULL, "key", &found);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_search returns INVALID_INPUT for NULL list");
}
*/

/**
 * TEST SUITE: list_write_out()
 */
/*
void test_list_write_out_empty_list() {
    LIST list = NULL;

    list_create(&list);
    status result = list_write_out(list, stdout);

    TEST_ASSERT(result == SUCCESS, "list_write_out returns SUCCESS on empty list");

    list_destroy(list);
}

void test_list_write_out_with_items() {
    LIST list = NULL;

    list_create(&list);
    for (int i = 0; i < 3; i++) {
        ITEM item = make_item();
        list_insert_tail(list, item);
    }

    printf("  (output below)\n");
    status result = list_write_out(list, stdout);

    TEST_ASSERT(result == SUCCESS, "list_write_out returns SUCCESS with items");

    list_destroy(list);
}

void test_list_write_out_null_list() {
    status result = list_write_out(NULL, stdout);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_write_out returns INVALID_INPUT for NULL list");
}

void test_list_write_out_null_file() {
    LIST list = NULL;

    list_create(&list);
    status result = list_write_out(list, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_write_out returns INVALID_INPUT for NULL file");

    list_destroy(list);
}
*/

/**
 * MAIN TEST RUNNER
 */

int main() {
    printf("========================================\n");
    printf("  LIST DATA STRUCTURE TEST SUITE\n");
    printf("========================================\n\n");

    printf("Testing list_create()...\n");
    test_list_create_success();
    test_list_create_null_pointer();
    test_list_create_empty_on_creation();

    printf("\nTesting list_destroy()...\n");
    test_list_destroy_empty_list();
    test_list_destroy_null_list();
    /*
    printf("\nTesting list_empty()...\n");
    test_list_empty_on_empty_list();
    test_list_empty_after_insert();
    test_list_empty_null_list();
    test_list_empty_null_result();

    printf("\nTesting list_insert_head()...\n");
    test_list_insert_head_single();
    test_list_insert_head_null_list();
    test_list_insert_head_null_item();

    printf("\nTesting list_insert_tail()...\n");
    test_list_insert_tail_single();
    test_list_insert_tail_null_list();
    test_list_insert_tail_null_item();
    test_list_insert_multiple_and_destroy();

    printf("\nTesting list_delete_head()...\n");
    test_list_delete_head_with_extract();
    test_list_delete_head_without_extract();
    test_list_delete_head_empty_list();
    test_list_delete_head_null_list();

    printf("\nTesting list_search()...\n");
    test_list_search_existing_key();
    test_list_search_missing_key();
    test_list_search_null_list();

    printf("\nTesting list_write_out()...\n");
    test_list_write_out_empty_list();
    test_list_write_out_with_items();
    test_list_write_out_null_list();
    test_list_write_out_null_file();
    */
    printf("\n========================================\n");
    printf("  TEST RESULTS: %d/%d passed\n", tests_passed, tests_run);
    printf("========================================\n");

    return (tests_passed == tests_run) ? 0 : 1;
}
