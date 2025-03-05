#pragma once
#ifndef __TRANSFORM__H__
#define __TRANSFORM__H__

#include "../Math/Vector/Vector.h"
#include "../Math/Matrix/Matrix.h"

namespace DSM {

	class Transform
	{
	public:
		Transform() = default;
		Transform(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector3& scale);
		Transform(const Transform&) = default;
		Transform(Transform&&) = default;
		Transform& operator=(const Transform&) = default;
		Transform& operator=(Transform&&) = default;
		~Transform() = default;

		void setPosition(const Math::Vector3& position) noexcept;
		void setPosition(float x, float y, float z) noexcept;
		void setScale(const Math::Vector3& scale) noexcept;
		void setScale(float x, float y, float z) noexcept;

		Math::Vector3 getPosition() const noexcept;
		Math::Vector3 getScale() const noexcept;
		Math::Matrix4x4 getTranslateMatrix() const noexcept;
		Math::Matrix4x4 getScaleMatrix() const noexcept;
		Math::Matrix4x4 getRotateMatrix() const noexcept;
		Math::Matrix4x4 getRotateXMatrix() const noexcept;
		Math::Matrix4x4 getRotateYMatrix() const noexcept;
		Math::Matrix4x4 getRotateZMatrix() const noexcept;
		Math::Matrix4x4 getWorldMatrix() const noexcept;
		Math::Matrix4x4 getWorldInvTransposeMatrix() const noexcept;

		void Rotate(const Math::Vector3& eulerAnglesInRadian) noexcept;
		void Translate(const Math::Vector3& direction, float magnitude) noexcept;
		void LookAt(const Math::Vector3& target, const Math::Vector3& up = { 0.0f, 1.0f, 0.0f }) noexcept;
		Math::Vector3 GetEulerAnglesFromRotationMatrix(const Math::Matrix3x3& rotationMatrix);

	private:
		Math::Vector3 m_Position{};
		Math::Vector3 m_Rotate{};
		Math::Vector3 m_Scale = Math::Vector3{ 1,1,1 };
	};

}

#endif // !__TRANSFORM__H__
