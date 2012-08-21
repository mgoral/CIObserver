file(GLOB_RECURSE CORE_SOURCE_FILES src/*.cpp)

add_library(core STATIC ${CORE_SOURCE_FILES})
target_link_libraries(
    core
    ${GTK2_LIBRARIES}
    ${POCO_FOUNDATION}
    ${POCO_NET}
    ${POCO_NET_SSL}
    ${POCO_CRYPTO}
)

install(
    TARGETS core
    ARCHIVE DESTINATION lib
)

create_test(core_tests core)
set(TEST_DEPS ${TEST_DEPS} PARENT_SCOPE)
