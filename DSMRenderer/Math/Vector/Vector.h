#pragma once
#ifndef __VECTOR__H__
#define __VECTOR__H__

#include "VectorCRTP.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace DSM {
	namespace Math {
		template <typename T, std::size_t N>
		class Vector : public VectorCRTP<T, N, Vector<T, N>>
		{
		public:
			using ValueType = T;

			constexpr Vector() noexcept;
			constexpr explicit Vector(const T& v) noexcept;
			constexpr Vector(const std::array<T, N>& data) noexcept;
			constexpr Vector(std::initializer_list<T> list) noexcept;
		};

		template<typename T, std::size_t N>
		constexpr Vector<T, N>::Vector() noexcept
			:VectorCRTP<T, N, Vector>() {}

		template<typename T, std::size_t N>
		constexpr Vector<T, N>::Vector(const T& v) noexcept
			:VectorCRTP<T, N, Vector>(v) {}

		template<typename T, std::size_t N>
		constexpr Vector<T, N>::Vector(const std::array<T, N>& data) noexcept
			:VectorCRTP<T, N, Vector>(data) {}

		template<typename T, std::size_t N>
		constexpr Vector<T, N>::Vector(std::initializer_list<T> list) noexcept
			:VectorCRTP<T, N, Vector>(std::move(list)) {}


		template <typename T, std::size_t N>
		struct VectorTraits<Vector<T, N>> {
			using Size = std::integral_constant<std::size_t, N>;
			using ValueType = T;
			using MinorType = Vector<T, N - 1>;
		};

		template <typename T>
		struct VectorTraits<Vector<T, 1>> {
			using Size = std::integral_constant<std::size_t, 1>;
			using ValueType = T;
			using MinorType = Vector<T, 1>;
		};

	}
}



#endif // !__VECTOR__H__
