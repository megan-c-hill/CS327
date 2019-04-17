cmake_minimum_required(VERSION 3.13)
project(CS327)

set(CMAKE_CXX_STANDARD 14)

include_directories(Assignment9)
include_directories(Assignment9/characters)
include_directories(Assignment9/descriptions)
include_directories(Assignment9/distance)

add_executable(CS327
        Assignment9/characters/Character.cpp
        Assignment9/characters/Character.h
        Assignment9/characters/characterHeap.cpp
        Assignment9/characters/characterHeap.h
        Assignment9/descriptions/dice.cpp
        Assignment9/descriptions/dice.h
        Assignment9/descriptions/itemDescription.cpp
        Assignment9/descriptions/itemDescription.h
        Assignment9/descriptions/monsterDescription.cpp
        Assignment9/descriptions/monsterDescription.h
        Assignment9/distance/distance.cpp
        Assignment9/distance/distance.h
        Assignment9/distance/pathFindingHeap.cpp
        Assignment9/distance/pathFindingHeap.h
        Assignment9/dungeon.cpp
        Assignment9/generate-dungeon.cpp
        Assignment9/generate-dungeon.h
        Assignment9/shared-components.cpp
        Assignment9/shared-components.h
        Assignment9/characters/Monster.cpp
        Assignment9/characters/Monster.h
        Assignment9/characters/Object.cpp
        Assignment9/characters/Object.h Assignment9/characters/Player.cpp Assignment9/characters/Player.h)
