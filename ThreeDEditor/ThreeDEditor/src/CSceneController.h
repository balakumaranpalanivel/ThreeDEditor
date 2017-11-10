#pragma once

#include "CScene.h"
#include "CRenderEngine.h"

class CObject;
// TODO: Friend Function

class CSceneController
{
public:

	CSceneController();

	// Use this function to initialise current scene
	static void InitialiseScene();

	//void Input(float delta);
	//void Update(float delta);
	static void RenderScene();
	static void UpdateScene();

	static void HandleKeypress(unsigned char key, int x, int y);

	static CScene mScene;
	static CShader* ourShader;
	static CRenderEngine* mRenderEngine;
};

