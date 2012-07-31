# ----- Target: CIObserver

add_subdirectory(core)

set(PROJECT_SOURCE_FILES main.cpp)
set(PROJECT_BIN ${PROJECT_NAME})

add_executable(${PROJECT_BIN} ${PROJECT_SOURCE_FILES})
target_link_libraries(${PROJECT_BIN} core)

if(NOT ${CMAKE_BUILD_TYPE} MATCHES "^[A-Za-z]*Deb[A-Za-z]+$")
    message(STATUS "Build type is '${CMAKE_BUILD_TYPE}'. Binaries will BE srtipped.")
    set_target_properties(
        ${PROJECT_BIN} PROPERTIES
        LINK_FLAGS "-s"
    )
elseif(${CMAKE_BUILD_TYPE} MATCHES "^[A-Za-z0-9_]+")
    message(STATUS "Build type is '${CMAKE_BUILD_TYPE}'. Binaries will NOT BE srtipped.")
endif()

# ----- Target: CIObserver_exe_test

set(PROJECT_TEST_BIN ${PROJECT_BIN}_test)

include_directories(
    ${PROJECT_SOURCE_DIR}/thirdparty/gmock/include
    ${PROJECT_SOURCE_DIR}/thirdparty/gmock/gtest/include
)

file(
    GLOB_RECURSE TEST_FILES
    */tests/*Tests.cpp
)

add_executable(${PROJECT_TEST_BIN} EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries(${PROJECT_TEST_BIN} gtest_main gmock)

# ----- Add custom targets and installation dir for main binary

if (NOT CMAKE_CROSSCOMPILING)
    add_custom_target(
        check
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_TEST_BIN}"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_BIN}"
        DEPENDS ${PROJECT_TEST_BIN} ${PROJECT_BIN}
        COMMENT "Checking build (UT + executing a binary)"
        VERBATIM
    ) # SOURCES ${test_SRCS})

    add_custom_target(
        test
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_TEST_BIN}"
        DEPENDS ${PROJECT_TEST_BIN}
        COMMENT "Executing Unit Tests"
        VERBATIM
    ) # SOURCES ${test_SRCS})
endif (NOT CMAKE_CROSSCOMPILING)

install(
    TARGETS ${PROJECT_BIN}
    RUNTIME DESTINATION bin
)
