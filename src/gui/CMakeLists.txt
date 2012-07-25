include_directories(
    include
)

set(
    gui_source_files,
    file(GLOB_RECURSE ./*.cpp)
)

add_library(gui ${core_source_files})
target_link_libraries(gui core)
