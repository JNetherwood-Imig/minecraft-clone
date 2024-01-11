#pragma once

#include <cglm/types-struct.h>

typedef struct FaceData {
    vec3s vertices[4];
    vec2s* uvs;
} FaceData;

extern vec3s vertexData[6][4];
extern vec2s uvData[4];
