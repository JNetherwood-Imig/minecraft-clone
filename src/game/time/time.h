#pragma once

#include "../types.h"

typedef struct timeState {
	f32 last;
	f32 now;
	f32 delta;
} TimeState;

void timeInit(void);
void timeUpdate(void);
