#pragma once
#ifndef __MESHDATA__H__
#define __MESHDATA__H__

#include <vector>
#include "../Math/Vector/Vector.h"

namespace DSM {
	struct Vertex
	{
		Math::Vector3 m_Position;
		Math::Vector2 m_TexCoord;
		Math::Vector3 m_Normal;
	};

	//struct MeshData
	//{
	//	bool m_NoNormal;
	//	std::vector<Vertex> m_Vertexs;
	//	std::vector<std::size_t> m_Indexs;
	//};

}
#endif // !__MESHDATA__H__
