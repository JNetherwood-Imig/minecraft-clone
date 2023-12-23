#pragma once

#include "../types.h"
#include "../input/input.h"

typedef struct configState {
	u32 keybinds[7];
} ConfigState;

void configInit(void);
void configKeyBind(InputKey key, const char* keyName);
