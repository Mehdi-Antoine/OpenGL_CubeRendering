#version 330

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs;
out vec3 vNormal_vs;
out vec2 vTexCoords;

void main() {

	//Conversion en coordonées homogènes
	vec4 homogen_position = vec4(aPosition, 1);
	vec4 homogen_normal = vec4(aNormal, 0);

	//Calcul des valeurs de sortie avec la MV et la NormalMatrix
	vPosition_vs = vec3(uMVMatrix * homogen_position);
	vNormal_vs = vec3(uNormalMatrix * homogen_normal);
	vTexCoords = aTexCoords;

	//Calcul de gl_position avec la MVP
    gl_Position = uMVPMatrix * homogen_position;    
}
