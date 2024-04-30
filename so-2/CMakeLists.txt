cmake_minimum_required(VERSION 3.28)
project(so_2)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(so_2 main.cpp
        helpClasses/People.cpp
        helpClasses/People.h)

target_link_libraries(so_2 ${CURSES_LIBRARIES})