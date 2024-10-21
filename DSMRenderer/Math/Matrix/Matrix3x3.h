#pragma once
#ifndef __MATRIX3X3__H__
#define __MATRIX3X3__H__

#include "MatrixBase.h"

namespace DSM {
	namespace Math {
		template<typename T, std::size_t Row, std::size_t Col>
		class Matrix;

		class Matrix3x3 : MatrixBase<Matrix3x3, Vector3, 3>
		{
		public:
			using MinorType = Matrix<float, 2, 2>;
			using BaseType = MatrixBase<Matrix3x3, Vector3, 3>;

			constexpr Matrix3x3() noexcept;
			constexpr explicit Matrix3x3(const T& v) noexcept;
			auto& operator=(std::initializer_list<T> list);
		};

		template<>
		struct MatrixTraits<Matrix3x3> {
			using ValueType = float;
			using Rows = std::integral_constant<std::size_t, 3>;
			using Cols = std::integral_constant<std::size_t, 3>;
			using MinorType = Matrix<float, 2, 2>;
			using ColType = Vector3;
			using TransposType = Matrix3x3;
		};

	}
}

#endif // !__MATRIX3X3__H__
