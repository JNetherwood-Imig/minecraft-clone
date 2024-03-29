#pragma once

#include "types.h"
#include <cglm/types.h>

// NOT IN USE

#define MAX_SIZE = 64

typedef struct dictionary {
    i32 keys[MAX_SIZE];
    void* values[MAX_SIZE];
	u32 size;
} Dictionary;

u32 getIndex(Dictionary* dict, i32 key);
void* getValue(Dictionary* dict, i32 key);
void insert(Dictionary* dict, i32 key, void* value);
