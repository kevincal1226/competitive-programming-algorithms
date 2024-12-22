cmake_minimum_required(VERSION 3.10)
project(CompetitiveProgrammingAlgorithms)

set(CMAKE_CXX_STANDARD 23)

find_package(GTest REQUIRED)

add_executable(tests tests.cpp)

target_link_libraries(tests GTest::GTest GTest::Main pthread)

