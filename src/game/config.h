#pragma once

#include "util/types.h"
#include "input.h"

// Create config state struct for storing keybind values in an array
typedef struct ConfigState {
	u32 keybinds[INPUT_KEY_ENUM_LENGTH];
} ConfigState;

// Create external config state
extern ConfigState config;

// Define function prototypes for initializing the config state and binding keys
void configInit(void);
void configKeyBind(InputKey key, const char* keyName);
