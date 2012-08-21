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

function(check_found lib_name var)
    if(${var} MATCHES "^[A-Za-z0-9_-]+NOTFOUND$")
        message(FATAL_ERROR "Found ${lib_name}: FALSE")
    else()
        message(STATUS "Found ${lib_name}: TRUE")
    endif()
endfunction(check_found)

macro(find_poco)
    find_library(
        POCO_CRYPTO
        NAMES PocoCrypto
    )
    check_found(POCO_CRYPTO ${POCO_CRYPTO})

    find_library(
        POCO_NET
        NAMES PocoNet
    )
    check_found(POCO_NET ${POCO_NET})

    find_library(
        POCO_NET_SSL
        NAMES PocoNetSSL
    )
    check_found(POCO_NET_SSL ${POCO_NET_SSL})

    find_library(
        POCO_FOUNDATION
        NAMES PocoFoundation
    )
    check_found(POCO_FOUNDATION ${POCO_FOUNDATION})

    find_library(
        POCO_UTIL
        NAMES PocoUtil
    )
    check_found(POCO_UTIL ${POCO_UTIL})

    find_library(
        POCO_XML
        NAMES PocoXML
    )
    check_found(POCO_XML ${POCO_XML})

    find_path(
        POCO_INC
        NAMES Poco/Poco.h
    )
    check_found(POCO-headers ${POCO_INC})
endmacro(find_poco)
