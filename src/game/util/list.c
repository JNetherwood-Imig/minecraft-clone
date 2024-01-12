#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// NOT IN USE

void listCreate(List* list) {
    list->head = NULL;
    list->length = 0;
}

void addNode(List* list, void* data) {
    Node* new = NULL;

    if (list->head == NULL) {
        new = malloc(sizeof(Node*));
        assert(new != NULL);
        
        new->data = data;
        list->head = new;
        new->next = NULL;
    } else {
        new = malloc(sizeof(Node*));
        assert(new != NULL);

        new->data = data;
        new->next = list->head;
        list->head = new;
        list->length++;
    }
}

i32 deleteNode(List* list, void* data) {
    Node* current = list->head;
    Node* prev = list->head;
    while (current != NULL) {
        if (current->data == data) {
            if (current ==list->head) {
                list->head = current->next;
            } else {
                prev->next = current->next;
                free(current);
                current = NULL;
            }

            return 1;
        }
        prev = current;
        current = current->next;
    }

    return 0;
}

// void insertNode(List* list, void* data, u32 position) {
//     Node* current = list->head;
//     while (current != NULL && position != 0) {
//         position--;
//     }

//     if (position != 0) {
//         printf("Requested position is too far into list!\nRequested position %d, list length is %d.\n", position, list->length);
//         return NULL;
//     }

//     Node* new = malloc(sizeof(Node));
//     if (new == NULL)
//         return NULL;

//     new->data = data;
//     new->next = current->next;
//     current->next = new;
//     list->length++;

// }
