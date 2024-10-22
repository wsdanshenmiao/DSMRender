#pragma once
#include <cstdint>
#include <fstream>
#include <vector>
#include "Color.h"

#pragma pack(push,1)
struct TGAHeader {
	std::uint8_t  idlength = 0;
	std::uint8_t  colormaptype = 0;
	std::uint8_t  datatypecode = 0;
	std::uint16_t colormaporigin = 0;
	std::uint16_t colormaplength = 0;
	std::uint8_t  colormapdepth = 0;
	std::uint16_t x_origin = 0;
	std::uint16_t y_origin = 0;
	std::uint16_t width = 0;
	std::uint16_t height = 0;
	std::uint8_t  bitsperpixel = 0;
	std::uint8_t  imagedescriptor = 0;
};
#pragma pack(pop)

class TGAColor :public DSM::Color
{
public:
	TGAColor() noexcept
		:Color(std::array<std::uint8_t, 4>{0}), bytespp(4) {}
	TGAColor(const std::uint8_t v, const std::uint8_t byte = 4) noexcept
		:Color(std::array<std::uint8_t, 4>{v, v, v, v}), bytespp(byte) {}
	TGAColor(
		const std::uint8_t r, const std::uint8_t g,
		const std::uint8_t b, const std::uint8_t a, const std::uint8_t byte = 4) noexcept
		:Color(std::array<std::uint8_t, 4>{r, g, b, a}), bytespp(byte) {}
	TGAColor(const std::array<std::uint8_t, 4>& color, const std::uint8_t byte = 4) noexcept
		:Color(color), bytespp(byte) {}
	TGAColor(std::array<std::uint8_t, 4>&& color, const std::uint8_t byte = 4) noexcept
		:Color(std::move(color)), bytespp(byte) {}

public:
	std::uint8_t bytespp;
};

struct TGAImage
{
	enum Format { GRAYSCALE = 1, RGB = 3, RGBA = 4 };

	TGAImage() = default;
	TGAImage(const int w, const int h, const int bpp);
	bool  read_tga_file(const std::string filename);
	bool write_tga_file(const std::string filename, const bool vflip = true, const bool rle = true) const;
	void flip_horizontally();
	void flip_vertically();
	TGAColor get(const int x, const int y) const;
	void set(const int x, const int y, TGAColor& c);
	int width()  const;
	int height() const;
private:
	bool   load_rle_data(std::ifstream& in);
	bool unload_rle_data(std::ofstream& out) const;

	int w = 0;
	int h = 0;
	std::uint8_t bpp = 0;
	std::vector<std::uint8_t> data = {};
};

