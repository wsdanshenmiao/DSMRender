#pragma once
#ifndef __LINE__H
#define __LINE__H

#include <functional>
#include "../Rendering/Tgaimage.h"
#include "../Math/Vector/Vector.h"

namespace DSM {
	namespace Geometry {

		class Line
		{
		public:
			Line(Math::Vector2 p0, Math::Vector2 p1, const Color& color = Color::white());

			void DrawLine(const std::function<void(int, int, const Color&)>& render);

		private:
			Math::Vector2 m_P0;
			Math::Vector2 m_P1;
			Color m_Color;
		};


	}
}


#endif // !__LINE__H
