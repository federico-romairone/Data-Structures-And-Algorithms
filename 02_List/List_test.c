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

static ITEM make_item(int n, char *s) {
    ITEM item = NULL;
    item_create(&item);
    item_insert_data(item, n, s);
    return item;
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

void test_list_insert_head_single() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM item;
    boolean empty;

    list_create(&list);
    item = make_item(1, "one");
    result = list_insert_head(list, item);

    TEST_ASSERT(result == SUCCESS, "list_insert_head returns SUCCESS");

    list_empty(list, &empty);
    TEST_ASSERT(empty == FALSE, "list is not empty after insert_head");

    list_write_out(list, stdout);

    list_destroy(list);
}

void test_list_insert_head_null_list() {
    ITEM item = make_item(1, "one");
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

void test_list_insert_head_multiple_and_destroy() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM item = NULL;

    list_create(&list);
    for (int i = 0; i < 5; i++) {
        item = make_item(i+1, "");
        list_insert_head(list, item);
    }
    list_write_out(list, stdout);
    result = list_destroy(list);

    TEST_ASSERT(result == SUCCESS,
                "list_destroy returns SUCCESS after inserting multiple items");
}

void test_list_insert_tail_single() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM item = NULL;
    boolean empty = FALSE;   
    
    list_create(&list); 
    item = make_item(1, "one");
    result = list_insert_tail(list, item);

    TEST_ASSERT(result == SUCCESS, "list_insert_tail returns SUCCESS");

    list_empty(list, &empty);
    TEST_ASSERT(empty == FALSE, "list is not empty after insert_tail");

    list_write_out(list, stdout);

    list_destroy(list);
}

void test_list_insert_tail_null_list() {
    ITEM item = make_item(1, "one");
    status result = list_insert_tail(NULL, item);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_insert_tail returns INVALID_INPUT for NULL list");

    item_destroy(item);
}

void test_list_insert_tail_null_item() {
    status result = SUCCESS;
    LIST list = NULL;

    list_create(&list);
    result = list_insert_tail(list, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_insert_tail returns INVALID_INPUT for NULL item");

    list_destroy(list);
}

void test_list_insert_tail_multiple_and_destroy() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM item = NULL;

    list_create(&list);
    for (int i = 0; i < 5; i++) {
        item = make_item(i+1, "");
        list_insert_tail(list, item);
    }
    list_write_out(list, stdout);
    result = list_destroy(list);

    TEST_ASSERT(result == SUCCESS,
                "list_destroy returns SUCCESS after inserting multiple items");
}


/**
 * TEST SUITE: list_empty()
 */

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
    ITEM item = make_item(1, "one");

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
    status result = SUCCESS;
    LIST list = NULL;

    list_create(&list);
    result = list_empty(list, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_empty returns INVALID_INPUT for NULL result pointer");

    list_destroy(list);
}


/**
 * TEST SUITE: list_search()
 */

void test_list_search_existing_key() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM item1 = NULL, item2 = NULL;
    ITEM found = NULL;

    list_create(&list);
    item1 = make_item(1, "one");
    item2 = make_item(2, "two");

    list_insert_head(list, item1);
    list_insert_head(list, item2);
    result = list_search(list, "one", &found);

    TEST_ASSERT(result == SUCCESS, "list_search returns SUCCESS for existing key");
    TEST_ASSERT(found != NULL, "list_search finds the item");
    item_write_out(found, stdout); fprintf(stdout, "\n");

    item_destroy(found);
    list_destroy(list);
}

void test_list_search_missing_key() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM found = NULL;
    ITEM item1 = NULL, item2 = NULL;

    list_create(&list);
    item1 = make_item(1, "one");
    item2 = make_item(2, "two");

    list_insert_head(list, item1);
    list_insert_head(list, item2);
    result = list_search(list, "ghost", &found);

    TEST_ASSERT(result == NOT_FOUND, "list_search return NOT_FOUND for missing key");

    item_destroy(found);
    list_destroy(list);
}

void test_list_search_null_list() {
    ITEM found = NULL;
    status result = list_search(NULL, "key", &found);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_search returns INVALID_INPUT for NULL list");
}


/**
 * TEST SUITE: list_delete_head()
 */

void test_list_delete_head_with_extract() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM item = make_item(1, "one");
    ITEM extracted = NULL;
    boolean empty;

    list_create(&list);
    list_insert_head(list, item);
    list_write_out(list, stdout);
    result = list_delete_head(list, TRUE, &extracted);
    list_write_out(list, stdout);

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
    status result = SUCCESS;    
    LIST list = NULL;
    ITEM item = make_item(1, "one");
    boolean empty;

    list_create(&list);
    list_insert_head(list, item);
    result = list_delete_head(list, FALSE, NULL);

    TEST_ASSERT(result == SUCCESS,
                "list_delete_head returns SUCCESS with extract=FALSE");

    list_empty(list, &empty);
    TEST_ASSERT(empty == TRUE, "list is empty after deleting the only element");

    list_destroy(list);
}

void test_list_delete_head_empty_list() {
    status result = SUCCESS;
    LIST list = NULL;

    list_create(&list);
    result = list_delete_head(list, FALSE, NULL);

    TEST_ASSERT(result == SUCCESS,
                "list_delete_head does nothing on empty list");

    list_destroy(list);
}

void test_list_delete_head_null_list() {
    status result = list_delete_head(NULL, FALSE, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_delete_head returns INVALID_INPUT for NULL list");
}

void test_list_delete_head_with_extract_more_items() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM item = NULL;
    ITEM extracted = NULL;
    boolean empty;

    list_create(&list);
    for (int i = 0; i < 5; i++) {
        item = make_item(i+1, "");
        list_insert_head(list, item);
    }
    list_write_out(list, stdout);
    result = list_delete_head(list, TRUE, &extracted);
    list_write_out(list, stdout);
    fprintf(stdout, "Ecxtracted item: "); 
    item_write_out(extracted, stdout);
    fprintf(stdout, "\n");

    TEST_ASSERT(result == SUCCESS,
                "list_delete_head returns SUCCESS with extract=TRUE");
    TEST_ASSERT(extracted != NULL,
                "list_delete_head extracts the item when extract=TRUE");
    
    item_destroy(extracted);
    for (int i = 0; i < 4; i++) {
        list_delete_head(list, TRUE, &extracted);
        item_destroy(extracted);
    }
    list_empty(list, &empty);
    TEST_ASSERT(empty == TRUE, "list is empty after deleting all elements");

    list_destroy(list);
}


/**
 * TEST SUITE: list_delete_position()
 */

void test_list_delete_position_head() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM extracted = NULL;
    boolean empty;

    list_create(&list);
    for (int i = 0; i < 3; i++) list_insert_tail(list, make_item(i+1, ""));
    list_write_out(list, stdout);
    result = list_delete_position(list, 0, TRUE, &extracted);
    list_write_out(list, stdout);
    item_write_out(extracted, stdout);
    fprintf(stdout, "\n");

    TEST_ASSERT(result == SUCCESS, "list_delete_position: delete head returns SUCCESS");
    TEST_ASSERT(extracted != NULL, "list_delete_position: head item extracted");

    item_destroy(extracted);
    list_destroy(list);
}

void test_list_delete_position_tail() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM extracted = NULL;

    list_create(&list);
    for (int i = 0; i < 3; i++) list_insert_tail(list, make_item(i+1, ""));
    list_write_out(list, stdout);
    result = list_delete_position(list, 2, TRUE, &extracted);
    list_write_out(list, stdout);
    item_write_out(extracted, stdout);
    fprintf(stdout, "\n");

    TEST_ASSERT(result == SUCCESS, "list_delete_position: delete tail returns SUCCESS");
    TEST_ASSERT(extracted != NULL, "list_delete_position: tail item extracted");

    item_destroy(extracted);
    list_destroy(list);
}

void test_list_delete_position_middle() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM extracted = NULL;

    list_create(&list);
    for (int i = 0; i < 5; i++) list_insert_tail(list, make_item(i+1, ""));
    list_write_out(list, stdout);
    result = list_delete_position(list, 2, TRUE, &extracted);
    list_write_out(list, stdout);
    item_write_out(extracted, stdout);
    fprintf(stdout, "\n");

    TEST_ASSERT(result == SUCCESS, "list_delete_position: delete middle returns SUCCESS");
    TEST_ASSERT(extracted != NULL, "list_delete_position: middle item extracted");

    item_destroy(extracted);
    list_destroy(list);
}

void test_list_delete_position_without_extract() {
    status result = SUCCESS;
    LIST list = NULL;
    boolean empty;

    list_create(&list);
    list_insert_tail(list, make_item(1, "one"));
    result = list_delete_position(list, 0, FALSE, NULL);

    TEST_ASSERT(result == SUCCESS, "list_delete_position: extract=FALSE returns SUCCESS");
    list_empty(list, &empty);
    TEST_ASSERT(empty == TRUE, "list_delete_position: list empty after delete without extract");

    list_destroy(list);
}

void test_list_delete_position_null_list() {
    ITEM extracted = NULL;
    status result = list_delete_position(NULL, 0, FALSE, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_delete_position: NULL list returns INVALID_INPUT");
}

void test_list_delete_position_negative_index() {
    status result = SUCCESS;
    LIST list = NULL;

    list_create(&list);
    list_insert_tail(list, make_item(1, "one"));
    result = list_delete_position(list, -1, FALSE, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_delete_position: negative index returns INVALID_INPUT");

    list_destroy(list);
}

void test_list_delete_position_out_of_bounds() {
    status result = SUCCESS;
    LIST list = NULL;

    list_create(&list);
    list_insert_tail(list, make_item(1, "one"));
    result = list_delete_position(list, 5, FALSE, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_delete_position: out-of-bounds index returns INVALID_INPUT");

    list_destroy(list);
}

void test_list_delete_position_extract_null_pnt() {
    status result = SUCCESS;
    LIST list = NULL;

    list_create(&list);
    list_insert_tail(list, make_item(1, "one"));
    result = list_delete_position(list, 0, TRUE, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_delete_position: extract=TRUE with NULL item_pnt returns INVALID_INPUT");

    list_destroy(list);
}

void test_list_delete_position_all_elements() {
    LIST list = NULL;
    ITEM extracted = NULL;
    boolean empty;
    status result = SUCCESS;

    list_create(&list);
    for (int i = 0; i < 3; i++) list_insert_tail(list, make_item(i+1, ""));
    for (int i = 0; i < 3; i++) {
        result = list_delete_position(list, 0, TRUE, &extracted);
        item_destroy(extracted);
        extracted = NULL;
    }
    list_empty(list, &empty);

    TEST_ASSERT(result == SUCCESS, "list_delete_position: deleting all elements returns SUCCESS");
    TEST_ASSERT(empty == TRUE, "list_delete_position: list empty after removing all elements");

    list_destroy(list);
}


/**
 * TEST SUITE: list_delete_key()
 */

void test_list_delete_key_head() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM extracted = NULL;

    list_create(&list);
    list_insert_tail(list, make_item(1, "one"));
    list_insert_tail(list, make_item(2, "two"));
    list_insert_tail(list, make_item(3, "three"));
    list_write_out(list, stdout);
    result = list_delete_key(list, "one", TRUE, &extracted);
    list_write_out(list, stdout);
    item_write_out(extracted, stdout);
    fprintf(stdout, "\n");

    TEST_ASSERT(result == SUCCESS, "list_delete_key: delete head by key returns SUCCESS");
    TEST_ASSERT(extracted != NULL, "list_delete_key: head item extracted by key");

    item_destroy(extracted);
    list_destroy(list);
}

void test_list_delete_key_tail() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM extracted = NULL;

    list_create(&list);
    list_insert_tail(list, make_item(1, "one"));
    list_insert_tail(list, make_item(2, "two"));
    list_insert_tail(list, make_item(3, "three"));
    list_write_out(list, stdout);
    result = list_delete_key(list, "three", TRUE, &extracted);
    list_write_out(list, stdout);
    item_write_out(extracted, stdout);
    fprintf(stdout, "\n");

    TEST_ASSERT(result == SUCCESS, "list_delete_key: delete tail by key returns SUCCESS");
    TEST_ASSERT(extracted != NULL, "list_delete_key: tail item extracted by key");

    item_destroy(extracted);
    list_destroy(list);
}

void test_list_delete_key_middle() {
    status result = SUCCESS;
    LIST list = NULL;
    ITEM extracted = NULL;

    list_create(&list);
    list_insert_tail(list, make_item(1, "one"));
    list_insert_tail(list, make_item(2, "two"));
    list_insert_tail(list, make_item(3, "three"));
    list_write_out(list, stdout);
    result = list_delete_key(list, "two", TRUE, &extracted);
    list_write_out(list, stdout);
    item_write_out(extracted, stdout);
    fprintf(stdout, "\n");

    TEST_ASSERT(result == SUCCESS, "list_delete_key: delete middle by key returns SUCCESS");
    TEST_ASSERT(extracted != NULL, "list_delete_key: middle item extracted by key");

    item_destroy(extracted);
    list_destroy(list);
}

void test_list_delete_key_without_extract() {
    status result = SUCCESS;
    LIST list = NULL;
    boolean empty;

    list_create(&list);
    list_insert_tail(list, make_item(1, "one"));
    result = list_delete_key(list, "one", FALSE, NULL);

    TEST_ASSERT(result == SUCCESS, "list_delete_key: extract=FALSE returns SUCCESS");

    list_empty(list, &empty);
    TEST_ASSERT(empty == TRUE, "list_delete_key: list empty after delete without extract");

    list_destroy(list);
}

void test_list_delete_key_not_found() {
    status result = SUCCESS;
    LIST list = NULL;

    list_create(&list);
    list_insert_tail(list, make_item(1, "one"));
    list_insert_tail(list, make_item(2, "two"));
    result = list_delete_key(list, "ghost", FALSE, NULL);

    TEST_ASSERT(result == NOT_FOUND, "list_delete_key: missing key returns NOT_FOUND");

    list_destroy(list);
}

void test_list_delete_key_null_list() {
    status result = list_delete_key(NULL, "one", FALSE, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_delete_key: NULL list returns INVALID_INPUT");
}

void test_list_delete_key_extract_null_pnt() {
    status result = SUCCESS;
    LIST list = NULL;

    list_create(&list);
    list_insert_tail(list, make_item(1, "one"));
    result = list_delete_key(list, "one", TRUE, NULL);

    TEST_ASSERT(result == INVALID_INPUT,
                "list_delete_key: extract=TRUE with NULL item_pnt returns INVALID_INPUT");

    list_destroy(list);
}

void test_list_delete_key_preserves_structure() {
    LIST list = NULL;
    boolean empty;

    list_create(&list);
    list_insert_tail(list, make_item(1, "one"));
    list_insert_tail(list, make_item(2, "two"));
    list_insert_tail(list, make_item(3, "three"));
    list_delete_key(list, "two", FALSE, NULL);

    list_empty(list, &empty);
    TEST_ASSERT(empty == FALSE, "list_delete_key: list still has elements after partial delete");

    list_write_out(list, stdout);
    list_destroy(list);
}


/**
 * MAIN TEST RUNNER
 */

int main() {
    printf("========================================\n");
    printf("  LIST DATA STRUCTURE TEST SUITE\n");
    printf("========================================\n\n");
    /*
    printf("Testing list_create()...\n");
    test_list_create_success();
    test_list_create_null_pointer();
    test_list_create_empty_on_creation();

    printf("\nTesting list_destroy()...\n");
    test_list_destroy_empty_list();
    test_list_destroy_null_list();

    printf("\nTesting list_insert_head()...\n");
    test_list_insert_head_single();
    test_list_insert_head_null_list();
    test_list_insert_head_null_item();
    test_list_insert_head_multiple_and_destroy();

    printf("\nTesting list_insert_tail()...\n");
    test_list_insert_tail_single();
    test_list_insert_tail_null_list();
    test_list_insert_tail_null_item();
    test_list_insert_tail_multiple_and_destroy();

    printf("\nTesting list_empty()...\n");
    test_list_empty_on_empty_list();
    test_list_empty_after_insert();
    test_list_empty_null_list();
    test_list_empty_null_result();

    printf("\nTesting list_search()...\n");
    test_list_search_existing_key();
    test_list_search_missing_key();
    test_list_search_null_list();
    
    printf("\nTesting list_delete_head()...\n");
    test_list_delete_head_with_extract();
    test_list_delete_head_without_extract();
    test_list_delete_head_empty_list();
    test_list_delete_head_null_list();
    test_list_delete_head_with_extract_more_items();

    printf("\nTesting list_delete_position()...\n");
    test_list_delete_position_head();
    test_list_delete_position_tail();
    test_list_delete_position_middle();
    test_list_delete_position_without_extract();
    test_list_delete_position_null_list();
    test_list_delete_position_negative_index();
    test_list_delete_position_out_of_bounds();
    test_list_delete_position_extract_null_pnt();
    test_list_delete_position_all_elements();

    printf("\nTesting list_delete_key()...\n");
    test_list_delete_key_head();
    test_list_delete_key_tail();
    test_list_delete_key_middle();
    test_list_delete_key_without_extract();
    test_list_delete_key_not_found();
    test_list_delete_key_null_list();
    test_list_delete_key_extract_null_pnt();
    test_list_delete_key_preserves_structure();
    */
    printf("\n========================================\n");
    printf("  TEST RESULTS: %d/%d passed\n", tests_passed, tests_run);
    printf("========================================\n");

    return (tests_passed == tests_run) ? 0 : 1;
}
