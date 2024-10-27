#pragma once
#ifndef __TRIANGLE__H__
#define __TRIANGLE__H__

#include <functional>
#include "../Math/Vector/Vector.h"
#include "../Rendering/Tgaimage.h"
#include "../Rendering/Shader/CommonShader.h"
#include "../Core/Model.h"


namespace DSM {
	namespace Geometry {
		class Triangle
		{
		public:
			using RenderFunc = const std::function<Color(const Rendering::VToP&)>&;

			static void triangleWithtBarycentric(const std::array<Rendering::VToP, 3>& vToPs, std::vector<float>& zBuffer, TGAImage& image, RenderFunc PS);
			void triangleWithoutExcess(const std::array<Math::Vector3, 3>& ts, std::vector<float>& zBuffer, TGAImage& image, Color color, RenderFunc render);
			static void triangleWithCross(const std::array<Math::Vector3, 3>& ts, std::vector<float>& zBuffer, TGAImage& image, Color color, RenderFunc render);

		private:
			static bool inTriangle(const std::array < Math::Vector3, 3 >& ts, Math::Vector3 p) noexcept;
			static Math::Vector3 barycentric(const std::array<Rendering::VToP, 3>& vToPs, const Math::Vector3& P) noexcept;
		};
	}
}

#endif // !__TRIANGLE__H__
