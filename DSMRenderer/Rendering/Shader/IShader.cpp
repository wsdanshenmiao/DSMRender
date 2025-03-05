#include "IShader.h"

namespace DSM {
	namespace Rendering {
		using namespace DSM::Math;

		VToP IShader::linearInterpolation(const std::array<VToP, 3>& vToPs, const Math::Vector3& bcScreen) noexcept
		{
			VToP vToP{};
			for (auto i = 0; i < 3; ++i) {
				vToP.m_PosH += vToPs[i].m_PosH * bcScreen[i];
				vToP.m_PosW += vToPs[i].m_PosW * bcScreen[i];
				vToP.m_Normal += vToPs[i].m_Normal * bcScreen[i];
				vToP.m_TexCoord += vToPs[i].m_TexCoord * bcScreen[i];
				vToP.m_Color += vToPs[i].m_Color * bcScreen[i];
			}
			return vToP;
		}

		void IShader::setWorldMatrix(const Math::Matrix4x4& world) noexcept
		{
			m_ConstData.m_World = world;
		}

		void IShader::setWorldInvTransposeMatrix(const Math::Matrix4x4& invTranspose) noexcept
		{
			m_ConstData.m_WorldInvTranspose = invTranspose;
		}

		void IShader::setViewMatrix(const Math::Matrix4x4& view) noexcept
		{
			m_ConstData.m_View = view;
		}

		void IShader::setProjMatrix(const Math::Matrix4x4& proj) noexcept
		{
			m_ConstData.m_Proj = proj;
		}

		void IShader::setProjMatrix(float eyeFov, float aspectRatio, float zNear, float zFar) noexcept
		{
			Matrix4x4 projection = Matrix4x4::identity();
			Matrix4x4 prj_matrix;
			prj_matrix << zNear, 0, 0, 0
				, 0, zNear, 0, 0
				, 0, 0, zNear + zFar, -zNear * zFar
				, 0, 0, 1, 0;

			float theta = eyeFov / 360.0f * 3.14;
			float height = tan(theta) * zNear * 2.0f;
			float width = height * aspectRatio;    //width / height = aspect ratio

			Matrix4x4 ortho_matrix;
			ortho_matrix << 2 / width, 0, 0, 0
				, 0, 2 / height, 0, 0
				, 0, 0, -2 / (zNear - zFar), (zNear + zFar) / (zNear - zFar)
				, 0, 0, 0, 1;

			projection = ortho_matrix * prj_matrix * projection;

			m_ConstData.m_Proj = projection;
		}


		void IShader::setEyePosW(const Math::Vector3& pos) noexcept
		{
			m_ConstData.m_EyePosW = pos;
			m_ConstData.m_View = Matrix4x4::identity();

			Matrix4x4 translate;
			translate << 1, 0, 0, -pos[0],
				0, 1, 0, -pos[1],
				0, 0, 1, -pos[2],
				0, 0, 0, 1;

			m_ConstData.m_View = translate * m_ConstData.m_View;
		}

		void IShader::setDirectionLight(const DirectionLight& light) noexcept
		{
			m_ConstData.m_DirLight.push_back(light);
		}

		Color IShader::sample2D(const TGAImage& texture, const Math::Vector2& uv) noexcept
		{
			return texture.get(uv.x() * texture.width(), uv.y() * texture.height());
		}

		void IShader::setTexture(const std::string name, const TGAImage& texture) noexcept
		{
			m_Textures.insert(std::make_pair(name, texture));
		}

	}


}