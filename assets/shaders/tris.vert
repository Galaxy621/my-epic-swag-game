#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;

layout(location = 0) out vec3 outColour;

layout (row_major) uniform UniformData {
    mat4 world;
    mat4 translation;
    mat4 scale;
    vec3 rotation;
};

void main() {
    mat4 rotX = mat4(
        1, 0, 0, 0,
        0, cos(rotation.x), -sin(rotation.x), 0,
        0, sin(rotation.x), cos(rotation.x), 0,
        0, 0, 0, 1
    );

    mat4 rotY = mat4(
        cos(rotation.y), 0, sin(rotation.y), 0,
        0, 1, 0, 0,
        -sin(rotation.y), 0, cos(rotation.y), 0,
        0, 0, 0, 1
    );

    mat4 rotZ = mat4(
        cos(rotation.z), -sin(rotation.z), 0, 0,
        sin(rotation.z), cos(rotation.z), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );

    mat4 rotationMatrix = rotZ * rotY * rotX;
    mat4 result = world * translation * scale * rotationMatrix;
    gl_Position = vec4(position, 1) * result;
    outColour = colour;
}