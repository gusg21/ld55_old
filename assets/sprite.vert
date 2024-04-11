#version 330

layout(location = 0) in vec3 in_vPos;
layout(location = 1) in vec2 in_vUv;

out vec2 out_vUv;

void main() {
    out_vUv = in_vUv;

    gl_Position = in_vPos;
}