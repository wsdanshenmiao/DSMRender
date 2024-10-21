#pragma once
#ifndef __VECTOR3__H__
#define __VECTOR3__H__

#include "VectorCRTP.h"

namespace DSM {
	namespace Math {
		class Vector2;
		class Vector4;

		class Vector3 : public VectorCRTP<float, 3, Vector3>
		{
		public:
			Vector3() noexcept;
			Vector3(const Vector2& v2)noexcept;
			Vector3(const std::array<float, 3>& data) noexcept;
			Vector3(std::initializer_list<float> list) noexcept;
			explicit Vector3(const float& v) noexcept;
			explicit Vector3(const float& x, const float& y, const float& z) noexcept;

			explicit operator Vector4() const noexcept;

			float& x() noexcept;
			float& y() noexcept;
			float& z() noexcept;
			const float& x() const noexcept;
			const float& y() const noexcept;
			const float& z() const noexcept;

			static Vector3 back() noexcept;
			static Vector3 down() noexcept;
			static Vector3 forward() noexcept;
			static Vector3 left() noexcept;
			static Vector3 right() noexcept;
			static Vector3 up() noexcept;

			static Vector3 reflect(const Vector3& v, const Vector3& normal);
			static float angle(const Vector3& v1, const Vector3& v2);
			static Vector3 cross(const Vector3& v1, const Vector3& v2) noexcept;
			static void orthoNormalize(Vector3& normal, Vector3& tangent);
			static void orthoNormalize(Vector3& normal, Vector3& tangent, Vector3& binormal);
			static Vector3 projectOnPlane(const Vector3& v, const Vector3& normal);
			static Vector3 rotateTowards(const Vector3& current, const Vector3& target, const float& maxRadiansDelta) noexcept;
		};




		template <>
		struct VectorTraits<Vector3> {
			using Size = std::integral_constant<std::size_t, 3>;
			using ValueType = float;
			using MinorType = Vector2;
		};

	}
}


#endif // !__VECTOR3__H__
