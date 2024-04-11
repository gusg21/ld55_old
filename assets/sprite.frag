#version 330

in vec2 in_vUv;

uniform sampler2D u_texMain;

out vec4 out_vColor;

void main() {
    out_vColor = texture(u_texMain, in_vUv);
}
