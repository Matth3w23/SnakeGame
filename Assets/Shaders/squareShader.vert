#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(aPos, 1.0, 1.0);
	//gl_Position = vec4(aPos, 1.0, 1.0);
}