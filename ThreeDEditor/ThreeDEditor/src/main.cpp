
//Some Windows Headers (For Time, IO, etc.)
#include <windows.h>
#include <mmsystem.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "teapot.h" // teapot mesh
#include <string> 
#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "CShader.h"
#include "CModel.h"

// Macro for indexing vertex buffer
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

using namespace std;

CShader ourShader;
CModel ourModel;

// Camera
glm::mat4 projection = glm::perspective<float>(45.0, ((float)(SCR_WIDTH/2) / (float)(SCR_HEIGHT)), 0.1f, 100.0f);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), cameraUp);

glm::vec3 translateVector = glm::vec3(0.0f, -1.75f, 0.0f);
glm::vec3 scaleVector = glm::vec3(0.2f, 0.2f, 0.2f);

glm::mat4 model;
glm::mat4 orthoProjection;
glm::mat4 orthoView;

static double  last_time = 0;
float radius = 10.0f;
double curr_time;
double delta;
bool firstMouse = true;

/*
	Declaring initiali values for the Euler angles
	Not defining "roll" angle for camera
*/
// Yaw is rotation of the object about the Y axis (look left/right)
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.

// Pitch is rotation of the object about the x axis (look up/down)
float pitch = 0.0f;

void display(){

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
	glClearColor (0.15f, 0.15f, 0.15f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ourShader.Use();

	// Perspective projection viewport
	glViewport(0, 0, SCR_WIDTH / 2, SCR_HEIGHT);
	ourShader.SetMat4("projection", projection);
	ourShader.SetMat4("view", view);
	ourShader.SetMat4("model", model);
	ourShader.SetVec3("viewPos", cameraPos);
	ourModel.Draw(ourShader);

	// Orthographic projection viewport
	glViewport(SCR_WIDTH/2, 0, SCR_WIDTH / 2, SCR_HEIGHT);
	orthoProjection = glm::ortho<float>(-2.0f, 2.0f, -2.0f, 2.0f, -200.0f, 200.0f);
	ourShader.SetMat4("projection", orthoProjection);
	orthoView = glm::lookAt(
		glm::vec3(1.0f, 1.5f, 1.5f),
		glm::vec3(0, 0, 0),
		cameraUp);
	ourShader.SetMat4("view", orthoView);
	ourShader.SetMat4("model", model);
	ourShader.SetVec3("viewPos", cameraPos);
	ourModel.Draw(ourShader);
}

void updateScene() 
{	
	// Wait until at least 16ms passed since start of last frame (Effectively caps framerate at ~60fps)
	curr_time = timeGetTime();
	delta = (curr_time - last_time);
	if (delta > 16.0f)
	{
		// Update the view matrix to move the camera based on user input
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		// Constantly rotate the model about the Y axis
		model = glm::rotate<float>(model, 0.01, glm::vec3(0.0f, 1.0f, 0.0f));
		
		last_time = curr_time;
	}

	glutSwapBuffers();

	// Draw the next frame
	glutPostRedisplay();
}

/*
Keypress functionality that implementes
	1. Camera Flyover on pressing w, a, s, d keys
	2. Translates the Model on pressing of 'i'
*/
void keyCB(unsigned char key, int x, int y)
{
	// Translate the model on key press of 'i'
	// The model always moves in the front direction it is facing
	if (key == 'i')
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.2f));
	}

	// Camer flyover in the viewport
	float cameraSpeed = 0.05f;

	/*
		To move the camera front and back we add/subtract a "delta"
		obtained by (speed * cameraFrontDirection) to the current position 
		of the camera
	*/
	if ( key == 'w')
		cameraPos += cameraSpeed * cameraFront;

	if ( key == 's')
		cameraPos -= cameraSpeed * cameraFront;

	/*
		Similar to the front and back movement we add/subtract a "delta" to current
		camera position. But the direction of movement (left/right) is obtained
		by cross product of the cameraUp and cameraFront directions.
	*/
	if ( key == 'd')
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if ( key == 'a')
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	glutPostRedisplay();
}

/*
Mouse click and drag functionality
	1. Pans the camera by computing Pitch and Yaw
*/
void mouseCB(int xpos, int ypos)
{
	/*
		Save the mouse position of the last frame
		and compute the pitch and yaw based on the 
		mouse position in the current frame
	*/
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	
	/*
		Compute the offse - change in mouse position
		and update the last frame mouse positions to 
		current frame
	*/
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	/*
		Add a sensitivity factor to smoothen the offset
		angles
	*/
	float sensitivity = 0.1;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	/*
		Increase the yaw and pitch 
	*/
	yaw += xoffset;
	pitch += yoffset;

	/*
		Constraint the camera view angles
	*/
	if (pitch > 89.0f)
		pitch = 89.0f;

	if (pitch < -89.0f)
		pitch = -89.0f;

	/*
		Converting the Yaw and Pitch angles to camera front direction 
		vector
	*/
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void init()
{
	// Set up the shaders
	ourShader.LoadShaders("../ThreeDEditor/src/shaders/modelLoadingVertexShader.txt",
		"../ThreeDEditor/src/shaders/modelLoadingFragmentShader.txt");

	// Load 3D Model from a seperate file
	ourModel.LoadModel("../Assets/Models/nanosuit/nanosuit.obj");

	// translate it down so it's at the center of the scene
	model = glm::translate(model, translateVector);

	// scale the model to fit the viewports
	model = glm::scale(model, scaleVector);	
}

int main(int argc, char** argv) {

	// Set up the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutCreateWindow("ThreeDEditor");

	// Register GLUT Callback functions
	glutDisplayFunc(display);
	glutIdleFunc(updateScene);
	glutKeyboardFunc(keyCB);		
	glutMotionFunc(mouseCB);

	// A call to glewInit() must be done after glut is initialized!
	// for non-lab machines, this line gives better modern GL suppor
	glewExperimental = GL_TRUE; 
	GLenum res = glewInit();
	// Check for any errors
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	// Set up your objects and shaders
	init();

	// Begin infinite event loop
	glutMainLoop();

	return 0;
}











