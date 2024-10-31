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
    mat4 rotationMatrix = mat4(
        vec4(cos(rotation.y) * cos(rotation.z), -cos(rotation.y) * sin(rotation.z), sin(rotation.y), 0),
        vec4(cos(rotation.x) * sin(rotation.z) + sin(rotation.x) * sin(rotation.y) * cos(rotation.z), cos(rotation.x) * cos(rotation.z) - sin(rotation.x) * sin(rotation.y) * sin(rotation.z), -sin(rotation.x) * cos(rotation.y), 0),
        vec4(sin(rotation.x) * sin(rotation.z) - cos(rotation.x) * sin(rotation.y) * cos(rotation.z), sin(rotation.x) * cos(rotation.z) + cos(rotation.x) * sin(rotation.y) * sin(rotation.z), cos(rotation.x) * cos(rotation.y), 0),
        vec4(0, 0, 0, 1)
    );
    
    mat4 result = world * translation * scale * rotationMatrix;
    gl_Position = vec4(position, 1) * result;
    outColour = colour;
}