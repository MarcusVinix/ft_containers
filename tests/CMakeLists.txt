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

add_executable(TestIncludes
tests_iterator.cpp
tests_reverse_iterator.cpp
tests_type_traits.cpp
tests_algorithm.cpp
tests_utility.cpp
tests_rb_tree.cpp
)
target_link_libraries(TestIncludes gtest_main)
target_include_directories(TestIncludes PUBLIC ${Header})
add_test(NAME TestIncludes COMMAND TestIncludes)

add_executable(TestVector tests_vector.cpp)
target_link_libraries(TestVector gtest_main)
target_include_directories(TestVector PUBLIC ${Header})
add_test(NAME TestVector COMMAND TestVector)

add_executable(TestStack tests_stack.cpp)
target_link_libraries(TestStack gtest_main)
target_include_directories(TestStack PUBLIC ${Header})
add_test(NAME TestStack COMMAND TestStack)

add_executable(TestMap tests_map.cpp)
target_link_libraries(TestMap gtest_main)
target_include_directories(TestMap PUBLIC ${Header})
add_test(NAME TestMap COMMAND TestMap)

add_executable(TestSet tests_set.cpp)
target_link_libraries(TestSet gtest_main)
target_include_directories(TestSet PUBLIC ${Header})
add_test(NAME TestSet COMMAND TestSet)

add_executable(TestPerformanceFt tests_performanceFt.cpp)
target_link_libraries(TestPerformanceFt gtest_main)
target_include_directories(TestPerformanceFt PUBLIC ${Header})
add_test(NAME TestPerformanceFt COMMAND TestPerformanceFt)

add_executable(TestPerformanceSTL tests_performanceSTL.cpp)
target_link_libraries(TestPerformanceSTL gtest_main)
target_include_directories(TestPerformanceSTL PUBLIC ${Header})
add_test(NAME TestPerformanceSTL COMMAND TestPerformanceSTL)


include(GoogleTest)
gtest_discover_tests(TestIncludes TestMap TestVector TestStack TestSet
TestPerformanceFt TestPerformanceSTL)
