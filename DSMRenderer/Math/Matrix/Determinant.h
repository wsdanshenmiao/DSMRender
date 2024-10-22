#pragma once
#ifndef __DETERMINANT__H__
#define __DETERMINANT__H__

#include <array>

namespace DSM {
	namespace Math {
		template <typename T, std::size_t Row, std::size_t Col>
		class Matrix;
		template<typename VectorType>
		struct VectorTraits;

		template <typename T, std::size_t Row, std::size_t Col>
		class Determinant
		{
		public:
			using Matrix = Matrix<T, Row, Col>;

			static constexpr auto CalculateDet(const Matrix& m);
		};

		template <typename T, std::size_t Row, std::size_t Col>
		constexpr auto Determinant<T, Row, Col>::CalculateDet(const Matrix& m)
		{
			T ret{ 0 };
			for (int i = Row; i--; )
				ret += m[0][i] * m.cofactor(0, i);
			return ret;
		}



		template <typename T>
		class Determinant<T, 1, 1>
		{
		public:
			using Matrix = Matrix<T, 1, 1>;

			static constexpr auto CalculateDet(const Matrix& m);
		};

		template <typename T>
		constexpr auto Determinant<T, 1, 1>::CalculateDet(const Matrix& m)
		{
			return m[0][0];
		}

	}
}

#endif // !__DETERMINANT__H__

