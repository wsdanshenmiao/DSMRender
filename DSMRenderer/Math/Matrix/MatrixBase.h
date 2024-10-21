#pragma once
#ifndef __MATRIXBASE__H__
#define __MATRIXBASE__H__

#include "../Vector/Vector.h"
#include "Determinant.h"

namespace DSM {
	namespace Math {

		template <typename MatrixType>
		struct MatrixTraits;

		/// <summary>
		/// 行主序矩阵，矩阵乘法须由子类自行定义
		/// </summary>
		/// <typeparam name="Derived"></typeparam>	������������
		/// <typeparam name="Row"></typeparam>	����
		template <typename Derived, typename V, std::size_t Row>
		class MatrixBase
		{
		public:
			using T = typename VectorTraits<V>::ValueType;
			using Col = typename VectorTraits<V>::Size;
			using MinorType = typename VectorTraits<V>::MinorType;
			using MinorMatrix = typename MatrixTraits<Derived>::MinorType;
			using ColType = typename MatrixTraits<Derived>::ColType;
			using TransposType = typename MatrixTraits<Derived>::TransposType;

			constexpr MatrixBase() noexcept;
			constexpr explicit MatrixBase(const T& v) noexcept;
			Derived& operator=(std::initializer_list<T> list);

			constexpr std::size_t size() const noexcept;
			void setRow(const std::size_t& idx, const V& row);
			void setRow(const std::size_t& idx, V&& row);
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


			V& operator[] (const std::size_t& idx);
			const V& operator[] (const std::size_t& idx) const;
			Derived& operator<< (std::initializer_list<T> list);
			Derived& operator<< (const T& v);
			Derived& operator,(const T& v);

			Derived& operator+=(const MatrixBase& other);
			Derived& operator-=(const MatrixBase& other);
			Derived& operator/=(const T& v);
			Derived& operator*=(const T& v);

			static constexpr Derived identity() noexcept;
			template<typename Ret, typename Left, typename Right>
			static constexpr Ret _MultiplicaeMatrix(const Left& left, const Right& right);

		protected:
			void _InitFormList(std::initializer_list<T>&& list);


		protected:
			std::array<V, Row> m_Data;
			std::size_t m_Col, m_Row;
		};

		template <typename Derived, typename V, std::size_t Row>
		constexpr MatrixBase<Derived, V, Row>::MatrixBase() noexcept
			:m_Col(0), m_Row(0) {
			m_Data.fill(V(0));
		}

		template <typename Derived, typename V, std::size_t Row>
		constexpr MatrixBase<Derived, V, Row>::MatrixBase(const T& v) noexcept
			:m_Col(0), m_Row(0) {
			m_Data.fill(V(v));
		}

		template <typename Derived, typename V, std::size_t Row>
		constexpr std::size_t MatrixBase<Derived, V, Row>::size() const noexcept
		{
			return Row * Col::value;
		}

		template <typename Derived, typename V, std::size_t Row>
		constexpr auto MatrixBase<Derived, V, Row>::getRow(const std::size_t& idx) const
		{
			if (!(0 <= idx && idx < Row))
				throw std::out_of_range("Index out of range.");
			return m_Data[idx];
		}

		template <typename Derived, typename V, std::size_t Row>
		void MatrixBase<Derived, V, Row>::setRow(const std::size_t& idx, const V& row)
		{
			if (!(0 <= idx && idx < Row))
				throw std::out_of_range("Index out of range.");
			m_Data[idx] = row;
		}

		template <typename Derived, typename V, std::size_t Row>
		void MatrixBase<Derived, V, Row>::setRow(const std::size_t& idx, V&& row)
		{
			if (!(0 <= idx && idx < Row))
				throw std::out_of_range("Index out of range.");
			m_Data[idx] = std::move(row);
		}

		template <typename Derived, typename V, std::size_t Row>
		constexpr auto MatrixBase<Derived, V, Row>::getCol(const std::size_t& idx) const
		{
			if (!(0 <= idx && idx < Col::value))
				throw std::out_of_range("Index out of range.");
			ColType col{};
			for (std::size_t i = 0; i < Row; col[i] = m_Data[i][idx], ++i);
			return col;
		}

		template <typename Derived, typename V, std::size_t Row>
		void MatrixBase<Derived, V, Row>::setCol(const std::size_t& idx, const ColType& col)
		{
			if (!(0 <= idx && idx < Col::value))
				throw std::out_of_range("Index out of range.");
			for (std::size_t i = 0; i < Row; m_Data[i][idx] = col[i], ++i);
		}

		/// <summary>
		/// ��ȡȥ����(row + 1)�У���(col + 1)�к���Ծ���
		/// </summary>
		/// <param name="row"></param>
		/// <param name="col"></param>
		/// <returns></returns>
		template <typename Derived, typename V, std::size_t Row>
		constexpr auto MatrixBase<Derived, V, Row>::getMinor(const std::size_t& row, const std::size_t& col) const
		{
			if (!(0 <= row && row < Row) || !(0 <= col && col < Col::value))
				throw std::logic_error("Row or col out of range.");
			MinorMatrix ret{};
			for (auto i = Row - 1; i--; ) {
				for (auto j = Col::value - 1; j--; ) {
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
		template <typename Derived, typename V, std::size_t Row>
		constexpr auto MatrixBase<Derived, V, Row>::cofactor(const std::size_t& row, const std::size_t& col) const
		{
			auto det = getMinor(row, col).calculateDet();
			return det * ((row + col) % 2 ? -1 : 1);
		}

		/// <summary>
		/// ���㵱ǰ���������ʽ
		/// </summary>
		/// <returns></returns>
		template <typename Derived, typename V, std::size_t Row>
		constexpr auto MatrixBase<Derived, V, Row>::calculateDet() const
		{
			return Determinant<Derived, V, Col::value>::CalculateDet(*this);
		}

		template <typename Derived, typename V, std::size_t Row>
		constexpr auto MatrixBase<Derived, V, Row>::adjugate() const
		{
			Derived ret{};
			for (auto i = Row; i--; )
				for (auto j = Col::value; j--; ret[j][i] = cofactor(i, j));
			return ret;
		}

		template <typename Derived, typename V, std::size_t Row>
		constexpr auto MatrixBase<Derived, V, Row>::transpose() const
		{
			TransposType ret{};
			for (auto i = Col::value; i--; ret[i] = getCol(i));
			return ret;
		}

		template <typename Derived, typename V, std::size_t Row>
		constexpr auto MatrixBase<Derived, V, Row>::invert() const
		{
			return adjugate() / calculateDet();
		}

		template <typename Derived, typename V, std::size_t Row>
		constexpr auto MatrixBase<Derived, V, Row>::invertTranspose() const
		{
			return invert().transpose();
		}

		template <typename Derived, typename V, std::size_t Row>
		V& MatrixBase<Derived, V, Row>::operator[](const std::size_t& idx)
		{
			if (!(0 <= idx && idx < Row))
				throw std::out_of_range("Index out of range.");
			return m_Data[idx];
		}

		template <typename Derived, typename V, std::size_t Row>
		const V& MatrixBase<Derived, V, Row>::operator[](const std::size_t& idx) const
		{
			if (!(0 <= idx && idx < Row))
				throw std::out_of_range("Index out of range.");
			return m_Data[idx];
		}

		template <typename Derived, typename V, std::size_t Row>
		Derived& MatrixBase<Derived, V, Row>::operator<<(std::initializer_list<T> list)
		{
			_InitFormList(std::move(list));
			return *static_cast<Derived*>(this);
		}

		/// <summary>
		/// ����<<��־�Ծ������¸�ֵ����Ӷ��ż�����ֵ
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		template <typename Derived, typename V, std::size_t Row>
		Derived& MatrixBase<Derived, V, Row>::operator<<(const T& v)
		{
			m_Col = 1;
			m_Row = 0;
			m_Data[0][0] = v;
			return *static_cast<Derived*>(this);
		}

		/// <summary>
		/// ���أ��Ծ���ֵ����δʹ��<<��Ϊδ���壬�������ȸ������ݣ��������ݲ��ı�
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		template <typename Derived, typename V, std::size_t Row>
		Derived& MatrixBase<Derived, V, Row>::operator,(const T& v)
		{
			if (m_Row >= Row)
				throw std::logic_error("Value size out of range.");
			m_Data[m_Row][m_Col++] = v;
			if (m_Col >= Col::value) {
				++m_Row;
				//m_Row = m_Row + 1 >= Row ? 0 : m_Row + 1;
				m_Col = 0;
			}
			return *static_cast<Derived*>(this);
		}

		template <typename Derived, typename V, std::size_t Row>
		Derived& MatrixBase<Derived, V, Row>::operator=(std::initializer_list<T> list)
		{
			_InitFormList(std::move(list));
			return *static_cast<Derived*>(this);
		}

		template <typename Derived, typename V, std::size_t Row>
		Derived& MatrixBase<Derived, V, Row>::operator+=(const MatrixBase& other)
		{
			for (auto i = Row; i--; m_Data[i] += other[i]);
			return *static_cast<Derived*>(this);
		}

		template <typename Derived, typename V, std::size_t Row>
		Derived& MatrixBase<Derived, V, Row>::operator-=(const MatrixBase& other)
		{
			for (auto i = Row; i--; m_Data[i] -= other[i]);
			return *static_cast<Derived*>(this);
		}

		template <typename Derived, typename V, std::size_t Row>
		Derived& MatrixBase<Derived, V, Row>::operator/=(const T& v)
		{
			for (auto i = Row; i--; m_Data[i] /= v);
			return *static_cast<Derived*>(this);
		}

		template<typename Derived, typename V, std::size_t Row>
		inline Derived& MatrixBase<Derived, V, Row>::operator*=(const T& v)
		{
			for (auto i = Row; i--; m_Data[i] *= v);
			return *static_cast<Derived*>(this);
		}

		template <typename Derived, typename V, std::size_t Row>
		constexpr Derived MatrixBase<Derived, V, Row>::identity() noexcept
		{
			MatrixBase m{};
			auto max = std::min(Row, Col::value);
			for (std::size_t i = 0; i < max; m_Data[i][i] = 1, ++i);
			return m;
		}

		template<typename Derived, typename V, std::size_t Row>
		template<typename Ret, typename Left, typename Right>
		inline constexpr Ret MatrixBase<Derived, V, Row>::_MultiplicaeMatrix(const Left& left, const Right& right)
		{
			using Rows = typename MatrixTraits<Left>::Rows;
			using Cols = typename MatrixTraits<Right>::Cols;
			Ret ret{ left };
			for (auto i = Rows::value; i--; )
				for (auto j = Cols::value; j--; )
					ret[i][j] = left[i] * right.getCol(j);
			return ret;
		}

		template <typename Derived, typename V, std::size_t Row>
		void MatrixBase<Derived, V, Row>::_InitFormList(std::initializer_list<T>&& list)
		{
			auto maxSize = std::min(list.size(), size()) / Row;
			for (auto i = 0; i < maxSize; ++i) {
				auto offset = list.begin() + i * Row;
				auto next = i + 1 >= maxSize ? list.end() : offset + Col::value;
				std::copy(offset, next, &m_Data[i][0]);
			}
		}






		template<typename Derived, typename V, std::size_t Row>
		Derived operator+(
			const MatrixBase<Derived, V, Row>& left,
			const MatrixBase<Derived, V, Row>& right) {
			Derived ret;
			for (auto i = Row; i--; ret[i] = left[i] + right[i]);
			return ret;
		}

		template<typename Derived, typename V, std::size_t Row>
		Derived operator-(
			const MatrixBase<Derived, V, Row>& left,
			const MatrixBase<Derived, V, Row>& right) {
			Derived ret;
			for (auto i = Row; i--; ret[i] = left[i] - right[i]);
			return ret;
		}

		template<typename Derived, typename V, std::size_t Row>
		Derived operator/(
			const MatrixBase<Derived, V, Row>& m,
			const typename MatrixBase<Derived, V, Row>::T& v) {
			Derived ret;
			for (auto i = Row; i--; ret[i] = m[i] / v);
			return ret;
		}

		template<typename Derived, typename V, std::size_t Row>
		Derived operator*(
			const MatrixBase<Derived, V, Row>& m,
			const typename MatrixBase<Derived, V, Row>::T& v) {
			Derived ret;
			for (auto i = Row; i--; ret[i] = m[i] * v);
			return ret;
		}

		template<typename Derived, typename V, std::size_t Row>
		Derived operator*(
			const typename MatrixBase<Derived, V, Row>::T& v,
			const MatrixBase<Derived, V, Row>& m) {
			Derived ret;
			for (auto i = Row; i--; ret[i] = m[i] * v);
			return ret;
		}

		template<typename Derived, typename V, std::size_t Row>
		std::ostream& operator<<(std::ostream& out, const MatrixBase<Derived, V, Row>& m)
		{
			for (int i = 0; i < Row; i++) out << m[i] << '\n';
			return out;
		}




	}
}

#endif // !__MATRIXBASE__H__
