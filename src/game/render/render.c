#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "../render.h"
#include "../global.h"
#include "../camera.h"
#include "render_internal.h"
#include "shader.h"

RenderStateInternal state = {0};

static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) {
	glViewport(0, 0, width, height);
}

void renderInit(void) {
	global.render.width = 1280;
	global.render.height = 720;
	global.render.window = renderInitWindow(global.render.width, global.render.height);
	glfwSetFramebufferSizeCallback(global.render.window, framebufferSizeCallback);
	glEnable(GL_DEPTH_TEST);
	
	renderInitShaders(&state);
	renderInitTextures(&state);
	renderInitCube(&state);

	bool wireframe = false;

	glPolygonMode(GL_FRONT_AND_BACK, wireframe? GL_LINE : GL_FILL);

	glm_mat4_identity(state.view);
	glm_mat4_identity(state.projection);

}

void renderBegin(void) {
	glClearColor(0.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaders.shaderDefault);
	glUniformMatrix4fv(glGetUniformLocation(shaders.shaderDefault, "view"), 1, GL_FALSE, state.view[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaders.shaderDefault, "projection"), 1, GL_FALSE, state.projection[0]);
	glm_perspective(glm_rad(camera.fov), (f32)global.render.width / (f32)global.render.height, 0.01f, 1000.0f, state.projection);
}

void renderCameraUpdate(void) {
	vec3 cameraCenter;
	glm_vec3_add(camera.position, camera.front, cameraCenter);
	glm_lookat(camera.position, cameraCenter, camera.up, state.view);
}

void renderEnd(void) {
	glfwPollEvents();
	glfwSwapBuffers(global.render.window);
}

void renderCube(vec3 position) {

	glBindTexture(GL_TEXTURE_2D, state.texture);
	glBindVertexArray(state.cubeVao);

	glm_mat4_identity(state.model);
	glm_translate(state.model, position);
	
	glUniformMatrix4fv(glGetUniformLocation(shaders.shaderDefault, "model"), 1, GL_FALSE, state.model[0]);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

