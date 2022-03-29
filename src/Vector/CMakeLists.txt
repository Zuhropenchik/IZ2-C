add_library(Vector Vector.h Vector.c)
target_include_directories(Vector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Vector LINK_PUBLIC Letters)