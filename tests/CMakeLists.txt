cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra -Werror -std=c++98 -g")

project(testCPP VERSION 1.0)
add_subdirectory(googletest)
add_executable(test
tests_vector.cpp
tests_type_traits.cpp
tests_algorithm.cpp
tests_utility.cpp
)

target_link_libraries( 
	test
	gtest_main )

target_include_directories(test PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/../includes
${CMAKE_CURRENT_SOURCE_DIR}/googletest)

include(GoogleTest)
gtest_discover_tests(test)