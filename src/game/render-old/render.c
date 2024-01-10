#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "../render.h"
#include "../global.h"
#include "../camera.h"
#include "render_internal.h"
#include "shader.h"
#include "texture.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

RenderStateInternal state = {0};

static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) {
	// Set viewport to new window size
	glViewport(0, 0, width, height);
	// Update global window information to match
	global.render.width = width;
	global.render.height = height;
}

// Initialize necessary values for rendering
void renderInit(void) {
	// Set default resolution
	global.render.width = 1280;
	global.render.height = 720;
	// Create window
	global.render.window = renderInitWindow(global.render.width, global.render.height);
	// Set framebuffer size callback
	glfwSetFramebufferSizeCallback(global.render.window, framebufferSizeCallback);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	
	// Initialize shaders, textures, and a block model
	renderInitShaders(&state);
	renderInitTextures(&state);
	renderInitCube(&state);

	// Set polygon mode to fill
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Initialize identities for view and projection matricies
	glm_mat4_identity(state.view);
	glm_mat4_identity(state.projection);

}

// First calls of render loop
void renderBegin(void) {
	// Set clear color to cyan and clear color and depth buffers
	glClearColor(0.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Bind shader
	shaderBind(&shaders.shaderDefault);
	// Set shader uniforms
	glUniformMatrix4fv(glGetUniformLocation(shaders.shaderDefault.id, "view"), 1, GL_FALSE, state.view[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaders.shaderDefault.id, "projection"), 1, GL_FALSE, state.projection[0]);
	// Calculate perspective matrix
	glm_perspective(glm_rad(camera.fov), (f32)global.render.width / (f32)global.render.height, 0.01f, 1000.0f, state.projection);
}

// Update camera view
void renderCameraUpdate(void) {
	vec3 cameraCenter;
	glm_vec3_add(camera.position, camera.front, cameraCenter);
	glm_lookat(camera.position, cameraCenter, camera.up, state.view);
}

void renderMain() {
	static vec3 position = {0.0f, 0.0f, 0.0f};
	eboBind(&state.cubeEbo);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 4; k++) {
				position[0] = i;
				position[1] = k;
				position[2] = j;
				renderCube(position);
			}
		}
	}
}

// Last calls of render loop
void renderEnd(void) {
	glfwPollEvents();
	glfwSwapBuffers(global.render.window);
}

void renderClean(void) {
	vaoDelete(&state.cubeVao);
	vboDelete(&state.cubeVbo);
	eboDelete(&state.cubeEbo);
	glfwTerminate();
}

// Render a cube
void renderCube(vec3 position) {
	// Bind texture
	textureBind(state.texture.id);
	vaoBind(state.cubeVao);

	// Initialize identity matrix for cube and translate it to the correct position in the world
	glm_mat4_identity(state.model);
	glm_translate(state.model, position);
	
	// Set model matrix for the shader
	glUniformMatrix4fv(glGetUniformLocation(shaders.shaderDefault.id, "model"), 1, GL_FALSE, state.model[0]);

	// Draw indices and unbind vao
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	vaoUnbind();
}

