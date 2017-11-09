#pragma once

#include "CCamera.h"

class CScene;
class CShader;

// TODO: Lights
class CRenderEngine
{
public:
	CRenderEngine();
	virtual ~CRenderEngine();

	void Render();

	// Takes as input a camera and lights
	// it does not mean it has the camera, it just processess the location of camera
	inline void AddCamera(CCamera* camera) { mMainCamera = camera; }
	inline void AddShader(CShader* shader) { mMainShader = shader; }
	inline void AddScene(CScene* scene) { mSceneToRender = scene;  }

	inline CCamera& GetMainCamera() { return *mMainCamera; }

private:
	CCamera* mMainCamera;
	CShader* mMainShader;
	CScene* mSceneToRender;
};