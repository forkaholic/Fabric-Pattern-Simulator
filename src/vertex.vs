#version 330 core
layout (location = 0) in vec3 Position;
uniform float gScale;
uniform mat4 gTranslation;

void main() {
	gl_Position = gTranslation * vec4(Position.x + gScale, Position.y, Position.z, 1.0);
	
