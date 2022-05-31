#include <gtest/gtest.h>
#include <algorithm>

bool predInt( int a, int b ) { return a == b; };
bool predString( std::string a, std::string b ) { return a == b; };

bool compInt( int a, int b ) { return a < b; }
bool compString( std::string a, std::string b ) { return a < b; }

TEST(TestAlgorithm, TestEqualEmpty) {
	std::vector<int> vec1;
	std::vector<int> vec2;
	std::vector<std::string> vec3;
	std::vector<std::string> vec4;

	EXPECT_TRUE(std::equal(vec1.begin(), vec1.end(), vec2.begin()));
	EXPECT_TRUE(std::equal(vec1.rbegin(), vec1.rend(), vec2.rbegin()));
	EXPECT_TRUE(std::equal(vec3.begin(), vec3.end(), vec4.begin()));
	EXPECT_TRUE(std::equal(vec3.rbegin(), vec3.rend(), vec4.rbegin()));
}

TEST(TestAlgorithm, TestEqualTrue) {
	std::vector<int> vec1 = {1, 2, 3, 4, 5};
	std::vector<int> vec2 = {1, 2, 3, 4, 5};
	std::vector<std::string> vec3 = {"one", "two", "three", "four", "five"};
	std::vector<std::string> vec4 = {"one", "two", "three", "four", "five"};

	EXPECT_TRUE(std::equal(vec1.begin(), vec1.end(), vec2.begin()));
	EXPECT_TRUE(std::equal(vec1.rbegin(), vec1.rend(), vec2.rbegin()));
	EXPECT_TRUE(std::equal(vec3.begin(), vec3.end(), vec4.begin()));
	EXPECT_TRUE(std::equal(vec3.rbegin(), vec3.rend(), vec4.rbegin()));
}

TEST(TestAlgorithm, TestEqualFalse) {
	std::vector<int> vec1 = {1, 2, 3, 4, 5};
	std::vector<int> vec2 = {1, 2, 5, 4, 5};
	std::vector<std::string> vec3 = {"one", "two", "three", "four", "five"};
	std::vector<std::string> vec4 = {"one", "two", "four", "four", "five"};

	EXPECT_FALSE(std::equal(vec1.begin(), vec1.end(), vec2.begin()));
	EXPECT_FALSE(std::equal(vec1.rbegin(), vec1.rend(), vec2.rbegin()));
	EXPECT_FALSE(std::equal(vec3.begin(), vec3.end(), vec4.begin()));
	EXPECT_FALSE(std::equal(vec3.rbegin(), vec3.rend(), vec4.rbegin()));
}

TEST(TestAlgorithm, TestEqualPred) {
	std::vector<int> vec1 = {1, 2, 3, 4, 5};
	std::vector<int> vec2 = {1, 2, 3, 4, 5};
	std::vector<std::string> vec3 = {"one", "two", "three", "four", "five"};
	std::vector<std::string> vec4 = {"one", "two", "three", "four", "five"};

	EXPECT_TRUE(std::equal(vec1.begin(), vec1.end(), vec2.begin(), predInt));
	EXPECT_TRUE(std::equal(vec1.rbegin(), vec1.rend(), vec2.rbegin(), predInt));
	EXPECT_TRUE(std::equal(vec3.begin(), vec3.end(), vec4.begin(), predString));
	EXPECT_TRUE(std::equal(vec3.rbegin(), vec3.rend(), vec4.rbegin(), predString));

	std::vector<int> vec5 = {1, 2, 3, 4, 5};
	std::vector<int> vec6 = {1, 2, 5, 4, 5};
	std::vector<std::string> vec7 = {"one", "two", "three", "four", "five"};
	std::vector<std::string> vec8 = {"one", "two", "four", "four", "five"};

	EXPECT_FALSE(std::equal(vec5.begin(), vec5.end(), vec6.begin(), predInt));
	EXPECT_FALSE(std::equal(vec5.rbegin(), vec5.rend(), vec6.rbegin(), predInt));
	EXPECT_FALSE(std::equal(vec7.begin(), vec7.end(), vec8.begin(), predString));
	EXPECT_FALSE(std::equal(vec7.rbegin(), vec7.rend(), vec8.rbegin(), predString));
}

TEST(TestAlgorithm, TestLexicoGraphicalEmpty) {
	std::vector<int> vec1;
	std::vector<int> vec2;
	std::vector<std::string> vec3;
	std::vector<std::string> vec4;

	EXPECT_FALSE(std::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()));
	EXPECT_FALSE(std::lexicographical_compare(vec1.rbegin(), vec1.rend(), vec2.rbegin(), vec2.rend()));
	EXPECT_FALSE(std::lexicographical_compare(vec3.begin(), vec3.end(), vec4.begin(), vec4.end()));
	EXPECT_FALSE(std::lexicographical_compare(vec3.rbegin(), vec3.rend(), vec4.rbegin(), vec4.rend()));
}

TEST(TestAlgorithm, TestLexicoGraphicalEqualValues) {
	std::vector<int> vec1 = {1, 2, 3, 4, 5};
	std::vector<int> vec2 = {1, 2, 3, 4, 5};
	std::vector<std::string> vec3 = {"one", "two", "three", "four", "five"};
	std::vector<std::string> vec4 = {"one", "two", "three", "four", "five"};

	EXPECT_FALSE(std::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()));
	EXPECT_FALSE(std::lexicographical_compare(vec1.rbegin(), vec1.rend(), vec2.rbegin(), vec2.rend()));
	EXPECT_FALSE(std::lexicographical_compare(vec3.begin(), vec3.end(), vec4.begin(), vec4.end()));
	EXPECT_FALSE(std::lexicographical_compare(vec3.rbegin(), vec3.rend(), vec4.rbegin(), vec4.rend()));
}

TEST(TestAlgorithm, TestLexicoGraphicalLess) {
	std::vector<int> vec1 = {1, 2, 3, 4, 5};
	std::vector<int> vec2 = {1, 2, 3, 4, 6};
	std::vector<std::string> vec3 = {"one", "two", "three", "four", "five"};
	std::vector<std::string> vec4 = {"one", "two", "three", "four", "six"};

	EXPECT_TRUE(std::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()));
	EXPECT_TRUE(std::lexicographical_compare(vec1.rbegin(), vec1.rend(), vec2.rbegin(), vec2.rend()));
	EXPECT_TRUE(std::lexicographical_compare(vec3.begin(), vec3.end(), vec4.begin(), vec4.end()));
	EXPECT_TRUE(std::lexicographical_compare(vec3.rbegin(), vec3.rend(), vec4.rbegin(), vec4.rend()));
}

TEST(TestAlgorithm, TestLexicoGraphicalGreater) {
	std::vector<int> vec1 = {1, 2, 3, 4, 5};
	std::vector<int> vec2 = {1, 2, 3, 4, 4};
	std::vector<std::string> vec3 = {"one", "two", "three", "four", "five"};
	std::vector<std::string> vec4 = {"one", "two", "three", "four", "b"};

	EXPECT_FALSE(std::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()));
	EXPECT_FALSE(std::lexicographical_compare(vec1.rbegin(), vec1.rend(), vec2.rbegin(), vec2.rend()));
	EXPECT_FALSE(std::lexicographical_compare(vec3.begin(), vec3.end(), vec4.begin(), vec4.end()));
	EXPECT_FALSE(std::lexicographical_compare(vec3.rbegin(), vec3.rend(), vec4.rbegin(), vec4.rend()));
}

TEST(TestAlgorithm, TestLexicoGraphicalComp) {
	std::vector<int> vec1 = {1, 2, 3, 4, 5};
	std::vector<int> vec2 = {1, 2, 3, 4, 7};
	std::vector<std::string> vec3 = {"one", "two", "three", "four", "five"};
	std::vector<std::string> vec4 = {"one", "two", "three", "four", "seven"};

	EXPECT_TRUE(std::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), compInt));
	EXPECT_TRUE(std::lexicographical_compare(vec1.rbegin(), vec1.rend(), vec2.rbegin(), vec2.rend(), compInt));
	EXPECT_TRUE(std::lexicographical_compare(vec3.begin(), vec3.end(), vec4.begin(), vec4.end(), compString));
	EXPECT_TRUE(std::lexicographical_compare(vec3.rbegin(), vec3.rend(), vec4.rbegin(), vec4.rend(), compString));

	std::vector<int> vec5 = {1, 2, 3, 4, 5};
	std::vector<int> vec6 = {1, 2, 3, 4, 4};
	std::vector<std::string> vec7 = {"one", "two", "three", "four", "five"};
	std::vector<std::string> vec8 = {"one", "two", "three", "four", "b"};

	EXPECT_FALSE(std::lexicographical_compare(vec5.begin(), vec5.end(), vec6.begin(), vec6.end(), compInt));
	EXPECT_FALSE(std::lexicographical_compare(vec5.rbegin(), vec5.rend(), vec6.rbegin(), vec6.rend(), compInt));
	EXPECT_FALSE(std::lexicographical_compare(vec7.begin(), vec7.end(), vec8.begin(), vec8.end(), compString));
	EXPECT_FALSE(std::lexicographical_compare(vec7.rbegin(), vec7.rend(), vec8.rbegin(), vec8.rend(), compString));
}
