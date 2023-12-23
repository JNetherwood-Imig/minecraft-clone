#version 410 core

out vec4 fragColor;
in vec2 textureCoords;

uniform sampler2D imageTexture;

void main() {
	fragColor = texture(imageTexture, textureCoords);
}
