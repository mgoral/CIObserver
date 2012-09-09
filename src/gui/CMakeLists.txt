file(GLOB_RECURSE CORE_SOURCE_FILES src/*.cpp)

add_library(gui STATIC ${CORE_SOURCE_FILES})
target_link_libraries(
    gui
    core
    ${POCO_FOUNDATION}
    ${POCO_UTIL}
)
