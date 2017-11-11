#include "CCamera.h"

CCamera::CCamera(glm::vec3 cameraPosition, glm::vec3 lookAtPosition)
{
	mCameraPosition = cameraPosition;
	mCameraTarget = lookAtPosition;

	mCameraDirection = glm::normalize(mCameraPosition - mCameraTarget);

	// Compute right direction in world space using 
	// world space up direction
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	mCameraRight = glm::normalize(glm::cross(up, mCameraDirection));

	mCameraUp = glm::normalize(glm::cross(mCameraDirection, mCameraRight));


	mView = glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), mCameraUp);
}
