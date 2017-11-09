#include "CRenderEngine.h"
#include "CScene.h"
#include "CCamera.h"

CRenderEngine::CRenderEngine()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
}

CRenderEngine::~CRenderEngine()
{

}

void CRenderEngine::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mSceneToRender->RenderAll(mMainShader, this);

	// TODO: Lights
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_ONE);
	//glDepthMask(GL_FALSE);
	//glDepthFunc(GL_EQUAL);

	//for (unsigned int i = 0; i < m_lights.size(); i++)
	//{
	//	m_activeLight = m_lights[i];
	//	object->RenderAll(m_activeLight->GetShader(), this);
	//}

	//glDepthMask(GL_TRUE);
	//glDepthFunc(GL_LESS);
	//glDisable(GL_BLEND);
}