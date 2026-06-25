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

static status search_recursive(link x, link z, KEY key, ITEM *item_pnt) {
    status result = SUCCESS;

    if (x == NULL) result = INVALID_INPUT;
    else if (x == z) result = item_create_void(item_pnt);
    else if (key_cmp(key, key_get(x->val)) == 0) *item_pnt = x->val;
    else result = search_recursive(x->next, z, key, item_pnt);

    return result;
}

status list_search(LIST list, KEY key, ITEM *item_pnt) {
    status result = SUCCESS;

    if (list == NULL) result = INVALID_INPUT;
    else result = search_recursive(list->head, list->z, key, item_pnt);

    return result;
}

status list_insert_head(LIST list, ITEM item) {
    status result = SUCCESS;

    if (list == NULL || item == NULL) result = INVALID_INPUT;
    else {
        result = node_create(&(list->head), item, list->head);
        if (result == SUCCESS) {
            // if first element, it is both the head and the tail
            if (list->n == 0) list->tail = list->head;
            list->n++;
        }
    }

    return result;
}

status list_insert_tail(LIST list, ITEM item) {
    status result = SUCCESS;
    link x;

    if (list == NULL || item == NULL) result = INVALID_INPUT;
    else {
        // first element
        if (list->n == 0) list_insert_head(list, item);
        // search for the tail
        else {
            for (x = list->head; x != list->tail;  x = x->next);
            result = node_create(&(x), item, list->z);
            if (result == SUCCESS) {
                // next of the previous tail become the new node
                list->tail->next = x;
                // the new node become the tail
                list->tail = x;
                list->n++;
            }
        }
    }

    return result;
}

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

static status traversal(link x, link z, FILE *fout) {
    status result = SUCCESS;

    // terminal case
    if (x == z) {
        fprintf(fout, "END");
        return SUCCESS;
    }
    
    // recursive case
    result = item_write_out(x->val, fout);
    if (result == SUCCESS) {
        fprintf(fout, " --> ");
        traversal(x->next, z, fout);
    }

    return result;
}

status list_write_out(LIST list, FILE *fout) {
    status result = SUCCESS;

    if (list == NULL || fout == NULL) result = INVALID_INPUT;
    else {
        fprintf(fout, "LIST: ");
        result = traversal(list->head, list->z, fout);
        if (result == SUCCESS) {
            fprintf(fout, "\nHead: ");
            item_write_out(list->head->val, fout);
            fprintf(fout, "\nTail: ");
            item_write_out(list->tail->val, fout);
            fprintf(fout, "\nn = %d\n", list->n);
        }
        else fprintf(fout, "Error!\n");
    }

    return result;
}