cmake_minimum_required( VERSION 3.10.2 )

project(Box_lib
        VERSION 0.1
        DESCRIPTION "Class library for designing the Box object, which contains different items."
        )

add_library(Box STATIC src/Box.cpp)

target_include_directories(Box
        PUBLIC include
        )

target_link_libraries(Box
        )

add_library(PSE::Box ALIAS Box)