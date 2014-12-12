#include "glimac/TrackballCamera.hpp"
#include <glimac/glm.hpp>

TrackballCamera::TrackballCamera(float distance, float angleX, float angleY) : m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY){
}

void TrackballCamera::moveFront(float distance){

	m_fDistance += distance;

}

void TrackballCamera::rotateLeft(float angleY){

	angleY = glm::radians(angleY);

	m_fAngleY += angleY;

}

void TrackballCamera::rotateUp(float angleX){

	angleX = glm::radians(angleX);
	m_fAngleX += angleX;

}

glm::mat4 TrackballCamera::getViewMatrix() const{
	glm::mat4 VMatrix;

	VMatrix = glm::translate(glm::mat4(), glm::vec3(0., 0., - m_fDistance));
	VMatrix = glm::rotate(VMatrix, m_fAngleX, glm::vec3(1, 0, 0));
	VMatrix = glm::rotate(VMatrix, m_fAngleY , glm::vec3(0, 1, 0));

	return VMatrix;
}