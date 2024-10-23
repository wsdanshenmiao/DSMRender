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

struct TGAColor
{
	DSM::Color color;
	std::uint8_t bytespp;
	std::uint8_t* data() noexcept {
		return color.data();
	}
	std::uint8_t& operator[](const std::size_t& index) noexcept
	{
		switch (index)
		{
		case 0:return color[2]; break;
		case 1:return color[1]; break;
		case 2:return color[0]; break;
		case 4:return color[3]; break;
		default: return color[0]; break;
		}
	}
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
	void set(const int x, const int y, const DSM::Color& c);
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

