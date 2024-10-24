#include "Line.h"

namespace DSM {
	namespace Geometry {

		Line::Line(Math::Vector2 p0, Math::Vector2 p1, const Color& color)
			:m_P0(p0), m_P1(p1), m_Color(color) {}


		void Line::DrawLine(RenderFunc render) noexcept
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

			int dx = (int)(m_P1.x() - m_P0.x());
			int dy = (int)(m_P1.y() - m_P0.y());
			int changeY = m_P1.y() > m_P0.y() ? 1 : -1;
			// 计算每次y方向的偏移量
			//float doffset = std::abs(dy / static_cast<float>(dx));
			int doffset = std::abs(dy) * 2;	// 消除浮点数，加速运算
			int offset = 0;
			// 以x为索引绘制
			int y = (int)m_P0.y();
			for (int x = (int)m_P0.x(); x <= m_P1.x(); ++x) {
				if (steep) {
					render(y, x, m_Color);
				}
				else {
					render(x, y, m_Color);
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

		void Line::LineRender(std::shared_ptr<Model> model, RenderFunc render, Math::Vector2 wh) noexcept
		{
			for (int i = 0; i < model->facetSize(); i++) {
				std::vector<int> face = model->facet(i);
				for (int j = 0; j < 3; j++) {
					Math::Vector3 v0 = model->vert(face[j]);
					Math::Vector3 v1 = model->vert(face[(j + 1) % 3]);
					float x0 = (v0.x() + 1.f) * wh.x() / 2.f;
					float y0 = (v0.y() + 1.f) * wh.y() / 2.f;
					float x1 = (v1.x() + 1.f) * wh.x() / 2.f;
					float y1 = (v1.y() + 1.f) * wh.y() / 2.f;
					Line({ x0, y0 }, { x1, y1 }, Color::white()).DrawLine(render);
				}
			}
		}
	}
}