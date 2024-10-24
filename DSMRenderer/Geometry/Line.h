#pragma once
#ifndef __LINE__H
#define __LINE__H

#include <functional>
#include <memory>
#include "../Rendering/Color.h"
#include "../Math/Vector/Vector.h"
#include "../Rendering/Model.h"

namespace DSM {
	namespace Geometry {

		class Line
		{
		public:
			using RenderFunc = const std::function<void(int, int, const Color&)>&;

			Line(Math::Vector2 p0, Math::Vector2 p1, const Color& color = Color::white());

			void DrawLine(RenderFunc render) noexcept;

			static void LineRender(std::shared_ptr<Model> model, RenderFunc render, Math::Vector2 wh) noexcept;

		private:
			Math::Vector2 m_P0;
			Math::Vector2 m_P1;
			Color m_Color;
		};


	}
}


#endif // !__LINE__H
