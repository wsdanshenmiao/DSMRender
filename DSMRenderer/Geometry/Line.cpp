#include "Line.h"

DSM::Geometry::Line::Line(int x0, int y0, int x1, int y1, const TGAColor& color)
	:m_X0(x0), m_Y0(y0), m_X1(x1), m_Y1(y1), m_Color(color) {}

DSM::Geometry::Line::~Line() {}

void DSM::Geometry::Line::DrawLine(TGAImage& rt)
{
	bool steep = false;
	// 以x为索引绘制时，当线很陡峭时会有严重的间隙，将绘制索引更改为y
	if (std::abs(m_X0 - m_X1) < std::abs(m_Y0 - m_Y1)) {
		std::swap(m_Y0, m_X0);
		std::swap(m_Y1, m_X1);
		steep = true;
	}
	// 保证线反向时能够绘制
	if (m_X0 > m_X1) {
		std::swap(m_X0, m_X1);
		std::swap(m_Y0, m_Y1);
	}

	//for (int x = m_X0; x <= m_X1; x++) {
	//	float t = (x - m_X0) / (float)(m_X1 - m_X0);
	//	int y = m_Y0 * (1. - t) + m_Y1 * t;
	//	if (steep) {
	//		rt.set(y, x, m_Color);
	//	}
	//	else {
	//		rt.set(x, y, m_Color);
	//	}
	//}

	// 教程中说这种更快，但实测比前一种慢
	int dx = m_X1 - m_X0;
	int dy = m_Y1 - m_Y0;
	int changeY = m_Y1 > m_Y0 ? 1 : -1;
	// 计算每次y方向的偏移量
	//float doffset = std::abs(dy / static_cast<float>(dx));
	int doffset = std::abs(dy) * 2;	// 消除浮点数，加速运算
	int offset = 0;
	// 以x为索引绘制
	int y = m_Y0;
	for (int x = m_X0; x <= m_X1; ++x) {
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
