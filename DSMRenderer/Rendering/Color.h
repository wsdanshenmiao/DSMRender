#pragma once
#ifndef __COLOR__H__
#define __COLOR__H__

#include <array>
#include <stdexcept>

namespace DSM {
	class Color
	{
	public:
		Color() noexcept;
		explicit Color(const std::uint8_t v) noexcept;
		Color(
			const std::uint8_t r, const std::uint8_t g,
			const std::uint8_t b, const std::uint8_t a) noexcept;
		Color(const std::array<std::uint8_t, 4>& color) noexcept;
		Color(std::array<std::uint8_t, 4>&& color) noexcept;

		constexpr auto& r() noexcept;
		constexpr auto& g() noexcept;
		constexpr auto& b() noexcept;
		constexpr auto& a() noexcept;
		std::uint8_t* data() noexcept;

		std::uint8_t& operator[](const std::size_t& index) noexcept;
		const std::uint8_t& operator[](const std::size_t& index) const noexcept;
		constexpr auto& operator+=(const Color& other) noexcept;
		constexpr auto& operator-=(const Color& other) noexcept;
		constexpr auto& operator*=(const Color& other) noexcept;
		constexpr auto& operator*=(const float& v) noexcept;
		constexpr auto& operator/=(const float& v) noexcept;

		static Color lerp(const Color& c1, const Color& c2, const float& t) noexcept;

	protected:
		std::array<std::uint8_t, 4> m_Color;
	};


	Color operator+(const Color& left, const Color& right) noexcept;
	Color operator-(const Color& left, const Color& right) noexcept;
	Color operator*(const Color& left, const Color& right) noexcept;
	Color operator*(const Color& left, const float& v) noexcept;
	Color operator/(const Color& left, const float& v) noexcept;
}

#endif // !__COLOR__H__
