include_directories(
    include
)

set(
    core_source_files,
    file(GLOB_RECURSE ./*.cpp)
)

add_library(core ${core_source_files})
