#include "CScene.h"

CScene::CScene()
{

}

CScene::~CScene()
{
	for (unsigned int i = 0; i < mChildren.size(); i++)
	{
		if (mChildren[i])
		{
			delete mChildren[i];
		}
	}
}

void CScene::AddChild(CObject* object)
{
	mChildren.push_back(object);
}

//void CScene::InputAll(float delta)
//{
//	// Update Itself
//	Input(delta);
//
//	for (unsigned int i = 0; i < mChildren.size; i++)
//	{
//		// Update all its children
//		mChildren[i]->InputAll(delta);
//	}
//}

//void CScene::UpdateAll(float delta)
//{
//	// Update Itself
//	Update(delta);
//
//	for (unsigned int i = 0; i < mChildren.size; i++)
//	{
//		// Update all its children
//		mChildren[i]->UpdateAll(delta);
//	}
//}

void CScene::RenderAll(CShader* shader, CRenderEngine* renderEngine)
{
	// Update Itself
	Render(shader, renderEngine);

	for (unsigned int i = 0; i < mChildren.size(); i++)
	{
		// Update all its children
		mChildren[i]->RenderAll(shader, renderEngine);
	}
}

//void CScene::Input(float delta)
//{
//
//}
//
//void CScene::Update(float delta)
//{
//
//}

void CScene::Render(CShader* shader, CRenderEngine* renderEngine)
{

}

std::vector<CObject*> CScene::GetAllAttached()
{
	std::vector<CObject*> result;

	for (unsigned int i = 0; i < mChildren.size(); i++)
	{
		std::vector<CObject*> childObjects = mChildren[i]->GetAllAttached();
		result.insert(result.end(), childObjects.begin(), childObjects.end());
	}

	//result.push_back(this);
	return result;
}