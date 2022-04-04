cmake_minimum_required(VERSION 3.0)
project(GoogleTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" )

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} Test.cpp main.cpp)
target_include_directories(GoogleTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(GoogleTest PUBLIC air_ticket GTest::gtest_main)

