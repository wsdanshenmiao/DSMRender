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
			float indensity = 0;
			for (const auto& light : m_ConstData.m_DirLight) {
				Vector3 dir = light.m_Dir.normalized();
				indensity += dir * i.m_Normal;
			}
			indensity = std::max(0.f, std::min(1.f, indensity));
			auto a = col.a();
			col *= indensity;
			col.a() = a;
			return col;
		}
	}
}
