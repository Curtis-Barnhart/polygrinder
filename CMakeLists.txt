cmake_minimum_required(VERSION 3.24)
project(polygrinder C)

set(CMAKE_C_STANDARD 11)

include_directories(/opt/homebrew/Cellar/glib/2.76.3/include/glib-2.0)
include_directories(/opt/homebrew/Cellar/glib/2.76.3/lib/glib-2.0/include)
include_directories(/opt/homebrew/opt/gettext/include)
include_directories(/opt/homebrew/Cellar/pcre2/10.42/include)


link_directories(/opt/homebrew/Cellar/glib/2.76.3/lib)
link_directories(/opt/homebrew/opt/gettext/lib)

add_executable(polygrinder main.c poly/polynomial.c main.h util/double_tracker.c util/double_tracker.h poly/polyprint.c poly/polyprint.h util/my_math.c util/my_math.h)

target_link_libraries(polygrinder glib-2.0)
target_link_libraries(polygrinder intl)
