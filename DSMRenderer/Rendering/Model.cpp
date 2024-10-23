#include "Model.h"
#include <iostream>
#include <sstream>
#include "../Math/Vector/Vector.h"

using namespace DSM::Math;

namespace DSM {

	Model::Model(const std::string filename)
	{
		std::ifstream ifs;
		ifs.open(filename, std::ifstream::in);
		if (ifs.fail())
			return;

		std::string line;
		while (!ifs.eof()) {	// 未达到文件尾
			std::getline(ifs, line);
			std::istringstream iss(line.c_str());
			char trash;
			if (!line.compare(0, 2, "v ")) {
				iss >> trash;
				Vector3 v;
				for (int i = 0; i < 3; i++) iss >> v[i];
				m_Vertexs.push_back(v);
			}
			else if (!line.compare(0, 2, "f ")) {
				std::vector<int> f;
				int itrash, idx;
				iss >> trash;
				while (iss >> idx >> trash >> itrash >> trash >> itrash) {
					idx--; // in wavefront obj all indices start at 1, not zero
					f.push_back(idx);
				}
				m_Facets.push_back(f);
			}
		}
		std::cerr << "# v# " << m_Vertexs.size() << " f# " << m_Facets.size() << std::endl;
	}

	std::size_t Model::vertSize() const
	{
		return m_Vertexs.size();
	}

	std::size_t Model::facetSize() const
	{
		return m_Facets.size();
	}

	Vector3& Model::vert(const std::size_t& index)
	{
		return m_Vertexs[index];
	}

	std::vector<int>& Model::facet(const std::size_t& index)
	{
		return m_Facets[index];
	}


}