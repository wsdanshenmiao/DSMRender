#include "IShader.h"

namespace DSM {
	namespace Rendering {

		void IShader::setWorldMatrix(const Math::Matrix4x4& world) noexcept
		{
			m_ConstData.m_World = world;
		}

		void IShader::setViewMatrix(const Math::Matrix4x4& view) noexcept
		{
			m_ConstData.m_View = view;
		}

		void IShader::setProjMatrix(const Math::Matrix4x4& proj) noexcept
		{
			m_ConstData.m_Proj = proj;
		}

		void IShader::setEyePosW(const Math::Vector3& pos) noexcept
		{
			m_ConstData.m_EyePosW = pos;
		}

		void IShader::setDirectionLight(const DirectionLight& light) noexcept
		{
			m_ConstData.m_DirLight.push_back(light);
		}


	}


}