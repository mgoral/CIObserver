function(create_test test_name link_libs)
    set(TEST_BIN ${test_name})
    set(TEST_TARGET ${test_name}_exe)

    include_directories(
        ${PROJECT_SOURCE_DIR}/thirdparty/gmock/include
        ${PROJECT_SOURCE_DIR}/thirdparty/gmock/gtest/include
        tests/mocks
    )

    file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

    add_executable(${TEST_BIN} EXCLUDE_FROM_ALL ${TEST_SOURCES})
    target_link_libraries(
        ${TEST_BIN}
        gtest_main
        gmock
        ${link_libs}
    )

    add_custom_target(
        ${TEST_TARGET}
        "${CMAKE_CURRENT_BINARY_DIR}/${TEST_BIN}"
        DEPENDS ${TEST_BIN}
        VERBATIM
    )

    set(TEST_DEPS ${TEST_DEPS} ${TEST_TARGET} PARENT_SCOPE)
endfunction(create_test)

