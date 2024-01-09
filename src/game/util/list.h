#pragma once

#include "types.h"

typedef struct node {
    f32 data;
    struct node* next;
} Node;

typedef struct list {
    Node* head;
    u32 length;
} List;

void listCreate(List* list);
Node* addNode(List* list, f32 data, u32 position);
i32 deleteNode(List* list, f32 data);
Node* insertNode(List* list, f32 data, u32 position);
