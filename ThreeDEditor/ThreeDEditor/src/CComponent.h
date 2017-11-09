#pragma once

#include "CObject.h"
#include "CShader.h"

class CTransform;
class CRenderEngine;

// TODO: Transform
class CComponent
{
public:
	virtual ~CComponent() {};

	virtual void Render(CShader* shader) {};

	inline void SetParent(CObject* parent) { mParent = parent;  };
	inline CTransform& GetTransform() { return mParent->GetTransform(); }
	inline const CTransform& GetTransform() const{ return mParent->GetTransform(); }

	// We need parents location to render the new component
	// GetTransform
	// GetTransform

private:
	CObject* mParent;

};