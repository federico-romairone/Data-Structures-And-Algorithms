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
    boolean initialized;
};

// Key functions

KEY key_get(ITEM item) {
    return item == NULL ? NULL : strdup(item->str);
}

int key_cmp(KEY k1, KEY k2) {
    return strcmp(k1, k2);
}

// Memory handling 

status item_create(ITEM *item_pnt) {
    status result = SUCCESS;
    ITEM item;

    item = (ITEM)malloc(sizeof(struct item));
    if (item == NULL) result = OUT_OF_MEMORY;
    else {
        item->num = 0;
        item->str = (char*)malloc(MAX_KEY_LEN * sizeof(char));
        item->str[0] = '\0';
        item->initialized = FALSE;
        *item_pnt = item;
    }

    return result;
}

status item_create_void(ITEM *item_pnt) {
    status result = SUCCESS;
    ITEM item;

    item = (ITEM)malloc(sizeof(struct item));
    if (item == NULL) result = OUT_OF_MEMORY;
    else {
        item->num = 0;
        item->str = NULL;
        item->initialized = FALSE;
        *item_pnt = item;
    }

    return result;
}

status item_destroy(ITEM item) {
    if (item != NULL) {
        free(item->str);
        free(item);
    }

    return SUCCESS;
}

// Input

status item_insert_from_file(ITEM item, FILE *fin) {
    status result = SUCCESS;
    int n;

    if (item == NULL || fin == NULL) result = INVALID_INPUT;
    else {
        n = fscanf(fin, "%d %s", &(item->num), item->str);
        if (n == 2) item->initialized = TRUE;
        else if (feof(fin)) result = END_OF_FILE;
        else result = INVALID_FILE_FORMAT;
    }

    return result;
}

status item_insert_from_keyboard(ITEM item) {
    status result = SUCCESS;
    int n;

    if (item == NULL) result = INVALID_INPUT;
    else {
        printf("<number> <string>: ");
        n = scanf("%d %s", &(item->num), item->str);
        if (n != 2) result = INVALID_FILE_FORMAT;
        else item->initialized = TRUE;
    }

    return result;
}

status item_insert_data(ITEM item, int n, char *s) {
    status result = SUCCESS;

    if (item == NULL) result = INVALID_INPUT;
    else {
        item->num = n;
        free(item->str);
        item->str = strdup(s);
        item->initialized = TRUE;
    }

    return SUCCESS;
}

// Output

status item_write_out(ITEM item, FILE *fout) {
    status result = SUCCESS;

    if (item == NULL || fout == NULL) result = INVALID_INPUT;
    else fprintf(fout, "{ number='%d' value='%s' initialized='%s' }",
                item->num, item->str, item->initialized == TRUE ? "TRUE" : "FALSE");  

    return result;
}

status item_cpy(ITEM dest, ITEM source) {
    status result = SUCCESS;

    if (dest == NULL || source == NULL)  result = INVALID_INPUT;
    else {
        dest->num = source->num;
        free(dest->str);
        dest->str = strdup(source->str);
        dest->initialized = source->initialized;
    }

    return result;
}