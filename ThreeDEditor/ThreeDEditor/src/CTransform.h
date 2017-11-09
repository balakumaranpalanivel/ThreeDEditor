#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>

class CTransform
{
public:
	CTransform(const glm::vec3& pos, const glm::quat& rot, glm::vec3 scale);

	glm::mat4 GetTransformation() const;

	bool HasChanged();

	// TODO
	void Rotate(const glm::quat& rotation);

	void LookAt(const glm::vec3& point, const glm::vec3& up);

	inline glm::vec3& GetPos() { return mPosition; }
	inline const glm::vec3& GetPos() const { return mPosition; }
	inline glm::quat& GetRot() { return mRotation; }
	inline const glm::quat& GetRot() const { return mRotation; }
	inline glm::vec3 GetScale() const { return mScale; }

	inline void SetPos(const glm::vec3& pos) { mPosition = pos; }
	inline void SetRot(const glm::quat& rot) { mRotation = rot; }
	inline void SetScale(glm::vec3 scale) { mScale = scale; }
	inline void SetParent(CTransform* parent) { mParent = parent; }

private:

	glm::mat4 GetParentMatrix() const;

	glm::vec3 mPosition;
	glm::quat mRotation;
	glm::vec3 mScale;

	CTransform* mParent;
	mutable glm::mat4 mParentMatrix;

	// TODO: WHY??
	mutable glm::vec3 mOldPosition;
	mutable glm::quat mOldRotation;
	mutable glm::vec3 mOldScale;
	mutable bool mInitialiseOld;

};