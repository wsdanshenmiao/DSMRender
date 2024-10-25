#include "../Rendering/Model.h"
#include "../Geometry/Line.h"
#include <memory>

using namespace DSM;
using namespace DSM::Geometry;

void TestLineRender(int argc, char** argv)
{
	std::shared_ptr<Model> model;

	const int width = 512;
	const int height = 512;
	TGAImage image(width, height, TGAImage::RGB);

	if (2 == argc) {
		model = std::make_shared<Model>(argv[1]);
	}
	else {
		model = std::make_shared<Model>("D:/Code/Computer Graphics/DSMRenderer/obj/Elena.obj");
	}
	auto render = [&](int x, int y, const Color& color) {
		image.set(x * 0.1 + 200, y * 0.1, color);
		};
	Line::LineRender(model, render, Math::Vector2{ width, height });

	image.write_tga_file("../Output/LineRender_Elena.tga");
}

//int main(int argc, char** argv)
//{
//	TestLineRender(argc, argv);
//	return 0;
//}