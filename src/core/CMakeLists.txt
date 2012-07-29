include_directories(include)

file(GLOB_RECURSE core_source_files src *.cpp)

# wxWidgets specific
find_package(wxWidgets COMPONENTS core base net xml)
include(${wxWidgets_USE_FILE})
message(dupa111: ${wxWidgets_USE_FILE}, ${wxWidgets_LIBRARIES})

add_library(core STATIC ${core_source_files})
target_link_libraries(core ${wxWidgets_LIBRARIES})
