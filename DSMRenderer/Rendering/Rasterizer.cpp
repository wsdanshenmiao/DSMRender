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
			std::vector<float> zBuffer(m_RenderTarget->width() * m_RenderTarget->height(), std::numeric_limits<float>::max());

			for (auto i = 0; i < m_Model->facetSize(); ++i) {
				std::array<VToP, 3> vToPs;
				// 处理每个顶点
				for (auto j = 0; j < 3; ++j) {
					Vertex& vert = m_Model->getVert(i * 3 + j);
					Vector4 pos = vert.m_Position;
					pos.w() = 1;
					VertexData data{ pos, vert.m_Normal,vert.m_TexCoord ,Color::white() };
					vToPs[j] = m_Shader->vertexShader(data);
					Vector4& posH = vToPs[j].m_PosH;
					posH = { (posH.x() + 1.f) * getWidth() / 2, (posH.y() + 1.f) * getHeight() / 2.f, posH.z() ,posH.w() };
				}
				auto func = [&](const VToP& i) ->Color {
					return m_Shader->pixelShader(i); };
				Geometry::Triangle::triangleWithtBarycentric(vToPs, zBuffer, *m_RenderTarget, func);
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

	}
}