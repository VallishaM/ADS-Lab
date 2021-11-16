
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
 
#define SKIPLIST_MAX_LEVEL 6
 
typedef struct node {
    int key;
    int value;
    struct node **forward;
} node;
 
typedef struct skiplist {
    int level;
    int size;
    struct node *header;
} skiplist;
 
skiplist *skiplist_init(skiplist *list) {
    int i;
    node *header = (node *) malloc(sizeof(struct node));
    list->header = header;
    header->key = INT_MAX;
    header->forward = (node **) malloc(
            sizeof(node*) * (SKIPLIST_MAX_LEVEL + 1));
    for (i = 0; i <= SKIPLIST_MAX_LEVEL; i++) {
        header->forward[i] = list->header;
    }
 
    list->level = 1;
    list->size = 0;
 
    return list;
}
 
static int rand_level() {
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL)
        level++;
    return level;
}
 
int skiplist_insert(skiplist *list, int key, int value) {
    node *update[SKIPLIST_MAX_LEVEL + 1];
    node *x = list->header;
    int i, level;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }
    x = x->forward[1];
 
    if (key == x->key) {
        x->value = value;
        return 0;
    } else {
        level = rand_level();
        if (level > list->level) {
            for (i = list->level + 1; i <= level; i++) {
                update[i] = list->header;
            }
            list->level = level;
        }
 
        x = (node *) malloc(sizeof(node));
        x->key = key;
        x->value = value;
        x->forward = (node **) malloc(sizeof(node*) * (level + 1));
        for (i = 1; i <= level; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
    return 0;
}
 
node *skiplist_search(skiplist *list, int key) {
    node *x = list->header;
    int i;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
    }
    if (x->forward[1]->key == key) {
        return x->forward[1];
    } else {
        return NULL;
    }
    return NULL;
}
 
static void skiplist_node_free(node *x) {
    if (x) {
        free(x->forward);
        free(x);
    }
}
 
int skiplist_delete(skiplist *list, int key) {
    int i;
    node *update[SKIPLIST_MAX_LEVEL + 1];
    node *x = list->header;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }
 
    x = x->forward[1];
    if (x->key == key) {
        for (i = 1; i <= list->level; i++) {
            if (update[i]->forward[i] != x)
                break;
            update[i]->forward[1] = x->forward[i];
        }
        skiplist_node_free(x);
 
        while (list->level > 1 && list->header->forward[list->level]
                == list->header)
            list->level--;
        return 0;
    }
    return 1;
}
 
static void skiplist_dump(skiplist *list) {
    node *x = list->header;
    while (x && x->forward[1] != list->header) {
        printf("%d[%d][%d]->", x->forward[1]->key, x->forward[1]->value);
        x = x->forward[1];
    }
    printf("NIL\n");
}
 
int main() {
    // int arr[] = { 3, 6, 9, 2, 11, 1, 4 }, i;
    skiplist list;
    skiplist_init(&list);
 
    // printf("Insert:--------------------\n");
    // for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
    //     skiplist_insert(&list, arr[i], arr[i]);
    // }
    // skiplist_dump(&list);
 
    // printf("Search:--------------------\n");
    // int keys[] = { 3, 4, 7, 10, 111 };
 
    // for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
    //     node *x = skiplist_search(&list, keys[i]);
    //     if (x) {
    //         printf("key = %d, value = %d\n", keys[i], x->value);
    //     } else {
    //         printf("key = %d, not fuound\n", keys[i]);
    //     }
    int choice = 0, data;
    while(choice!=-1) {
        printf("Enter 1 for insertion\n");
        printf("Enter 2 for deletion\n");
        printf("Enter 3 to search the list\n");
        printf("Enter 4 for printing the list\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter the data : ");
                scanf("%d", &data);
                skiplist_insert(&list, data, data);
                printf("Inserted\n");
                break;
            case 2:
                printf("Enter the key to delete :");
                printf("%d", &data);
                skiplist_delete(&list, data);
                break;
            case 3:
                printf("Enter the key to be searched : ");
                printf("%d", &data);
                if( skiplist_search(&list, data) == null)
                    printf("%d not found in the list", data);
                else
                    printf("%d found in the list", data);
                break;
            case 4:
                skiplist_dump();
                break;
            default:
                printf("Invalid Selection");


                

        }
    }
    }
 
    printf("Search:--------------------\n");
    skiplist_delete(&list, 3);
    skiplist_delete(&list, 9);
    skiplist_dump(&list);
 
    return 0;
}