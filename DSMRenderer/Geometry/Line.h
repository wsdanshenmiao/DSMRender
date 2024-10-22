#pragma once
#ifndef __LINE__H
#define __LINE__H

#include "../Rendering/Tgaimage.h"
#include "../Math/Vector/Vector.h"

namespace DSM {
	namespace Geometry {

		class Line
		{
		public:
			Line(Math::Vector2 p0, Math::Vector2 p1, const TGAColor& color = { 255 });

			void DrawLine(TGAImage& rt);

		private:
			Math::Vector2 m_P0;
			Math::Vector2 m_P1;
			TGAColor m_Color;
		};


	}
}


#endif // !__LINE__H
