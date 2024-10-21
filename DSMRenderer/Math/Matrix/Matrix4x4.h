#pragma once
#ifndef __MATRIX4X4__H__
#define __MATRIX4X4__H__

#include "MatrixBase.h"

namespace DSM {
	namespace Math {
		class Matrix3x3;

		class Matrix4x4 : MatrixBase<Matrix4x4, Vector4, 4>
		{
		public:
			using MinorType = Matrix3x3;
			using BaseType = MatrixBase<Matrix4x4, Vector4, 4>;

			constexpr Matrix4x4() noexcept;
			constexpr explicit Matrix4x4(const T& v) noexcept;
			auto& operator=(std::initializer_list<T> list);
		};

		template<>
		struct MatrixTraits<Matrix4x4> {
			using ValueType = float;
			using Rows = std::integral_constant<std::size_t, 4>;
			using Cols = std::integral_constant<std::size_t, 4>;
			using MinorType = Matrix3x3;
			using ColType = Vector4;
			using TransposType = Matrix4x4;
		};

	}
}

#endif // !__MATRIX4X4__H__
