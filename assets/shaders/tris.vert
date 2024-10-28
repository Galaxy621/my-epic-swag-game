#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;

layout(location = 0) out vec3 outColour;

uniform UniformData {
    float gameTime;
};

void main() {
    gl_Position.xyz = position * abs(sin(gameTime));
    gl_Position.w = 1.0;

    outColour = colour;

}