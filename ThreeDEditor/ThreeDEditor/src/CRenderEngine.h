#pragma once

#include "CCamera.h"
#include "CShader.h"

class CScene;

// TODO: Lights
class CRenderEngine
{
public:
	CRenderEngine();
	virtual ~CRenderEngine();

	void Render();

	// Takes as input a camera and lights
	// it does not mean it has the camera, it just processess the location of camera
	void AddCamera(CCamera* camera);
	void AddShader(CShader* shader);
	inline void AddScene(CScene* scene) { mSceneToRender = scene;  };

private:
	CCamera* mMainCamera;
	CShader* mMainShader;
	CScene* mSceneToRender;
};