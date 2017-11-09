#pragma once
#include "CComponent.h"
#include "CModel.h"

class CSimpleRenderer :public CComponent
{
public:
	CSimpleRenderer(CModel* model)
	{
		mModel = model;
	}

	virtual ~CSimpleRenderer()
	{ }

	virtual void Render(CShader* shader, CRenderEngine* renderingEngine)
	{
		shader->Use();
		shader->UpdateUniforms(GetTransform(), renderingEngine);
		mModel->Render(shader);
	}

private:
	CModel *mModel;
};