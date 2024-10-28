#include "../Rendering/Tgaimage.h"
#include "../Rendering/Rasterizer.h"
#include "../Rendering/Shader/CommonShader.h"
#include "../Math/Matrix/Matrix.h"

using namespace DSM;
using namespace DSM::Math;
using namespace DSM::Rendering;

void TestShader()
{
	std::shared_ptr renderTarget = std::make_shared<TGAImage>(512, 512, TGAImage::RGB);
	std::shared_ptr model = std::make_shared<Model>("D:/Code/Computer Graphics/DSMRenderer/obj/Model/dragon.obj");
	std::unique_ptr shader = std::make_unique<CommonShader>();
	shader->setDirectionLight({ { 0,0,1 } ,Color::white() });
	Matrix4x4 world;
	world << .1, 0, 0, 0,
		0, .1, 0, 0,
		0, 0, .1, 0,
		0, 0, 0, 1;
	shader->setWorldMatrix(world);
	Rasterizer rasterizer(renderTarget, model, std::move(shader));
	rasterizer.draw();
	renderTarget->write_tga_file("../Output/output.tga");
}

int main()
{
	TestShader();
	return 0;
}