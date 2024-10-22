#include "Matrix3x3.h"

namespace DSM {
	namespace Math {
		constexpr Matrix3x3::Matrix3x3() noexcept
			:BaseType() {}

		constexpr Matrix3x3::Matrix3x3(const T& v) noexcept
			:BaseType(v) {}

		auto& Matrix3x3::operator=(std::initializer_list<T> list)
		{
			BaseType::_InitFormList(std::move(list));
			return *this;
		}


		//auto operator*(const Matrix3x3& left, const Matrix3x3& right)
		//{
		//	using Ret = Matrix3x3;
		//	using Left = Matrix3x3;
		//	using Right = Matrix3x3;
		//	return Ret::BaseType::_MultiplicaeMatrix<Ret, Left, Right>(left, right);
		//}

	}
}
