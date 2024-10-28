#include "CommonShader.h"

namespace DSM {
	namespace Rendering {
		using namespace Math;

		VToP CommonShader::vertexShader(const VertexData& v)
		{
			VToP o;
			Matrix4x4 VP = m_ConstData.m_Proj * m_ConstData.m_View;
			o.m_PosH = VP * m_ConstData.m_World * v.m_PosL;
			o.m_Normal = (Matrix3x3)m_ConstData.m_WorldInvTranspose * v.m_Normal.normalized();
			o.m_TexCoord = v.m_TexCoord;
			o.m_Color = v.m_Color;
			return o;
		}

		Color CommonShader::pixelShader(const VToP& i)
		{
			Color col = i.m_Color;
			Color albedo{};
			Color diffuse = Color::black();
			if (m_Texture != nullptr) {
				albedo = sample2D(*m_Texture, i.m_TexCoord);
			}
			for (const auto& light : m_ConstData.m_DirLight) {
				Vector3 dir = light.m_Dir.normalized();
				diffuse = light.m_Color * albedo * std::max(0.f, i.m_Normal * light.m_Dir);
			}
			auto a = col.a();
			col *= diffuse;
			col.a() = a;
			return col;
		}
		void CommonShader::setTexture(std::shared_ptr<TGAImage> texture) noexcept
		{
			m_Texture = texture;
		}
	}
}
