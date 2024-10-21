#pragma once
#ifndef __DETERMINANT__H__
#define __DETERMINANT__H__

#include <array>

namespace DSM {
	namespace Math {
		template <typename Derived, typename Vector, std::size_t Row>
		class MatrixBase;
		template<typename VectorType>
		struct VectorTraits;

		template <typename Derived, typename Vector, std::size_t Row>
		class Determinant
		{
		public:
			using Matrix = MatrixBase<Derived, Vector, Row>;
			using T = typename VectorTraits<Vector>::ValueType;

			static constexpr auto CalculateDet(const Matrix& m);
		};

		template <typename Derived, typename Vector, std::size_t Row>
		constexpr auto Determinant<Derived, Vector, Row>::CalculateDet(const Matrix& m)
		{
			T ret{ 0 };
			for (int i = Row; i--; )
				ret += m[0][i] * m.cofactor(0, i);
			return ret;
		}



		template <typename Derived, typename Vector>
		class Determinant<Derived, Vector, 1>
		{
		public:
			using Matrix = MatrixBase<Derived, Vector, 1>;
			using T = typename VectorTraits<Vector>::ValueType;

			static constexpr auto CalculateDet(const Matrix& m);
		};

		template <typename Derived, typename Vector>
		constexpr auto Determinant<Derived, Vector, 1>::CalculateDet(const Matrix& m)
		{
			return m[0][0];
		}

	}
}

#endif // !__DETERMINANT__H__

