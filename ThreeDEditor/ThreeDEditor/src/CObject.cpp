#include "CObject.h"
#include "CComponent.h"
#include "CShader.h"
#include "CRenderEngine.h"

CObject::CObject()
{

}

void CObject::AddChild(CObject* child)
{
	mChildren.push_back(child);
}

void CObject::AddComponent(CComponent* component)
{
	mComponents.push_back(component);
	component->SetParent(this);
}

void CObject::RenderAll(CShader* shader, CRenderEngine* renderEngine)
{
	Render(shader, renderEngine);

	for (unsigned int i = 0; i < mChildren.size(); i++)
		mChildren[i]->RenderAll(shader, renderEngine);
}


void CObject::Render(CShader* shader, CRenderEngine* renderEngine)
{
	for (unsigned int i = 0; i <= mComponents.size(); i++)
	{
		mComponents[i]->Render(shader, renderEngine);
	}
}

std::vector<CObject*> CObject::GetAllAttached()
{
	std::vector<CObject*> result;

	for (unsigned int i = 0; i < mChildren.size(); i++)
	{
		std::vector<CObject*> childObjects = mChildren[i]->GetAllAttached();
		result.insert(result.end(), childObjects.begin(), childObjects.end());
	}

	result.push_back(this);

	return result;
}

