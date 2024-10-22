#pragma once
#ifndef __MATRIX3X3__H__
#define __MATRIX3X3__H__

#include "MatrixBase.h"

namespace DSM {
	namespace Math {
		template<typename T, std::size_t Row, std::size_t Col>
		class Matrix;

		class Matrix3x3 : public MatrixBase<Matrix3x3, Vector3, 3>
		{
		public:
			using MinorType = Matrix<float, 2, 2>;
			using BaseType = MatrixBase<Matrix3x3, Vector3, 3>;

			constexpr Matrix3x3() noexcept;
			constexpr explicit Matrix3x3(const T& v) noexcept;
			auto& operator=(std::initializer_list<T> list);
		};


	}
}

#endif // !__MATRIX3X3__H__
