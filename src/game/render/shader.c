#include <glad/glad.h>
#include "shader.h"
#include "../io.h"
#include "../util/utils.h"

Shaders shaders = {0};

Shader shaderCreate(const char* vertexShaderPath, const char* fragmentShaderPath) {
    i32 success;
	char infoLog[512];

	File vertexShaderFile = ioFileRead(vertexShaderPath);
	if (!vertexShaderFile.isValid)
		ERROR_EXIT("Error reading vertex shader: %s\n", vertexShaderPath);

	u32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char* const*)&vertexShaderFile, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		ERROR_EXIT("Error compiling vertex shader.\n%s\n", infoLog);
	}

	File fragmentShaderFile = ioFileRead(fragmentShaderPath);
	if (!fragmentShaderFile.isValid)
		ERROR_EXIT("Error reading fragment shader: %s\n", fragmentShaderPath);

	u32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char* const*)&fragmentShaderFile, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		ERROR_EXIT("Error compiling fragment shader.\n%s\n", infoLog);
	}

	Shader shader = {0};

	shader.id = glCreateProgram();
	glAttachShader(shader.id, vertexShader);
	glAttachShader(shader.id, fragmentShader);
	glLinkProgram(shader.id);
	glGetProgramiv(shader.id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader.id, 512, NULL, infoLog);
		ERROR_EXIT("Error linking shader.\n%s\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	free(vertexShaderFile.data);
	free(fragmentShaderFile.data);

	return shader;
}

void shaderBind(Shader* shader) {
	glUseProgram(shader->id);
}

void shaderUnbind(void) {
	glUseProgram(0);
}

void shaderDelete(Shader* shader) {
	glDeleteShader(shader->id);
}

void shaderUniform(Shader* shader, const char* uniform, f32* value) {
	glUniformMatrix4fv(glGetUniformLocation(shader->id, uniform), 1, GL_FALSE, value);
}

