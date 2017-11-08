#include "CComponent.h"
#include "CRenderEngine.h"

CComponent::~CComponent()
{

}

void CComponent::SetParent(CObject* parent)
{
	mParent = parent;
}

// Inheriting class should override
void CComponent::Render(CShader* shader, CRenderEngine* renderEngine)
{

}