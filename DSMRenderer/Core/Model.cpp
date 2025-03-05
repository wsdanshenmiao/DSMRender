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
		loadTexture(filename, "_diffuse.tga", m_DiffuseTex);
		loadTexture(filename, "_spec.tga", m_SpecularTex);
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

	const TGAImage& Model::getDiffuse() noexcept
	{
		return m_DiffuseTex;
	}

	const TGAImage& Model::getSpecular() noexcept
	{
		return m_SpecularTex;
	}

	void Model::loadTexture(std::string filename, const std::string suffix, TGAImage& texture)
	{
		size_t dot = filename.find_last_of(".");
		if (dot == std::string::npos) return;
		std::string texfile = filename.substr(0, dot) + suffix;
		std::cerr << "texture file " << texfile << " loading " << (texture.read_tga_file(texfile.c_str()) ? "ok" : "failed") << std::endl;
		texture.flip_vertically();
	}



}