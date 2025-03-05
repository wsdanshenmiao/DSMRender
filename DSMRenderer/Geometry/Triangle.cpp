#include "Triangle.h"

using namespace DSM::Math;

namespace DSM {
	namespace Geometry {
		using namespace Rendering;

		void Triangle::triangleWithtBarycentric(const std::array<VToP, 3>& vToPs, std::vector<float>& zBuffer, TGAImage& image, const std::unique_ptr<IShader>& shader) {
			// 选取边界
			Vector2 bMin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
			Vector2 bMax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
			Vector2 clamp(image.width() - 1, image.height() - 1);
			for (const auto& vToP : vToPs) {
				for (int j = 0; j < 2; ++j) {
					bMin[j] = std::max(0.f, std::min(bMin[j], vToP.m_PosH[j]));
					bMax[j] = std::min(clamp[j], std::max(bMax[j], vToP.m_PosH[j]));
				}
			}
			Vector3 P{};
			for (P.x() = std::floor(bMin.x()); P.x() <= bMax.x(); P.x()++) {
				for (P.y() = std::floor(bMin.y()); P.y() <= bMax.y(); P.y()++) {
					Vector3 bcScreen = barycentric(vToPs, Vector3(P.x() + .5f, P.y() + .5f, P.z()));
					if (bcScreen.x() < -1e-1f || bcScreen.y() < -1e-1f || bcScreen.z() < -1e-1f) continue;
					P.z() = 0;
					for (auto i = 0; i < 3; P.z() += vToPs[i].m_PosH.z() * bcScreen[i], ++i);
					int index = P.x() + image.width() * P.y();
					if (P.z() > zBuffer[index]) {	// 通过深度测试
						VToP vToP{};
						for (auto i = 0; i < 3; ++i) {
							vToP.m_PosH += vToPs[i].m_PosH * bcScreen[i];
							vToP.m_Normal += vToPs[i].m_Normal * bcScreen[i];
							vToP.m_TexCoord += vToPs[i].m_TexCoord * bcScreen[i];
							vToP.m_Color += vToPs[i].m_Color * bcScreen[i];
						}
						Color color = shader->pixelShader(vToP);
						image.set(P.x(), P.y(), color);
						zBuffer[index] = P.z();
					}
				}
			}
		}

		void Triangle::triangleWithCross(const std::array<VToP, 3>& vToPs, std::vector<float>& zBuffer, TGAImage& image, const std::unique_ptr<IShader>& shader)
		{
			// 最左下角的点和最右上角的点
			Vector2 bMin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
			Vector2 bMax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
			Vector2 clamp(image.width() - 1, image.height() - 1);
			for (const auto& vToP : vToPs) {
				for (int j = 0; j < 2; ++j) {
					bMin[j] = std::max(0.f, std::min(bMin[j], vToP.m_PosH[j]));
					bMax[j] = std::min(clamp[j], std::max(bMax[j], vToP.m_PosH[j]));
				}
			}
			// 遍历范围内的每一个点
			for (auto i = std::floor(bMin.x()); i <= bMax.x(); ++i) {
				for (auto j = std::floor(bMin.y()); j <= bMax.y(); ++j) {
					if (inTriangle(vToPs, Vector3(i + .5f, j + .5f, 0))) {
						Vector3 bcScreen = barycentric(vToPs, Vector3(i + .5f, j + .5f, 0));
						float z = 0;
						for (auto i = 0; i < 3; z += vToPs[i].m_PosH.z() * bcScreen[i], ++i);
						int index = int(i + j * image.width());
						if (z > zBuffer[index]) {
							VToP vToP = shader->linearInterpolation(vToPs, bcScreen);
							Color color = shader->pixelShader(vToP);
							image.set(i, j, color);
							zBuffer[index] = z;
						}
					}
				}
			}
		}

		//void Triangle::triangleWithoutExcess(const std::array<Vector3, 3>& ts, std::vector<float>& zBuffer, TGAImage& image, Color color, RenderFunc render)
		//{
		//	auto [t0, t1, t2] = ts;
		//	if (t0.y() == t1.y() && t0.y() == t2.y())return;
		//	// 由下到上分别为t0,t1,t2
		//	if (t0.y() > t1.y())
		//		std::swap(t0, t1);
		//	if (t0.y() > t2.y())
		//		std::swap(t0, t2);
		//	if (t1.y() > t2.y())
		//		std::swap(t1, t2);
		//	float invTotalH = 1 / (t2.y() - t0.y() + 1);
		//	float invHalfH1 = 1 / (t1.y() - t0.y() + 1); // 防止到达t0,t1高度相同
		//	float invhalfH2 = 1 / (t2.y() - t1.y() + 1);
		//	// 沿着线绘制三角形
		//	for (int y = t0.y(); y <= t2.y() && y <= image.height() - 1; ++y) {
		//		bool firstHalf = y >= t1.y();	// 判断是否在上半边
		//		float len1 = firstHalf ? (float)(y - t1.y()) * invhalfH2 : (float)(y - t0.y()) * invHalfH1;
		//		float len2 = ((float)y - t0.y()) * invTotalH;
		//		Vector3 t01 = firstHalf ? t1 + (t2 - t1) * len1 : t0 + (t1 - t0) * len1;
		//		Vector3 t02 = t0 + (t2 - t0) * len2;
		//		if (t01.x() > t02.x())
		//			std::swap(t01, t02);

		//		// 绘制线框内部
		//		t01.x() = std::max(0.f, t01.x());
		//		t01.x() = std::min(image.width() - 1.f, t01.x());
		//		for (int x = t01.x(); x <= t02.x(); ++x) {
		//			Vector3 bcScreen = barycentric(ts, Vector3(x, y, 0));
		//			float z = 0;
		//			for (auto i = 0; i < 3; z += ts[i].z() * bcScreen[i], ++i);
		//			int index = int(x + y * image.width());
		//			if (z < zBuffer[index]) {	// 通过深度测试
		//				render(x, y, color);
		//				zBuffer[index] = z;
		//			}
		//		}
		//	}
		//}







		Vector3 Triangle::barycentric(const std::array<VToP, 3>& vToPs, const Vector3& P) noexcept
		{
			Vector4 ts[3] = { vToPs[0].m_PosH,vToPs[1].m_PosH,vToPs[2].m_PosH };
			Vector3 u = Vector3::cross(
				Vector3(ts[2].x() - ts[0].x(), ts[1].x() - ts[0].x(), ts[0].x() - P.x()),
				Vector3(ts[2].y() - ts[0].y(), ts[1].y() - ts[0].y(), ts[0].y() - P.y()));
			if (std::abs(u.z()) < 1) return Vector3(-1, 1, 1);
			return Vector3(1.f - (u.x() + u.y()) / u.z(), u.y() / u.z(), u.x() / u.z());
		}

		bool Triangle::inTriangle(const std::array<VToP, 3>& vToPs, Vector3 p) noexcept
		{
			Vector3 ts[3];
			for (auto i = 0; i < 3; ++i) {
				auto& v = vToPs[i].m_PosH;
				ts[i] = Vector3{ v.x(),v.y(),v.z() };
			}
			Vector3 t0 = ts[0], t1 = ts[1], t2 = ts[2];
			Vector3 e0 = t1 - t0, e1 = t2 - t1, e2 = t0 - t2;
			Vector3 n0 = Vector3::cross(e0, t0 - p);
			Vector3 n1 = Vector3::cross(e1, t1 - p);
			Vector3 n2 = Vector3::cross(e2, t2 - p);
			//return n0 * n1 > 0 && n0 * n2 > 0;
			return n0.z() > 0 ? (n1.z() > 0 && n2.z() > 0) : (n1.z() <= 0 && n2.z() <= 0);
		}


	}
}
