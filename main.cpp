#include "any.hpp"
#include <string>
#include <iostream>

int main()
{
	stl::Any test = 123;
	std::cout << stl::AnyCast<int>(test) << '\n';

	test = std::string{"abc"};	
	std::cout << stl::AnyCast<std::string>(test) << '\n';

	return 0;
}
