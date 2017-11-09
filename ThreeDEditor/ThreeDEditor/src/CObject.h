#pragma once
#include <vector>
#include "CTransform.h"

class CRenderEngine;
class CShader;
class CComponent;

// TODO: Implement constructor

class CObject
{
public:
	CObject();
	virtual ~CObject() {}

	void AddChild(CObject* child);
	void AddComponent(CComponent* component);

	void RenderAll(CShader* shader, CRenderEngine* renderEngine);

	std::vector<CObject*> GetAllAttached();

	inline CTransform& GetTransform() { return mTransform; }
	
private:

	//void Input(float delta);
	//void Update(float delta);
	void Render(CShader* shader, CRenderEngine* renderEngine);

	std::vector<CObject*> mChildren;
	std::vector<CComponent*> mComponents;
	CTransform mTransform;

};