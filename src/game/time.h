#pragma once

#include "util/types.h"

// Define time state struct for holding current time and time delta
typedef struct TimeState {
	f32 last;
	f32 now;
	f32 delta;
} TimeState;

// Create external time state object
extern TimeState time;

// Define function prototypes for initializing and updating time state data
void timeInit(void);
void timeUpdate(void);
