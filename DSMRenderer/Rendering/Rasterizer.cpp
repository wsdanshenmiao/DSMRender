#include "Rasterizer.h"
#include "../Math/Vector/Vector.h"
#include "../Geometry/Triangle.h"

namespace DSM {
	namespace Rendering {
		using namespace Math;

		Rasterizer::Rasterizer(const std::shared_ptr<TGAImage>& target,
			const std::shared_ptr<Model>& model,
			std::unique_ptr<IShader>&& shader)
			:m_RenderTarget(target), m_Model(model), m_Shader(std::move(shader)) {}

		void Rasterizer::draw()
		{
			std::vector<float> zBuffer(m_RenderTarget->width() * m_RenderTarget->height(), -std::numeric_limits<float>::max());

			for (auto i = 0; i < m_Model->facetSize(); ++i) {
				std::array<VToP, 3> vToPs;
				// 处理每个顶点
				for (auto j = 0; j < 3; ++j) {
					Vertex& vert = m_Model->getVert(i * 3 + j);
					VertexData data = { vert.m_Position, vert.m_Normal, vert.m_TexCoord, Color::white() };
					vToPs[j] = m_Shader->vertexShader(data);	// 顶点着色器
					HomogeneousToScreen(vToPs[j].m_PosH);	// 从齐次空间变换到屏幕空间
				}
				// 三角形光栅化
				Geometry::Triangle::triangleWithCross(vToPs, zBuffer, *m_RenderTarget, m_Shader);
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



		void Rasterizer::HomogeneousToScreen(Vector4& posH) noexcept
		{
			posH.x() = (posH.x() + 1.f) * getWidth() / 2.f;
			posH.y() = (posH.y() + 1.f) * getHeight() / 2.f;
		}

	}
}