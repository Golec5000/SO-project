cmake_minimum_required(VERSION 3.28)
project(SoThredsApp)

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
