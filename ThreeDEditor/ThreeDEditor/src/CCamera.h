#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CCamera
{
public:
	//Constructor
	CCamera(glm::vec3 cameraPosition, glm::vec3 lookAtPosition);

	// Position of the camera
	glm::vec3 mCameraPosition;

	// Point which the camera is looking at
	glm::vec3 mCameraTarget;

	// Direction of the camera which is essentially the vector subtraction of
	// CameraPosition and CameraTarget.
	// TODO: Since camera points toward -ve Z, direction should be towards +ve Z. WHY?
	glm::vec3 mCameraDirection;

	// Up Vector
	glm::vec3  mCameraUp;

	// Right Direction - world space
	glm::vec3 mCameraRight;

	// LookAt matrix of the camera to transform world co-ordinates into view space
	glm::mat4 mView;

};