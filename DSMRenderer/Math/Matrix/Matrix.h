#pragma once
#ifndef __MATRIX__H__
#define __MATRIX__H__

#include "MatrixBase.h"

namespace DSM {
	namespace Math {

		template<typename T, std::size_t Row, std::size_t Col>
		class Matrix : public MatrixBase<Matrix<T, Row, Col>, Vector<T, Col>, Row>
		{
		public:
			using MinorType = Matrix<T, Row - 1, Col - 1>;
			using BaseType = typename MatrixBase<Matrix<T, Row, Col>, Vector<T, Col>, Row>;

			constexpr Matrix() noexcept;
			constexpr explicit Matrix(const T& v) noexcept;
			auto& operator=(std::initializer_list<T> list);
		};

		template<typename T, std::size_t Row, std::size_t Col>
		constexpr Matrix<T, Row, Col>::Matrix() noexcept
			:BaseType() {}

		template<typename T, std::size_t Row, std::size_t Col>
		constexpr Matrix<T, Row, Col>::Matrix(const T& v) noexcept
			:BaseType(v) {}

		template<typename T, std::size_t Row, std::size_t Col>
		auto& Matrix<T, Row, Col>::operator=(std::initializer_list<T> list)
		{
			BaseType::_InitFormList(std::move(list));
			return *this;
		}





		template<typename T, std::size_t R1, std::size_t C, std::size_t R2>
		auto operator*(const Matrix<T, R1, C>& left, const Matrix<T, C, R2>& right)
		{
			using Ret = Matrix<T, R1, R2>;
			using Left = Matrix<T, R1, C>;
			using Right = Matrix<T, C, R2>;
			return Ret::BaseType::_MultiplicaeMatrix<Ret, Left, Right>(left, right);
		}


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
	}
}

#endif // !__MATRIX__H__
