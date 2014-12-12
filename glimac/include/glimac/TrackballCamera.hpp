#pragma once
#include <glimac/glm.hpp>

class TrackballCamera{

private:

	float m_fDistance,
		  m_fAngleX,
		  m_fAngleY;

public:

//---------------------------CONSTRUCTOR-------------------------------------

	TrackballCamera(float distance = 20, float angleX = 0, float angleY = 0);

//----------------------------FUNCTIONS--------------------------------------

	//déplacement :
	void moveFront(float distance);
	void rotateLeft(float angleY);
	void rotateUp(float angleX);

	//calcul :
	glm::mat4 getViewMatrix() const;

};