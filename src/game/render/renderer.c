#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <cglm/struct/mat4.h>
#include "../renderer.h"
#include "shader.h"
#include "chunk.h"
#include "../camera.h"
#include "../util/utils.h"

Renderer renderer = {0};

static mat4 view, projection;

static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) {
	glViewport(0, 0, width, height);
}

static GLFWwindow* createWindow(u32 width, u32 height) {
	if (!glfwInit()) {
		ERROR_EXIT("Failed to initialize glfw\n");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	GLFWwindow* window = glfwCreateWindow(width, height, "Minecraft Clone", NULL, NULL);
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

static void renderCameraUpdate(void) {
	vec3 cameraCenter;
	glm_vec3_add(camera.position, camera.front, cameraCenter);
	glm_lookat(camera.position, cameraCenter, camera.up, view);
}

Chunk chunk;

void renderInit(void) {
	renderer.width = 1280;
	renderer.height = 720;
	renderer.window = createWindow(renderer.width, renderer.height);

	chunk = createChunk((vec3s){{0.0f, 0.0f, 5.0f}});

	glfwSetFramebufferSizeCallback(renderer.window, framebufferSizeCallback);

	shaderBind(&shaders.shaderDefault);

	glm_mat4_identity(view);
	glm_mat4_identity(projection);
}

void renderBegin(void) {
	glClearColor(0.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shaderUniform(&shaders.shaderDefault, "view", view[0]);
	shaderUniform(&shaders.shaderDefault, "projection", projection[0]);
	glm_perspective(
		glm_rad(camera.fov),
		(f32)renderer.width / (f32)renderer.height,
		0.1f,
		100.0f,
		projection);
}

void renderMain(void) {
	renderChunk(&chunk, &shaders.shaderDefault);
	renderCameraUpdate();
}

void renderEnd(void) {
	glfwPollEvents();
	glfwSwapBuffers(renderer.window);
}

