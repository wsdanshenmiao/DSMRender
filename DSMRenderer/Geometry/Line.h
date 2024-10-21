#pragma once
#ifndef __LINE__H
#define __LINE__H

#include "../Tool/Tgaimage.h"

namespace DSM {
	namespace Geometry {

		class Line
		{
		public:
			Line(int x0, int y0, int x1, int y1, const TGAColor& color = { 0,0,0,0 });
			Line(const Line& other) = default;
			~Line();

			void DrawLine(TGAImage& rt);

		private:
			int m_X0, m_Y0;
			int m_X1, m_Y1;
			TGAColor m_Color;
		};


	}
}


#endif // !__LINE__H
