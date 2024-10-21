#include "../Tool/Tgaimage.h"
#include "../Geometry/Line.h"
#include "../Math/Vector/Vector.h"
#include "../Math/Matrix/Matrix.h"
#include "../Tool/Timer.h"
#include <random>
#include <array>
#include <vector>
#include "model.h"
#include "geometry.h"
#include <complex>
#include <valarray>

using namespace DSM;


int main(int argc, char** argv)
{
	using namespace Math;
	TGAImage image(1024, 1024, TGAImage::RGB);

	/*
	Vector<float, 3> v1;
	Vector<float, 3> v3(1);
	Vector<float, 3> v2{ 2.f, 1.f, 0.f };
	Vector<float, 3> v4(v2);

	std::cout << v2.size() << '\n' << v2.magnitude() << '\n' << v2.sqrMagnitude() << '\n' << v2.normalized();
	std::cout << Vector<float, 3>::zero() << '\n' << Vector<float, 3>::one() << '\n' << Vector<float, 3>::positiveInfinity() << '\n' << Vector<float, 3>::negativeInfinity() << '\n' << Vector<float, 3>::distance(v1, v2) << '\n' << Vector<float, 3>::lerp(v1, v2, 0.5) << '\n' << Vector<float, 3>::max(v1, v2) << '\n' << Vector<float, 3>::min(v1, v2) << '\n' << Vector<float, 3>::project(v3, v2) << '\n' << Vector<float, 3>::scale(v1, v2) << '\n' << Vector<float, 3>::clampMagnitude(v2, 2) << '\n';


	std::cout << v1 + v2 << v1 - v2 << v1 * v2 << v1 * 1.0f << v1 / 2.0f << v1[0] << '\n';
	Vector2 t0;
	Vector2 t1{ 2.f };
	Vector2 t2{ 1.0f,9.0f };
	Vector2 t3 = t1;

	std::cout << t1 + t2 << t1 - t2 << t1 * t2 * t2 - t1 << t1 * 1.0f << t1 / 2.0f << t1[0] << '\n';
	std::cout << t2.x() << t2.y() << Vector2::down() << Vector2::left() << Vector2::right() << Vector2::up() << '\n';
	std::cout << Vector2::angle(t3, t1) << '\n' << Vector2::reflect(Vector2{ 1,1 }, Vector2{ 0,1 });

	Vector3 a0{};
	Vector3 a1{ Vector3::up() };
	Vector3 a2{ Vector3::right() };
	Vector3 a3{ 2,3,4 };
	Vector3 a4 = t1;

	std::cout << Vector3::cross(a1, a2);

	Vector4 z0;
	Vector4 z1{ 2.f };
	Vector4 z2{ 1.0f,9.0f };
	Vector4 z3 = t1;
	Vector4 z4 = a4;
	*/

	Matrix<float, 4, 4> m0;
	Matrix<float, 4, 4> m1(1);
	m0.setRow(0, { 1,2,3,4 });
	//std::cout << m0 << '\n' << m1.getRow(0) << '\n' << m0.getCol(0) << '\n';
	Matrix<float, 4, 4> m2;
	m2 = { 1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f };
	//std::cout << m2;

	Matrix<float, 4, 4> m3;
	m3 << 1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 4.0f,
		10.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 40.0f;
	std::cout << m3;
	std::cout << m3.transpose();
	std::cout << m3.getMinor(1, 1);
	std::cout << m3.cofactor(0, 1) << '\n';
	std::cout << m3.calculateDet() << '\n';
	std::cout << m3.invert();
	std::cout << m3.invertTranspose();

	image.write_tga_file("output.tga");
	return 0;
}
