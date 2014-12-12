#version 330

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs;
out vec3 vColor;

mat4 billboarding(bool spherical){
	mat4 modelView = uMVMatrix; 

	// Première colonne. 
	modelView[0][0] = 1.0; 
	modelView[0][1] = 0.0; 
	modelView[0][2] = 0.0; 

	if(spherical){
		// Deuxième colonne. 
		modelView[1][0] = 0.0; 
		modelView[1][1] = 1.0; 
		modelView[1][2] = 0.0; 
	}
	 
	// Troisème colonne. 
	modelView[2][0] = 0.0; 
	modelView[2][1] = 0.0; 
	modelView[2][2] = 1.0; 

	return modelView;
}

void main() {

	//Conversion en coordonées homogènes
	vec4 homogen_position = vec4(aPosition, 1);

	mat4 modelView = uMVMatrix; 

	vec4 positionView = modelView * homogen_position;

	vPosition_vs = vec3(positionView);

	gl_Position = uPMatrix * positionView;

    vColor = aColor;
}
