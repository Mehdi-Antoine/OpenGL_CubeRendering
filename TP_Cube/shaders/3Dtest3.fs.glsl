#version 330

in vec3 vPosition_vs;
in vec3 g_Color;
in vec3 vColor;


out vec3 fFragColor;

void main() {
    fFragColor = g_Color;//vec3(1,0,0);
    //fFragColor = vColor;//vec3(1,0,0);
}
