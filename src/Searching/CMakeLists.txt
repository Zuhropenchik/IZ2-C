add_library(Searching Searching.h Searching.c)
target_include_directories(Searching PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Searching LINK_PUBLIC Letters Vector)