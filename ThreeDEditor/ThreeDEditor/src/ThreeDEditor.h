#pragma once
#include <glm/glm.hpp>

class ThreeDEditor
{
public:
	ThreeDEditor(unsigned int width, unsigned int height, 
		glm::vec2 windowPosition);
	virtual ~ThreeDEditor();

	void CreateGLUTWindow(int argc, char** argv);
	void InitialiseGLUT();

	void InitialiseScene();
	void RegisterRenderCallback();

	void Run();

private:

	unsigned int mWidth;
	unsigned int mHeight;
	glm::vec2 mWindowPosition;
	
};