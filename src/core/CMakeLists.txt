file(GLOB_RECURSE CORE_SOURCE_FILES src/*.cpp)

# wxWidgets specific
find_package(wxWidgets COMPONENTS core base net xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(core STATIC ${CORE_SOURCE_FILES})
target_link_libraries(core ${wxWidgets_LIBRARIES})

install(
    TARGETS core
    ARCHIVE DESTINATION lib
)

create_test(core_tests core)
set(TEST_DEPS ${TEST_DEPS} PARENT_SCOPE)
