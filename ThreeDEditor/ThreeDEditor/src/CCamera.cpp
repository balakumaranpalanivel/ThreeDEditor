#include "CCamera.h"
#include "CShader.h"

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

	mView = glm::lookAt(cameraPosition, 
		glm::vec3(0.0f, 0.0f, 0.0f), mCameraUp);

	// TODO: Change proper perspective camera
	mProjection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

}

glm::mat4 CCamera::GetViewMatrix()
{
	return mView;
}

glm::mat4 CCamera::GetProjectionMatrix()
{
	return mProjection;
}

//void CCamera::ProcessKeyboardInput(unsigned char key, int x, int y)
//{
//	if (key == 'x') {
//		//Translate the base, etc.
//		std::cout << "KEY PRESSED \n";
//	}
//}