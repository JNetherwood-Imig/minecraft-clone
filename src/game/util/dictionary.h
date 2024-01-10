#pragma once

#include "types.h"
#include <cglm/types.h>

// const u32 MAX_SIZE = 64;

typedef struct dictionary {
    i32 keys[64];
    void* values[64];
	u32 size;
} Dictionary;

u32 getIndex(Dictionary* dict, i32 key);
void* getValue(Dictionary* dict, i32 key);
void insert(Dictionary* dict, i32 key, void* value);
