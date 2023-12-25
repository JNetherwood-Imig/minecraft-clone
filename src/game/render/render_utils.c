#include <glad/glad.h>
#include "../utils.h"
#include "../types.h"
#include "../io/io.h"

u32 renderCreateShader(const char* vertexShaderPath, const char* fragmentShaderPath) {
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

	u32 shader = glCreateProgram();
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		ERROR_EXIT("Error linking shader.\n%s\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	free(vertexShaderFile.data);
	free(fragmentShaderFile.data);

	return shader;
}
