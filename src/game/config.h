#pragma once

#include "types.h"
#include "input.h"

typedef struct configState {
	u32 keybinds[7];
} ConfigState;

extern ConfigState config;

void configInit(void);
void configKeyBind(InputKey key, const char* keyName);
