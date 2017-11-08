
#include "CSceneController.h"

CSceneController::CSceneController()
{

}

CSceneController::~CSceneController()
{

}

CSceneController::CSceneController(CSceneController& sceneController)
{

}

void CSceneController::operator=(CSceneController& CSceneController)
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

void CSceneController::Render(CRenderEngine* renderEngine)
{
	renderEngine->Render(&mScene);
}

CScene& CSceneController::GetScene()
{
	return mScene;
}