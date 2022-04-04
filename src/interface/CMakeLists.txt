add_library(interface interface.h interface.c)
target_include_directories(interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(interface LINK_PUBLIC Letters Vector)
if(parallel)
    target_link_libraries(interface LINK_PUBLIC Searching_Parallel)
else()
    target_link_libraries(interface LINK_PUBLIC Searching_Consistent)
endif(parallel)

