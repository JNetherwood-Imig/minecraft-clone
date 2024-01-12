#pragma once

#include "../util/types.h"

// Define texture struct with a texture id and resolution info
typedef struct Texture {
	u32 id;
	u32 width;
	u32 height;
} Texture;

// Define textures struct to store a collection of textures
typedef struct Textures {
	Texture altas;
} Textures;

// Define external textures struct
extern Textures textures;

// Define texture utility function prototypes
Texture textureCreate(const char* filePath);
void textureBind(u32 texture);
void textureUnbind(void);
void textureDelete(Texture* texture);
