/**
 * Item is an integer.
 */

#include "Item.h"

/**
 * @struct item
 * @brief Generic item with a string and a number
 */
struct item {
    int num;
    char *str;
    int initialized;
};

status item_create(ITEM *item_pnt) {
    ITEM item;
    status result = SUCCESS;

    item = (ITEM)malloc(sizeof(struct item));
    if (item == NULL) result = OUT_OF_MEMORY;
    else {
        item->num = 0;
        item->str = (char*)malloc(MAX_KEY_LEN * sizeof(char));
        item->str[0] = '\0';
        item->initialized = 0;
        *item_pnt = item;
    }

    return result;
}

status item_destroy(ITEM item) {
    status result = SUCCESS;

    if (item == NULL) result = INVALID_INPUT;
    else {
        free(item->str);
        free(item);
    }

    return result;
}

// Getters

status item_get_key(ITEM item, KEY key);

status item_get_value(ITEM item, VALUE value);

// Input

status item_fill_from_file(ITEM item, FILE *fin) {
    status result = SUCCESS;
    int n;

    if (item == NULL || fin == NULL) result = INVALID_INPUT;
    else {
        n = fscanf(fin, "%d %s\n", &(item->num), item->str);
        if (n == 2) item->initialized = TRUE;
        else if (feof(fin)) result = END_OF_FILE;
        else result = INVALID_FILE_FORMAT;
    }

    return result;
}

status item_fill_from_keyboard(ITEM item) {
    status result = SUCCESS;
    int n;

    if (item == NULL) result = INVALID_INPUT;
    else {
        n = scanf("%d %s\n", &(item->num), item->str);
        if (n != 2) result = INVALID_FILE_FORMAT;
        else item->initialized = TRUE;
    }

    return result;
}

// Output

status item_write_out(ITEM item, FILE *fout) {
    status result = SUCCESS;

    if (item == NULL || fout == NULL) result = INVALID_INPUT;
    else fprintf(fout, "{ number='%d' value='%s' initialized='%s' }",
                item->num, item->str, item->initialized == TRUE ? "TRUE" : "FALSE");  

    return result;
}