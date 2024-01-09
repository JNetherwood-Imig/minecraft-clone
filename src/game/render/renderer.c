#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "renderer.h"
#include "block.h"
#include "shader.h"
#include "../util/utils.h"
#include "../global.h"

Renderer renderer = {0};

static mat4 view, projection;

static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) {
	glViewport(0, 0, width, height);
}

static GLFWwindow* createWindow(u32 width, u32 height) {
	// Initialize GLFW
	if (!glfwInit()) {
		ERROR_EXIT("Failed to initialize GLFW\n");
	}

	// GLFW window hints (set set version to 4.6 core)
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// Create GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, "Minecraft Clone", NULL, NULL);
	if (!window) {
		glfwTerminate();
		ERROR_EXIT("Failed to create window\n");
	}

	glfwMakeContextCurrent(window);

	// Load OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		glfwDestroyWindow(window);
		ERROR_EXIT("Failed to load OpenGL\n");
	}

	// Enable VSYNC
	glfwSwapInterval(1);

	return window;
}

static void renderCameraUpdate(void) {
	vec3 cameraCenter;
	glm_vec3_add(global.camera.position, global.camera.front, cameraCenter);
	glm_lookat(global.camera.position, cameraCenter, global.camera.up, view);
}

Block dirt = {0};
BlockType dirt_t = {
	.atlasRow = 0,
	.atlasCollumn = 2
};

void renderInit(void) {
	renderer.width = 1280;
	renderer.height = 720;
	renderer.window = createWindow(renderer.width, renderer.height);

	glfwSetFramebufferSizeCallback(renderer.window, framebufferSizeCallback);

	dirt = createBlock(&dirt_t);

	glm_mat4_identity(view);
	glm_mat4_identity(projection);
}

void renderBegin(void) {
	glClearColor(0.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderDefault.id);
	glUniformMatrix4fv(glGetUniformLocation(shaderDefault.id, "view"), 1, GL_FALSE, view[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderDefault.id, "projection"), 1, GL_FALSE, projection[0]);
	glm_perspective(
		glm_rad(global.camera.fov),
		(f32)renderer.width / (f32)renderer.height,
		0.1f,
		100.0f,
		projection);
}

void renderMain(void) {
	renderBlock(&dirt, (vec3){ 0.0f, 0.0f, 0.0f });
	renderCameraUpdate();
}

void renderEnd(void) {
	glfwPollEvents();
	glfwSwapBuffers(renderer.window);
}

