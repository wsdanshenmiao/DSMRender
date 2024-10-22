#include "Line.h"

namespace DSM {
	namespace Geometry {
		using namespace Math;
		Line::Line(Vector2 p0, Vector2 p1, const TGAColor& color)
			:m_P0(p0), m_P1(p1), m_Color(color) {}


		void Line::DrawLine(TGAImage& rt)
		{
			bool steep = false;
			// 以x为索引绘制时，当线很陡峭时会有严重的间隙，将绘制索引更改为y
			if (std::abs(m_P0.x() - m_P1.x()) < std::abs(m_P0.y() - m_P1.y())) {
				std::swap(m_P0.y(), m_P0.x());
				std::swap(m_P1.y(), m_P1.x());
				steep = true;
			}
			// 保证线反向时能够绘制
			if (m_P0.x() > m_P1.x()) {
				std::swap(m_P0.x(), m_P1.x());
				std::swap(m_P0.y(), m_P1.y());
			}

			//for (int x = m_P0.x(); x <= m_P1.x(); x++) {
			//	float t = (x - m_P0.x()) / (float)(m_P1.x() - m_P0.x());
			//	int y = m_P0.y() * (1. - t) + m_P1.y() * t;
			//	if (steep) {
			//		rt.set(y, x, m_Color);
			//	}
			//	else {
			//		rt.set(x, y, m_Color);
			//	}
			//}

			int dx = m_P1.x() - m_P0.x();
			int dy = m_P1.y() - m_P0.y();
			int changeY = m_P1.y() > m_P0.y() ? 1 : -1;
			// 计算每次y方向的偏移量
			//float doffset = std::abs(dy / static_cast<float>(dx));
			int doffset = std::abs(dy) * 2;	// 消除浮点数，加速运算
			int offset = 0;
			// 以x为索引绘制
			int y = m_P0.y();
			for (int x = m_P0.x(); x <= m_P1.x(); ++x) {
				if (steep) {
					rt.set(y, x, m_Color);
				}
				else {
					rt.set(x, y, m_Color);
				}
				offset += doffset;
				//if (offset > .5f) {
				//	offset -= 1.f;
				if (offset > dx) {
					offset -= dx * 2;
					y += changeY;
				}
			}
		}
	}
}