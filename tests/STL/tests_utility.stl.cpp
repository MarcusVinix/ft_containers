#include <gtest/gtest.h>
#include <utility>

TEST(TestUtilityPair, TestUtilityPairConstruct) {
	std::pair<std::string, double> pair1;
	std::pair<std::string, double> pair2("potato", 2.30);
	std::pair<std::string, double> pair3(pair2);


	EXPECT_EQ(pair1.first, "");
	EXPECT_EQ(pair1.second, 0);
	pair1 = std::make_pair("fries", 0.99);
	EXPECT_EQ(pair1.first, "fries");
	EXPECT_EQ(pair1.second, 0.99);
	EXPECT_EQ(pair2.first, "potato");
	EXPECT_EQ(pair2.second, 2.30);
	EXPECT_EQ(pair3.first, "potato");
	EXPECT_EQ(pair3.second, 2.30);
}

TEST(TestUtilityPair, TestUtilityPairRelationalOperator) {
	std::pair<int, char> foo(10, 'z');
	std::pair<int, char> bar(90, 'a');

	EXPECT_FALSE(foo == bar);
	EXPECT_TRUE(foo != bar);
	EXPECT_TRUE(foo < bar);
	EXPECT_FALSE(foo > bar);
	EXPECT_TRUE(foo <= bar);
	EXPECT_FALSE(foo >= bar);
}


TEST(TestUtilityMakePair, TestUtilityMakePair) {
	std::pair<int, int> foo;
	std::pair<int, int> bar;

	foo = std::make_pair(10, 20);
	bar = std::make_pair(10.5, 'A');
	EXPECT_EQ(foo.first, 10);
	EXPECT_EQ(foo.second, 20);
	EXPECT_EQ(bar.first, 10);
	EXPECT_EQ(bar.second, 65);
}
