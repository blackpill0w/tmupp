cmake_minimum_required(VERSION 3.14)
project(tmupp CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#string(CONCAT CMAKE_CXX_FLAGS
#  "${CMAKE_CXX_FLAGS}"
#  " -static -Wall -Wextra"
#  " -Wfloat-conversion -Wsign-conversion"
#  " -Wshadow -Wduplicated-cond"
#  " -Wduplicated-branches -Wlogical-op"
#  " -Wnull-dereference -Wuseless-cast"
#  " -Wformat=2 -Wformat-security")

set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING OFF)

include_directories("deps/miniaudio")


add_subdirectory("deps/Midx")

add_subdirectory("deps/FTXUI")
include_directories("deps/FTXUI/include")

add_executable(tmupp
  src/main.cpp
  src/miniaudio.cpp)

target_link_libraries(tmupp
  Midx
  ftxui::screen
  ftxui::component
  ftxui::dom)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
