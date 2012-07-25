cmake_minimum_required(VERSION 2.6)
project(ciobserver_exe)

add_subdirectory(core)

set(ciobserver_source_files main.cpp)
add_executable(ciobserver ${ciobserver_source_files})
