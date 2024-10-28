#pragma once
#ifndef __COMMONSHADER__H__
#define __COMMONSHADER__H__

#include <memory>
#include "IShader.h"
#include "../../Rendering/Tgaimage.h"

namespace DSM {
	namespace Rendering {

		class CommonShader : public IShader
		{
		public:
			VToP vertexShader(const VertexData& v) override;
			Color pixelShader(const VToP& i) override;
			void setTexture(std::shared_ptr<TGAImage> texture) noexcept;

		private:
			std::shared_ptr<TGAImage> m_Texture = nullptr;
		};
	}
}

#endif // !__COMMONSHADER__H__
