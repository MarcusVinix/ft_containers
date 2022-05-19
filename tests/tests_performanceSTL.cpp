#include <gtest/gtest.h>
#include <vector>
#include <stack>

const int count = 100000;

TEST(TestPerformanceVectorSTL, TestPerformanceVectorSTL) {
	std::vector<int> vec;

	for (int i = 0; i < count; i++)
		vec.push_back(i);
	for (long int i = 0; i < count; i++)
		vec.pop_back();

}

TEST(TestPerformanceStackSTL, TestPerformanceStackSTL) {
	std::stack<int, std::vector<int>> stc;

	for (int i = 0; i < count; i++)
		stc.push(i);
	for (int i = 0; i < count; i++)
		stc.pop();
}
