#pragma once
#ifndef __VECTOR2__H__
#define __VECTOR2__H__

#include "VectorCRTP.h"

namespace DSM {
	namespace Math {
		template<typename T, std::size_t N>
		class Vector;
		class Vector3;
		class Vector4;

		class Vector2 : public VectorCRTP<float, 2, Vector2>
		{
		public:
			Vector2() noexcept;
			Vector2(const std::array<float, 2>& data) noexcept;
			Vector2(std::initializer_list<float> list) noexcept;
			explicit Vector2(const float& v) noexcept;
			explicit Vector2(const float& x, const float& y) noexcept;

			explicit operator Vector3() const noexcept;
			explicit operator Vector4() const noexcept;

			float& x() noexcept;
			float& y() noexcept;
			const float& x() const noexcept;
			const float& y() const noexcept;

			static Vector2 down() noexcept;
			static Vector2 left() noexcept;
			static Vector2 right() noexcept;
			static Vector2 up() noexcept;

			static Vector2 perpendicular(const Vector2& v) noexcept;
			static Vector2 reflect(const Vector2& v, const Vector2& normal);
			static float angle(const Vector2& v1, const Vector2& v2);
		};



	}
}


#endif // !__VECTOR2__H__
