cmake_minimum_required(VERSION 2.6)
project(CIObserver)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0 -fno-inline")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Os")

add_subdirectory(src)
add_subdirectory(thirdparty EXCLUDE_FROM_ALL)

