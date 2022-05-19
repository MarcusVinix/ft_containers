#include <gtest/gtest.h>
#include <vector.hpp>
// #include <stack.hpp>
#include <stack>

using namespace std;

TEST(TestStackConstructor, TestStackConstructor) {
	ft::vector<int> vec(5, 200);
	std::deque<int> deq(10, 300);
	stack<int> stc1;
	stack<int> stc2(deq);
	stack<int, ft::vector<int>> stc3(vec);
	stack<int, std::deque<int>> stc4(deq);

	EXPECT_EQ(stc1.size(), 0);
	EXPECT_EQ(stc2.size(), 10);
	EXPECT_EQ(stc3.size(), 5);
	EXPECT_EQ(stc4.size(), 10);
}

TEST(TestStackMemberFunctions, TestStackMemberFunctionsEmpty) {
	ft::vector<int> vec(5, 200);
	std::deque<int> deq(10, 300);
	stack<int, ft::vector<int>> stc1(vec);
	stack<int, std::deque<int>> stc2(deq);

	EXPECT_FALSE(stc1.empty());
	EXPECT_FALSE(stc2.empty());
	while (!stc1.empty())
		stc1.pop();
	while (!stc2.empty())
		stc2.pop();
	EXPECT_TRUE(stc1.empty());
	EXPECT_TRUE(stc2.empty());
}

TEST(TestStackMemberFunctions, TestStackMemberFunctionsSize) {
	ft::vector<int> vec(5, 200);
	std::deque<int> deq(10, 300);
	stack<int> stc1;
	stack<int> stc2(deq);
	stack<int, ft::vector<int>> stc3(vec);
	stack<int, std::deque<int>> stc4(deq);

	EXPECT_EQ(stc1.size(), 0);
	stc2.pop();
	EXPECT_EQ(stc2.size(), 9);
	stc3.pop();
	EXPECT_EQ(stc3.size(), 4);
	stc4.push(11);
	EXPECT_EQ(stc4.size(), 11);
}

TEST(TestStackMemberFunctions, TestStackMemberFunctionsTop) {
	stack<int, ft::vector<int>> vec;

	vec.push(10);
	vec.push(20);
	vec.push(30);

	stack<int, ft::vector<int>> const deq(vec);
	EXPECT_EQ(vec.top(), 30);
	vec.top() -= 10;
	EXPECT_EQ(vec.top(), 20);
	vec.top() += 20;
	EXPECT_EQ(vec.top(), 40);

	vec.pop();
	EXPECT_EQ(vec.top(), 20);

	EXPECT_EQ(deq.top(), 30);
}

TEST(TestStackMemberFunctions, TestStackMemberFunctionsPushAndPop) {
	stack<int, ft::vector<int>> vec;
	stack<int, std::deque<int>> deq;

	for (int i = 1; i < 11; i++) {
		vec.push(i);
		deq.push(i);
	}

	for (int i = 10; i > 0; i--) {
		EXPECT_EQ(vec.top(), i);
		EXPECT_EQ(deq.top(), i);
		vec.pop();
		deq.pop();
	}
	vec.pop();
	deq.pop();
}

TEST(TestStackNonMemberFunctions, TestStackNonMemberFunctionsRelationalOperators) {
	ft::vector<int> vec(10, 20);
	ft::vector<int> vec2(10, 20);
	ft::vector<int> vec3(10, 30);
	stack<int, ft::vector<int>> stc1(vec);
	stack<int, ft::vector<int>> stc2(vec2);
	stack<int, ft::vector<int>> stc3(vec3);

	EXPECT_TRUE(vec == vec2);
	EXPECT_FALSE(vec == vec3);

	EXPECT_FALSE(vec != vec2);
	EXPECT_TRUE(vec != vec3);

	EXPECT_FALSE(vec < vec2);
	EXPECT_TRUE(vec < vec3);

	EXPECT_TRUE(vec <= vec2);
	EXPECT_TRUE(vec <= vec3);

	EXPECT_FALSE(vec > vec2);
	EXPECT_FALSE(vec > vec3);

	EXPECT_TRUE(vec >= vec2);
	EXPECT_FALSE(vec >= vec3);
}