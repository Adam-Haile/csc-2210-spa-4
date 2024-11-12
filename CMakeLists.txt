cmake_minimum_required(VERSION 3.29)
project(csc_2210_spa_4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")


include_directories(include)

add_executable(csc_2210_spa_4
        src/GameController.h
        src/Map.h
        src/Room.h
        src/RoomEntity.h
        src/View.h
    src/GameController.cpp
    src/main.cpp
    src/Map.cpp
    src/Room.cpp
    src/RoomEntity.cpp
    src/View.cpp
        src/Player.cpp
        src/Player.h)
