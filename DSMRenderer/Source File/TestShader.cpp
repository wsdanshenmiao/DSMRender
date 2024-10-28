#include "../Rendering/Tgaimage.h"
#include "../Rendering/Rasterizer.h"
#include "../Rendering/Shader/CommonShader.h"
#include "../Math/Matrix/Matrix.h"

using namespace DSM;
using namespace DSM::Math;
using namespace DSM::Rendering;

void TestShader()
{
	std::shared_ptr renderTarget = std::make_shared<TGAImage>(4096, 4096, TGAImage::RGB);
	std::unique_ptr model = std::make_unique<Model>("D:/Code/Computer Graphics/DSMRenderer/obj/diablo3_pose/diablo3_pose.obj");
	std::unique_ptr shader = std::make_unique<CommonShader>();
	shader->setTexture(model->getDiffuse());
	shader->setDirectionLight({ { 0,0,1 } ,Color::white() });
	Matrix4x4 world;
	world << 1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;
	shader->setWorldMatrix(world);
	Rasterizer rasterizer(renderTarget);
	GameObject object;
	object.setModel(std::move(model));
	object.setShader(std::move(shader));
	rasterizer.addObject(std::move(object));
	rasterizer.draw();
	renderTarget->write_tga_file("../Output/output.tga");
}

int main()
{
	TestShader();
	return 0;
}