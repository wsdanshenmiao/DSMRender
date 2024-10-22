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


		auto operator*(const Matrix4x4& left, const Matrix4x4& right)
		{
			using Ret = Matrix4x4;
			using Left = Matrix4x4;
			using Right = Matrix4x4;
			return Matrix4x4::BaseType::_MultiplicaeMatrix<Ret, Left, Right>(left, right);
		}

	}
}
