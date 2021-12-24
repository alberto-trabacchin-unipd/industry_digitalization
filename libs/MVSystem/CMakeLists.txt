cmake_minimum_required( VERSION 3.10.2 )

project(mvsystem_lib
        VERSION 0.1
        DESCRIPTION "Defines a machine vision system."
        )

add_library(MVSystem STATIC src/MVSystem.cpp)

target_include_directories(MVSystem
        PUBLIC include
        )

target_link_libraries(MVSystem
        )

add_library(PSE::MVSystem ALIAS MVSystem)