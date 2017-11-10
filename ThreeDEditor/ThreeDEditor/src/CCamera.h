#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "CComponent.h"

class CCamera : public CComponent
{
public:
	//Constructor
	CCamera(glm::vec3 cameraPosition, glm::vec3 lookAtPosition);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	void HandleKeypress(unsigned char key, int x, int y);

	void Update();

private:
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

	// Camera Front - To Move the camera front
	glm::vec3 mCameraFront;

	// LookAt matrix of the camera to transform world co-ordinates into view space
	glm::mat4 mView;

	// Projection matrix of the camera
	glm::mat4 mProjection;

	float mCameraSpeed;
	//// Process Keyboard Input
	//void ProcessKeyboardInput(unsigned char key, int x, int y);
};