#pragma once
#ifndef __RASTERIZER__H__
#define __RASTERIZER__H__

#include <memory>
#include "Tgaimage.h"
#include "Shader/IShader.h"
#include "../Core/Model.h"

namespace DSM {
	namespace Rendering {

		class Rasterizer
		{
		public:
			Rasterizer(const std::shared_ptr<TGAImage>& target,
				const std::shared_ptr<Model>& model,
				std::unique_ptr<IShader>&& shader);

			void draw();
			int getWidth()const noexcept;
			int getHeight()const noexcept;

		private:
			void HomogeneousToScreen(Math::Vector4& posH) noexcept;

		private:
			std::shared_ptr<TGAImage> m_RenderTarget;
			std::unique_ptr<IShader> m_Shader;
			std::shared_ptr<Model> m_Model;
		};

	}
}

#endif // !__RASTERIZER__H__
