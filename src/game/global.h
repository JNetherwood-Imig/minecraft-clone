#pragma once

#include "render/render.h"
#include "input/input.h"
#include "config/config.h"
#include "time/time.h"
#include "camera/camera.h"

typedef struct global {
	RenderState render;
	InputState input;
	ConfigState config;
	TimeState time;
	Camera camera;
} Global;

extern Global global;
