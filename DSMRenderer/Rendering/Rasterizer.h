#pragma once
#ifndef __RASTERIZER__H__
#define __RASTERIZER__H__

#include <memory>
#include "Tgaimage.h"
#include "../Core/GameObject.h"

namespace DSM {
	namespace Rendering {

		class Rasterizer
		{
		public:
			Rasterizer(const std::shared_ptr<TGAImage>& target);

			void draw();
			int getWidth()const noexcept;
			int getHeight()const noexcept;
			void addObject(GameObject&& object) noexcept;

		private:
			void HomogeneousToScreen(Math::Vector4& posH) noexcept;

		private:
			std::shared_ptr<TGAImage> m_RenderTarget;
			std::vector<GameObject> m_Objects;
		};

	}
}

#endif // !__RASTERIZER__H__
