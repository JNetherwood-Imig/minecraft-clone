#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/struct.h>
#include "../renderer.h"
#include "shader.h"
#include "chunk.h"
#include "../camera.h"
#include "../util/utils.h"
#include <stdio.h>

// Initialize empty renderer struct
Renderer renderer = {0};

// GLFW framebuffer size callback function to handle window resizing
static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) {
	// Set glViewport to the new window size
	glViewport(0, 0, width, height);
	// Update renderer window information
	// which is used for calculating the view matrix aspect ratio
	renderer.width = width;
	renderer.height = height;
}

// Function for creating a new GLFW window and initializing OpenGL
static GLFWwindow* createWindow(u32 width, u32 height) {
	// Initialize GLFW and check for errors
	if (!glfwInit()) {
		ERROR_EXIT("Failed to initialize glfw\n");
	}

	// Set window hints to use OpenGL version 4.1 Core (Necessary for Mac support)
	// and enable OpenGL forward compatability if MacOS is detected
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// Create a new GLFW window and check for errors
	GLFWwindow* window = glfwCreateWindow(width, height, "Minecraft Clone", NULL, NULL);
	if (!window) {
		glfwTerminate();
		ERROR_EXIT("Error creating window\n");
	}
	// Set window as the current OpenGL context
	glfwMakeContextCurrent(window);

	// Initialize OpenGL using glad to load function pointers
	//  and check for errors
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		ERROR_EXIT("Failed to load OpenGL\n");
	}

	// Enable/disable VSYNC
	static bool vsync = true;
	glfwSwapInterval(vsync);

	// Print some OpenGL info
	printf("Vendor: 	%s\n", glGetString(GL_VENDOR));
	printf("Renderer: 	%s\n", glGetString(GL_RENDERER));
	printf("Version: 	%s\n", glGetString(GL_VERSION));

	return window;
}

// Function to update the view matrix using the camera position
static void renderCameraUpdate(void) {
	vec3s cameraCenter = glms_vec3_add(camera.position, camera.front);
	renderer.state.view = glms_lookat(camera.position, cameraCenter, camera.up);
}

// Initalize a temporary chunk
Chunk chunk;

// Function called at the beginning of the program
// to set up the renderer and basic OpenGL functionality
void renderInit(void) {
	// Initialize renderer window size
	renderer.width = 1280;
	renderer.height = 720;
	// Create renderer window
	renderer.window = createWindow(renderer.width, renderer.height);
	// Create and bind the default shader,
	shaders.shaderDefault = shaderCreate("shaders/default.vert", "shaders/default.frag");
	shaderBind(&shaders.shaderDefault);
	
	// Create chunk texture from texture atlas
	textures.altas = textureCreate("assets/atlas.png");

	// Create the chunk at position 0, 0, 0,
	chunk = createChunk((vec3s){{0.0f, 0.0f, 0.0f}});

	// Set the GLFW framebuffer size callback function
	glfwSetFramebufferSizeCallback(renderer.window, framebufferSizeCallback);

	// Enable OpenGL depth test and backface culling,
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	// Set an identity matrix for the view and projection matrices
	renderer.state.view = glms_mat4_identity();
	renderer.state.projection = glms_mat4_identity();
}

// First stage in render loop
void renderBegin(void) {

	// Set color buffer clear color
	// and clear color and depth buffers
	glClearColor(0.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Set shader uniforms for view and projection matrices
	shaderUniform(&shaders.shaderDefault, "view", renderer.state.view.raw[0]);
	shaderUniform(&shaders.shaderDefault, "projection", renderer.state.projection.raw[0]);

	// Update projection matrix using glms_perspective()
	renderer.state.projection  = glms_perspective(
		glm_rad(camera.fov), 
		(f32)renderer.width / (f32)renderer.height, 
		0.01f, 1000.0f);
}

// Main portion of render loop
void renderMain(void) {
	renderChunk(&chunk);
	renderCameraUpdate();
}

// Final calls of render loop
void renderEnd(void) {
	glfwPollEvents();
	glfwSwapBuffers(renderer.window);
}

// Clean up renderer and terminate GLFW
void renderTerminate(void) {
	shaderDelete(&shaders.shaderDefault);
	glfwTerminate();
}
