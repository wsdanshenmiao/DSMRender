#pragma once
#ifndef __ISHADER__H__
#define __ISHADER__H__

#include <vector>
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
			Math::Vector3 m_Normal;
			Math::Vector2 m_TexCoord;
			Color m_Color;
		};

		class IShader
		{
		public:
			virtual VToP vertexShader(const VertexData& v) = 0;
			virtual Color pixelShader(const VToP& i) = 0;

			void setWorldMatrix(const Math::Matrix4x4& world) noexcept;
			void setViewMatrix(const Math::Matrix4x4& view) noexcept;
			void setProjMatrix(const Math::Matrix4x4& proj) noexcept;
			void setEyePosW(const Math::Vector3& pos) noexcept;
			void setDirectionLight(const DirectionLight& light) noexcept;

			static Color sample2D(const TGAImage& texture, const Math::Vector2& uv) noexcept;

		protected:
			CBuffer m_ConstData;
		};

	}
}


#endif // !__ISHADER__H__
