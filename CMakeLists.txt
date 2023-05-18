cmake_minimum_required(VERSION 3.24)
project(polygrinder C)

set(CMAKE_C_STANDARD 11)

include_directories(/opt/homebrew/Cellar/glib/2.76.1/lib/glib-2.0/include)
include_directories(/opt/homebrew/Cellar/glib/2.76.1/include/glib-2.0)
link_directories(/opt/homebrew/Cellar/glib/2.76.1/lib)

add_executable(polygrinder main.c polynomial.c main.h c_improvements.c c_improvements.h)

target_link_libraries(polygrinder glib-2.0)
