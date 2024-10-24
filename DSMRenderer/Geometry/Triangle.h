#pragma once
#ifndef __TRIANGLE__H__
#define __TRIANGLE__H__

#include "../Math/Vector/Vector.h"

namespace DSM {
	namespace Geometry {
		class Triangle
		{
		public:
			Triangle();

		private:
			Math::Vector3 m_P0;
			Math::Vector3 m_P1;
			Math::Vector3 m_P2;
		};
	}
}

#endif // !__TRIANGLE__H__
