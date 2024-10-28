#include "Model.h"
#include <iostream>
#include <sstream>
#include "ModelLoader.h"
#include "../Math/Vector/Vector.h"

using namespace DSM::Math;

namespace DSM {

	Model::Model(const std::string filename)
	{
		ModelLoader::LoadModel(filename, m_Mesh);
	}

	std::size_t Model::vertSize() const
	{
		return m_Mesh.size();
	}

	std::size_t Model::facetSize() const
	{
		return m_Mesh.size() / 3;
	}

	Vertex& Model::getVert(const std::size_t& index) noexcept
	{
		return m_Mesh[index];
	}

	Vector3& Model::getVertPos(const std::size_t& index) noexcept
	{
		return m_Mesh[index].m_Position;
	}

	bool Model::haveNormal() noexcept
	{
		return m_HaveNormal;
	}



}