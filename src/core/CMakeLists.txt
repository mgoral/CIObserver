include_directories(include)

file(GLOB_RECURSE CORE_SOURCE_FILES src/*.cpp)

# wxWidgets specific
find_package(wxWidgets COMPONENTS core base net xml)
include(${wxWidgets_USE_FILE})

add_library(core STATIC ${CORE_SOURCE_FILES})
target_link_libraries(core ${wxWidgets_LIBARIES})

install(
    TARGETS core
    ARCHIVE DESTINATION lib
)
