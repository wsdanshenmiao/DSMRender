#include "../Rendering/Tgaimage.h"
#include "../Math/Vector/Vector.h"
#include "../Rendering/Model.h"
#include "../Tool/Timer.h"
#include <random>
#include <functional>

using namespace DSM;
using namespace DSM::Math;
using RenderFunc = const std::function<void(int, int, const Color&)>&;

bool inTriangle(const std::array<Vector2, 3>& ts, Vector3 p)
{
	Vector3 t0 = ts[0], t1 = ts[1], t2 = ts[2];
	Vector3 e0 = t1 - t0, e1 = t2 - t1, e2 = t0 - t2;
	Vector3 n0 = Vector3::cross(e0, t0 - p);
	Vector3 n1 = Vector3::cross(e1, t1 - p);
	Vector3 n2 = Vector3::cross(e2, t2 - p);
	return n0 * n1 >= 0 && n0 * n2 >= 0;
	//return n0.z() > 0 ? (n1.z() > 0 && n2.z() > 0) : (n1.z() <= 0 && n2.z() <= 0);
}

Vector3 barycentric(const std::array<Vector2, 3>& ts, Vector2 P)
{
	Vector3 u = Vector3::cross(
		Vector3(ts[2][0] - ts[0][0], ts[1][0] - ts[0][0], ts[0][0] - P[0]),
		Vector3(ts[2][1] - ts[0][1], ts[1][1] - ts[0][1], ts[0][1] - P[1]));
	if (std::abs(u.z()) < 1) return Vector3(-1, 1, 1);
	return Vector3(1.f - (u.x() + u.y()) / u.z(), u.y() / u.z(), u.x() / u.z());
}

void triangleWithtBarycentric(const std::array<Vector2, 3>& ts, TGAImage& image, Color color, RenderFunc render) {
	Vector2 bMin(image.width() - 1, image.height() - 1);
	Vector2 bMax(0, 0);
	Vector2 clamp(image.width() - 1, image.height() - 1);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 2; ++j) {
			bMin[j] = std::max(0.f, std::min(bMin[j], ts[i][j]));
			bMax[j] = std::min(clamp[j], std::max(bMax[j], ts[i][j]));
		}
	}
	Vector2 P;
	for (P.x() = bMin.x(); P.x() <= bMax.x(); P.x()++) {
		for (P.y() = bMin.y(); P.y() <= bMax.y(); P.y()++) {
			Vector3 bc_screen = barycentric(ts, P);
			if (bc_screen.x() < 0 || bc_screen.y() < 0 || bc_screen.z() < 0) continue;
			render(P.x(), P.y(), color);
		}
	}
}


void triangleWithoutExcess(const std::array<Vector2, 3>& ts, TGAImage& image, Color color, RenderFunc render)
{
	auto [t0, t1, t2] = ts;
	if (t0.y() == t1.y() && t0.y() == t2.y())return;
	// 由下到上分别为t0,t1,t2
	if (t0.y() > t1.y())
		std::swap(t0, t1);
	if (t0.y() > t2.y())
		std::swap(t0, t2);
	if (t1.y() > t2.y())
		std::swap(t1, t2);
	float invTotalH = 1 / (t2.y() - t0.y() + 1);
	float invHalfH1 = 1 / (t1.y() - t0.y() + 1); // 防止到达t0,t1高度相同
	float invhalfH2 = 1 / (t2.y() - t1.y() + 1);
	// 沿着线绘制三角形
	//  && y <= image.height() - 1
	for (int y = t0.y(); y <= t2.y(); ++y) {
		bool firstHalf = y >= t1.y();	// 判断是否在上半边
		float len1 = firstHalf ? (float)(y - t1.y()) * invhalfH2 : (float)(y - t0.y()) * invHalfH1;
		float len2 = (float)(y - t0.y()) * invTotalH;
		Math::Vector2 t01 = firstHalf ? t1 + (t2 - t1) * len1 : t0 + (t1 - t0) * len1;
		Math::Vector2 t02 = t0 + (t2 - t0) * len2;
		if (t01.x() > t02.x())
			std::swap(t01, t02);

		// 绘制线框内部
		//t01.x() = std::max(0.f, t01.x());
		//t01.x() = std::min(image.width() - 1.f, t01.x());
		for (int x = t01.x(); x <= t02.x(); render(x, y, color), ++x);
	}
}


void triangleWithCross(const std::array<Vector2, 3>& ts, TGAImage& image, Color color, RenderFunc render)
{
	// 最左下角的点和最右上角的点
	Vector2 bMin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vector2 bMax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	Vector2 clamp(image.width() - 1, image.height() - 1);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 2; ++j) {
			bMin[j] = std::max(0.f, std::min(bMin[j], ts[i][j]));
			bMax[j] = std::min(clamp[j], std::max(bMax[j], ts[i][j]));
		}
	}
	// 遍历范围内的每一个点
	for (auto i = bMin.x(); i < bMax.x(); ++i) {
		for (auto j = bMin.y(); j < bMax.y(); ++j) {
			if (inTriangle(ts, Vector3(i, j, 0))) {
				render(i, j, color);
			}
		}
	}
}


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
		triangleWithtBarycentric({ t0[0], t0[1], t0[2] },
			image, Color(rangeC(eigen), rangeC(eigen), rangeC(eigen), 255),
			[&](int x, int y, const Color& Color) {
				image.set(x, y, Color);
			});
	}
	timer.Stop("Draw Triangle:");
}

Vector2 WorldToScreen(const Vector3& v, const TGAImage& image)
{
	float scale = 0.2;
	return Vector2(int((v.x() + 1.f) * image.width() / 2.f) * scale + 250, int((v.y() + 1.f) * image.height() / 2.f) * scale);
}


void TestTriangleRender(TGAImage& image)
{
	std::shared_ptr model = std::make_shared<Model>("D:/Code/Computer Graphics/DSMRenderer/obj/Elena_Triangle.obj");
	std::mt19937 eigen(rand());
	std::uniform_int_distribution<int> rangeC(0, 255);

	for (int i = 0; i < model->facetSize(); i++) {
		std::vector<int> face = model->facet(i);
		Vector2 screen_coords[3];
		for (int j = 0; j < 3; j++) {
			Vector3 world_coords = model->vert(face[j]);
			screen_coords[j] = WorldToScreen(world_coords, image);
		}
		triangleWithoutExcess({ screen_coords[0], screen_coords[1], screen_coords[2] },
			image, Color(rangeC(eigen), rangeC(eigen), rangeC(eigen), 255),
			[&](int x, int y, const Color& Color) {
				image.set(x, y, Color);
			});
	}
}

void TestTriangleRenderWithLight(TGAImage& image)
{
	std::shared_ptr model = std::make_shared<Model>("D:/Code/Computer Graphics/DSMRenderer/obj/Model/dragon.obj");

	// 光照方向
	Vector3 lightDir{ 0,0,-1 };

	for (int i = 0; i < model->facetSize(); i++) {
		std::vector<int> face = model->facet(i);
		Vector3 worldCoords[3];
		Vector2 screen_coords[3];
		for (int j = 0; j < 3; j++) {
			worldCoords[j] = model->vert(face[j]);
			screen_coords[j] = WorldToScreen(worldCoords[j], image);
		}
		Vector3 normal = Vector3::cross(worldCoords[1] - worldCoords[0], worldCoords[2] - worldCoords[0]);
		float indensity = normal.normalized() * lightDir;
		if (indensity > 0)
			triangleWithoutExcess({ screen_coords[0], screen_coords[1], screen_coords[2] },
				image, Color(indensity * 255, indensity * 255, indensity * 255, 255),
				[&](int x, int y, const Color& Color) {
					image.set(x, y, Color); });
	}
}

void test()
{
	const int width = 512;
	const int height = 512;
	TGAImage image(width, height, TGAImage::RGB);

	Timer timer;
	TestTriangleRenderWithLight(image);

	image.write_tga_file("../Output/output.tga");
}

//int main(int argc, char** argv)
//{
//	test();
//	return 0;
//}