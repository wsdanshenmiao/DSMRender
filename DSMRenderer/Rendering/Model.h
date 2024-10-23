#pragma once
#ifndef __MODEL__H__
#define __MODEL__H__

#include <vector>
#include "MeshData.h"
#include "Tgaimage.h"

namespace DSM {
	class Math::Vector2;
	class Math::Vector3;

	class Model
	{
	public:
		Model(const std::string filename);

		std::size_t vertSize() const;
		std::size_t facetSize() const;
		Math::Vector3& vert(const std::size_t& index);
		std::vector<int>& facet(const std::size_t& index);
	public:
		std::vector<Math::Vector3> m_Vertexs;
		std::vector<std::vector<int>> m_Facets;
	};
}

#endif // !__MODEL__H__
