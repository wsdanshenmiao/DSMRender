#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace DSM {
	namespace Math {
		Vector2::Vector2() noexcept
			:VectorCRTP<float, 2, Vector2>() {}

		Vector2::Vector2(const std::array<float, 2>& data) noexcept
			:VectorCRTP<float, 2, Vector2>(data) {}

		Vector2::Vector2(std::initializer_list<float> list) noexcept
			:VectorCRTP<float, 2, Vector2>({ std::move(list) }) {}

		Vector2::Vector2(const float& v) noexcept
			:VectorCRTP<float, 2, Vector2>(v) {}

		Vector2::Vector2(const float& x, const float& y) noexcept
			:VectorCRTP<float, 2, Vector2>({ x,y }) {}

		Vector2::operator Vector3() const noexcept
		{
			return Vector3{ x(),y(),0 };
		}

		Vector2::operator Vector4() const noexcept
		{
			return Vector4{ x(),y(),0,0 };
		}

		float& Vector2::x() noexcept
		{
			return m_Data[0];
		}

		float& Vector2::y() noexcept
		{
			return m_Data[1];
		}

		const float& Vector2::x() const noexcept
		{
			return m_Data[0];
		}

		const float& Vector2::y() const noexcept
		{
			return m_Data[1];
		}

		Vector2 Vector2::down() noexcept
		{
			return Vector2{ 0, -1 };
		}

		Vector2 Vector2::left() noexcept
		{
			return Vector2{ -1, 0 };
		}

		Vector2 Vector2::right() noexcept
		{
			return Vector2{ 1, 0 };
		}

		Vector2 Vector2::up() noexcept
		{
			return Vector2{ 0, 1 };
		}

		/// <summary>
		/// 计算向量逆时针旋转90度后的向量
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector2 Vector2::perpendicular(const Vector2& v) noexcept
		{
			return Vector2{ -v.y(),v.x() };
		}

		Vector2 Vector2::reflect(const Vector2& v, const Vector2& normal)
		{
			auto standV = v.normalized();
			auto standN = normal.normalized();
			auto standRef = 2 * (standV * standN) * standN - standV;
			return  standRef * v.magnitude();
		}

		/// <summary>
		/// 计算两个向量之间的弧度角[0,180]
		/// </summary>
		/// <param name="v1"></param>
		/// <param name="v2"></param>
		/// <returns></returns>
		float Vector2::angle(const Vector2& v1, const Vector2& v2)
		{
			float dotProduct = v1 * v2;
			float sqrMagnitudeProduct = v1.sqrMagnitude() * v2.sqrMagnitude();

			if (sqrMagnitudeProduct == 0) {
				throw std::invalid_argument("Cannot calculate angle with zero-length vector.");
			}

			float cosA = dotProduct / sqrMagnitudeProduct;
			cosA = cosA > 1 ? 1 : (cosA < -1 ? -1 : cosA);

			return std::acos(cosA);
		}


	}
}

