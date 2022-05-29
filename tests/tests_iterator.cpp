#include <gtest/gtest.h>
#include <iterator.hpp>
#include <vector.hpp>

TEST(TestIterator, TestIteratorIncrementAndDecrement) {
	int ar[] = {1, 2, 3, 4, 5};
	ft::vector<int> vec(ar, ar + 5);
	ft::vector<int>::iterator it = vec.begin();

	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_EQ(*it, 2);
	it++;
	EXPECT_EQ(*it, 3);
	++it;
	EXPECT_EQ(*it, 4);
	it++;
	EXPECT_EQ(*it, 5);

	--it;
	EXPECT_EQ(*it, 4);
	it--;
	EXPECT_EQ(*it, 3);
	--it;
	EXPECT_EQ(*it, 2);
	it--;
	EXPECT_EQ(*it, 1);
}

TEST(TestIterator, TestIteratorOperatorPlusAndMinus) {
	int ar[] = {1, 2, 3, 4, 5};
	ft::vector<int> vec(ar, ar + 5);
	ft::vector<int>::iterator it = vec.begin();

	EXPECT_EQ(*it, 1);
	*it += 5;
	EXPECT_EQ(*it, 6);
	EXPECT_EQ(*it + 2, 8);
	*it -= 5;
	EXPECT_EQ(*it, 1);
	EXPECT_EQ(*it - 1, 0);
	EXPECT_EQ(it[4], 5);
}

TEST(TestIterator, TestIteratorRelationalOperator) {
	int ar[] = {1, 2, 3, 4, 5};
	ft::vector<int> vec(ar, ar + 5);
	ft::vector<int>::iterator it = vec.begin();

	ft::vector<int> const cvec(ar, ar + 5);
	ft::vector<int>::const_iterator cit = cvec.begin();

	int ar2[] = {1, 2, 3, 4, 5, 6};
	ft::vector<int> const cvec2(ar2, ar2 + 6);
	ft::vector<int>::const_iterator cit2 = cvec2.begin();

	EXPECT_FALSE(it == cit);
	EXPECT_FALSE(it == cit2);
	
	EXPECT_TRUE(it != cit);
	EXPECT_TRUE(it != cit2);

	EXPECT_FALSE(it > cit);
	EXPECT_FALSE(it > cit2);
	
	EXPECT_TRUE(it < cit);
	EXPECT_TRUE(it < cit2);
	
	EXPECT_TRUE(it <= cit);
	EXPECT_TRUE(it <= cit2);
	
	EXPECT_FALSE(it >= cit);
	EXPECT_FALSE(it >= cit2);
}
