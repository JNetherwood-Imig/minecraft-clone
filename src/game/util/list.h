#pragma once

#include "types.h"

typedef struct node {
    void* data;
    struct node* next;
} Node;

typedef struct list {
    Node* head;
    u32 length;
} List;

void listCreate(List* list);
void addNode(List* list, void* data);
i32 deleteNode(List* list, void* data);
Node* insertNode(List* list, void* data, u32 position);
