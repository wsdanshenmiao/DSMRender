#pragma once
#ifndef __COLOR__H__
#define __COLOR__H__

#include <array>

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

		std::uint8_t& r() noexcept;
		std::uint8_t& g() noexcept;
		std::uint8_t& b() noexcept;
		std::uint8_t& a() noexcept;
		const std::uint8_t& r() const noexcept;
		const std::uint8_t& g() const noexcept;
		const std::uint8_t& b() const noexcept;
		const std::uint8_t& a() const noexcept;
		const std::uint8_t* data() const noexcept;
		std::uint8_t* data() noexcept;

		std::uint8_t& operator[](const std::size_t& index) noexcept;
		const std::uint8_t& operator[](const std::size_t& index) const noexcept;
		auto& operator+=(const Color& other) noexcept;
		auto& operator-=(const Color& other) noexcept;
		auto& operator*=(const Color& other) noexcept;
		auto& operator*=(const float& v) noexcept;
		auto& operator/=(const float& v) noexcept;

		static Color lerp(const Color& c1, const Color& c2, const float& t) noexcept;
		static Color white() noexcept;
		static Color black()noexcept;
		static Color red() noexcept;
		static Color green() noexcept;
		static Color blue() noexcept;

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
