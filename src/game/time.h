#pragma once

#include "util/types.h"

typedef struct timeState {
	f32 last;
	f32 now;
	f32 delta;
} TimeState;

extern TimeState time;

void timeInit(void);
void timeUpdate(void);
