cmake_minimum_required(VERSION 3.21)
project(IZ2 C)

set(CMAKE_C_STANDARD 99)
add_subdirectory(src)
add_executable(IZ2 main.c)
file(GLOB DATA_FILES "Data/*.txt")
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data)
target_link_libraries(IZ2 LINK_PUBLIC Letters Vector Sorting Searching interface)
