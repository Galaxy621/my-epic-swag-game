#version 410 core

layout(location = 0) in vec3 inColour;

layout(location = 0) out vec4 colour;

void main() {
    colour = vec4(1, 1, 1, 1);
    colour.rgb = inColour;
}