#include "Matrix4x4.h"

namespace DSM {
	namespace Math {
		constexpr Matrix4x4::Matrix4x4() noexcept
			:BaseType() {}

		constexpr Matrix4x4::Matrix4x4(const T& v) noexcept
			:BaseType(v) {}

		auto& Matrix4x4::operator=(std::initializer_list<T> list)
		{
			BaseType::_InitFormList(std::move(list));
			return *this;
		}


	}
}
