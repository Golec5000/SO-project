cmake_minimum_required(VERSION 3.28)
project(SoThredsApp)

# Find the ncurses library
find_package(Curses REQUIRED)

include_directories(/usr/include/ncursesw) # dla ncursesw
# lub
include_directories(/usr/include) # dla ncurses

set(CMAKE_CXX_STANDARD 11)

add_executable(SoThredsApp main/main.cpp
        map/MainAppMap.cpp
        map/MainAppMap.h
        threads/mapRender/MapRender.cpp
        threads/mapRender/MapRender.h
        threads/switch/SwitchThread.cpp
        threads/switch/SwitchThread.h
        threads/entity/Person.cpp
        threads/entity/Person.h
        threads/entityGenerator/EntityGenerator.cpp
        threads/entityGenerator/EntityGenerator.h)

## Link your executable with the ncurses library
target_link_libraries(SoThredsApp ${CURSES_LIBRARIES})
