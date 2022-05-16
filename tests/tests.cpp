#include <iostream>
#include <vector>
#include <gtest/gtest.h>

/**
 * Test of vector container
 * OBS: Needed change all vector<int> and vector<string> to ft::.
 * The last test of swap non member function need change from std to ft.
 */

using namespace std;

vector<int>::size_type default_capacity = 0;
vector<int>::size_type five_capacity = 5;

typedef vector<int>::iterator int_iterator;
typedef vector<string>::iterator string_iterator;
typedef vector<int>::const_iterator int_const_iterator;
typedef vector<string>::const_iterator string_const_iterator;
typedef vector<int>::reverse_iterator int_riterator;
typedef vector<string>::reverse_iterator string_riterator;

TEST(TestVectorConstructors, TestVectorDefaultConstructor) {
	vector<int> vec1;
	vector<int, std::allocator<int>> vec2;

	EXPECT_EQ(vec1.size(), 0);
	EXPECT_EQ(vec1.capacity(), default_capacity);
	EXPECT_EQ(vec2.size(), 0);
	EXPECT_EQ(vec2.capacity(), default_capacity);
}

TEST(TestVectorConstructors, TestVectorFillConstructor) {
	vector<int> vec1(5);
	vector<string> vec2(5, "fill");

	EXPECT_EQ(vec1.size(), 5);
	EXPECT_EQ(vec1.capacity(), 5);
	for(int_iterator it = vec1.begin(); it != vec1.end(); it++)
		EXPECT_EQ(*it, 0);

	EXPECT_EQ(vec2.size(), 5);
	EXPECT_EQ(vec2.capacity(), 5);
	for(string_iterator it = vec2.begin(); it != vec2.end(); it++)
		EXPECT_EQ(*it, "fill");
}

TEST(TestVectorConstructors, TestVectorRangeConstructor) {
	int array1[] = {1, 2, 3, 4, 5};
	std::string array2[] = { "one", "two", "three", "four", "five"};

	vector<int> vec1(array1, array1 + 5);
	vector<std::string> vec2(array2, array2 + 5);

	EXPECT_EQ(vec1.size(), 5);
	EXPECT_EQ(vec1.capacity(), five_capacity);
	for (int i  = 0; i < 5; i++)
		EXPECT_EQ(vec1[i], array1[i]);
		
	EXPECT_EQ(vec2.size(), 5);
	EXPECT_EQ(vec2.capacity(), five_capacity);
	for (int i  = 0; i < 5; i++)
		EXPECT_EQ(vec2[i], array2[i]);
}

TEST(TestVectorConstructors, TestVectorCopyConstructor) {
	int array1[] = {1, 2, 3, 4, 5};
	std::string array2[] = { "one", "two", "three", "four", "five"};

	vector<int> vec1(array1, array1 + 5);
	vector<std::string> vec2(array2, array2 + 5);

	vector<int> vec3(vec1);
	vector<std::string> vec4(vec2);

	EXPECT_EQ(vec3.size(), 5);
	EXPECT_EQ(vec3.capacity(), five_capacity);
	for (int i  = 0; i < 5; i++)
		EXPECT_EQ(vec3[i], array1[i]);
		
	EXPECT_EQ(vec4.size(), 5);
	EXPECT_EQ(vec4.capacity(), five_capacity);
	for (int i  = 0; i < 5; i++)
		EXPECT_EQ(vec4[i], array2[i]);
}

TEST(TestVectorOperators, TestVectorAssignmentOperator) {
	int array1[] = {1, 2, 3, 4, 5};
	std::string array2[] = { "one", "two", "three", "four", "five"};

	vector<int> vec1(array1, array1 + 5);
	vector<std::string> vec2(array2, array2 + 5);

	vector<int> vec3 = vec1;
	vector<std::string> vec4 = vec2;

	EXPECT_EQ(vec3.size(), 5);
	EXPECT_EQ(vec3.capacity(), five_capacity);
	for (int i  = 0; i < 5; i++)
		EXPECT_EQ(vec3[i], array1[i]);
		
	EXPECT_EQ(vec4.size(), 5);
	EXPECT_EQ(vec4.capacity(), five_capacity);
	for (int i  = 0; i < 5; i++)
		EXPECT_EQ(vec4[i], array2[i]);
}

TEST(TestVectorIterator, TestVectorIteratorBegin) {
	int array1[] = {1, 2, 3, 4, 5};
	std::string array2[] = { "one", "two", "three", "four", "five"};

	vector<int> vec1(array1, array1 + 5);
	vector<std::string> vec2(array2, array2 + 5);

	int_iterator it = vec1.begin();
	EXPECT_EQ(*it, 1);
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(*(it + i), array1[i]);

	string_iterator it2 = vec2.begin();
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(*(it2 + i), array2[i]);

	vector<int> const vec3(array1, array1 + 5);
	vector<std::string> vec4(array2, array2 + 5);

	int_const_iterator it3 = vec3.begin();
	EXPECT_EQ(*it, 1);
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(*(it3 + i), array1[i]);

	string_const_iterator it4 = vec4.begin();
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(*(it4 + i), array2[i]);
}

TEST(TestVectorIterator, TestVectorIteratorEnd) {
	int array1[] = {1, 2, 3, 4, 5};
	std::string array2[] = { "one", "two", "three", "four", "five"};

	vector<int> vec1(array1, array1 + 5);
	vector<std::string> vec2(array2, array2 + 5);

	int_iterator it = vec1.end();
	for (int i = 4; i >= 0; i--, --it)
		EXPECT_EQ(*(it - 1), array1[i]);

	string_iterator it2 = vec2.end();
	for (int i = 4; i >= 0; i--, --it2)
		EXPECT_EQ(*(it2 - 1), array2[i]);

	vector<int> const vec3(array1, array1 + 5);
	vector<std::string> const vec4(array2, array2 + 5);

	int_const_iterator it3 = vec3.end();
	for (int i = 4; i >= 0; i--, --it3)
		EXPECT_EQ(*(it3 - 1), array1[i]);

	string_const_iterator it4 = vec4.end();
	for (int i = 4; i >= 0; i--, --it4)
		EXPECT_EQ(*(it4 - 1), array2[i]);
}

TEST(TestVectorIterator, TestVectorIteratorRBegin) {
	int array1[] = {1, 2, 3, 4, 5};
	std::string array2[] = { "one", "two", "three", "four", "five"};

	vector<int> vec1(array1, array1 + 5);
	vector<std::string> vec2(array2, array2 + 5);

	int_riterator rit = vec1.rbegin();
	int_iterator it = vec1.end();
	EXPECT_EQ(*rit, 5);
	for (int i = 0; i < 5; ++i, rit++)
		EXPECT_EQ(*rit, *(it - 1 - i));

	string_riterator rit2 = vec2.rbegin();
	string_iterator it2 = vec2.end();
	for (int i = 0; i < 5; ++i, rit2++)
		EXPECT_EQ(*rit2, *(it2 - 1 - i));
}

TEST(TestVectorIterator, TestVectorIteratorREnd) {
	int array1[] = {1, 2, 3, 4, 5};
	std::string array2[] = { "one", "two", "three", "four", "five"};

	vector<int> vec1(array1, array1 + 5);
	vector<std::string> vec2(array2, array2 + 5);

	int_riterator rit = vec1.rend();
	int_iterator it = vec1.begin();

	for (int i = 0; i < 5; i++, --rit)
		EXPECT_EQ(*(rit - 1), *(it + i));

	string_riterator rit2 = vec2.rend();
	string_iterator it2 = vec2.begin();
	for (int i = 0; i < 5; i++, --rit2)
		EXPECT_EQ(*(rit2 - 1), *(it2 + i));
}

TEST(TestVectorCapacity, TestVectorSize) {
	vector<int> vec1;
	EXPECT_EQ(vec1.size(), 0);

	int array1[] = {1, 2, 3, 4, 5};
	vector<int> vec2(array1, array1 + 5);
	EXPECT_EQ(vec2.size(), 5);

	vector<int> vec3(vec2);
	EXPECT_EQ(vec3.size(), 5);
}

TEST(TestVectorCapacity, TestVectorMaxSize) {
	std::allocator<int> alloc;
	vector<int> vec(alloc);
	EXPECT_EQ(vec.max_size(), alloc.max_size());
}

TEST(TestVectorCapacity, TestVectorResize) {
	vector<int>	vec;
	int array[] = { 1, 2, 3, 4, 5, 100, 100, 100, 0, 0, 0, 0 };

	for (int i = 1; i < 10; i++)
		vec.push_back(i);
	vec.resize(5);
	vec.resize(8, 100);
	vec.resize(12);
	int i = 0;
	for (int_iterator it = vec.begin(); it != vec.end(); it++, i++)
		EXPECT_EQ(*it, array[i]);
}

TEST(TestVectorCapacity, TestVectorCapacity) {
	vector<int> vec1;
	EXPECT_EQ(vec1.capacity(), default_capacity);

	vector<int> vec2(5);
	EXPECT_EQ(vec2.capacity(), 5);

	vector<int> vec3(10, 5);
	EXPECT_EQ(vec3.capacity(), 10);
}

TEST(TestVectorCapacity, TestVectorEmpty) {
	vector<int> vec;
	EXPECT_TRUE(vec.empty());

	vector<int> vec2(5);
	EXPECT_FALSE(vec2.empty());

	vector<int> vec3(1, 10);
	EXPECT_FALSE(vec3.empty());
}

TEST(TestVectorCapacity, TestVectorReserve) {
	vector<int> vec;
	EXPECT_EQ(vec.capacity(), default_capacity);

	vec.reserve(5);
	EXPECT_EQ(vec.capacity(), 5);

	vector<int> vec2(10);
	EXPECT_EQ(vec2.capacity(), 10);
	vec2.reserve(5);
	EXPECT_EQ(vec2.capacity(), 10);
}

TEST(TestVectorElementAccess, TestVectorElementAccessOperator) {
	int array[] = {1, 2, 3, 4, 5};
	vector<int> vec(array, array + 5);
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(vec[i], array[i]);
	vec.reserve(12);
	for ( int i = 5; i < 10; i++)
		vec[i] = i + 1;
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(vec[i], i + 1);

	vector<int> const vec2(array, array + 5);
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(vec2[i], array[i]);
}

TEST(TestVectorElementAccess, TestVectorAt) {
	int array[] = {1, 2, 3, 4, 5};
	vector<int> vec(array, array + 5);
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(vec.at(i), array[i]);
	EXPECT_THROW(vec.at(5), std::out_of_range);

	vector<int> const vec2(array, array + 5);
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(vec2.at(i), array[i]);
	EXPECT_THROW(vec2.at(5), std::out_of_range);
}

TEST(TestVectorElementAccess, TestVectorFront) {
	int array[] = {1, 2, 3, 4, 5};
	vector<int> vec(array, array + 5);
	EXPECT_EQ(vec.front(), 1);
	
	vector<int> const vec2(array, array + 5);
	EXPECT_EQ(vec2.front(), 1);
}

TEST(TestVectorElementAccess, TestVectorBack) {
	int array[] = {1, 2, 3, 4, 5};
	vector<int> vec(array, array + 5);
	EXPECT_EQ(vec.back(), 5);
	
	vector<int> const vec2(array, array + 5);
	EXPECT_EQ(vec2.back(), 5);
}

TEST(TestVectorModifiers, TestVectorAssign) {
	vector<int> vec;
	vec.assign(5, 100);
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(vec[i], 100);
	
	vector<int> vec2;
	vec.assign(vec.begin(), vec.end());
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(vec[i], 100);
}

TEST(TestVectorModifiers, TestVectorPushBack) {
	vector<int> vec;
	for (int i = 0; i < 5; i++)
		vec.push_back(i);
	EXPECT_EQ(vec.size(), 5);
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(vec[i], i);

	int array[] = {1, 2, 3, 4, 5};
	vector<int> vec2(array, array + 5);
	EXPECT_EQ(vec2.size(), 5);
	vec2.push_back(6);
	EXPECT_EQ(vec2[5], 6);
	EXPECT_EQ(vec2.size(), 6);
}

TEST(TestVectorModifiers, TestVectorPopBack) {
	vector<int> vec(5);
	EXPECT_EQ(vec.size(), 5);
	vec.pop_back();
	EXPECT_EQ(vec.size(), 4);

	vector<int> vec2(10, 100);
	EXPECT_EQ(vec2.size(), 10);
	vec2.pop_back();
	EXPECT_EQ(vec2.size(), 9);
}

TEST(TestVectorModifiers, TestVectorInsert) {
	vector<int> vec(5, 100);
	vec.insert(vec.begin(), 7);
	EXPECT_EQ(vec[0], 7);
	for (int i = 1; i < 4; i++)
		EXPECT_EQ(vec[i], 100);
	
	vec.insert(vec.begin(), 10, 5);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(vec[i], 5);

	vector<int> vec2;
	vec2.insert(vec2.begin(), vec.begin(), vec.end());
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(vec[i], 5);
}

TEST(TestVectorModifiers, TestVectorErase) {
	int array[] = {1, 2, 3, 4, 5};
	vector<int> vec(array, array + 5);
	vec.erase(vec.begin());
	EXPECT_EQ(vec.size(), 4);
	EXPECT_EQ(vec[0], 2);

	vec.erase(vec.begin() + 2, vec.end());
	EXPECT_EQ(vec.size(), 2);
	EXPECT_EQ(vec[0], 2);
	EXPECT_EQ(vec[1], 3);

	vector<int> vec2(array, array + 5);
	vec2.erase(vec2.begin() + 2);
	EXPECT_EQ(vec2[2], 4);
	EXPECT_EQ(vec2.size(), 4);
}

TEST(TestVectorModifiers, TestVectorSwap) {
	vector<int> foo(3, 100);
	vector<int> bar(5, 200);

	foo.swap(bar);
	EXPECT_EQ(foo.size(), 5);
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(foo[i], 200);
	EXPECT_EQ(bar.size(), 3);
	for (int i = 0; i < 3; i++)
		EXPECT_EQ(bar[i], 100);
}

TEST(TestVectorModifiers, TestVectorClear) {
	vector<int> vec(5, 200);
	EXPECT_EQ(vec.size(), 5);
	EXPECT_EQ(vec[0], 200);

	vec.clear();
	EXPECT_EQ(vec.size(), 0);
	vec.push_back(100);
	EXPECT_EQ(vec[0], 100);
}

TEST(TestVectorAllocator, TestVectorGetAllocator) {
	vector<int> vec;
	int *p;
	unsigned int i;

	p = vec.get_allocator().allocate(5);
	for (i = 0; i < 5; i++)
		vec.get_allocator().construct(&p[i], i);
	for (i = 0; i < 5; i++)
		EXPECT_EQ(p[i], i);
	for (i = 0; i < 5; i++)
		vec.get_allocator().destroy(&p[i]);
	vec.get_allocator().deallocate(p, 5);
}

TEST(TestVectorNonMemberFunctionOverloads, TestVectorRelationalOperators) {
	vector<int> vec1(3, 100);
	vector<int> vec2(3, 100);
	vector<int> vec3(3, 200);
	vector<int> vec4(5, 100);

	EXPECT_TRUE(vec1 == vec2);
	EXPECT_FALSE(vec1 == vec3);
	EXPECT_FALSE(vec1 == vec4);

	EXPECT_FALSE(vec1 != vec2);
	EXPECT_TRUE(vec1 != vec3);
	EXPECT_TRUE(vec1 != vec4);

	EXPECT_FALSE(vec1 < vec2);
	EXPECT_TRUE(vec1 < vec3);
	EXPECT_TRUE(vec1 < vec4);

	EXPECT_TRUE(vec1 <= vec2);
	EXPECT_TRUE(vec1 <= vec3);
	EXPECT_TRUE(vec1 <= vec4);

	EXPECT_FALSE(vec1 > vec2);
	EXPECT_FALSE(vec1 > vec3);
	EXPECT_FALSE(vec1 > vec4);

	EXPECT_TRUE(vec1 >= vec2);
	EXPECT_FALSE(vec1 >= vec3);
	EXPECT_FALSE(vec1 >= vec4);
}

TEST(TestVectorNonMemberFunctionOverloads, TestVectorSwapOverload) {
	vector<int> foo(3, 100);
	vector<int> bar(5, 200);

	std::swap(bar, foo);
	EXPECT_EQ(foo.size(), 5);
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(foo[i], 200);
	EXPECT_EQ(bar.size(), 3);
	for (int i = 0; i < 3; i++)
		EXPECT_EQ(bar[i], 100);
}