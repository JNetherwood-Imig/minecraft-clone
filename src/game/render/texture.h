#pragma once

#include "../types.h"

typedef struct texture {
	u32 id;
	u32 resolution;
} Texture;

Texture textureCreate(const char* filePath);
void textureBind(u32 texture);
void textureUnbind(void);
void textureDelete(Texture* texture);
