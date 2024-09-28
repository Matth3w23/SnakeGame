#version 330 core
out vec4 color;

uniform vec3 squareColour;

void main() {    
    color = vec4(squareColour, 1.0);
}  