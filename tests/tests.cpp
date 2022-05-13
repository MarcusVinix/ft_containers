#include <iostream>
#include <vector>
#include <gtest/gtest.h>

using namespace std;

vector<int>::size_type default_capacity = 0;
vector<int>::size_type five_capacity = 5;

typedef vector<int>::iterator int_iterator;
typedef vector<string>::iterator string_iterator;
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