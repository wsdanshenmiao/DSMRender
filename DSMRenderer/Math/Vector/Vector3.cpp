#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"

namespace DSM {
	namespace Math {
		Vector3::Vector3() noexcept
			:VectorCRTP<float, 3, Vector3>() {}

		Vector3::Vector3(const Vector2& v2) noexcept
			:VectorCRTP<float, 3, Vector3>({ v2.x(),v2.y(),0 }) {}

		Vector3::Vector3(const std::array<float, 3>& data) noexcept
			:VectorCRTP<float, 3, Vector3>(data) {}

		Vector3::Vector3(std::initializer_list<float> list) noexcept
			:VectorCRTP<float, 3, Vector3>(std::move(list)) {}

		Vector3::Vector3(const float& v) noexcept
			:VectorCRTP<float, 3, Vector3>(v) {}

		Vector3::Vector3(const float& x, const float& y, const float& z) noexcept
			:VectorCRTP<float, 3, Vector3>({ x,y,z }) {}

		Vector3::operator Vector4() const noexcept
		{
			return Vector4{ x(),y(),z(),0 };
		}

		float& Vector3::x() noexcept
		{
			return m_Data[0];
		}

		float& Vector3::y() noexcept
		{
			return m_Data[1];
		}

		float& Vector3::z() noexcept
		{
			return m_Data[2];
		}

		const float& Vector3::x() const noexcept
		{
			return m_Data[0];
		}

		const float& Vector3::y() const noexcept
		{
			return m_Data[1];
		}

		const float& Vector3::z() const noexcept
		{
			return m_Data[2];
		}

		Vector3 Vector3::back() noexcept
		{
			return Vector3{ 0,0,-1 };
		}

		Vector3 Vector3::down() noexcept
		{
			return Vector3{ 0,-1,0 };
		}

		Vector3 Vector3::forward() noexcept
		{
			return Vector3{ 0,0,1 };
		}

		Vector3 Vector3::left() noexcept
		{
			return Vector3{ -1,0,0 };
		}

		Vector3 Vector3::right() noexcept
		{
			return Vector3{ 1,0,0 };
		}

		Vector3 Vector3::up() noexcept
		{
			return Vector3{ 0,1,0 };
		}

		Vector3 Vector3::reflect(const Vector3& v, const Vector3& normal)
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
		float Vector3::angle(const Vector3& v1, const Vector3& v2)
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

		/// <summary>
		/// 计算两个向量叉乘
		/// </summary>
		/// <param name="v1"></param>
		/// <param name="v2"></param>
		/// <returns></returns>
		Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2) noexcept
		{
			return Vector3{
				v1.y() * v2.z() - v1.z() * v2.y(),
				v1.z() * v2.x() - v1.x() * v2.z(),
				v1.x() * v2.y() - v1.y() * v2.x() };
		}

		/// <summary>
		/// 进行施密特向量正交,构建坐标系
		/// </summary>
		/// <param name="normal"></param>
		/// <param name="tangent"></param>
		void Vector3::orthoNormalize(Vector3& normal, Vector3& tangent, Vector3& binormal)
		{
			normalize(normal);
			tangent = tangent - project(tangent, normal);
			normalize(tangent);
			binormal = cross(tangent, normal);
		}
		void Vector3::orthoNormalize(Vector3& normal, Vector3& tangent)
		{
			normalize(normal);
			tangent = tangent - project(tangent, normal);
			normalize(tangent);
		}

		Vector3 Vector3::projectOnPlane(const Vector3& v, const Vector3& normal)
		{
			Vector3 standN = normal.normalized();
			Vector3 tangent = v;
			orthoNormalize(standN, tangent);
			return tangent;
		}

		/// <summary>
		/// 将向量current向向量target插值旋转
		/// </summary>
		/// <param name="current"></param>
		/// <param name="target"></param>
		/// <param name="maxRadiansDelta"></param> 该参数在范围[0,1]内
		/// <returns></returns>
		Vector3 Vector3::rotateTowards(const Vector3& current, const Vector3& target, const float& maxRadiansDelta) noexcept
		{
			Vector3 v = lerp(current, target, maxRadiansDelta);
			normalize(v);
			return v * current.magnitude();
		}

	}
}
