#include "CommonShader.h"

namespace DSM {
	namespace Rendering {
		using namespace Math;

		VToP CommonShader::vertexShader(const VertexData& v)
		{
			VToP o;
			Matrix4x4 VP = m_ConstData.m_Proj * m_ConstData.m_View;
			o.m_PosH = VP * m_ConstData.m_World * v.m_PosL;
			o.m_PosW = (Vector3)(m_ConstData.m_World * v.m_PosL);
			o.m_Normal = (Matrix3x3)m_ConstData.m_WorldInvTranspose * v.m_Normal.normalized();
			o.m_TexCoord = v.m_TexCoord;
			o.m_Color = v.m_Color;
			return o;
		}

		Color CommonShader::pixelShader(const VToP& i)
		{
			Color albedo{};
			std::uint8_t gloss = 255;
			Color diffuse = Color::black();
			Color specular = Color::black();
			Vector3 viewDir = (m_ConstData.m_EyePosW - i.m_PosW).normalized();

			if (auto tex = m_Textures.find("Diffuse"); tex != m_Textures.end()) {
				albedo = sample2D(tex->second, i.m_TexCoord);
			}
			if (auto tex = m_Textures.find("Specular"); tex != m_Textures.end()) {
				gloss = sample2D(tex->second, i.m_TexCoord).r();
			}

			for (const auto& light : m_ConstData.m_DirLight) {
				Vector3 lightDir = -light.m_Dir.normalized();
				Vector3 halfDir = (viewDir + lightDir).normalized();
				Vector3 normal = i.m_Normal.normalized();
				Vector3 dir = lightDir.normalized();
				diffuse += light.m_Color * i.m_Color * albedo * std::max(0.f, normal * lightDir);
				specular += light.m_Color * i.m_Color * std::pow(std::max(0.f, normal * halfDir), 40);
			}

			Color ambient = albedo * .08f;
			Color col = diffuse + specular + ambient;
			col.a() = albedo.a();

			return col;
		}
	}
}
