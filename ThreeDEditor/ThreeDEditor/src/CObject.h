#pragma once
#include <vector>

class CRenderEngine;
class CShader;

// TODO: Implement constructor

class CObject
{
public:
	CObject();
	virtual ~CObject() {}

	void AddChild(CObject* child);
	void RenderAll(CShader* shader, CRenderEngine* renderEngine);

	std::vector<CObject*> GetAllAttached();
	
private:

	//void Input(float delta);
	//void Update(float delta);
	void Render(CShader* shader, CRenderEngine* renderEngine);

	std::vector<CObject*> mChildren;


};