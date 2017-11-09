#pragma once
#include <vector>

#include "CObject.h"
#include "CShader.h"
#include "CRenderEngine.h"

// TODO: Render Grid here
class CScene
{
public:
	CScene();
	virtual ~CScene();

	//void AddChild(CObject* object);

	// Methods to handle input for self and all its children
	//void InputAll(float delta);
	//void UpdateAll(float delta);
	void RenderAll(CShader* shader, CRenderEngine* renderEngine);

	//std::vector<CObject*> GetAllAttached();

	inline void AddToScene(CObject* child) { mRoot.AddChild(child); };

private:
	// Methods to handle input for self
	//void Input(float delta);
	//void Update(float delta);
	// TODO: Scene should render itself a grid 
	void Render(CShader* shader, CRenderEngine* renderEngine);

	CObject mRoot;

};