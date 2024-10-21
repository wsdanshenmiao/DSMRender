#include "Vector4.h"
#include "Vector2.h"
#include "Vector3.h"

namespace DSM {
	namespace Math {
		Vector4::Vector4() noexcept
			:VectorCRTP<float, 4, Vector4>() {}

		Vector4::Vector4(const Vector2& v2) noexcept
			:VectorCRTP<float, 4, Vector4>({ v2.x(),v2.y(),0,0 }) {}

		Vector4::Vector4(const Vector3& v3) noexcept
			:VectorCRTP<float, 4, Vector4>({ v3.x(), v3.y(), v3.z(), 0 }) {}

		Vector4::Vector4(const std::array<float, 4>& data) noexcept
			:VectorCRTP<float, 4, Vector4>(data) {}

		Vector4::Vector4(std::initializer_list<float> list) noexcept
			:VectorCRTP<float, 4, Vector4>(std::move(list)) {}

		Vector4::Vector4(const float& v) noexcept
			:VectorCRTP<float, 4, Vector4>(v) {}

		Vector4::Vector4(const float& x, const float& y, const float& z) noexcept
			:VectorCRTP<float, 4, Vector4>({ x,y,z,0 }) {}

		float& Vector4::x() noexcept
		{
			return m_Data[0];
		}

		float& Vector4::y() noexcept
		{
			return m_Data[1];
		}

		float& Vector4::z() noexcept
		{
			return m_Data[2];
		}

		float& Vector4::w() noexcept
		{
			return m_Data[3];
		}

		const float& Vector4::x() const noexcept
		{
			return m_Data[0];
		}

		const float& Vector4::y() const noexcept
		{
			return m_Data[1];
		}

		const float& Vector4::z() const noexcept
		{
			return m_Data[2];
		}

		const float& Vector4::w() const noexcept
		{
			return m_Data[3];
		}

	}
}

