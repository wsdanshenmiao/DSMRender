#pragma once
#ifndef __MODEL__H__
#define __MODEL__H__

#include <vector>
#include "ModelLoader.h"
#include "../Rendering/Tgaimage.h"

namespace DSM {
	class Math::Vector2;
	class Math::Vector3;

	class Model
	{
	public:
		Model(const std::string filename);

		std::size_t vertSize() const;
		std::size_t facetSize() const;

		Vertex& getVert(const std::size_t& index) noexcept;
		Math::Vector3& getVertPos(const std::size_t& index) noexcept;
		std::shared_ptr<TGAImage> getDiffuse() noexcept;

	private:
		void loadTexture(std::string filename, const std::string suffix, TGAImage& texture);

	private:
		std::string m_Name;
		std::vector<Vertex> m_Mesh;
		std::shared_ptr<TGAImage> m_DiffuseTex;
	};
}

#endif // !__MODEL__H__
