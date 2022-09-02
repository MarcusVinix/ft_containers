cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra -Werror -std=c++98 -g")

set(Header ${CMAKE_CURRENT_SOURCE_DIR}/../includes
${CMAKE_CURRENT_SOURCE_DIR}/../iterators
${CMAKE_CURRENT_SOURCE_DIR}/../containers
${CMAKE_CURRENT_SOURCE_DIR}/googletest)

project(testCPP VERSION 1.0)
add_subdirectory(googletest)

enable_testing()

add_executable(TestFTContainers
tests_iterator.cpp
tests_reverse_iterator.cpp
tests_type_traits.cpp
tests_algorithm.cpp
tests_utility.cpp
tests_rb_tree.cpp
tests_vector.cpp
tests_stack.cpp
tests_map.cpp
tests_set.cpp
tests_performanceFt.cpp
)
target_link_libraries(TestFTContainers gtest_main)
target_include_directories(TestFTContainers PUBLIC ${Header})
add_test(NAME TestFTContainers COMMAND TestFTContainers)

add_executable(TestSTLContainers
STL/tests_iterator.stl.cpp
STL/tests_reverse_iterator.stl.cpp
STL/tests_type_traits.stl.cpp
STL/tests_algorithm.stl.cpp
STL/tests_utility.stl.cpp
STL/tests_vector.stl.cpp
STL/tests_stack.stl.cpp
STL/tests_map.stl.cpp
STL/tests_set.stl.cpp
tests_performanceSTL.cpp
)
target_link_libraries(TestSTLContainers gtest_main)
target_include_directories(TestSTLContainers PUBLIC ${Header})
add_test(NAME TestSTLContainers COMMAND TestSTLContainers)

include(GoogleTest)
gtest_discover_tests(TestFTContainers TestSTLContainers)
