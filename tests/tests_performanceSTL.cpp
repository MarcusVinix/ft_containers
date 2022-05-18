#include <gtest/gtest.h>
#include <vector>

const int count = 100000;

TEST(TestPerformanceVectorSTL, TestPerformanceVectorSTLPushBack) {
	std::vector<int> vec;

	for (int i = 0; i < count; i++)
		vec.push_back(i);
	for (int i = 0; i < count; i++)
		vec.pop_back();

}
