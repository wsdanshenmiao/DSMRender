#pragma once
#ifndef __COMMONSHADER__H__
#define __COMMONSHADER__H__

#include "IShader.h"

namespace DSM {
	namespace Rendering {

		class CommonShader : public IShader
		{
		public:
			VToP vertexShader(const VertexData& v) override;
			Color pixelShader(const VToP& i) override;

		};
	}
}

#endif // !__COMMONSHADER__H__
