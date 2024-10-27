#include "Light.h"

namespace DSM {
	namespace Rendering {
		DirectionLight::DirectionLight(const Math::Vector3& dir, const Color& color)
			:m_Dir(dir), m_Color(color) {}



	}
}