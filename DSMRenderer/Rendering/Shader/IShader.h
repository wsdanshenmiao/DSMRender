#pragma once
#ifndef __ISHADER__H__
#define __ISHADER__H__

#include <vector>
#include <map>
#include "../../Math/Vector/Vector.h"
#include "../../Math/Matrix/Matrix.h"
#include "../Tgaimage.h"
#include "../Color.h"
#include "../Light.h"

namespace DSM {
	namespace Rendering {
		struct CBuffer
		{
			Math::Matrix4x4 m_World;
			Math::Matrix4x4 m_View;
			Math::Matrix4x4 m_Proj;
			Math::Matrix4x4 m_WorldInvTranspose;
			Math::Vector3 m_EyePosW;
			std::vector<DirectionLight> m_DirLight;
		};
		struct VertexData
		{
			Math::Vector4 m_PosL;
			Math::Vector3 m_Normal;
			Math::Vector2 m_TexCoord;
			Color m_Color;
		};
		struct VToP
		{
			Math::Vector4 m_PosH;
			Math::Vector3 m_PosW;
			Math::Vector3 m_Normal;
			Math::Vector2 m_TexCoord;
			Color m_Color;
		};

		class IShader
		{
		public:
			virtual VToP vertexShader(const VertexData& v) = 0;
			virtual Color pixelShader(const VToP& i) = 0;
			virtual VToP linearInterpolation(const std::array<VToP, 3>& vToPs, const Math::Vector3& bcScreen) noexcept;

			void setWorldMatrix(const Math::Matrix4x4& world) noexcept;
			void setWorldInvTransposeMatrix(const Math::Matrix4x4& invTranspose)noexcept;
			void setViewMatrix(const Math::Matrix4x4& view) noexcept;
			void setProjMatrix(const Math::Matrix4x4& proj) noexcept;
			void setProjMatrix(float eyeFov, float aspectRatio, float zNear, float zFar) noexcept;
			void setEyePosW(const Math::Vector3& pos) noexcept;
			void setDirectionLight(const DirectionLight& light) noexcept;
			void setTexture(const std::string name, const TGAImage& texture) noexcept;

			static Color sample2D(const TGAImage& texture, const Math::Vector2& uv) noexcept;

		protected:
			CBuffer m_ConstData;
			std::map<std::string, TGAImage> m_Textures;
		};

	}
}


#endif // !__ISHADER__H__
