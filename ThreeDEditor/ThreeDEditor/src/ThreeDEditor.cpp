#include "ThreeDEditor.h"
#include "CSceneController.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

ThreeDEditor::ThreeDEditor(unsigned int width, unsigned int height,
	glm::vec2 windowPosition) :	
	mWidth(width),
	mHeight(height),
	mWindowPosition(windowPosition)
{

}

ThreeDEditor::~ThreeDEditor()
{

}


void ThreeDEditor::CreateGLUTWindow(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(mWindowPosition.x, mWindowPosition.y);
	glutInitWindowSize(mWidth, mHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// TODO: Window Identifier handling
	glutCreateWindow("ThreeD Editor");
}

void ThreeDEditor::InitialiseGLUT()
{
	glewExperimental = GL_TRUE; //for non-lab machines, this line gives better modern GL support
	GLenum res = glewInit();
	// Check for any errors
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		exit(0);
	}
}

void ThreeDEditor::InitialiseScene()
{
	// TODO:
}

void ThreeDEditor::RegisterRenderCallback()
{
	glutDisplayFunc(CSceneController::RenderScene);
}

void ThreeDEditor::Run()
{
	glutMainLoop();
}