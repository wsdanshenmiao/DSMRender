#include "../Rendering/Tgaimage.h"
#include "../Geometry/Line.h"
#include "../Math/Vector/Vector.h"
#include "../Math/Matrix/Matrix.h"
#include "../Tool/Timer.h"
#include "model.h"
#include "geometry.h"
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
	TGAImage image(2048, 2048, TGAImage::RGB);

	Vector2 t0[3] = { Vector2(100, 700),   Vector2(500, 1600),  Vector2(700, 800) };
	Vector2 t1[3] = { Vector2(1800, 500),  Vector2(1500, 10),   Vector2(700, 1800) };
	Vector2 t2[3] = { Vector2(1800, 1500), Vector2(1200, 1600), Vector2(1300, 1800) };
	triangle(t0[0], t0[1], t0[2], image, Color::red());
	triangle(t1[0], t1[1], t1[2], image, Color::blue());
	triangle(t2[0], t2[1], t2[2], image, Color::green());

	image.write_tga_file("output.tga");
	return 0;
}
