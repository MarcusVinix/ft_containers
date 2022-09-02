#include <gtest/gtest.h>
#include <vector>
#include <stack>
#include <deque>

TEST(TestStackConstructor, TestStackConstructor) {
	std::vector<int> vec(5, 200);
	std::deque<int> deq(10, 300);
	std::stack<int> stc1;
	std::stack<int> stc2(deq);
	std::stack<int, std::vector<int>> stc3(vec);
	std::stack<int, std::deque<int>> stc4(deq);

	EXPECT_EQ(stc1.size(), 0);
	EXPECT_EQ(stc2.size(), 10);
	EXPECT_EQ(stc3.size(), 5);
	EXPECT_EQ(stc4.size(), 10);
}

TEST(TestStackMemberFunctions, TestStackMemberFunctionsEmpty) {
	std::vector<int> vec(5, 200);
	std::deque<int> deq(10, 300);
	std::stack<int, std::vector<int>> stc1(vec);
	std::stack<int, std::deque<int>> stc2(deq);

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
	std::vector<int> vec(5, 200);
	std::deque<int> deq(10, 300);
	std::stack<int> stc1;
	std::stack<int> stc2(deq);
	std::stack<int, std::vector<int>> stc3(vec);
	std::stack<int, std::deque<int>> stc4(deq);

	EXPECT_EQ(stc1.size(), 0);
	stc2.pop();
	EXPECT_EQ(stc2.size(), 9);
	stc3.pop();
	EXPECT_EQ(stc3.size(), 4);
	stc4.push(11);
	EXPECT_EQ(stc4.size(), 11);
}

TEST(TestStackMemberFunctions, TestStackMemberFunctionsTop) {
	std::stack<int, std::vector<int>> vec;

	vec.push(10);
	vec.push(20);
	vec.push(30);

	std::stack<int, std::vector<int>> const vec2(vec);
	EXPECT_EQ(vec.top(), 30);
	vec.top() -= 10;
	EXPECT_EQ(vec.top(), 20);
	vec.top() += 20;
	EXPECT_EQ(vec.top(), 40);

	vec.pop();
	EXPECT_EQ(vec.top(), 20);

	EXPECT_EQ(vec2.top(), 30);
}

TEST(TestStackMemberFunctions, TestStackMemberFunctionsPushAndPop) {
	std::stack<int, std::vector<int>> vec;
	std::stack<int, std::deque<int>> deq;

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
	std::vector<int> vec(10, 20);
	std::vector<int> vec2(10, 20);
	std::vector<int> vec3(10, 30);
	std::stack<int, std::vector<int>> stc1(vec);
	std::stack<int, std::vector<int>> stc2(vec2);
	std::stack<int, std::vector<int>> stc3(vec3);

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