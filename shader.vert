#version 400 core

#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPos;

layout(location = 0) out vec3 fragColor;

const vec3 color[3] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

void main() {
    gl_Position = vec4(inPos, 1.0);

    fragColor = color[gl_VertexID];
}
