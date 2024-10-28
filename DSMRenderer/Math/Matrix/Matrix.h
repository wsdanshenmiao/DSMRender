#pragma once
#ifndef __MATRIX__H__
#define __MATRIX__H__

#include <iostream>
#include "../Vector/Vector.h"
#include "Determinant.h"
#include "MatrixTraits.h"

namespace DSM {
	namespace Math {

		/// <summary>
		/// 行主序矩阵，矩阵乘法须由子类自行定义
		/// </summary>
		/// <typeparam name="Matrix"></typeparam>	������������
		/// <typeparam name="Row"></typeparam>	����
		template <typename T, std::size_t Row, std::size_t Col>
		class Matrix
		{
		public:
			using RowType = typename MatrixTraits<Matrix>::RowType;
			using ColType = typename MatrixTraits<Matrix>::ColType;
			using LowerType = Matrix<T, Row - 1, Col - 1>;

			constexpr Matrix() noexcept;
			constexpr explicit Matrix(const T& v) noexcept;
			auto& operator=(std::initializer_list<T> list);

			operator LowerType() const noexcept;

			constexpr std::size_t size() const noexcept;
			void setRow(const std::size_t& idx, const RowType& row);
			void setRow(const std::size_t& idx, RowType&& row);
			void setCol(const std::size_t& idx, const ColType& col);
			constexpr auto getRow(const std::size_t& idx) const;
			constexpr auto getCol(const std::size_t& idx) const;
			constexpr auto getMinor(const std::size_t& row, const std::size_t& col) const;
			constexpr auto cofactor(const std::size_t& row, const std::size_t& col) const;
			constexpr auto calculateDet() const;
			constexpr auto adjugate() const;
			constexpr auto transpose() const;
			constexpr auto invert() const;
			constexpr auto invertTranspose() const;


			auto& operator[] (const std::size_t& idx);
			const auto& operator[] (const std::size_t& idx) const;
			auto& operator<< (std::initializer_list<T> list);
			auto& operator<< (const T& v);
			auto& operator,(const T& v);

			auto& operator+=(const Matrix& other);
			auto& operator-=(const Matrix& other);
			auto& operator/=(const T& v);
			auto& operator*=(const T& v);

			static constexpr auto identity();
			static constexpr auto zero() noexcept;
			//template<typename Ret, typename Left, typename Right>
			//static constexpr Ret _MultiplicaeMatrix(const Left& left, const Right& right);

		protected:
			void _InitFormList(std::initializer_list<T>&& list);


		protected:
			std::array<RowType, Row> m_Data;
			std::size_t m_Col, m_Row;
		};

		template <typename T, std::size_t Row, std::size_t Col>
		constexpr Matrix<T, Row, Col>::Matrix() noexcept
			:m_Col(0), m_Row(0) {
			for (std::size_t i = 0; i < Row; ++i) {
				for (std::size_t j = 0; j < Col; ++j) {
					m_Data[i][j] = i == j ? T{ 1 } : T{ 0 };
				}
			}
		}

		template <typename T, std::size_t Row, std::size_t Col>
		constexpr Matrix<T, Row, Col>::Matrix(const T& v) noexcept
			:m_Col(0), m_Row(0) {
			m_Data.fill(RowType(v));
		}

		template <typename T, std::size_t Row, std::size_t Col>
		constexpr std::size_t Matrix<T, Row, Col>::size() const noexcept
		{
			return Row * Col;
		}

		template <typename T, std::size_t Row, std::size_t Col>
		constexpr auto Matrix<T, Row, Col>::getRow(const std::size_t& idx) const
		{
			if (!(0 <= idx && idx < Row))
				throw std::out_of_range("Index out of range.");
			return m_Data[idx];
		}

		template <typename T, std::size_t Row, std::size_t Col>
		void Matrix<T, Row, Col>::setRow(const std::size_t& idx, const RowType& row)
		{
			if (!(0 <= idx && idx < Row))
				throw std::out_of_range("Index out of range.");
			m_Data[idx] = row;
		}

		template <typename T, std::size_t Row, std::size_t Col>
		void Matrix<T, Row, Col>::setRow(const std::size_t& idx, RowType&& row)
		{
			if (!(0 <= idx && idx < Row))
				throw std::out_of_range("Index out of range.");
			m_Data[idx] = std::move(row);
		}

		template <typename T, std::size_t Row, std::size_t Col>
		constexpr auto Matrix<T, Row, Col>::getCol(const std::size_t& idx) const
		{
			if (!(0 <= idx && idx < Col))
				throw std::out_of_range("Index out of range.");
			ColType col{};
			for (std::size_t i = 0; i < Row; col[i] = m_Data[i][idx], ++i);
			return col;
		}

		template <typename T, std::size_t Row, std::size_t Col>
		void Matrix<T, Row, Col>::setCol(const std::size_t& idx, const ColType& col)
		{
			if (!(0 <= idx && idx < Col))
				throw std::out_of_range("Index out of range.");
			for (std::size_t i = 0; i < Row; m_Data[i][idx] = col[i], ++i);
		}

		/// <summary>
		/// ��ȡȥ����(row + 1)�У���(col + 1)�к���Ծ���
		/// </summary>
		/// <param name="row"></param>
		/// <param name="col"></param>
		/// <returns></returns>
		template <typename T, std::size_t Row, std::size_t Col>
		constexpr auto Matrix<T, Row, Col>::getMinor(const std::size_t& row, const std::size_t& col) const
		{
			if (!(0 <= row && row < Row) || !(0 <= col && col < Col))
				throw std::logic_error("Row or col out of range.");
			Matrix<T, Row - 1, Col - 1> ret{};
			for (auto i = Row - 1; i--; ) {
				for (auto j = Col - 1; j--; ) {
					ret[i][j] = m_Data[i < row ? i : i + 1][j < col ? j : j + 1];
				}
			}
			return ret;
		}

		/// <summary>
		/// �������(row + 1)�У���(col + 1)�е�����ʽ
		/// </summary>
		/// <param name="row"></param>
		/// <param name="col"></param>
		/// <returns></returns>
		template <typename T, std::size_t Row, std::size_t Col>
		constexpr auto Matrix<T, Row, Col>::cofactor(const std::size_t& row, const std::size_t& col) const
		{
			auto det = getMinor(row, col).calculateDet();
			return det * ((row + col) % 2 ? -1 : 1);
		}

		/// <summary>
		/// ���㵱ǰ���������ʽ
		/// </summary>
		/// <returns></returns>
		template <typename T, std::size_t Row, std::size_t Col>
		constexpr auto Matrix<T, Row, Col>::calculateDet() const
		{
			return Determinant<T, Row, Col>::CalculateDet(*this);
		}

		template <typename T, std::size_t Row, std::size_t Col>
		constexpr auto Matrix<T, Row, Col>::adjugate() const
		{
			Matrix ret{};
			for (auto i = Row; i--; )
				for (auto j = Col; j--; ret[j][i] = cofactor(i, j));
			return ret;
		}

		template <typename T, std::size_t Row, std::size_t Col>
		constexpr auto Matrix<T, Row, Col>::transpose() const
		{
			Matrix<T, Col, Row> ret{};
			for (auto i = Col; i--; ret[i] = getCol(i));
			return ret;
		}

		template <typename T, std::size_t Row, std::size_t Col>
		constexpr auto Matrix<T, Row, Col>::invert() const
		{
			return adjugate() / calculateDet();
		}

		template <typename T, std::size_t Row, std::size_t Col>
		constexpr auto Matrix<T, Row, Col>::invertTranspose() const
		{
			return invert().transpose();
		}

		template <typename T, std::size_t Row, std::size_t Col>
		auto& Matrix<T, Row, Col>::operator[](const std::size_t& idx)
		{
			if (!(0 <= idx && idx < Row))
				throw std::out_of_range("Index out of range.");
			return m_Data[idx];
		}

		template <typename T, std::size_t Row, std::size_t Col>
		const auto& Matrix<T, Row, Col>::operator[](const std::size_t& idx) const
		{
			if (!(0 <= idx && idx < Row))
				throw std::out_of_range("Index out of range.");
			return m_Data[idx];
		}

		template <typename T, std::size_t Row, std::size_t Col>
		auto& Matrix<T, Row, Col>::operator<<(std::initializer_list<T> list)
		{
			_InitFormList(std::move(list));
			return *this;
		}

		/// <summary>
		/// ����<<��־�Ծ������¸�ֵ����Ӷ��ż�����ֵ
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		template <typename T, std::size_t Row, std::size_t Col>
		auto& Matrix<T, Row, Col>::operator<<(const T& v)
		{
			m_Col = 1;
			m_Row = 0;
			m_Data[0][0] = v;
			return *this;
		}

		/// <summary>
		/// 输入一个元素到矩阵内
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		template <typename T, std::size_t Row, std::size_t Col>
		auto& Matrix<T, Row, Col>::operator,(const T& v)
		{
			if (m_Row >= Row)
				throw std::logic_error("Value size out of range.");
			m_Data[m_Row][m_Col++] = v;
			if (m_Col >= Col) {
				++m_Row;
				//m_Row = m_Row + 1 >= Row ? 0 : m_Row + 1;
				m_Col = 0;
			}
			return *this;
		}

		template <typename T, std::size_t Row, std::size_t Col>
		auto& Matrix<T, Row, Col>::operator=(std::initializer_list<T> list)
		{
			_InitFormList(std::move(list));
			return *this;
		}

		template<typename T, std::size_t Row, std::size_t Col>
		inline Matrix<T, Row, Col>::operator LowerType() const noexcept
		{
			return LowerType{};
		}

		template <typename T, std::size_t Row, std::size_t Col>
		auto& Matrix<T, Row, Col>::operator+=(const Matrix& other)
		{
			for (auto i = Row; i--; m_Data[i] += other[i]);
			return *this;
		}

		template <typename T, std::size_t Row, std::size_t Col>
		auto& Matrix<T, Row, Col>::operator-=(const Matrix& other)
		{
			for (auto i = Row; i--; m_Data[i] -= other[i]);
			return *this;
		}

		template <typename T, std::size_t Row, std::size_t Col>
		auto& Matrix<T, Row, Col>::operator/=(const T& v)
		{
			for (auto i = Row; i--; m_Data[i] /= v);
			return *this;
		}

		template<typename T, std::size_t Row, std::size_t Col>
		inline auto& Matrix<T, Row, Col>::operator*=(const T& v)
		{
			for (auto i = Row; i--; m_Data[i] *= v);
			return *this;
		}

		template <typename T, std::size_t Row, std::size_t Col>
		constexpr auto Matrix<T, Row, Col>::identity()
		{
			Matrix m{};
			auto max = std::min(Row, Col);
			for (std::size_t i = 0; i < max; m[i][i] = 1, ++i);
			return m;
		}

		template<typename T, std::size_t Row, std::size_t Col>
		inline constexpr auto Matrix<T, Row, Col>::zero() noexcept
		{
			return Matrix{};
		}

		//template<typename T, std::size_t Row, std::size_t Col>
		//template<typename Ret, typename Left, typename Right>
		//inline constexpr Ret Matrix<T, Row, Col>::_MultiplicaeMatrix(const Left& left, const Right& right)
		//{
		//	Ret ret{ left };
		//	for (auto i = Row; i--; )
		//		for (auto j = Col; j--; )
		//			ret[i][j] = left[i] * right.getCol(j);
		//	return ret;
		//}

		template <typename T, std::size_t Row, std::size_t Col>
		void Matrix<T, Row, Col>::_InitFormList(std::initializer_list<T>&& list)
		{
			auto maxSize = std::min(list.size(), size()) / Row;
			for (auto i = 0; i < maxSize; ++i) {
				auto offset = list.begin() + i * Row;
				auto next = i + 1 >= maxSize ? list.end() : offset + Col;
				std::copy(offset, next, &m_Data[i][0]);
			}
		}






		template<typename T, std::size_t Row, std::size_t Col>
		auto operator+(const Matrix<T, Row, Col>& left, const Matrix<T, Row, Col>& right) {
			Matrix<T, Row, Col> ret{ left };
			for (auto i = Row; i--; ret[i] += right[i]);
			return ret;
		}

		template<typename T, std::size_t Row, std::size_t Col>
		auto operator-(const Matrix<T, Row, Col>& left, const Matrix<T, Row, Col>& right) {
			Matrix<T, Row, Col> ret{ left };
			for (auto i = Row; i--; ret[i] -= right[i]);
			return ret;
		}

		template<typename T, std::size_t Row, std::size_t Col>
		auto operator/(const Matrix<T, Row, Col>& m, const T& v)
		{
			Matrix<T, Row, Col> ret{ m };
			for (auto i = Row; i--; ret[i] /= v);
			return ret;
		}

		template<typename T, std::size_t Row, std::size_t Col>
		auto operator*(const Matrix<T, Row, Col>& m, const T& v)
		{
			Matrix<T, Row, Col> ret{ m };
			for (auto i = Row; i--; ret[i] *= v);
			return ret;
		}

		template<typename T, std::size_t Row, std::size_t Col>
		auto operator*(const T& v, const Matrix<T, Row, Col>& m)
		{
			Matrix<T, Row, Col> ret{ m };
			for (auto i = Row; i--; ret[i] *= v);
			return ret;
		}

		template<typename T, std::size_t Row, std::size_t Col>
		std::ostream& operator<<(std::ostream& out, const Matrix<T, Row, Col>& m)
		{
			for (auto i = 0; i < Row; out << m[i] << '\n', i++);
			return out;
		}


		template<typename T, std::size_t R1, std::size_t C, std::size_t R2>
		auto operator*(const Matrix<T, R1, C>& left, const Matrix<T, C, R2>& right)
		{
			Matrix<T, R1, R2> ret{};
			for (auto i = R1; i--; )
				for (auto j = R2; j--; )
					ret[i][j] = left[i] * right.getCol(j);
			return ret;
		}

		template<typename T, std::size_t Row, std::size_t Col>
		auto operator*(const Matrix<T, Row, Col>& m, const typename Matrix<T, Row, Col>::RowType& v)
		{
			typename Matrix<T, Row, Col>::ColType ret;
			for (auto i = Row; i--; ret[i] = m[i] * v);
			return ret;
		}

		template<typename T, std::size_t Row, std::size_t Col>
		auto operator*(const typename Matrix<T, Row, Col>::ColType& v, const Matrix<T, Row, Col>& m)
		{
			typename Matrix<T, Row, Col>::RowType ret;
			for (auto i = Col; i--; ret[i] = v * m.getCol(i));
			return ret;
		}

	}
}

#endif // !__MATRIX__H__
