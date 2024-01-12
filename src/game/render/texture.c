#include <glad/glad.h>
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Initialize empty textures struct
Textures textures = {0};

// Abstraction for binding a texture
void textureBind(u32 texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
}

// Abstraction for unbinding active texture
void textureUnbind(void) {
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Abstraction for deleting texture
void textureDelete(Texture* texture) {
	glDeleteTextures(1, &texture->id);
}

// Function that returns a texture struct given a file path
Texture textureCreate(const char* filePath) {

	// Initializes empty texture struct
	Texture texture = {0};

	// Generates texture and stores it in the texture id,
	// then binds the texture
	glGenTextures(1, &texture.id);
	textureBind(texture.id);

	// Sets texure wrapping parameters and mipmaping to nearest
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load data from file using stb_image
	i32 width, height, channels;
	unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

	// If the texture was successfully loaded,
	// set the texture image and generate the mipmaps,
	// then set the texture resolution and free the data
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		texture.width = width;
		texture.height = height;
		stbi_image_free(data);
	// If the texture was not successfully loaded,,
	// print an error
	} else {
		printf("Failed to load texture\n");
	}

	// Unbind texture
	textureUnbind();
	
	return texture;
}

