#pragma once

#include "CScene.h"
#include "CRenderEngine.h"

class CSceneController
{
public:
	CSceneController();
	virtual ~CSceneController();

	// Use this function to initialise current scene
	virtual void InitialiseScene();

	//void Input(float delta);
	//void Update(float delta);
	void Render(CRenderEngine* renderEngine);

	CScene& GetScene();

private:

	// Private Copy constructor
	CSceneController(CSceneController& sceneController);
	void operator=(CSceneController& sceneController);

	CScene mScene;
};