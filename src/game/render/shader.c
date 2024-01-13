#include "../../include/glad/glad.h"
#include "shader.h"
#include "../io.h"
#include "../util/utils.h"

// Initialize empty shaders struct
Shaders shaders = {0};

// Function to return a shader struct using a vertex shader path and fragment shader path
Shader shaderCreate(const char* vertexShaderPath, const char* fragmentShaderPath) {
	// Variables to store success status and info log
    i32 success;
	char infoLog[512];

	// Read vertex shader file and check for validity
	File vertexShaderFile = ioFileRead(vertexShaderPath);
	if (!vertexShaderFile.isValid)
		ERROR_EXIT("Error reading vertex shader: %s\n", vertexShaderPath);

	// Create vertex shader, set the shader source, and compile it
	u32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char* const*)&vertexShaderFile, NULL);
	glCompileShader(vertexShader);
	// Get shader compilation status
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	// If shader compilation failed, exit the program and print the error log
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		ERROR_EXIT("Error compiling vertex shader.\n%s\n", infoLog);
	}

	// Read fragment shader file and check for validity
	File fragmentShaderFile = ioFileRead(fragmentShaderPath);
	if (!fragmentShaderFile.isValid)
		ERROR_EXIT("Error reading fragment shader: %s\n", fragmentShaderPath);

	// Create fragment shader, set the shader source, and compile it
	u32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char* const*)&fragmentShaderFile, NULL);
	glCompileShader(fragmentShader);
	// Get shader compilation status
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	// If shader compilation failed, exit the program and print the error log
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		ERROR_EXIT("Error compiling fragment shader.\n%s\n", infoLog);
	}

	// Create empty shader struct
	Shader shader = {0};

	// Create a shader program for id field of the shader struct
	shader.id = glCreateProgram();
	// Attach the vertex and fragment shaders
	glAttachShader(shader.id, vertexShader);
	glAttachShader(shader.id, fragmentShader);
	// Link the shader program
	glLinkProgram(shader.id);
	// Get program linking status
	glGetProgramiv(shader.id, GL_LINK_STATUS, &success);
	// If linking failed, exit the program and print the error log
	if (!success) {
		glGetProgramInfoLog(shader.id, 512, NULL, infoLog);
		ERROR_EXIT("Error linking shader.\n%s\n", infoLog);
	}

	// Delete the shaders as they are no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// Free the memory of the vertex and fragment shader files
	free(vertexShaderFile.data);
	free(fragmentShaderFile.data);

	return shader;
}

// Abstraction for binding a shader
void shaderBind(Shader* shader) {
	glUseProgram(shader->id);
}

// Abstraction for unbinding active shader program
void shaderUnbind(void) {
	glUseProgram(0);
}

// Abstraction for deleting a shader
void shaderDelete(Shader* shader) {
	glDeleteShader(shader->id);
}

// Abstraction for setting shader uniforms
void shaderUniform(Shader* shader, const char* uniform, f32* value) {
	glUniformMatrix4fv(glGetUniformLocation(shader->id, uniform), 1, GL_FALSE, value);
}

