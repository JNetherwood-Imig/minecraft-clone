#pragma once

#include <cglm/vec3.h>
#include "../types.h"

typedef struct camera {
	f32 speed;
	f32 fov;
	vec3 position;
	vec3 front;
	vec3 view;
	vec3 up;
	vec3 forward;
	vec3 right;
} Camera;

void cameraInit(void);
void cameraUpdate(void);
