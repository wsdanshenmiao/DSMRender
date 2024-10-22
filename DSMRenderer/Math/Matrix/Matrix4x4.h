#pragma once
#ifndef __MATRIX4X4__H__
#define __MATRIX4X4__H__

#include "MatrixBase.h"

namespace DSM {
	namespace Math {
		class Matrix3x3;

		class Matrix4x4 : public MatrixBase<Matrix4x4, Vector4, 4>
		{
		public:
			using MinorType = Matrix3x3;
			using BaseType = MatrixBase<Matrix4x4, Vector4, 4>;

			constexpr Matrix4x4() noexcept;
			constexpr explicit Matrix4x4(const T& v) noexcept;
			auto& operator=(std::initializer_list<T> list);

			friend auto operator*(const Matrix4x4& left, const Matrix4x4& right);
		};


	}
}

#endif // !__MATRIX4X4__H__
