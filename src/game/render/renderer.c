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

static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) {
	glViewport(0, 0, width, height);
	renderer.width = width;
	renderer.height = height;
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
	glm_lookat(camera.position, cameraCenter, camera.up, renderer.state.view.raw);
}

Chunk chunk;

void renderInit(void) {
	renderer.width = 1280;
	renderer.height = 720;
	renderer.window = createWindow(renderer.width, renderer.height);
	shaders.shaderDefault = shaderCreate("shaders/default.vert", "shaders/default.frag");

	chunk = createChunk((vec3s){{0.0f, 0.0f, 0.0f}});

	glfwSetFramebufferSizeCallback(renderer.window, framebufferSizeCallback);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	shaderBind(&shaders.shaderDefault);

	renderer.state.view = glms_mat4_identity();
	renderer.state.projection = glms_mat4_identity();
}

void renderBegin(void) {
	glClearColor(0.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shaderUniform(&shaders.shaderDefault, "view", renderer.state.view.raw[0]);
	shaderUniform(&shaders.shaderDefault, "projection", renderer.state.projection.raw[0]);
	glm_perspective(
		glm_rad(camera.fov),
		(f32)renderer.width / (f32)renderer.height,
		0.1f,
		100.0f,
		renderer.state.projection.raw);
}

void renderMain(void) {
	renderChunk(&chunk);
	renderCameraUpdate();
}

void renderEnd(void) {
	glfwPollEvents();
	glfwSwapBuffers(renderer.window);
}

