#pragma once

#include <cglm/types-struct.h>
#include "../util/dictionary.h"
#include "../util/list.h"

typedef enum faces {
	BLOCK_FACE_FRONT,
	BLOCK_FACE_BACK,
	BLOCK_FACE_LEFT,
	BLOCK_FACE_RIGHT,
	BLOCK_FACE_TOP,
	BLOCK_FACE_BOTTOM
} BlockFace;

typedef struct faceData {
    vec3s vertices[4];
    vec2s uvs[4];
} FaceData;

typedef struct faceDataRaw {
    Dictionary faces;
} FaceDataRaw;

extern FaceDataRaw faceDataRaw;
