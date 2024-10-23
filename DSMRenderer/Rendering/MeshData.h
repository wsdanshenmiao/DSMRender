#pragma once
#ifndef __MESHDATA__H__
#define __MESHDATA__H__

#include <vector>
#include "../Math/Vector/Vector.h"

namespace DSM {
	struct MeshData
	{
		std::vector<Math::Vector3> m_Vertexs;
		std::vector<Math::Vector2> m_TexCoords;
		std::vector<Math::Vector3> m_Normals;
		std::vector<int> m_FacetVert;
		std::vector<int> m_FacetTex;
		std::vector<int> m_FacetNornal;
	};

}
#endif // !__MESHDATA__H__
