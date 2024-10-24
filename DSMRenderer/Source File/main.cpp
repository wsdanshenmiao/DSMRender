#include "../Rendering/Tgaimage.h"
#include "../Rendering/Model.h"
#include "../Geometry/Line.h"
#include "../Math/Vector/Vector.h"
#include "../Math/Matrix/Matrix.h"
#include "../Tool/Timer.h"
#include <random>
#include <memory>

using namespace DSM;
using namespace DSM::Geometry;

void triangle(Math::Vector2 t0, Math::Vector2 t1, Math::Vector2 t2, TGAImage& image, Color color)
{
	if (t0.y() == t1.y() && t0.y() == t2.y())return;
	// 由下到上分别为t0,t1,t2
	if (t0.y() > t1.y())
		std::swap(t0, t1);
	if (t0.y() > t2.y())
		std::swap(t0, t2);
	if (t1.y() > t2.y())
		std::swap(t1, t2);
	float totalHeight = t2.y() - t0.y();
	float halfHeight1 = t1.y() - t0.y(); // 防止到达t0,t1高度相同
	float halfHeight2 = t2.y() - t1.y();
	// 沿着线绘制三角形
	for (int y = t0.y(); y <= t2.y(); ++y) {
		bool firstHalf = y >= t1.y();	// 判断是否在上半边
		float len1 = firstHalf ? (float)(y - t1.y()) / halfHeight2 : (float)(y - t0.y()) / halfHeight1;
		float len2 = (float)(y - t0.y()) / totalHeight;
		Math::Vector2 t01 = firstHalf ? t1 + (t2 - t1) * len1 : t0 + (t1 - t0) * len1;
		Math::Vector2 t02 = t0 + (t2 - t0) * len2;
		if (t01.x() > t02.x())
			std::swap(t01, t02);
		// 绘制线框内部
		for (int x = t01.x(); x <= t02.x(); image.set(x, y, color), ++x);
	}
}

int main(int argc, char** argv)
{
	std::shared_ptr<Model> model = nullptr;
	const int width = 512;
	const int height = 512;
	float scale = 10;
	float transX = 1000;

	//if (2 == argc) {
	//	model = std::make_unique<Model>(argv[1]);
	//}
	//else {
	//	model = std::make_unique<Model>("D:/Code/Computer Graphics/DSMRenderer/obj/Elena.obj");
	//}

	TGAImage image(width, height, TGAImage::RGB);

	Math::Vector2 t0[3] = { Math::Vector2(10, 70),   Math::Vector2(50, 160),  Math::Vector2(70, 80) };
	Math::Vector2 t1[3] = { Math::Vector2(180, 50),  Math::Vector2(150, 1),   Math::Vector2(70, 180) };
	Math::Vector2 t2[3] = { Math::Vector2(180, 150), Math::Vector2(120, 160), Math::Vector2(130, 180) };
	triangle(t0[0], t0[1], t0[2], image, Color::red());
	triangle(t1[0], t1[1], t1[2], image, Color::white());
	triangle(t2[0], t2[1], t2[2], image, Color::green());
	//auto render = [&](int x, int y, const Color& color) {
	//	image.set(x, y, color);
	//	};
	//Line::LineRender(model, render, Math::Vector2{ width, height });

	image.write_tga_file("output.tga");
	return 0;
}
