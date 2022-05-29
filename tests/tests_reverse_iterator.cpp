#include <gtest/gtest.h>
#include <iterator.hpp>
#include <reverse_iterator.hpp>
#include <vector.hpp>

TEST(TestReverseIterator, TestReverseIteratorIncrementAndDecrement) {
	int ar[] = {1, 2, 3, 4, 5};
	ft::vector<int> vec(ar, ar + 5);
	ft::vector<int>::reverse_iterator it = vec.rbegin();

	EXPECT_EQ(*it, 5);
	++it;
	EXPECT_EQ(*it, 4);
	it++;
	EXPECT_EQ(*it, 3);
	++it;
	EXPECT_EQ(*it, 2);
	it++;
	EXPECT_EQ(*it, 1);

	--it;
	EXPECT_EQ(*it, 2);
	it--;
	EXPECT_EQ(*it, 3);
	--it;
	EXPECT_EQ(*it, 4);
	it--;
	EXPECT_EQ(*it, 5);
}

TEST(TestReverseIterator, TestReverseIteratorOperatorPlusAndMinus) {
	int ar[] = {1, 2, 3, 4, 5};
	ft::vector<int> vec(ar, ar + 5);
	ft::vector<int>::reverse_iterator it = vec.rbegin();

	EXPECT_EQ(*it, 5);
	*it += 5;
	EXPECT_EQ(*it, 10);
	EXPECT_EQ(*it + 2, 12);
	*it -= 5;
	EXPECT_EQ(*it, 5);
	EXPECT_EQ(*it - 1, 4);
	EXPECT_EQ(it[4], 1);
}

TEST(TestReverseIterator, TestReverseIteratorRelationalOperator) {
	int ar[] = {1, 2, 3, 4, 5};
	ft::vector<int> vec(ar, ar + 5);
	ft::vector<int>::reverse_iterator it = vec.rbegin();

	ft::vector<int> const cvec(ar, ar + 5);
	ft::vector<int>::const_reverse_iterator cit = cvec.rbegin();

	int ar2[] = {1, 2, 3, 4, 5, 6};
	ft::vector<int> const cvec2(ar2, ar2 + 6);
	ft::vector<int>::const_reverse_iterator cit2 = cvec2.rbegin();

	EXPECT_FALSE(it == cit);
	EXPECT_FALSE(it == cit2);
	
	EXPECT_TRUE(it != cit);
	EXPECT_TRUE(it != cit2);

	EXPECT_TRUE(it > cit);
	EXPECT_TRUE(it > cit2);
	
	EXPECT_FALSE(it < cit);
	EXPECT_FALSE(it < cit2);
	
	EXPECT_FALSE(it <= cit);
	EXPECT_FALSE(it <= cit2);
	
	EXPECT_TRUE(it >= cit);
	EXPECT_TRUE(it >= cit2);
}
