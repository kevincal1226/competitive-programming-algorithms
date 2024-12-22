cmake_minimum_required(VERSION 3.10)
project(CompetitiveProgrammingAlgorithms)

set(CMAKE_CXX_STANDARD 23)

find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp")

add_executable(tests ${SOURCES} src/tests.cpp)

target_link_libraries(tests GTest::GTest GTest::Main pthread)

