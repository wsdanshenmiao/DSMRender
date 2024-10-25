#include "../Math/Vector/Vector.h"
#include "../Rendering/Tgaimage.h"
#include "../Geometry/Line.h"
#include <functional>

using namespace DSM;
using namespace DSM::Math;
using namespace DSM::Geometry;
using RenderFunc = const std::function<void(int, int, const Color&)>&;

Vector3 barycentric(const std::array<Vector3, 3>& ts, const Vector3& P)
{
	Vector3 u = Vector3::cross(
		Vector3(ts[2][0] - ts[0][0], ts[1][0] - ts[0][0], ts[0][0] - P[0]),
		Vector3(ts[2][1] - ts[0][1], ts[1][1] - ts[0][1], ts[0][1] - P[1]));
	if (std::abs(u.z()) < 1) return Vector3(-1, 1, 1);
	return Vector3(1.f - (u.x() + u.y()) / u.z(), u.y() / u.z(), u.x() / u.z());
}

bool inTriangle(const std::array<Vector3, 3>& ts, Vector3 p)
{
	Vector3 t0 = ts[0], t1 = ts[1], t2 = ts[2];
	Vector3 e0 = t1 - t0, e1 = t2 - t1, e2 = t0 - t2;
	Vector3 n0 = Vector3::cross(e0, t0 - p);
	Vector3 n1 = Vector3::cross(e1, t1 - p);
	Vector3 n2 = Vector3::cross(e2, t2 - p);
	//return n0 * n1 > 0 && n0 * n2 > 0;
	return n0.z() > 0 ? (n1.z() > 0 && n2.z() > 0) : (n1.z() <= 0 && n2.z() <= 0);
}


void triangleWithtBarycentric(const std::array<Vector3, 3>& ts, std::vector<float>& zBuffer, TGAImage& image, Color color, RenderFunc render) {
	Vector2 bMin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vector2 bMax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	Vector2 clamp(image.width() - 1, image.height() - 1);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 2; ++j) {
			bMin[j] = std::max(0.f, std::min(bMin[j], ts[i][j]));
			bMax[j] = std::min(clamp[j], std::max(bMax[j], ts[i][j]));
		}
	}
	Vector3 P{};
	for (P.x() = std::floor(bMin.x()); P.x() <= bMax.x(); P.x()++) {
		for (P.y() = std::floor(bMin.y()); P.y() <= bMax.y(); P.y()++) {
			Vector3 bcScreen = barycentric(ts, P);
			if (bcScreen.x() < -1e-2 || bcScreen.y() < -1e-2 || bcScreen.z() < -1e-2) continue;
			P.z() = 0;
			for (auto i = 0; i < 3; P.z() += ts[i].z() * bcScreen[i], ++i);
			int index = P.x() + image.width() * P.y();
			if (P.z() < zBuffer[index]) {	// 通过深度测试
				render(P.x(), P.y(), color);
				zBuffer[index] = P.z();
			}
		}
	}
}

void triangleWithCross(const std::array<Vector3, 3>& ts, std::vector<float>& zBuffer, TGAImage& image, Color color, RenderFunc render)
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
	for (auto i = std::floor(bMin.x()); i < bMax.x(); ++i) {
		for (auto j = std::floor(bMin.y()); j < bMax.y(); ++j) {
			if (inTriangle(ts, Vector3(i, j, 0))) {
				Vector3 bcScreen = barycentric(ts, Vector3(i, j, 0));
				float z = 0;
				for (auto i = 0; i < 3; z += ts[i].z() * bcScreen[i], ++i);
				int index = int(i + j * image.width());
				if (z < zBuffer[index]) {
					render(i, j, color);
					zBuffer[index] = z;
				}
			}
		}
	}
}

void triangleWithoutExcess(const std::array<Vector3, 3>& ts, std::vector<float>& zBuffer, TGAImage& image, Color color, RenderFunc render)
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
	for (int y = t0.y(); y <= t2.y() && y <= image.height() - 1; ++y) {
		bool firstHalf = y >= t1.y();	// 判断是否在上半边
		float len1 = firstHalf ? (float)(y - t1.y()) * invhalfH2 : (float)(y - t0.y()) * invHalfH1;
		float len2 = ((float)y - t0.y()) * invTotalH;
		Vector3 t01 = firstHalf ? t1 + (t2 - t1) * len1 : t0 + (t1 - t0) * len1;
		Vector3 t02 = t0 + (t2 - t0) * len2;
		if (t01.x() > t02.x())
			std::swap(t01, t02);

		// 绘制线框内部
		t01.x() = std::max(0.f, t01.x());
		t01.x() = std::min(image.width() - 1.f, t01.x());
		for (int x = t01.x(); x <= t02.x(); ++x) {
			Vector3 bcScreen = barycentric(ts, Vector3(x, y, 0));
			float z = 0;
			for (auto i = 0; i < 3; z += ts[i].z() * bcScreen[i], ++i);
			int index = int(x + y * image.width());
			if (z < zBuffer[index]) {	// 通过深度测试
				render(x, y, color);
				zBuffer[index] = z;
			}
		}
	}
}



Vector3 WorldToScreen(const Vector3& v, const TGAImage& image)
{
	float scale = 0.1;
	return Vector3(int((v.x() + 1.f) * image.width() / 2.f) * scale + 250, int((v.y() + 1.f) * image.height() / 2.f) * scale, v.z());
}

void TestZ_Buffer()
{
	TGAImage scene(512, 512, TGAImage::RGB);
	std::shared_ptr model = std::make_shared<Model>("D:/Code/Computer Graphics/DSMRenderer/obj/Model/Elena.obj");
	std::vector<float> zBuffer(scene.width() * scene.height(), std::numeric_limits<float>::max());
	Vector3 lightDir{ 0,0,-1 };

	auto render = [&](int x, int y, const Color& color) {
		scene.set(x, y, color);
		};

	for (auto i = 0; i < model->facetSize(); ++i) {
		auto facet = model->facet(i);
		std::array<Vector3, 3> ts;
		std::array<Vector3, 3> worldCoords;
		for (auto j = 0; j < 3; ++j) {
			worldCoords[j] = model->vert(facet[j]);
			ts[j] = WorldToScreen(worldCoords[j], scene);
		}
		Vector3 normal = Vector3::cross(worldCoords[1] - worldCoords[0], worldCoords[2] - worldCoords[0]);
		float indensity = normal.normalized() * lightDir;
		if (indensity > 0) {
			triangleWithCross(ts, zBuffer, scene, Color(indensity * 255, indensity * 255, indensity * 255, 255), render);
		}
	}

	scene.write_tga_file("../Output/output.tga");
}

int main()
{
	TestZ_Buffer();
	return 0;
}