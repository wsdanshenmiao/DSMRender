#pragma once
#ifndef __TRIANGLE__H__
#define __TRIANGLE__H__

#include <functional>
#include "../Math/Vector/Vector.h"
#include "../Rendering/Tgaimage.h"

namespace DSM {
	namespace Geometry {
		class Triangle
		{
		public:
			using RenderFunc = const std::function<void(int, int, const Color&)>&;

			static void triangleWithoutExcess(const std::array<Math::Vector2, 3>& ts, TGAImage& image, Color color, RenderFunc render);
			static void triangleWithCross(const std::array<Math::Vector2, 3>& ts, TGAImage& image, Color color, RenderFunc render);
			static void triangleWithtBarycentric(const std::array<Math::Vector2, 3>& ts, TGAImage& image, Color color, RenderFunc render);

		private:
			static bool inTriangle(const std::array < Math::Vector2, 3 >& ts, Math::Vector3 p);
			static Math::Vector3 barycentric(const std::array<Math::Vector2, 3>& ts, Math::Vector2 P);
		};
	}
}

#endif // !__TRIANGLE__H__
