#include "../Rendering/Tgaimage.h"
#include "../Geometry/Line.h"
#include "../Math/Vector/Vector.h"
#include "../Math/Matrix/Matrix.h"
#include "../Tool/Timer.h"
#include "model.h"
#include "geometry.h"
#include <random>
#include <memory>

using namespace DSM::Math;
using namespace DSM::Geometry;

void triangle(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, TGAColor color) {
	Line{ t0, t1, color }.DrawLine(image);
	Line{ t1, t2, color }.DrawLine(image);
	Line{ t2, t0, color }.DrawLine(image);
}

int main(int argc, char** argv)
{
	TGAImage image(1024, 1024, TGAImage::RGB);
	const TGAColor white = TGAColor(255, 255, 255, 255);
	const TGAColor red = TGAColor(255, 0, 0, 255);
	const TGAColor green = TGAColor(0, 255, 0, 255);
	Vector2 t0[3] = { Vector2(10, 70),   Vector2(50, 160),  Vector2(70, 80) };
	Vector2 t1[3] = { Vector2(180, 50),  Vector2(150, 1),   Vector2(70, 180) };
	Vector2 t2[3] = { Vector2(180, 150), Vector2(120, 160), Vector2(130, 180) };
	triangle(t0[0], t0[1], t0[2], image, red);
	triangle(t1[0], t1[1], t1[2], image, white);
	triangle(t2[0], t2[1], t2[2], image, green);

	image.write_tga_file("output.tga");
	return 0;
}
