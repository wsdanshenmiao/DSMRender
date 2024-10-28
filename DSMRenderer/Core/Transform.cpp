#include "Transform.h"

namespace DSM {
	using namespace Math;

	Transform::Transform(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector3& scale)
		:m_Position(position), m_Rotate(rotation), m_Scale(scale) {}

	void Transform::setPosition(const Math::Vector3& position) noexcept
	{
		m_Position = position;
	}

	void Transform::setPosition(float x, float y, float z) noexcept
	{
		setPosition(Vector3{ x,y, z });
	}

	void Transform::setScale(const Math::Vector3& scale) noexcept
	{
		m_Scale = scale;
	}

	void Transform::setScale(float x, float y, float z) noexcept
	{
		setScale(Vector3{ x,y,z });
	}

	Math::Vector3 Transform::getPosition() const noexcept
	{
		return m_Position;
	}

	Math::Vector3 Transform::getScale() const noexcept
	{
		return m_Scale;
	}

	void Transform::Rotate(const Math::Vector3& eulerAnglesInRadian) noexcept
	{
		m_Rotate += eulerAnglesInRadian;
	}

	void Transform::Translate(const Math::Vector3& direction, float magnitude) noexcept
	{
		Vector3 dir = direction.normalized();
		m_Position += dir * magnitude;
	}

	void Transform::LookAt(const Math::Vector3& target, const Math::Vector3& up) noexcept
	{
		Vector3 z = (m_Position - target).normalized();
		Vector3 x = Vector3::cross(up, z).normalized();
		Vector3 y = Vector3::cross(z, x).normalized();
		Matrix3x3 Minv = Matrix3x3::identity();
		Matrix3x3 Tr = Matrix3x3::identity();
		for (int i = 0; i < 3; i++) {
			Minv[0][i] = x[i];
			Minv[1][i] = y[i];
			Minv[2][i] = z[i];
			Tr[i][3] = -m_Position[i];
		}
		m_Rotate = GetEulerAnglesFromRotationMatrix(Minv * Tr);
	}

	Vector3 Transform::GetEulerAnglesFromRotationMatrix(const Matrix3x3& rotationMatrix)
	{
		Vector3 rotation{};
		// 通过旋转矩阵反求欧拉角
		float c = sqrtf(1.0f - rotationMatrix[2][1] * rotationMatrix[2][1]);
		// 防止r[2][1]出现大于1的情况
		if (isnan(c))
			c = 0.0f;

		rotation.z() = atan2f(rotationMatrix[0][1], rotationMatrix[1][1]);
		rotation.x() = atan2f(-rotationMatrix[2][1], c);
		rotation.y() = atan2f(rotationMatrix[2][0], rotationMatrix[2][2]);
		return rotation;
	}


}
