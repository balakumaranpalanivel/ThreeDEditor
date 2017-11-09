
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

#include "ThreeDEditor.h"

// Macro for indexing vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

CCamera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

using namespace std;
GLuint shaderProgramID;

unsigned int teapot_vao = 0;
int width = 800.0;
int height = 600.0;
GLuint loc1;
GLuint loc2;

// VBO Functions - click on + to expand
#pragma region VBO_FUNCTIONS

float grid_vertex_count = 0;
float *grid_vertex_points;

GLuint element_buffer_length = 0;
GLuint *element_buffer;

void drawGrid(int nHalfSize)
{
	grid_vertex_count = pow((nHalfSize * 2) + 1, 2);
	grid_vertex_points = new float[grid_vertex_count*3];
	int j = 0;
	for (float x = -nHalfSize; x <= nHalfSize; x++)
	{
		for (float y = -nHalfSize; y <= nHalfSize; y++)
		{
			grid_vertex_points[j++] = x;
			grid_vertex_points[j++] = 0;
			grid_vertex_points[j++] = y;
		}
	}

	j = 0;
	int vertices_in_row = ((nHalfSize * 2) + 1);
	element_buffer_length = ((2 * pow(vertices_in_row, 2)) - (2 * vertices_in_row)) * 2;
	element_buffer = new GLuint[element_buffer_length];
	for (int i = 0; i <= (grid_vertex_count - vertices_in_row); i += vertices_in_row)
	{
		for (int k = i; k <= (i + vertices_in_row) - 1; k++)
		{
			if (k != (i + vertices_in_row) - 1)
			{
				// 0 to 1
				element_buffer[j++] = k;
				element_buffer[j++] = k + 1;
			}

			if (k + vertices_in_row < grid_vertex_count)
			{
				// 0 to 3
				element_buffer[j++] = k;
				element_buffer[j++] = k + vertices_in_row;
			}
		}
	}
}



#pragma endregion VBO_FUNCTIONS

CShader ourShader;
CModel ourModel;

void display(){

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
	glClearColor (0.5f, 0.5f, 0.5f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram (shaderProgramID);

	// don't forget to enable shader before setting uniforms
	ourShader.Use();

	// view/projection transformations
	glm::mat4 projection = glm::perspective<float>(45.0, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.mView;
	ourShader.SetMat4("projection", projection);
	ourShader.SetMat4("view", view);

	//// render the loaded model
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
	ourShader.SetMat4("model", model);
	ourModel.Draw(ourShader);

    glutSwapBuffers();
}


void init()
{
	// Set up the shaders
	//GLuint shaderProgramID = CompileShaders();
	ourShader.LoadShaders("../ThreeDEditor/src/shaders/modelLoadingVertexShader.txt",
		"../ThreeDEditor/src/shaders/modelLoadingFragmentShader.txt");

	// TODO: Load 3D Model from a seperate file
	//ourModel.LoadModel("../Assets/Models/nanosuit/nanosuit.obj");

	ourModel.LoadModel("../Assets/Models/crate/Crate1.3ds");

	
}

int main(int argc, char** argv) {

	// Set up the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("Viewport Teapots");

	// Tell glut where the display function is
	glutDisplayFunc(display);

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
	

	//ThreeDEditor threeDEditor(SCR_WIDTH, SCR_HEIGHT, glm::vec2(-1, -1));

	//threeDEditor.CreateGLUTWindow(argc, argv);
	//threeDEditor.InitialiseGLUT();
	//threeDEditor.RegisterRenderCallback();

	//threeDEditor.InitialiseGLUT();

	//threeDEditor.Run();

	//return 0;
}











