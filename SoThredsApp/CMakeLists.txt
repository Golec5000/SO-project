cmake_minimum_required(VERSION 3.28)
project(SoThredsApp)

set(CMAKE_CXX_STANDARD 11)

add_executable(SoThredsApp main/main.cpp
        map/MaInAppMap.cpp
        map/MaInAppMap.h
        threads/mapRender/MapRender.cpp
        threads/mapRender/MapRender.h)
