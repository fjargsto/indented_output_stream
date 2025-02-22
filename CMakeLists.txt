cmake_minimum_required(VERSION 3.5)

set(BOOST_INCLUDE "../dep/include" CACHE PATH "Boost include directory.")
include_directories(${BOOST_INCLUDE} ./include)
set(BOOST_LINK "../dep/lib" CACHE PATH "Boost library directory.")
link_directories(${BOOST_LINK})

project(indented_output_stream)
include(CTest)
add_executable(example example/main.cpp)

add_executable(unit_test unit_test/main.cpp)
target_link_libraries(unit_test libboost_unit_test_framework.a)

add_test(NAME example_test
         COMMAND example)
add_test(NAME unit_test
         COMMAND unit_test)
