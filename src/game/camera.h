#pragma once

#include "../include/cglm/types-struct.h"
#include "util/types.h"

// Camera struct to store all camera data
typedef struct Camera {
	f32 speed;
	f32 fov;
	f32 yaw;
	f32 pitch;
	vec3s position;
	vec3s front;
	vec3s forward;
	vec3s right;
	vec3s up;
} Camera;

// Create external camera object
extern Camera camera;

// Define function prototypes for initializing and updating camera data
void cameraInit(void);
void cameraUpdate(void);
