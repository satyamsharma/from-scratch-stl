#include "any.hpp"
#include "uniquePtr.hpp"
#include <string>
#include <iostream>

int main()
{
	// stl::Any
	stl::Any test = 123;
	std::cout << stl::AnyCast<int>(test) << '\n';

	test = std::string{"abc"};	
	std::cout << stl::AnyCast<std::string>(test) << '\n';

	// stl::Optional

	// stl::UniquePtr
	UniquePtr<int> ptr{new int{3}};
	UniquePtr<int> ptr1{std::move(ptr)};
	UniquePtr<int> ptr2{new int{4}};
	ptr1 = std::move(ptr2);

	// stl::SharedPtr
	// stl::Allocator
	// std::HashMap

	return 0;
}
