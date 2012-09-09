cmake_minimum_required(VERSION 2.8)
project(CIObserver)

include(InternalFunctions.cmake)

set(PROJECT_INSTALL_DIR share/${PROJECT_NAME})

if(NOT CMAKE_BUILD_TYPE)
    set(
        CMAKE_BUILD_TYPE "Debug"
        CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
        FORCE
    )
endif(NOT CMAKE_BUILD_TYPE)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0 -fno-inline")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Os")

add_definitions("-std=c++0x")

add_subdirectory(src)
add_subdirectory(thirdparty EXCLUDE_FROM_ALL)

install(DIRECTORY data DESTINATION ${PROJECT_INSTALL_DIR})

