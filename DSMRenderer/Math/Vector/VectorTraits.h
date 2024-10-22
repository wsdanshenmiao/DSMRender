#pragma once
#ifndef __VECTORTRAITS__H__
#define __VECTORTRAITS__H__

#include <type_traits>

namespace DSM {
	namespace Math {
		template<typename T, std::size_t N>
		class Vector;
		class Vector2;
		class Vector3;
		class Vector4;

		// 结构体帮助提取 Vector 的 N  
		template <typename VectorType>
		struct VectorTraits;

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

		template <>
		struct VectorTraits<Vector2> {
			using Size = std::integral_constant<std::size_t, 2>;
			using ValueType = float;
			using MinorType = Vector<float, 1>;
		};

		template <>
		struct VectorTraits<Vector3> {
			using Size = std::integral_constant<std::size_t, 3>;
			using ValueType = float;
			using MinorType = Vector2;
		};

		template <>
		struct VectorTraits<Vector4> {
			using Size = std::integral_constant<std::size_t, 4>;
			using ValueType = float;
			using MinorType = Vector3;
		};



	}
}

#endif // !__VECTORTRAITS__H__
