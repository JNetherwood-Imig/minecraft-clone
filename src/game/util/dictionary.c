#include "dictionary.h"
#include <cglm/types.h>
#include <string.h>
#include <stdio.h>

u32 getIndex(Dictionary* dict, char* key) {
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            return i;
        }
    }
    return -1;
}

u32 getValue(Dictionary* dict, char* key) {
    u32 index = getIndex(dict, key);
    if (index == -1) {
        return -1;
    } else {
        return dict->values[index];
    }
}

void insert(Dictionary* dict, char* key, vec3 value) {
    u32 index = getIndex(dict, key);
    if (index == -1) {
        strcpy(dict->keys[dict->size], key);
        dict->values[dict->size] = value;
    }
}

void printDictionary(Dictionary* dict) {
    for (int i = 0; i < dict->size; i++) {
        printf("%s: %d\n", dict->keys[i], dict->values[i]);
    }
}
