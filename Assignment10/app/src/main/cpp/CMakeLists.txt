cmake_minimum_required(VERSION 3.4.1)

add_library(hello-jni SHARED
            hello-jni.c
        generate-dungeon.cpp
        generate-dungeon.h
        shared-components.cpp
        shared-components.h
#        characters/Character.cpp
#        characters/Character.h
#        characters/Monster.cpp
#        characters/Player.cpp
#        characters/characterHeap.cpp
#        characters/Monster.h
#        characters/Player.h
#        characters/characterHeap.h
        )

# Include libraries needed for hello-jni lib
target_link_libraries(hello-jni
                      android
                      log)
