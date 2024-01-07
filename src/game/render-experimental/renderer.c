#include <glad/glad.h>
#include "../types.h"

static u32 texture;

void renderCube(void) {
    glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vao);

	glm_mat4_identity(state.model);
	glm_translate(state.model, (vec3){0, 0, 0});
	
	glUniformMatrix4fv(glGetUniformLocation(state.shaderDefault, "model"), 1, GL_FALSE, state.model[0]);

	glDrawElements(GL_TRIANGLES, 0, 36);
}