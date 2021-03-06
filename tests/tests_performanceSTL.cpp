#include <gtest/gtest.h>
#include <vector>
#include <stack>
#include <map>
#include <set>

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

TEST(TestPerformanceMapStl, TestPerformanceMapStl) {
	std::map<int, int> map;

	for(int i = 0; i < count; i++)
		map[i] = i;
	map.clear();
}

TEST(TestPerformanceMapStl, TestPerformanceMapStlErase) {
	std::map<int, int> map;

	for(int i = 0; i < count; i++)
		map[i] = i;
	std::map<int, int>::iterator it = map.begin();
	map.erase(it, map.end());
}

TEST(TestPerformanceSetStl, TestPerformanceSetStl) {
	std::set<int> set;
	for (int i = 0; i < count; i++)
		set.insert(i);
	set.clear();
}

TEST(TestPerformanceSetStl, TestPerformanceSetStlErase) {
	std::set<int> set;
	for (int i = 0; i < count; i++)
		set.insert(i);
	std::set<int>::iterator it = set.begin();
	set.erase(it, set.end());
}