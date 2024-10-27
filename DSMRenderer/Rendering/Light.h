#pragma once
#ifndef __LIGHT__H__
#define __LIGHT__H__

#include "../Math/Vector/Vector.h"
#include "Color.h"

namespace DSM {
	namespace Rendering {
		struct DirectionLight
		{
			DirectionLight(const Math::Vector3& dir, const Color& color);

			Math::Vector3 m_Dir;
			Color m_Color;
		};

	}
}

#endif // !__LIGHT__H__
