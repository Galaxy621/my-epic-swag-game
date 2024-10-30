#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;

layout(location = 0) out vec3 outColour;

uniform UniformData {
    float gameTime;

    float windowWidth;
    float windowHeight;
};

void main() {
    gl_Position.x = position.x * abs(sin(gameTime));
    gl_Position.y = position.y * abs(sin(gameTime));

    gl_Position.w = 1.0;

    outColour = colour;

}