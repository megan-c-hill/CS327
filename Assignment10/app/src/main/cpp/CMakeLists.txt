cmake_minimum_required(VERSION 3.4.1)

add_library(hello-jni SHARED
        hello-jni.cpp
        generate-dungeon.cpp
        generate-dungeon.h
        shared-components.cpp
        shared-components.h
        characters/Character.cpp
        characters/Character.h
        descriptions/monsterDescription.cpp
        descriptions/monsterDescription.h
        descriptions/itemDescription.cpp
        descriptions/itemDescription.h
        descriptions/dice.cpp
        descriptions/dice.h
        characters/Player.cpp
        characters/Player.h
        characters/Object.cpp
        characters/Object.h
        characters/characterHeap.cpp
        characters/characterHeap.h
        characters/Monster.cpp
        characters/Monster.h
        descriptions/monsterDescriptionFile.cpp
        descriptions/monsterDescriptionFile.h
        descriptions/itemDescriptionFile.h
        descriptions/itemDescriptionFile.cpp
        distance/distance.h
        distance/distance.cpp
        distance/pathFindingHeap.cpp
        distance/pathFindingHeap.h
        )

# Include libraries needed for hello-jni lib
target_link_libraries(hello-jni
                      android
                      log)
