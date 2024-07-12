#version 330 core

uniform float gScale;
out vec4 FragColor;

void main() {
	FragColor = vec4(gScale * 1.0, gScale * 0.5 + 0.5, (gScale + 1.0) / 2.0, 1.0);
}
