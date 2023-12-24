#pragma once

#include <cglm/vec3.h>
#include "../types.h"

typedef struct camera {
	f32 speed;
	f32 fov;
	f32 yaw;
	f32 pitch;
	vec3 position;
	vec3 front;
	vec3 forward;
	vec3 right;
	vec3 up;
} Camera;

void cameraInit(void);
void cameraUpdate(void);
