#pragma once

#include "CObject.h"
#include "CShader.h"

class CRenderEngine;

// TODO: Transform
class CComponent
{
public:
	virtual ~CComponent();

	virtual void Render(CShader* shader, CRenderEngine* renderEngine);

	void SetParent(CObject* parent);

	// We need parents location to render the new component
	// GetTransform
	// GetTransform

private:
	CObject* mParent;

};