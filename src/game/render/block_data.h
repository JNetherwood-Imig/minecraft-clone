#pragma once

#include <cglm/types.h>
#include "../util/dictionary.h"
#include "../util/list.h"

typedef struct faceData {
    vec3 vertices[4];
    vec2 uvs[4];
} FaceData;

typedef struct faceDataRaw {
    Dictionary faces;
} FaceDataRaw;
