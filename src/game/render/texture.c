#include <glad/glad.h>
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void textureBind(u32 texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
}

void textureUnbind(void) {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void textureDelete(Texture* texture) {
	glDeleteTextures(1, &texture->id);
	free(texture);
}

Texture textureCreate(const char* filePath) {

	Texture texture = {0};

	glGenTextures(1, &texture.id);
	textureBind(texture.id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	i32 width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		texture.resolution = width;
		stbi_image_free(data);
	} else {
		printf("Failed to load texture\n");
	}

	textureUnbind();
	
	return texture;
}

