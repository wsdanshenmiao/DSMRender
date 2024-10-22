#pragma once
#ifndef __MATRIXTRAITS__H__
#define __MATRIXTRAITS__H__

namespace DSM {
	namespace Math {
		template<typename T, std::size_t Row, std::size_t Col>
		class Matrix;
		class Matrix3x3;
		class Matrix4x4;

		template <typename MatrixType>
		struct MatrixTraits;

		template<typename T, std::size_t Row, std::size_t Col>
		struct MatrixTraits < Matrix<T, Row, Col>>
		{
			using ValueType = T;
			using Rows = std::integral_constant<std::size_t, Row>;
			using Cols = std::integral_constant<std::size_t, Col>;
			using MinorType = Matrix<T, Row - 1, Col - 1>;
			using ColType = Vector<T, Row>;
			using TransposType = Matrix<T, Row, Col>;
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

#endif // !__MATRIXTRAITS__H__
