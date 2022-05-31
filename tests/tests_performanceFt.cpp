#include <gtest/gtest.h>
#include <vector.hpp>
#include <stack.hpp>
#include <map.hpp>
#include <set.hpp>

const int count = 100000;

TEST(TestPerformanceVectorFt, TestPerformanceVectorFt) {
	ft::vector<int> vec;

	for (int i = 0; i < count; i++)
		vec.push_back(i);
	for (long int i = 0; i < count; i++)
		vec.pop_back();
}

TEST(TestPerformanceStackFt, TestPerformanceStackFt) {
	ft::stack<int, ft::vector<int>> stc;

	for (int i = 0; i < count; i++)
		stc.push(i);
	for (int i = 0; i < count; i++)
		stc.pop();
}

TEST(TestPerformanceMapFt, TestPerformanceMapFt) {
	ft::map<int, int> map;

	for(int i = 0; i < count; i++)
		map[i] = i;
	map.clear();
}

TEST(TestPerformanceSetFt, TestPerformanceSetFt) {
	ft::set<int> set;
	for (int i = 0; i < count; i++)
		set.insert(i);
	set.clear();
}

