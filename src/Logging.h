
#include <iostream>

#define LOG(a) std::cout<<a<<std::endl
#define LOG_ERROR(a) std::cerr<<a<<std::endl
#define TEST_ERROR(message,a,b,result) if (a != b) { \
	std::cerr << "Error in " << message <<" , expected: " << a << " Got: " << b << std::endl; \
	result = false;\
}