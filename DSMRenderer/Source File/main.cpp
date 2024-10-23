#include "../Rendering/Tgaimage.h"
#include "../Rendering/Model.h"
#include "../Geometry/Line.h"
#include "../Math/Vector/Vector.h"
#include "../Math/Matrix/Matrix.h"
#include "../Tool/Timer.h"
#include <random>
#include <memory>

using namespace DSM;
using namespace DSM::Math;
using namespace DSM::Geometry;

void triangle(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, Color color) {
	auto render = [&](int x, int y, const Color& color) {
		image.set(x, y, color);
		};
	Line{ t0, t1, color }.DrawLine(render);
	Line{ t1, t2, color }.DrawLine(render);
	Line{ t2, t0, color }.DrawLine(render);
}

int main(int argc, char** argv)
{
	Model* model = nullptr;
	const int width = 2048;
	const int height = 2048;
	float scale = 10;
	float transX = 1000;
	if (2 == argc) {
		model = new Model(argv[1]);
	}
	else {
		model = new Model("D:/Code/Computer Graphics/DSMRenderer/obj/Elena.obj");
	}

	TGAImage image(width, height, TGAImage::RGB);
	for (int i = 0; i < model->facetSize(); i++) {
		std::vector<int> face = model->facet(i);
		for (int j = 0; j < 3; j++) {
			Vector3 v0 = model->vert(face[j]);
			Vector3 v1 = model->vert(face[(j + 1) % 3]);
			float x0 = (v0.x() + 1.f) * width / 2.f / scale + transX;
			float y0 = (v0.y() + 1.f) * height / 2.f / scale;
			float x1 = (v1.x() + 1.f) * width / 2.f / scale + transX;
			float y1 = (v1.y() + 1.f) * height / 2.f / scale;
			Line({ x0, y0 }, { x1, y1 }, Color::white()).DrawLine([&](int x, int y, const Color& color) {
				image.set(x, y, color);
				});
		}
	}

	image.write_tga_file("output.tga");
	delete model;
	return 0;
}
