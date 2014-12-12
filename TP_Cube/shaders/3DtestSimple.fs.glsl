#version 330

in vec3 vPosition_vs;
in vec3 vColor;

out vec3 fFragColor;

void main() {
    fFragColor = vColor;
}
