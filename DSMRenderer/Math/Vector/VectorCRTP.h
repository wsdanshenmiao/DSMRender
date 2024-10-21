#pragma once
#ifndef __VECTORCRTP__H__
#define __VECTORCRTP__H__

#include <array>
#include <initializer_list>
#include <iostream>
#include <math.h>

namespace DSM {
	namespace Math {

		// CRTP
		template <typename T, std::size_t N, typename Derived>
		class VectorCRTP
		{
		public:
			using ValueType = T;

			constexpr VectorCRTP() noexcept;
			constexpr explicit VectorCRTP(const T& v) noexcept;
			constexpr VectorCRTP(const std::array<T, N>& data) noexcept;
			constexpr VectorCRTP(std::initializer_list<T> list) noexcept;
			//template <typename... Args>
			//Vector(const Args&... args);

			constexpr std::size_t size() const noexcept;
			void fill(const T& v) noexcept;
			constexpr T magnitude() const noexcept;
			constexpr T sqrMagnitude() const noexcept;
			constexpr Derived normalized() const noexcept;

			Derived& operator+=(const VectorCRTP& other) noexcept;
			Derived& operator-=(const VectorCRTP& other) noexcept;
			Derived& operator*=(const T& v) noexcept;
			Derived& operator/=(const T& v) noexcept;
			T& operator[](const std::size_t& i);
			const T& operator[](const std::size_t& i) const;

			static void normalize(VectorCRTP& v) noexcept;
			static constexpr T distance(const VectorCRTP& v1, const VectorCRTP& v2) noexcept;
			static constexpr Derived zero() noexcept;
			static constexpr Derived one() noexcept;
			static constexpr Derived negativeInfinity() noexcept;
			static constexpr Derived positiveInfinity() noexcept;
			static constexpr Derived clampMagnitude(const VectorCRTP& v, const T& maxLen) noexcept;
			static constexpr Derived lerp(const VectorCRTP& v1, const VectorCRTP& v2, const float& t) noexcept;
			static constexpr Derived max(const VectorCRTP& v1, const VectorCRTP& v2) noexcept;
			static constexpr Derived min(const VectorCRTP& v1, const VectorCRTP& v2) noexcept;
			static constexpr Derived project(const VectorCRTP& v1, const VectorCRTP& v2);
			static constexpr Derived scale(const VectorCRTP& v1, const VectorCRTP& v2) noexcept;


		protected:
			std::array<T, N> m_Data;
		};

		template <typename T, std::size_t N, typename Derived>
		constexpr VectorCRTP<T, N, Derived>::VectorCRTP() noexcept
		{
			m_Data.fill(0);
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr VectorCRTP<T, N, Derived>::VectorCRTP(const T& v) noexcept
		{
			m_Data.fill(v);
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr VectorCRTP<T, N, Derived>::VectorCRTP(const std::array<T, N>& data) noexcept
			:m_Data(data) {}

		template <typename T, std::size_t N, typename Derived>
		constexpr VectorCRTP<T, N, Derived>::VectorCRTP(std::initializer_list<T> list) noexcept
		{
			std::size_t s = list.size() < size() ? list.size() : size();
			std::memcpy(m_Data.data(), list.begin(), sizeof(T) * s);
		}

		//template <typename T, std::size_t N, typename Derived>
		//template<typename ...Args>
		//Vector<T, N, Derived>::Vector(const Args & ...args)
		//	: m_Data({ static_cast<T>(args)... }) {}

		template <typename T, std::size_t N, typename Derived>
		constexpr std::size_t VectorCRTP<T, N, Derived>::size() const noexcept
		{
			return m_Data.size();
		}

		template<typename T, std::size_t N, typename Derived>
		void VectorCRTP<T, N, Derived>::fill(const T& v) noexcept
		{
			m_Data.fill(v);
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr T VectorCRTP<T, N, Derived>::magnitude() const noexcept
		{
			return std::sqrt(sqrMagnitude());
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr T VectorCRTP<T, N, Derived>::sqrMagnitude() const noexcept
		{
			T ret{ 0 };
			for (const auto& data : m_Data) {
				ret += data * data;
			}
			return ret;
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr Derived VectorCRTP<T, N, Derived>::normalized() const noexcept
		{
			Derived ret(m_Data);
			normalize(ret);
			return ret;
		}

		template <typename T, std::size_t N, typename Derived>
		Derived& VectorCRTP<T, N, Derived>::operator+=(const VectorCRTP& other) noexcept
		{
			for (std::size_t i = 0; i < other.size(); ++i) {
				m_Data[i] += other.m_Data[i];
			}
			return *static_cast<Derived*>(this);
		}

		template <typename T, std::size_t N, typename Derived>
		Derived& VectorCRTP<T, N, Derived>::operator-=(const VectorCRTP& other) noexcept
		{
			for (std::size_t i = 0; i < other.size(); ++i) {
				m_Data[i] -= other.m_Data[i];
			}
			return *static_cast<Derived*>(this);
		}

		template <typename T, std::size_t N, typename Derived>
		Derived& VectorCRTP<T, N, Derived>::operator*=(const T& v) noexcept
		{
			for (std::size_t i = 0; i < size(); ++i) {
				m_Data[i] *= v;
			}
			return *static_cast<Derived*>(this);
		}

		template <typename T, std::size_t N, typename Derived>
		Derived& VectorCRTP<T, N, Derived>::operator/=(const T& v) noexcept
		{
			T inv = 1 / v;
			for (std::size_t i = 0; i < size(); ++i) {
				m_Data[i] *= inv;
			}
			return *static_cast<Derived*>(this);
		}

		template <typename T, std::size_t N, typename Derived>
		T& VectorCRTP<T, N, Derived>::operator[](const std::size_t& i)
		{
			if (!(0 <= i && i < size()))
				throw std::out_of_range("Index out of range.");
			return m_Data[i];
		}

		template <typename T, std::size_t N, typename Derived>
		const T& VectorCRTP<T, N, Derived>::operator[](const std::size_t& i) const
		{
			if (!(0 <= i && i < size()))
				throw std::out_of_range("Index out of range.");
			return m_Data[i];
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr Derived VectorCRTP<T, N, Derived>::zero() noexcept
		{
			return Derived(0);
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr Derived VectorCRTP<T, N, Derived>::one() noexcept
		{
			return Derived(1);
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr Derived VectorCRTP<T, N, Derived>::negativeInfinity() noexcept
		{
			return Derived(std::numeric_limits<float>::lowest());
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr Derived VectorCRTP<T, N, Derived>::positiveInfinity() noexcept
		{
			return Derived(std::numeric_limits<float>::max());
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr Derived VectorCRTP<T, N, Derived>::clampMagnitude(const VectorCRTP& v, const T& maxLen) noexcept
		{
			return v.sqrMagnitude() > maxLen ? Derived{ v.normalized() * maxLen } : Derived{ v.m_Data };
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr T VectorCRTP<T, N, Derived>::distance(const VectorCRTP& v1, const VectorCRTP& v2) noexcept
		{
			return (v1 - v2).magnitude();
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr Derived VectorCRTP<T, N, Derived>::lerp(const VectorCRTP& v1, const VectorCRTP& v2, const float& t) noexcept
		{
			// 限制t的范围[0,1]
			float rangeT = t < 0 ? 0 : (t > 1 ? 1 : t);
			return Derived(v1 * (1 - rangeT) + v2 * rangeT);
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr Derived VectorCRTP<T, N, Derived>::max(const VectorCRTP& v1, const VectorCRTP& v2) noexcept
		{
			VectorCRTP tmp;
			for (std::size_t i = 0; i < tmp.size(); ++i) {
				tmp[i] = std::max(v1.m_Data[i], v2.m_Data[i]);
			}
			return *static_cast<Derived*>(&tmp);
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr Derived VectorCRTP<T, N, Derived>::min(const VectorCRTP& v1, const VectorCRTP& v2) noexcept
		{
			VectorCRTP tmp;
			for (std::size_t i = 0; i < tmp.size(); ++i) {
				tmp[i] = std::min(v1.m_Data[i], v2.m_Data[i]);
			}
			return *static_cast<Derived*>(&tmp);
		}

		template <typename T, std::size_t N, typename Derived>
		void VectorCRTP<T, N, Derived>::normalize(VectorCRTP& v) noexcept
		{
			T m = 1 / v.magnitude();
			for (std::size_t i = 0; i < v.size(); ++i) {
				v.m_Data[i] *= m;
			}
		}

		/// 返回向量v1投影到v2后的投影向量
		template <typename T, std::size_t N, typename Derived>
		constexpr Derived VectorCRTP<T, N, Derived>::project(const VectorCRTP& v1, const VectorCRTP& v2)
		{
			return v1 * v2 / v2.sqrMagnitude() * v2;
		}

		template <typename T, std::size_t N, typename Derived>
		constexpr Derived VectorCRTP<T, N, Derived>::scale(const VectorCRTP& v1, const VectorCRTP& v2) noexcept
		{
			VectorCRTP tmp;
			for (std::size_t i = 0; i < v1.size(); ++i) {
				tmp[i] = v1.m_Data[i] * v2.m_Data[i];
			}
			return *static_cast<Derived*>(&tmp);
		}







		template <typename T, std::size_t N, typename Derived>
		Derived operator+(const VectorCRTP<T, N, Derived>& left, const VectorCRTP<T, N, Derived>& right) noexcept
		{
			VectorCRTP<T, N, Derived> tmp(left);
			return tmp += right;
		}

		template <typename T, std::size_t N, typename Derived>
		Derived operator-(const VectorCRTP<T, N, Derived>& left, const VectorCRTP<T, N, Derived>& right) noexcept
		{
			VectorCRTP<T, N, Derived> tmp(left);
			return tmp -= right;
		}

		template <typename T, std::size_t N, typename Derived>
		T operator*(const VectorCRTP<T, N, Derived>& left, const VectorCRTP<T, N, Derived>& right)
		{
			T ret = 0;
			for (std::size_t i = 0; i < left.size(); ++i) {
				ret += left[i] * right[i];
			}
			return ret;
		}

		template <typename T, std::size_t N, typename Derived>
		Derived operator*(const VectorCRTP<T, N, Derived>& left, const T& right) noexcept
		{
			VectorCRTP<T, N, Derived> tmp(left);
			;
			return tmp *= right;
		}

		template <typename T, std::size_t N, typename Derived>
		Derived operator*(const T& left, const VectorCRTP<T, N, Derived>& right) noexcept
		{
			VectorCRTP<T, N, Derived> tmp(right);
			return tmp *= left;
		}

		template <typename T, std::size_t N, typename Derived>
		Derived operator/(const VectorCRTP<T, N, Derived>& left, const T& right) noexcept
		{
			VectorCRTP<T, N, Derived> tmp(left);
			return tmp /= right;
		}

		template <typename T, std::size_t N, typename Derived>
		std::ostream& operator<<(std::ostream& out, const VectorCRTP<T, N, Derived>& v)
		{
			for (int i = 0; i < v.size(); i++) out << v[i] << " ";
			return out;
		}





		// 结构体帮助提取 Vector 的 N  
		template <typename VectorType>
		struct VectorTraits;
	}
}


#endif // !__VECTORCRTP__H__
