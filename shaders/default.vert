#version 410 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTextureCoords;

out vec2 textureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(aPosition, 1.0);
	textureCoords = aTextureCoords;
}
