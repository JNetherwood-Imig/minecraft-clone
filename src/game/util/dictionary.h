#include "types.h"
#include <cglm/types.h>

const u32 MAX_SIZE = 64;

typedef struct dictionary {
    char* keys[MAX_SIZE];
    vec3 values[MAX_SIZE];
    u32 size;
} Dictionary;

u32 getIndex(Dictionary* dict, char* key);
u32 getValue(Dictionary* dict, char* key);
void insert(Dictionary* dict, char* key, vec3 value);
void printDictionary(Dictionary* dict);