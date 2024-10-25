#include "Model.h"
#include <iostream>
#include <sstream>
#include "../Math/Vector/Vector.h"

using namespace DSM::Math;

namespace DSM {

	inline void split(const std::string& in,
		std::vector<std::string>& out,
		std::string token)
	{
		out.clear();

		std::string temp;

		for (int i = 0; i < int(in.size()); i++)
		{
			std::string test = in.substr(i, token.size());

			if (test == token)
			{
				if (!temp.empty())
				{
					out.push_back(temp);
					temp.clear();
					i += (int)token.size() - 1;
				}
				else
				{
					out.push_back("");
				}
			}
			else if (i + token.size() >= in.size())
			{
				temp += in.substr(i, token.size());
				out.push_back(temp);
				break;
			}
			else
			{
				temp += in[i];
			}
		}
	}


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
				std::vector<std::string> sface;
				split(line, sface, " ");

				for (auto face : sface) {
					if (face == "f")continue;
					std::vector<std::string> svert;
					int fv, ft, fn;
					split(face, svert, "/");

					switch (svert.size())
					{
					case 3: fn = std::stoul(svert[2]);
					case 2: ft = std::stoul(svert[1]);
					case 1: fv = std::stoul(svert[0]); break;
					}
					f.push_back(--fv);
				}
				//m_Facets.push_back(f);
				if (f.size() == 3) {	// 三角形
					m_Facets.push_back(f);
				}
				else {	// 进行拆分
					for (auto i = 1; i + 1 < f.size(); ++i) {
						std::vector<int> tmp{ f[0],f[i], f[i + 1] };
						m_Facets.push_back(std::move(tmp));
					}
				}
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