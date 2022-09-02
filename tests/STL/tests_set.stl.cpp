#include <gtest/gtest.h>
#include <set>

TEST(TestSet, TestSetConstructorDefault) {
	std::set<int> set;

	EXPECT_EQ(set.size(), 0);
	EXPECT_TRUE(set.empty());
}

TEST(TestSet, TestSetConstructorRange) {
	int ar[] = {1, 2, 3, 4, 5};
	std::set<int> set(ar, ar + 5);

	EXPECT_FALSE(set.empty());
	EXPECT_EQ(set.size(), 5);
	std::set<int>::iterator it = set.begin();
	for (int i = 0; i < 5; i++, it++)
		EXPECT_EQ(*it, i + 1);
}

TEST(TestSet, TestSetConstructorCopy) {
	int ar[] = {1, 2, 3, 4, 5};
	std::set<int> set(ar, ar + 5);
	std::set<int> copy(set);

	EXPECT_FALSE(copy.empty());
	EXPECT_EQ(copy.size(), 5);
	std::set<int>::iterator it = copy.begin();
	for (int i = 0; i < 5; i++, it++)
		EXPECT_EQ(*it, i + 1);
}

TEST(TestSet, TestSetAssignmentOperator) {
	int ar[] = {1, 2, 3, 4, 5};
	std::set<int> set(ar, ar + 5);
	std::set<int> copy;
	copy = set;

	EXPECT_FALSE(copy.empty());
	EXPECT_EQ(copy.size(), 5);
	std::set<int>::iterator it = copy.begin();
	for (int i = 0; i < 5; i++, it++)
		EXPECT_EQ(*it, i + 1);
}

TEST(TestSet, TestSetIteratorBeginAndEnd) {
	int ar[] = {1, 2, 3, 4, 5};
	std::set<int> set(ar, ar + 5);
	std::set<int>::iterator it = set.begin();

	EXPECT_EQ(*it, 1);
	it++;
	EXPECT_EQ(*it, 2);
	++it;
	EXPECT_EQ(*it, 3);
	it++;
	EXPECT_EQ(*it, 4);
	++it;
	EXPECT_EQ(*it, 5);

	std::set<int>::iterator ite = set.end();
	ite--;
	EXPECT_EQ(*ite, 5);
	--ite;
	EXPECT_EQ(*ite, 4);
	ite--;
	EXPECT_EQ(*ite, 3);
	--ite;
	EXPECT_EQ(*ite, 2);
	ite--;
	EXPECT_EQ(*ite, 1);

	std::set<int> const cset(ar, ar + 5);
	std::set<int>::const_iterator cit = cset.begin();

	EXPECT_EQ(*cit, 1);
	cit++;
	EXPECT_EQ(*cit, 2);
	++cit;
	EXPECT_EQ(*cit, 3);
	cit++;
	EXPECT_EQ(*cit, 4);
	++cit;
	EXPECT_EQ(*cit, 5);

	std::set<int>::const_iterator cite = cset.end();
	cite--;
	EXPECT_EQ(*cite, 5);
	--cite;
	EXPECT_EQ(*cite, 4);
	cite--;
	EXPECT_EQ(*cite, 3);
	--cite;
	EXPECT_EQ(*cite, 2);
	cite--;
	EXPECT_EQ(*cite, 1);
}

TEST(TestSet, TestSetReverseIteratorRBeginAndREnd) {
	int ar[] = {1, 2, 3, 4, 5};
	std::set<int> set(ar, ar + 5);
	std::set<int>::reverse_iterator it = set.rbegin();

	EXPECT_EQ(*it, 5);
	it++;
	EXPECT_EQ(*it, 4);
	++it;
	EXPECT_EQ(*it, 3);
	it++;
	EXPECT_EQ(*it, 2);
	++it;
	EXPECT_EQ(*it, 1);

	std::set<int>::reverse_iterator ite = set.rend();
	--ite;
	EXPECT_EQ(*ite, 1);
	--ite;
	EXPECT_EQ(*ite, 2);
	ite--;
	EXPECT_EQ(*ite, 3);
	--ite;
	EXPECT_EQ(*ite, 4);
	ite--;
	EXPECT_EQ(*ite, 5);

	std::set<int> const cset(ar, ar + 5);
	std::set<int>::const_reverse_iterator cit = cset.rbegin();

	EXPECT_EQ(*cit, 5);
	cit++;
	EXPECT_EQ(*cit, 4);
	++cit;
	EXPECT_EQ(*cit, 3);
	cit++;
	EXPECT_EQ(*cit, 2);
	++cit;
	EXPECT_EQ(*cit, 1);

	std::set<int>::const_reverse_iterator cite = cset.rend();
	--cite;
	EXPECT_EQ(*cite, 1);
	--cite;
	EXPECT_EQ(*cite, 2);
	cite--;
	EXPECT_EQ(*cite, 3);
	--cite;
	EXPECT_EQ(*cite, 4);
	cite--;
	EXPECT_EQ(*cite, 5);
}

TEST(TestSet, TestSetEmpty) {
	std::set<int> set;
	EXPECT_TRUE(set.empty());
	EXPECT_EQ(set.size(), 0);
}

TEST(TestSet, TestSetSize) {
	int ar[] = {1, 2, 3, 4, 5};
	std::set<int> set;
	std::set<int> set2(ar, ar + 5);

	EXPECT_EQ(set.size(), 0);
	EXPECT_EQ(set2.size(), 5);
}

TEST(TestSet, TestSetInsert) {
	std::set<int> set;
	int ar[] = {10, 20, 30, 40};
	std::set<int> set2(ar, ar + 4);

	EXPECT_EQ(set.size(), 0);
	set.insert(80);
	set.insert(90);
	set.insert(100);
	EXPECT_EQ(set.size(), 3);

	std::set<int>::iterator it = set.begin();
	set.insert(it, 50);
	set.insert(it, 60);
	set.insert(it, 70);
	EXPECT_EQ(set.size(), 6);

	set.insert(set2.begin(), set2.end());
	it = set.begin();

	for (int i = 10; i < 110; i += 10, it++)
		EXPECT_EQ(*it, i);

	EXPECT_EQ(set.size(), 10);
}

TEST(TestSet, TestSetErase) {
	int ar[] = {10, 20, 30, 40};
	std::set<int> set(ar, ar + 4);
	EXPECT_EQ(set.size(), 4);
	
	std::set<int>::iterator it = set.begin();
	set.erase(it);
	EXPECT_EQ(set.size(), 3);
	set.erase(20);
	EXPECT_EQ(set.size(), 2);

	set.insert(50);
	set.insert(60);
	set.insert(70);
	set.insert(80);
	EXPECT_EQ(set.size(), 6);

	std::set<int>::iterator it2 = set.begin();
	std::set<int>::iterator it3 = set.find(80);
	set.erase(it2, it3);
	EXPECT_EQ(set.size(), 1);
	set.erase(100);
	set.erase(500);
	EXPECT_EQ(set.size(), 1);
}

TEST(TestSet, TestSetSwap) {
	std::set<int> set;
	int ar[] = {10, 20, 30, 40};
	std::set<int> set2(ar, ar + 4);

	set.insert(80);
	set.insert(90);
	set.insert(100);
	EXPECT_EQ(set.size(), 3);

	set.swap(set2);
	EXPECT_EQ(set.size(), 4);
	EXPECT_EQ(set2.size(), 3);
	std::set<int>::iterator it = set.begin();
	for (int i = 10; i < 50; i += 10, it++)
		EXPECT_EQ(*it, i);

	std::set<int>::iterator it2 = set2.begin();
	for (int i = 80; i < 110; i += 10, it2++)
		EXPECT_EQ(*it2, i);
}

TEST(TestSet, TestSetClear) {
	int ar[] = {10, 20, 30, 40};
	std::set<int> set(ar, ar + 4);
	EXPECT_EQ(set.size(), 4);
	EXPECT_FALSE(set.empty());

	set.clear();
	EXPECT_EQ(set.size(), 0);
	EXPECT_TRUE(set.empty());
}

TEST(TestSet, TestSetKeyComp) {
	int ar[] = {10, 20, 30, 40};
	std::set<int> set(ar, ar + 4);
	std::set<int>::key_compare key_comp = set.key_comp();

	EXPECT_TRUE(key_comp(10, 20));
	EXPECT_TRUE(key_comp(20, 30));
	EXPECT_TRUE(key_comp(30, 40));
	EXPECT_FALSE(key_comp(40, 30));
}

TEST(TestSet, TestSetValueComp) {
	int ar[] = {10, 20, 30, 40};
	std::set<int> set(ar, ar + 4);
	std::set<int>::value_compare valueComp = set.value_comp();

	EXPECT_TRUE(valueComp(10, 20));
	EXPECT_FALSE(valueComp(20, 10));
	EXPECT_TRUE(valueComp(20, 30));
	EXPECT_FALSE(valueComp(30, 20));
}

TEST(TestSet, TestSetFind) {
	int ar[] = {10, 20, 30, 40};
	std::set<int> set(ar, ar + 4);
	std::set<int>::iterator first = set.find(10);
	EXPECT_EQ(*first, 10);
	
	std::set<int>::iterator second = set.find(20);
	EXPECT_EQ(*second, 20);
	
	std::set<int>::iterator third = set.find(30);
	EXPECT_EQ(*third, 30);
	
	std::set<int>::iterator it = set.find(80);

	EXPECT_EQ(it, set.end());

	std::set<int> const cSet(set);

	std::set<int>::const_iterator cit = cSet.find(30);
	EXPECT_EQ(*cit, 30);
}

TEST(TestSet, TestSetCount) {
	int ar[] = {10, 20, 30, 40};
	std::set<int> set(ar, ar + 4);

	EXPECT_EQ(set.count(10), 1);
	EXPECT_EQ(set.count(20), 1);
	EXPECT_EQ(set.count(30), 1);
	EXPECT_EQ(set.count(40), 1);
	EXPECT_EQ(set.count(50), 0);
	EXPECT_EQ(set.count(62), 0);
	EXPECT_EQ(set.count(70), 0);

	set.erase(10);
	EXPECT_EQ(set.count(10), 0);
}

TEST(TestSet, TestSetLowerBound) {
	int ar[] = {10, 20, 30, 40};
	std::set<int> set(ar, ar + 4);

	std::set<int>::iterator it = set.lower_bound(10);
	EXPECT_EQ(*it, 10);

	it = set.lower_bound(20);
	EXPECT_EQ(*it, 20);

	set.erase(30);
	it = set.lower_bound(30);
	EXPECT_EQ(*it, 40);

	set.insert(30);

	const std::set<int> set2(set);
	std::set<int>::const_iterator cit = set2.lower_bound(10);
	EXPECT_EQ(*cit, 10);
	
	std::set<int>::const_iterator cit2 = set2.lower_bound(80);
	EXPECT_EQ(cit2, set2.end());
}

TEST(TestSet, TestSetUpperBound) {
	int ar[] = {10, 20, 30, 40};
	std::set<int> set(ar, ar + 4);

	std::set<int>::iterator it = set.upper_bound(10);
	EXPECT_EQ(*it, 20);

	it = set.upper_bound(20);
	EXPECT_EQ(*it, 30);

	set.erase(30);
	it = set.upper_bound(30);
	EXPECT_EQ(*it, 40);

	set.insert(30);

	const std::set<int> set2(set);
	std::set<int>::const_iterator cit = set2.upper_bound(10);
	EXPECT_EQ(*cit, 20);
	
	std::set<int>::const_iterator cit2 = set2.upper_bound(80);
	EXPECT_EQ(cit2, set2.end());
}

TEST(TestSet, TestSetEqualRange) {
	int ar[] = {10, 20, 30, 40, 100};
	std::set<int> set(ar, ar + 5);

	std::pair<std::set<int>::iterator, std::set<int>::iterator> ret;
	ret = set.equal_range(10);
	EXPECT_EQ(*ret.first, 10);
	EXPECT_EQ(*ret.second, 20);

	ret = set.equal_range(20);
	EXPECT_EQ(*ret.first, 20);
	EXPECT_EQ(*ret.second, 30);

	ret = set.equal_range(60);
	EXPECT_EQ(*ret.first, 100);
	EXPECT_EQ(*ret.second, 100);

	std::set<int> const cset(ar, ar + 5);

	std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> cret;
	cret = cset.equal_range(10);
	EXPECT_EQ(*cret.first, 10);
	EXPECT_EQ(*cret.second, 20);

	cret = cset.equal_range(20);
	EXPECT_EQ(*cret.first, 20);
	EXPECT_EQ(*cret.second, 30);

	cret = cset.equal_range(60);
	EXPECT_EQ(*cret.first, 100);
	EXPECT_EQ(*cret.second, 100);
}

TEST(TestSet, TestSetGetAllocator) {
	std::set<int> set;
	std::allocator<int> alloc;
	EXPECT_EQ(set.get_allocator(), alloc);
}

TEST(TestSet, TestSetRelationalOperators) {
	int ar[] = {10, 20, 30, 40};
	int ar2[] = {10, 20, 30, 40, 50, 60, 70};
	std::set<int> set(ar, ar + 4);
	std::set<int> set2(ar2, ar2 + 7);
	std::set<int> const set3(set2);

	EXPECT_FALSE(set == set2);
	EXPECT_TRUE(set != set2);
	EXPECT_TRUE(set < set2);
	EXPECT_FALSE(set > set2);
	EXPECT_TRUE(set <= set2);
	EXPECT_FALSE(set >= set2);

	EXPECT_FALSE(set == set3);
	EXPECT_TRUE(set != set3);
	EXPECT_TRUE(set < set3);
	EXPECT_FALSE(set > set3);
	EXPECT_TRUE(set <= set3);
	EXPECT_FALSE(set >= set3);

	EXPECT_TRUE(set2 == set3);
	EXPECT_FALSE(set2 != set3);
	EXPECT_FALSE(set2 < set3);
	EXPECT_FALSE(set2 > set3);
	EXPECT_TRUE(set2 <= set3);
	EXPECT_TRUE(set2 >= set3);
}

TEST(TestSet, TestSetNonMemberSwap) {
	int ar[] = {10, 20, 30, 40};
	int ar2[] = {10, 20, 30, 40, 100};
	std::set<int> set(ar, ar + 4);
	std::set<int> set2(ar2, ar2 + 5);

	EXPECT_EQ(set.size(), 4);
	EXPECT_EQ(set2.size(), 5);

	std::swap(set2, set);
	EXPECT_EQ(set.size(), 5);
	EXPECT_EQ(set2.size(), 4);

	EXPECT_TRUE(set2 != set);
	EXPECT_FALSE(set2 == set);
}