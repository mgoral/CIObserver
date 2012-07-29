include_directories(
    include
)

add_library(gui ${core_source_files})
target_link_libraries(gui core)
