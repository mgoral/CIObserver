#find_package(GTK2 2.4 REQUIRED gtk gtkmm)
find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GTKMM glibmm-2.4)

find_poco()

include_directories(
    core/include
    gui/include
    #${GTK2_INCLUDE_DIRS}
    ${GTKMM_INCLUDE_DIRS}
    ${POCO_INC}
)

add_subdirectory(core)
add_subdirectory(gui)

set(PROJECT_SOURCE_FILES main.cpp MainApp.cpp)
set(PROJECT_BIN ${PROJECT_NAME})

add_executable(${PROJECT_BIN} ${PROJECT_SOURCE_FILES})
target_link_libraries(${PROJECT_BIN} core gui)

if(NOT ${CMAKE_BUILD_TYPE} MATCHES "^[A-Za-z]*Deb[A-Za-z]+$")
    message(STATUS "Build type is '${CMAKE_BUILD_TYPE}'. Binaries WILL BE srtipped.")
    set_target_properties(
        ${PROJECT_BIN} PROPERTIES
        LINK_FLAGS "-s"
    )
elseif(${CMAKE_BUILD_TYPE} MATCHES "^[A-Za-z0-9_]+")
    message(STATUS "Build type is '${CMAKE_BUILD_TYPE}'. Binaries will NOT BE srtipped.")
endif()

# ----- Add custom targets and installation dir for main binary

if (NOT CMAKE_CROSSCOMPILING)
    add_custom_target(
        check
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_BIN}"
        DEPENDS test ${PROJECT_BIN}
        COMMENT "Checking build (UT + executing a binary)"
        VERBATIM
    ) # SOURCES ${test_SRCS})

        add_custom_target(
        test
        DEPENDS ${TEST_DEPS} # created in added subdirs
        COMMENT "Executing Unit Tests"
        VERBATIM
    ) # SOURCES ${test_SRCS})
endif (NOT CMAKE_CROSSCOMPILING)

install(TARGETS ${PROJECT_BIN}
    RUNTIME DESTINATION ${PROJECT_INSTALL_DIR}
)

if(CMAKE_HOST_UNIX)
    install(CODE
        "message(STATUS \"Creating symbolic links...\")
        execute_process(
            COMMAND ln -sf ../${PROJECT_INSTALL_DIR}/${PROJECT_NAME}
            WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin
        )"
    )
endif(CMAKE_HOST_UNIX)

