#pragma once

#include "CScene.h"
#include "CRenderEngine.h"

class CObject;

class CSceneController
{
public:


	// Use this function to initialise current scene
	static void InitialiseScene();

	//void Input(float delta);
	//void Update(float delta);
	static void RenderScene();

	static CScene mScene;
	static CRenderEngine mRenderEngine;

private:
	CSceneController();
};

