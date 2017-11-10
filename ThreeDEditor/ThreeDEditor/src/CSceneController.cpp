#include "CSceneController.h"
#include "CSimpleRenderer.h"

CScene CSceneController::mScene;
CShader* CSceneController::ourShader;
CRenderEngine* CSceneController::mRenderEngine;

CSceneController::CSceneController()
{
}


void CSceneController::InitialiseScene()
{
	mRenderEngine = new CRenderEngine();


	CObject* masterChief = new CObject();
	//masterChief->AddComponent(new CSimpleRenderer(new CModel("../Assets/Models/nanosuit/nanosuit.obj")));
	masterChief->AddComponent(new CSimpleRenderer(new CModel("../Assets/Models/nanosuit/nanosuit.obj")));
	masterChief->GetTransform().SetPos(glm::vec3(0.0f, -3.0f, 0.0f));
	masterChief->GetTransform().SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	//masterChief->AddComponent(camera);
	
	CObject* cameraObject = new CObject();
	CCamera* camera = new CCamera(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	cameraObject->AddComponent(camera);
	mRenderEngine->AddCamera(camera);

	mScene.AddToScene(masterChief);
	mScene.AddToScene(cameraObject);

	ourShader = new CShader("../ThreeDEditor/src/shaders/modelLoadingVertexShader.txt",
		"../ThreeDEditor/src/shaders/modelLoadingFragmentShader.txt");
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
	mScene.RenderAll(ourShader, mRenderEngine);
	glutSwapBuffers();
}

void CSceneController::UpdateScene()
{
	mScene.RenderAll(ourShader, mRenderEngine);
}

void CSceneController::HandleKeypress(unsigned char key, int x, int y)
{
	mRenderEngine->GetMainCamera().HandleKeypress(key, x, y);
}
