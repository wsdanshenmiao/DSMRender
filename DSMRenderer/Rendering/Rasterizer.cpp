#include "Rasterizer.h"
#include "../Math/Vector/Vector.h"
#include "../Geometry/Triangle.h"

namespace DSM {
	namespace Rendering {
		using namespace Math;

		Rasterizer::Rasterizer(const std::shared_ptr<TGAImage>& target)
			:m_RenderTarget(target) {}

		void Rasterizer::draw()
		{
			for (const auto& object : m_Objects) {
				std::vector<float> zBuffer(m_RenderTarget->width() * m_RenderTarget->height(), -std::numeric_limits<float>::max());
				auto& model = object.getModel();
				auto& shader = object.getShader();
				shader->setWorldMatrix(object.getTransform().getWorldMatrix());
				shader->setWorldInvTransposeMatrix(object.getTransform().getWorldInvTransposeMatrix());
				for (auto i = 0; i < model->facetSize(); ++i) {
					std::array<VToP, 3> vToPs;
					// 处理每个顶点
					for (auto j = 0; j < 3; ++j) {
						Vertex& vert = model->getVert(i * 3 + j);
						Vector4 posH{ vert.m_Position.x(),vert.m_Position.y(),vert.m_Position.z(),1 };
						VertexData data = { posH, vert.m_Normal, vert.m_TexCoord, Color::white() };
						vToPs[j] = shader->vertexShader(data);	// 顶点着色器
						HomogeneousToScreen(vToPs[j].m_PosH);	// 从齐次空间变换到屏幕空间
					}
					// 三角形光栅化
					Geometry::Triangle::triangleWithCross(vToPs, zBuffer, *m_RenderTarget, shader);
				}
			}
		}

		int Rasterizer::getWidth() const noexcept
		{
			return m_RenderTarget->width();
		}

		int Rasterizer::getHeight() const noexcept
		{
			return m_RenderTarget->height();
		}

		void Rasterizer::addObject(GameObject&& object) noexcept
		{
			m_Objects.push_back(std::forward<GameObject>(object));
		}



		void Rasterizer::HomogeneousToScreen(Vector4& posH) noexcept
		{
			posH.x() = (posH.x() + 1.f) * getWidth() / 2.f;
			posH.y() = (posH.y() + 1.f) * getHeight() / 2.f;
		}

	}
}