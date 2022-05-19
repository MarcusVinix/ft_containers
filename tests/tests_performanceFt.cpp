#include <gtest/gtest.h>
#include <vector.hpp>

const int count = 100000;

TEST(TestPerformanceVectorFt, TestPerformanceVectorFt) {
	ft::vector<int> vec;

	for (int i = 0; i < count; i++)
		vec.push_back(i);
	for (long int i = 0; i < count; i++)
		vec.pop_back();
}
