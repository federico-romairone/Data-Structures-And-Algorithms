#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct node* link; 

/**
 * @struct node
 * @brief Dynamic linked structure in a list
 * 
 * Manages a dynamically allocated node.
 */
struct node {
    ITEM val;   // Data in the node
    link next;  // pointer to the next node in list
};

/**
 * @struct list
 * @brief Dynamic container for generic ITEM elements
 * 
 * Manages a dynamically allocated list of nodes.
 */
struct list { 
    link head;  // Pointer to the first dinamic element of the list
    link tail;  // Pointer to the last dinamic element of the list
    link z;     // Pointer to the sentinel node
    int n;      // Number of elements
};

// node operations

status node_create(link *x_pnt, ITEM val, link next) {
    status result = SUCCESS;
    link x;

    if (val == NULL) result = INVALID_INPUT;
    else {
        x = (link)malloc(sizeof(struct node));
        if (x == NULL) result = OUT_OF_MEMORY;
        else {
            x->val = val;
            x->next = next;
            *x_pnt = x;
        }
    }

    return result;
}

status node_destroy(link x) {
    status result = SUCCESS;

    if (x != NULL) {
        result = item_destroy(x->val);
        if (result == SUCCESS) free(x);
    }

    return result;
}

// Memory handling 

status list_create(LIST *list_pnt) {
    status result = SUCCESS;
    LIST list;
    ITEM item_void;

    if (list_pnt == NULL) result = INVALID_INPUT;
    else {
        list = (LIST)malloc(sizeof(struct list));
        if (list == NULL) result = OUT_OF_MEMORY;
        else {
            list->n = 0;
            result = item_create_void(&item_void);
            if (result == SUCCESS) {
                result = node_create(&(list->z), item_void, NULL);
                if (result == SUCCESS) {
                    list->head = list->tail = list->z; 
                    *list_pnt = list;
                }
                else item_destroy(item_void);
            }
            else free(list);
        }
    }

    return result;
}

static status destroy_recursive(link x, link z) {
    status result = SUCCESS;
    
    if (x == NULL) result = INVALID_INPUT;
    else if (x != z) {
        result = destroy_recursive(x->next, z);
        if (result == SUCCESS) result = node_destroy(x);
    }

    return result;
}

status list_destroy(LIST list) {
    status result = SUCCESS;

    if (list != NULL) {
        result = destroy_recursive(list->head, list->z);
        if (result == SUCCESS) {
            result = node_destroy(list->z);
            free(list);
        }
    }

    return result;
}

// Search, insert, delete

status list_search(LIST list, KEY key, ITEM *item_pnt);

status list_insert_head(LIST list, ITEM item);

status list_insert_tail(LIST list, ITEM item);

status list_delete_head(LIST list, boolean extract, ITEM *item_pnt);

status list_delete_position(LIST list, int index, boolean extract, ITEM *item_pnt);

status list_delete_key(LIST list, KEY key, boolean extract, ITEM *item_pnt);

// Setters and status

status list_empty(LIST list, boolean *empty_pnt) {
    status result = SUCCESS;

    if (list == NULL) result = INVALID_INPUT;
    else *empty_pnt = (list->n == 0);

    return result;
}

// Output

status list_write_out(LIST list, FILE *fout); // ricorsivo