#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include "../util/utils.h"
#include "../util/types.h"
#include "render_internal.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"

GLFWwindow *renderInitWindow(u32 width, u32 height) {
	if (!glfwInit()) {
		ERROR_EXIT("Failed to initialize glfw\n");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Minecraft Clone", NULL, NULL);
	if (!window) {
		glfwTerminate();
		ERROR_EXIT("Error creating window\n");
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		ERROR_EXIT("Failed to load OpenGL\n");
	}

	glfwSwapInterval(1);

	printf("Vendor: 	%s\n", glGetString(GL_VENDOR));
	printf("Renderer: 	%s\n", glGetString(GL_RENDERER));
	printf("Version: 	%s\n", glGetString(GL_VERSION));

	return window;
}

void renderInitCube(RenderStateInternal* state) {

	// Create array of vertices for cube
	 f32 vertices[] = {
	//   x      y      z  
		// Front face
		-0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

		// Back face
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,

		// Left face
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

		// Right face
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,

		// Top face
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

		// Bottom face
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
	};

	// Create array of texture coordinates
	f32 uvs[] = {
	//  u     v
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f

	};
    
    u32 indices[] = {
		// Front
        0, 1, 3,
        1, 2, 3,

		// Back
        4, 5, 7,
        5, 6, 7,

		// Left
        8, 9, 11,
        9, 10, 11,

		// Right
        12, 13, 15,
        13, 14, 15,

		// Top
        16, 17, 19,
        17, 18, 19,

		// Bottom
        20, 21, 23,
        21, 22, 23
    };

	// Create VAO
	vaoCreate(&state->cubeVao);

	// Create vertex vbo and set vertex position vao attribute
	vboCreate(&state->cubeVbo, vertices, sizeof(vertices), false);
	vaoAttrib(0, 3, 0, 0);

	// Create UV vbo and set texture coordinate vao attribute
	u32 uvVbo;
	vboCreate(&uvVbo, uvs, sizeof(uvs), false);
	vaoAttrib(1, 2, 0, 0);

	vboBind(&state->cubeVbo);
	eboCreate(&state->cubeEbo, indices, sizeof(indices), false);
	vaoUnbind();
	vboUnbind();
}

void renderInitShaders(RenderStateInternal* state) {
	shaders.shaderDefault = shaderCreate("shaders/default.vert", "shaders/default.frag");
}
void renderInitTextures(RenderStateInternal* state) {
	state->texture = textureCreate("assets/grass.png");
}

