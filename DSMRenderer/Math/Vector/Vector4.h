#pragma once
#ifndef __VECTOR4__H__
#define __VECTOR4__H__

#include "VectorCRTP.h"

namespace DSM {
	namespace Math {
		class Vector2;
		class Vector3;

		class Vector4 : VectorCRTP<float, 4, Vector4>
		{
		public:
			Vector4() noexcept;
			Vector4(const Vector2& v2) noexcept;
			Vector4(const Vector3& v3) noexcept;
			Vector4(const std::array<float, 4>& data) noexcept;
			Vector4(std::initializer_list<float> list) noexcept;
			explicit Vector4(const float& v) noexcept;
			explicit Vector4(const float& x, const float& y, const float& z) noexcept;

			float& x() noexcept;
			float& y() noexcept;
			float& z() noexcept;
			float& w() noexcept;
			const float& x() const noexcept;
			const float& y() const noexcept;
			const float& z() const noexcept;
			const float& w() const noexcept;
		};



		template <>
		struct VectorTraits<Vector4> {
			using Size = std::integral_constant<std::size_t, 4>;
			using ValueType = float;
			using MinorType = Vector3;
		};
	}
}

#endif // !__VECTOR4__H__
