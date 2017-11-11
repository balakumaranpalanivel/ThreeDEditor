
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
#include "CCamera.h"
#include "CModel.h"

// Macro for indexing vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

using namespace std;
GLuint shaderProgramID;

unsigned int teapot_vao = 0;
int width = 1600.0;
int height = 600.0;
GLuint loc1;
GLuint loc2;

// VBO Functions - click on + to expand
#pragma region VBO_FUNCTIONS

float grid_vertex_count = 0;
float *grid_vertex_points;

GLuint element_buffer_length = 0;
GLuint *element_buffer;

CShader ourShader;
CModel ourModel;

CCamera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f));

glm::mat4 projection = glm::perspective<float>(45.0, ((float)(SCR_WIDTH/2) / (float)(SCR_HEIGHT)), 0.1f, 100.0f);
//glm::mat4 projection = glm::ortho<float>(0, 400, 0, 400, -1, 1);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 view = camera.mView;

glm::vec3 translateVector = glm::vec3(0.0f, -1.75f, 0.0f);
glm::vec3 scaleVector = glm::vec3(0.2f, 0.2f, 0.2f);

//// render the loaded model
glm::mat4 model;
glm::mat4 orthoProjection;
glm::mat4 orthoView;

// it's a bit too big for our scene, so scale it down

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;

void display(){

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
	glClearColor (0.15f, 0.15f, 0.15f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ourShader.Use();

	glViewport(0, 0, SCR_WIDTH / 2, SCR_HEIGHT);
	ourShader.SetMat4("projection", projection);
	ourShader.SetMat4("view", view);
	ourShader.SetMat4("model", model);
	ourShader.SetVec3("viewPos", cameraPos);
	ourModel.Draw(ourShader);

	glViewport(SCR_WIDTH/2, 0, SCR_WIDTH / 2, SCR_HEIGHT);
	orthoProjection = glm::ortho<float>(-2.0f, 2.0f, -2.0f, 2.0f, 0.0f, 200.0f);

	ourShader.SetMat4("projection", orthoProjection);
	orthoView = glm::lookAt(
		glm::vec3(1.0f, 1.5f, 1.5f),
		glm::vec3(0, 0, 0),
		cameraUp);
	ourShader.SetMat4("view", orthoView);
	ourShader.SetMat4("model", model);
	ourShader.SetVec3("viewPos", cameraPos);
	ourModel.Draw(ourShader);
	// don't forget to enable shader before setting uniforms

	// view/projection transformations
	//ourShader.SetMat4("projection", projection);
	//ourShader.SetMat4("view", view);
	//ourShader.SetMat4("model", model);
	//ourModel.Draw(ourShader);

 //   glutSwapBuffers();
}
#define PI 3.14159265
static double  last_time = 0;
float radius = 10.0f;
double constant = PI / 180;
double curr_time;
double delta;
void updateScene() 
{	

	// Wait until at least 16ms passed since start of last frame (Effectively caps framerate at ~60fps)
	curr_time = timeGetTime();
	delta = (curr_time - last_time);
	if (delta > 16.0f)
	{
	
		/*float camX = sin(timeGetTime()) * radius * 0.3;
		float camZ = cos(timeGetTime()) * radius * 0.3;
		view = glm::lookAt(
			glm::vec3(camX, 0.0f, camZ),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);*/

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		model = glm::rotate<float>(model, 0.01, glm::vec3(0.0f, 1.0f, 0.0f));
		
		last_time = curr_time;
	
	}

	glutSwapBuffers();

	// Draw the next frame
	glutPostRedisplay();
}

void keyCB(unsigned char key, int x, int y)	/* called on key press */
{
	if (key == 'i')
	{
		/*projection = glm::perspective<float>(90.0, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);*/
		// Moves in the front direction
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate<float>(model, 30, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3();
	}

	float cameraSpeed = 0.05f; // adjust accordingly
	if ( key == 'w')
		cameraPos += cameraSpeed * cameraFront;

	if ( key == 's')
		cameraPos -= cameraSpeed * cameraFront;

	if ( key == 'd')
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if ( key == 'a')
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	glutPostRedisplay();
}

void mouse_callback(int xpos, int ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;

	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void init()
{
	// Create 3 vertices that make up a triangle that fits on the viewport 
	GLfloat vertices[] = {-1.0f, -1.0f, 0.0f, 1.0,
			1.0f, -1.0f, 0.0f, 1.0, 
			0.0f, 1.0f, 0.0f, 1.0};
	// Create a color array that identfies the colors of each vertex (format R, G, B, A)
	GLfloat colors[] = {0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f};
	// Set up the shaders
	//GLuint shaderProgramID = CompileShaders();
	ourShader.LoadShaders("../ThreeDEditor/src/shaders/modelLoadingVertexShader.txt",
		"../ThreeDEditor/src/shaders/modelLoadingFragmentShader.txt");

	// TODO: Load 3D Model from a seperate file
	ourModel.LoadModel("../Assets/Models/nanosuit/nanosuit.obj");
	model = glm::translate(model, translateVector); // translate it down so it's at the center of the scene
	model = glm::scale(model, scaleVector);

	// load teapot mesh into a vertex buffer array
	//generateObjectBufferTeapot ();
	
}

int main(int argc, char** argv) {

	// Set up the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutCreateWindow("Viewport Teapots");

	// Tell glut where the display function is
	glutDisplayFunc(display);
	glutIdleFunc(updateScene);
	glutKeyboardFunc(keyCB);		/* set window's key callback */
	glutMotionFunc(mouse_callback);

	// A call to glewInit() must be done after glut is initialized!
	glewExperimental = GL_TRUE; //for non-lab machines, this line gives better modern GL support
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











