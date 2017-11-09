#include "CTransform.h"

glm::mat4 CTransform::GetParentMatrix() const
{
	if (mParent != 0 && mParent->HasChanged())
		mParentMatrix = mParent->GetTransformation();

	return mParentMatrix;
}

CTransform::CTransform(const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f),
	const glm::quat& rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f))
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;

	mInitialiseOld = false;
	mParent = 0;

	mParentMatrix = glm::mat4();
}

glm::mat4 CTransform::GetTransformation() const
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), mPosition);
	glm::mat4 rotationMatrix = glm::mat4_cast(mRotation);
	glm::mat4 scaleMatrix = glm::scale(mScale);

	glm::mat4 resultMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	return GetParentMatrix() * resultMatrix;
}

// TODO: WHY ???
bool CTransform::HasChanged()
{
	if (mParent != 0 && mParent->HasChanged())
		return true;

	if (mPosition != mOldPosition)
		return true;

	if (mRotation != mOldRotation)
		return true;

	if (mScale != mOldScale)
		return true;

	return false;
}

void CTransform::Rotate(const glm::quat& rotation)
{
	// TODO
}

void CTransform::LookAt(const glm::vec3& point, const glm::vec3& up)
{
	// TODO
}