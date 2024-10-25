#include "../Rendering/Tgaimage.h"
#include "../Math/Vector/Vector.h"
#include "../Rendering/Model.h"
#include "../Geometry/Triangle.h"
#include "../Tool/Timer.h"
#include <random>
#include <functional>

using namespace DSM;
using namespace DSM::Geometry;
using namespace DSM::Math;

void TestEfficiency(TGAImage& image)
{
	std::mt19937 eigen(rand());
	std::uniform_int_distribution<int> rangeP(0, 512);
	std::uniform_int_distribution<int> rangeC(0, 255);

	Timer timer;
	for (std::size_t i = 0; i < 100; ++i) {
		Math::Vector2 t0[3] = { Math::Vector2(rangeP(eigen), rangeP(eigen)),
			Math::Vector2(rangeP(eigen), rangeP(eigen)),
			Math::Vector2(rangeP(eigen), rangeP(eigen)) };
		Triangle::triangleWithtBarycentric({ t0[0], t0[1], t0[2] },
			image, Color(rangeC(eigen), rangeC(eigen), rangeC(eigen), 255),
			[&](int x, int y, const Color& Color) {
				image.set(x, y, Color);
			});
	}
	timer.Stop("Draw Triangle:");
}

void TestTriangleRender(TGAImage& image)
{
	std::shared_ptr model = std::make_shared<Model>("D:/Code/Computer Graphics/DSMRenderer/obj/Elena.obj");
	std::mt19937 eigen(rand());
	std::uniform_int_distribution<int> rangeC(0, 255);

	for (int i = 0; i < model->facetSize(); i++) {
		std::vector<int> face = model->facet(i);
		Vector2 screen_coords[3];
		for (int j = 0; j < 3; j++) {
			Vector3 world_coords = model->vert(face[j]);
			screen_coords[j] = Vector2((world_coords.x() + 1.) * image.width() / 2.,
				(world_coords.y() + 1.) * image.height() / 2.);
		}
		Triangle::triangleWithoutExcess({ screen_coords[0], screen_coords[1], screen_coords[2] },
			image, Color(rangeC(eigen), rangeC(eigen), rangeC(eigen), 255),
			[&](int x, int y, const Color& Color) {
				image.set(x * 0.1 + 500, y * 0.1, Color);
			});
	}
}

void TestTriangleRenderWithLight(TGAImage& image)
{
	std::shared_ptr model = std::make_shared<Model>("D:/Code/Computer Graphics/DSMRenderer/obj/Elena.obj");

	// 光照方向
	Vector3 lightDir{ 0,0,1 };

	for (int i = 0; i < model->facetSize(); i++) {
		std::vector<int> face = model->facet(i);
		Vector3 worldCoords[3];
		Vector2 screen_coords[3];
		for (int j = 0; j < 3; j++) {
			worldCoords[j] = model->vert(face[j]);
			screen_coords[j] = Vector2((worldCoords[j].x() + 1.) * image.width() / 2.,
				(worldCoords[j].y() + 1.) * image.height() / 2.);
		}
		Vector3 normal = Vector3::cross(worldCoords[1] - worldCoords[0], worldCoords[2] - worldCoords[0]);
		float indensity = normal.normalized() * lightDir;
		if (indensity > 0)
			Triangle::triangleWithCross({ screen_coords[0], screen_coords[1], screen_coords[2] },
				image, Color(indensity * 255, indensity * 255, indensity * 255, 255),
				[&](int x, int y, const Color& Color) {
					image.set(x, y, Color); });
	}
}

void test()
{
	const int width = 1024;
	const int height = 1024;
	TGAImage image(width, height, TGAImage::RGB);

	Timer timer;
	TestTriangleRenderWithLight(image);

	image.write_tga_file("../Output/output.tga");
}

int main(int argc, char** argv)
{
	test();
	return 0;
}