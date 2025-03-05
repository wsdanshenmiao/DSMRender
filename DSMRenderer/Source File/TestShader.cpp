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
	Vector3 eyePos{ 0,0,10 };

	std::unique_ptr shader = std::make_unique<CommonShader>();
	shader->setDirectionLight({ { 0,0,-1 } ,Color::white() });
	shader->setEyePosW(eyePos);
	shader->setTexture("Diffuse", model->getDiffuse());
	shader->setTexture("Specular", model->getSpecular());
	shader->setProjMatrix(90, 1, .1, 100);
	Rasterizer rasterizer(renderTarget);

	GameObject object;
	Transform& objectTrans = object.getTransform();
	//objectTrans.setScale(.5, .5, .5);
	//objectTrans.setPosition(.5, .5, .5);
	objectTrans.Rotate({ 0,0, 0 });
	object.setModel(std::move(model));
	object.setShader(std::move(shader));

	rasterizer.addObject(std::move(object));
	rasterizer.draw();
	renderTarget->write_tga_file("../Output/ShaderWithBlinnPhone.tga");
}

#include <variant>
#include <assert.h>
int main()
{
	//TestShader();
	std::variant<int, std::string> v = "abc";
	assert(not std::holds_alternative<int>(v));
	assert(std::holds_alternative<std::string>(v));
	return 0;
}