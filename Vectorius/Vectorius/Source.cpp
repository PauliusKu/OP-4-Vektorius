#include <iostream>
#include <string>
#include "vector.h"
#include "timer.h"


template<typename T> double test_push_back(unsigned int size) {
	Timer start;
	T v;
	const std::string somestring = "asdgds";
	for (int i = 0; i < size; i++) {
		v.push_back(i);
	}
	return start.elapsed();
}

int main(int argc, char *argv[])
{
	for (unsigned int i = 100000; i < 1000000000; i *= 10)
	{
		std::cout << "Push_back test" << std::endl;
		std::cout << "size " << i << ": " << std::endl;
		std::cout << test_push_back<Vector<int>>(i) << " s" << std::endl;
		std::cout << test_push_back<std::vector<int>>(i) << " s" << std::endl;
		std::cout << "-------------------------------" << std::endl;
	}
	system("pause");
	return 0;
}