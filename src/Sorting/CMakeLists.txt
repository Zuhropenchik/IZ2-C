add_library(Sorting Sorting.h Sorting.c)
target_include_directories(Sorting PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Sorting LINK_PUBLIC Letters Vector)