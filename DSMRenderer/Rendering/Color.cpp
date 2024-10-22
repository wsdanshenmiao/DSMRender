#include "Color.h"

namespace DSM {

	Color::Color() noexcept
		:m_Color(std::array<std::uint8_t, 4>{0}) {}

	Color::Color(const std::uint8_t v) noexcept
		:m_Color(std::array<std::uint8_t, 4>{v, v, v, v}) {}

	Color::Color(
		const std::uint8_t r, const std::uint8_t g,
		const std::uint8_t b, const std::uint8_t a) noexcept
		:m_Color(std::array<std::uint8_t, 4>{r, g, b, a}) {}

	Color::Color(const std::array<std::uint8_t, 4>& color) noexcept
		:m_Color(color) {}

	Color::Color(std::array<std::uint8_t, 4>&& color) noexcept
		:m_Color(std::move(color)) {}

	constexpr auto& Color::r() noexcept
	{
		return m_Color[0];
	}

	constexpr auto& Color::g() noexcept
	{
		return m_Color[1];
	}

	constexpr auto& Color::b() noexcept
	{
		return m_Color[2];
	}

	constexpr auto& Color::a() noexcept
	{
		return m_Color[3];
	}

	std::uint8_t* Color::data() noexcept
	{
		return m_Color.data();
	}

	std::uint8_t& Color::operator[](const std::size_t& index) noexcept
	{
		return m_Color[index];
	}

	const std::uint8_t& Color::operator[](const std::size_t& index) const noexcept
	{
		return m_Color[index];
	}

	constexpr auto& Color::operator+=(const Color& other) noexcept
	{
		for (auto i = m_Color.size(); i--; m_Color[i] = std::min(m_Color[i] + other[i], 255));
		return *this;
	}

	constexpr auto& Color::operator-=(const Color& other) noexcept
	{
		for (auto i = m_Color.size(); i--; m_Color[i] = std::max(m_Color[i] + other[i], 0));
		return *this;
	}

	constexpr auto& Color::operator*=(const Color& other) noexcept
	{
		for (auto i = m_Color.size(); i--;) {
			int c = m_Color[i] * other[i];
			m_Color[i] = static_cast<std::uint8_t>(c / 255);
		}
		return *this;
	}

	constexpr auto& Color::operator*=(const float& v) noexcept
	{
		float value = std::max(v, 0.f);
		for (auto& c : m_Color) {
			c = value < 1.0f ? static_cast<std::uint8_t>(c * value) :
				std::min<int>(static_cast<int>(c * value), 255);
		}
		return *this;
	}

	constexpr auto& Color::operator/=(const float& v) noexcept
	{
		float value = std::max(v, 0.f);
		for (auto& c : m_Color) {
			c = value >= 1.0f ? static_cast<std::uint8_t>(c / value) :
				std::min<int>(static_cast<int>(c / value), 255);
		}
		return *this;
	}

	Color Color::lerp(const Color& c1, const Color& c2, const float& t) noexcept
	{
		return c1 * (1 - t) + c2 * t;
	}






	Color operator+(const Color& left, const Color& right) noexcept
	{
		Color ret{ left };
		return ret += right;
	}

	Color operator-(const Color& left, const Color& right) noexcept
	{
		Color ret{ left };
		return ret -= right;
	}

	Color operator*(const Color& left, const Color& right) noexcept
	{
		Color ret{ left };
		return ret *= right;
	}

	Color operator*(const Color& left, const float& v) noexcept
	{
		Color ret{ left };
		return ret *= v;
	}

	Color operator/(const Color& left, const float& v) noexcept
	{
		Color ret{ left };
		return ret /= v;
	}

}
