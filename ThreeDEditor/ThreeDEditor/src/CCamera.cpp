#include "CCamera.h"
#include "CShader.h"

#include <iostream>

// TODO: Camera direction should be updated based on parent component transform
CCamera::CCamera(glm::vec3 cameraPosition, glm::vec3 lookAtPosition)
{
	mCameraPosition = cameraPosition;
	mCameraTarget = lookAtPosition;

	mCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	mCameraSpeed = 0.05f;

	mCameraDirection = glm::normalize(mCameraPosition - mCameraTarget);

	// Compute right direction in world space using 
	// world space up direction
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	mCameraRight = glm::normalize(glm::cross(up, mCameraDirection));

	mCameraUp = glm::normalize(glm::cross(mCameraDirection, mCameraRight));

	mView = glm::lookAt(mCameraPosition,
		glm::vec3(0.0f, 0.0f, 0.0f), mCameraUp);

	// TODO: Change proper perspective camera
	mProjection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}

void CCamera::Update()
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	mCameraDirection = glm::normalize(mCameraPosition - mCameraTarget);
	mCameraRight = glm::normalize(glm::cross(up, mCameraDirection));
	mCameraUp = glm::normalize(glm::cross(mCameraDirection, mCameraRight));
	mView = glm::lookAt(mCameraPosition,
		mCameraPosition + mCameraFront, mCameraUp);
	mProjection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

	glutPostRedisplay();
}
glm::mat4 CCamera::GetViewMatrix()
{
	return mView;
}

glm::mat4 CCamera::GetProjectionMatrix()
{
	return mProjection;
}

void CCamera::HandleKeypress(unsigned char key, int x, int y)
{
	int x1 = 5;
	std::cout << "Pressed Something\n";

	if (key == 'w')
	{
		mCameraPosition += mCameraSpeed * mCameraFront;
	}

	if (key == 's')
	{
		mCameraPosition -= mCameraSpeed * mCameraFront;
	}

	Update();
}

//void CCamera::ProcessKeyboardInput(unsigned char key, int x, int y)
//{
//	if (key == 'x') {
//		//Translate the base, etc.
//		std::cout << "KEY PRESSED \n";
//	}
//}