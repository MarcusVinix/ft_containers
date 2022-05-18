#include <gtest/gtest.h>
#include <type_traits.hpp>

TEST(TestTypeTraits, TestIsIntegralTrue) {
	EXPECT_TRUE(ft::is_integral<bool>::value == true);
	EXPECT_TRUE(ft::is_integral<char>::value == true);
	EXPECT_TRUE(ft::is_integral<wchar_t>::value == true);
	EXPECT_TRUE(ft::is_integral<signed char>::value == true);
	EXPECT_TRUE(ft::is_integral<short int>::value == true);
	EXPECT_TRUE(ft::is_integral<int>::value == true);
	EXPECT_TRUE(ft::is_integral<long int>::value == true);
	EXPECT_TRUE(ft::is_integral<long long int>::value == true);
	EXPECT_TRUE(ft::is_integral<unsigned char>::value == true);
	EXPECT_TRUE(ft::is_integral<unsigned short int>::value == true);
	EXPECT_TRUE(ft::is_integral<unsigned int>::value == true);
	EXPECT_TRUE(ft::is_integral<unsigned long int>::value == true);
	EXPECT_TRUE(ft::is_integral<unsigned long long int>::value == true);
}

TEST(TestTypeTraits, TestIsIntegralFalse) {
	EXPECT_FALSE(ft::is_integral<bool>::value == false);
	EXPECT_FALSE(ft::is_integral<char>::value == false);
	EXPECT_FALSE(ft::is_integral<wchar_t>::value == false);
	EXPECT_FALSE(ft::is_integral<signed char>::value == false);
	EXPECT_FALSE(ft::is_integral<short int>::value == false);
	EXPECT_FALSE(ft::is_integral<int>::value == false);
	EXPECT_FALSE(ft::is_integral<long int>::value == false);
	EXPECT_FALSE(ft::is_integral<long long int>::value == false);
	EXPECT_FALSE(ft::is_integral<unsigned char>::value == false);
	EXPECT_FALSE(ft::is_integral<unsigned short int>::value == false);
	EXPECT_FALSE(ft::is_integral<unsigned int>::value == false);
	EXPECT_FALSE(ft::is_integral<unsigned long int>::value == false);
	EXPECT_FALSE(ft::is_integral<unsigned long long int>::value == false);
}