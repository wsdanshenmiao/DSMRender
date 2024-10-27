#pragma once
#ifndef __MODELLOADER__H__
#define	__MODELLOADER__H__

#include <vector>
#include "../Math/Vector/Vector.h"

namespace DSM {

	struct Vertex
	{
		Math::Vector3 m_Position;
		Math::Vector2 m_TexCoord;
		Math::Vector3 m_Normal;
	};

	class ModelLoader
	{
	public:
		static bool LoadModel(const std::string& filename, std::vector<Vertex>& mesh);

	private:
		static void split(const std::string& in, std::vector<std::string>& out, std::string token);
		static bool LoadFacet(std::vector<Vertex>& mesh, std::string line,
			const std::vector<Math::Vector3>& Positions,
			const std::vector<Math::Vector2>& Texcoords,
			const std::vector<Math::Vector3>& Normals);
	};

}

#endif // !__MODELLOADER__H__
