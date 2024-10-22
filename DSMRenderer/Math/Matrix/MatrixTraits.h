#pragma once
#ifndef __MATRIXTRAITS__H__
#define __MATRIXTRAITS__H__

namespace DSM {
	namespace Math {
		template <typename T, std::size_t Row, std::size_t Col>
		class Matrix;
		template <typename T, std::size_t N>
		class Vector;
		class Vector2;
		class Vector3;
		class Vecotr4;

		using Matrix4x4 = Matrix<float, 4, 4>;
		using Matrix3x3 = Matrix<float, 3, 3>;
		using Matrix2x2 = Matrix<float, 2, 2>;

		template <typename MatrixType>
		struct MatrixTraits;

		template<typename T, std::size_t Row, std::size_t Col>
		struct MatrixTraits<Matrix<T, Row, Col>> {
			using RowType = Vector<T, Col>;
			using ColType = Vector<T, Row>;
		};

		template<>
		struct MatrixTraits<Matrix4x4> {
			using RowType = Vector4;
			using ColType = Vector4;
		};
		template<typename T, std::size_t Row>
		struct MatrixTraits<Matrix<T, Row, 4>> {
			using RowType = Vector4;
			using ColType = Vector<T, Row>;
		};
		template<typename T, std::size_t Col>
		struct MatrixTraits<Matrix<T, 4, Col>> {
			using RowType = Vector<T, Col>;
			using ColType = Vector4;
		};

		template<>
		struct MatrixTraits<Matrix3x3> {
			using RowType = Vector3;
			using ColType = Vector3;
		};
		template<typename T, std::size_t Row>
		struct MatrixTraits<Matrix<T, Row, 3>> {
			using RowType = Vector3;
			using ColType = Vector<T, Row>;
		};
		template<typename T, std::size_t Col>
		struct MatrixTraits<Matrix<T, 3, Col>> {
			using RowType = Vector<T, Col>;
			using ColType = Vector3;
		};

		template<>
		struct MatrixTraits<Matrix2x2> {
			using RowType = Vector2;
			using ColType = Vector2;
		};
		template<typename T, std::size_t Row>
		struct MatrixTraits<Matrix<T, Row, 2>> {
			using RowType = Vector2;
			using ColType = Vector<T, Row>;
		};
		template<typename T, std::size_t Col>
		struct MatrixTraits<Matrix<T, 2, Col>> {
			using RowType = Vector<T, Col>;
			using ColType = Vector2;
		};



	}
}

#endif // !__MATRIXTRAITS__H__
