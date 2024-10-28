#include "ModelLoader.h"
#include <fstream>
#include <sstream>

namespace DSM {

	using namespace Math;
	// 返回值表示是否有法线
	void ModelLoader::LoadModel(const std::string& filename, std::vector<Vertex>& mesh)
	{
		std::ifstream ifs;
		ifs.open(filename, std::ifstream::in);
		if (ifs.fail())
			return;

		std::vector<Math::Vector3> Positions;
		std::vector<Math::Vector2> Texcoords;
		std::vector<Math::Vector3> Normals;

		std::string line;
		while (!ifs.eof()) {	// 未达到文件尾
			std::getline(ifs, line);
			std::istringstream iss(line.c_str());
			char trash;
			if (!line.compare(0, 2, "v ")) {
				iss >> trash;
				Math::Vector3 v;
				for (int i = 0; i < 3; i++) iss >> v[i];
				Positions.push_back(v);
			}
			else if (!line.compare(0, 3, "vn ")) {
				iss >> trash >> trash;
				Math::Vector3 n;
				for (int i = 0; i < 3; i++) iss >> n[i];
				Normals.push_back(n.normalized());
			}
			else if (!line.compare(0, 3, "vt ")) {
				iss >> trash >> trash;
				Math::Vector2 t;
				for (int i = 0; i < 2; i++) iss >> t[i];
				Texcoords.push_back(t);
			}
			else if (!line.compare(0, 2, "f ")) {
				LoadFacet(mesh, line, Positions, Texcoords, Normals);
			}
		}
		std::cerr << "# v# " << Positions.size() << " f# " << mesh.size() / 3 << std::endl;
	}





	void ModelLoader::split(const std::string& in, std::vector<std::string>& out, std::string token)
	{
		out.clear();
		std::string temp;
		for (int i = 0; i < int(in.size()); i++) {
			std::string test = in.substr(i, token.size());

			if (test == token) {
				if (!temp.empty()) {
					out.push_back(temp);
					temp.clear();
					i += (int)token.size() - 1;
				}
				else {
					out.push_back("");
				}
			}
			else if (i + token.size() >= in.size()) {
				temp += in.substr(i, token.size());
				out.push_back(temp);
				break;
			}
			else {
				temp += in[i];
			}
		}
	}

	// 返回值表示是否有法线
	void ModelLoader::LoadFacet(std::vector<Vertex>& mesh, std::string line,
		const std::vector<Vector3>& Positions,
		const std::vector<Vector2>& Texcoords,
		const std::vector<Vector3>& Normals)
	{
		std::vector<int> fs[3];
		std::vector<std::string> sface;
		split(line, sface, " ");

		// 拆分每个面
		for (auto face : sface) {
			if (face == "f")continue;
			std::vector<std::string> svert;
			int factor[3]{};
			split(face, svert, "/");

			// 获取面中的数据
			for (auto i = 0; i < svert.size(); ++i) {
				if (svert[i] != "") {
					fs[i].push_back(std::stoul(svert[i]) - 1);
				}
			}
		}

		int type = 0;	// fv/ft/fn
		if (fs[1].size() == 0 && fs[2].size() == 0) {	// fv
			type = 1;
		}
		else if (fs[1].size() == 0) {	// fv//fn
			type = 2;
		}
		else if (fs[2].size() == 0) {	// fv/ft
			type = 3;
		}

		auto [fvs, fts, fns] = fs;
		auto preSize = mesh.size();
		if (fvs.size() == 3) {	// 三角形
			Vertex vert[3];
			for (auto i = 0; i < 3; ++i) {
				switch (type) {
				case 0:vert[i] = { Positions[fvs[i]], Texcoords[fts[i]], Normals[fns[i]] }; break;
				case 1:vert[i] = { Positions[fvs[i]] ,Vector2{0,0} }; break;
				case 2:vert[i] = { Positions[fvs[i]], Vector2{0,0}, Normals[fns[i]] }; break;
				case 3:vert[i] = { Positions[fvs[i]], Texcoords[fts[i]] }; break;
				}
				mesh.push_back(vert[i]);
			}
			Vector3 normal = Vector3::cross(vert[2].m_Position - vert[0].m_Position,
				vert[1].m_Position - vert[0].m_Position);
			for (auto& v : vert) {
				v.m_Normal = normal;
			}
		}
		else {	// 进行拆分
			for (auto i = 1; i + 1 < fvs.size(); ++i) {
				int index[3] = { 0, i, i + 1 };
				for (auto j = 0; j < 3; ++j) {
					int fi = index[j];
					Vertex vert;
					switch (type) {
					case 0:vert = { Positions[fvs[fi]], Texcoords[fts[fi]], Normals[fns[fi]] }; break;
					case 1:vert = { Positions[fvs[fi]] ,Vector2{0,0} }; break;
					case 2:vert = { Positions[fvs[fi]], Texcoords[fts[fi]] }; break;
					case 3:vert = { Positions[fvs[fi]], Vector2{0,0}, Normals[fns[fi]] }; break;
					}
					mesh.push_back(vert);
				}
			}
		}
		if (type == 1 || type == 3) {
			Vector3 normal = Vector3::cross(mesh[preSize + 1].m_Position - mesh[preSize].m_Position,
				mesh[preSize + 2].m_Position - mesh[preSize].m_Position);
			for (auto i = preSize; i < mesh.size(); ++i) {
				mesh[i].m_Normal = normal;
			}
		}
	}

}