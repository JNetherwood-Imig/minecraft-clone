#include "dictionary.h"
#include <cglm/types.h>
#include <stdio.h>

// NOT IN USE

u32 getIndex(Dictionary* dict, i32 key) {
    for (int i = 0; i < dict->size; i++) {
        if (dict->keys[i] == key) {
            return i;
        }
    }
    return -1;
}

void* getValue(Dictionary* dict, i32 key) {
    u32 index = getIndex(dict, key);
    if (index == -1) {
        return NULL;
    } else {
        return dict->values[index];
    }
}

void insert(Dictionary* dict, i32 key, void* value) {
    u32 index = getIndex(dict, key);
    if (index == -1) {
        dict->keys[dict->size] = key;
        dict->values[dict->size] = &value;
    }
}

