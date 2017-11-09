
#include "CSceneController.h"

CRenderEngine CSceneController::mRenderEngine;
CScene CSceneController::mScene;

CSceneController::CSceneController()
{

}


void CSceneController::InitialiseScene()
{

}

//void CSceneController::Input(float delta)
//{
//	mScene.InputAll(delta);
//}
//
//void CSceneController::Update(float delta)
//{
//	mScene.UpdatAll(delta);
//}

void CSceneController::RenderScene()
{
	mRenderEngine.AddScene(&CSceneController::mScene);

	// Extract shader from game object in scene

	
	// TODO - START RENDERING
	mRenderEngine.Render();
}
