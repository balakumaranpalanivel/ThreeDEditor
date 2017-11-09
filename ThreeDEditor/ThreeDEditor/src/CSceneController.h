#pragma once

#include "CScene.h"
#include "CRenderEngine.h"

class CSceneController
{
public:


	// Use this function to initialise current scene
	static void InitialiseScene();

	//void Input(float delta);
	//void Update(float delta);
	static void RenderScene();


private:
	CSceneController();

	static CScene mScene;
	static CRenderEngine mRenderEngine;
};

