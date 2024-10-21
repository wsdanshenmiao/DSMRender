#pragma once
#ifndef __MATRIX__H__
#define __MATRIX__H__

#include "MatrixBase.h"

namespace DSM {
	namespace Math {

		template<typename T, std::size_t Col, std::size_t Row>
		class Matrix : public MatrixBase<Matrix<T, Col, Row>, Vector<T, Col>, Row>
		{
		public:
			using MinorType = Matrix<T, Col - 1, Row - 1>;
			using BaseType = typename MatrixBase<Matrix<T, Col, Row>, Vector<T, Col>, Row>;

			constexpr Matrix() noexcept;
			constexpr explicit Matrix(const T& v) noexcept;
			Matrix& operator=(const Matrix& other) = default;
			auto& operator=(std::initializer_list<T> list);

		};

		template<typename T, std::size_t Col, std::size_t Row>
		constexpr Matrix<T, Col, Row>::Matrix() noexcept
			:BaseType() {}

		template<typename T, std::size_t Col, std::size_t Row>
		constexpr Matrix<T, Col, Row>::Matrix(const T& v) noexcept
			:BaseType(v) {}

		template<typename T, std::size_t Col, std::size_t Row>
		auto& Matrix<T, Col, Row>::operator=(std::initializer_list<T> list)
		{
			BaseType::_InitFormList(std::move(list));
			return *this;
		}






		template<typename T, std::size_t Col, std::size_t Row>
		struct MatrixTraits < Matrix<T, Col, Row>>
		{
			using ValueType = T;
			using MinorType = Matrix<T, Col - 1, Row - 1>;
			using ColType = Vector<T, Row>;
			using TransposType = Matrix<T, Row, Col>;
		};
	}
}

#endif // !__MATRIX__H__
