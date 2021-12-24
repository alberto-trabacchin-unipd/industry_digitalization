cmake_minimum_required( VERSION 3.10.2 )

project(PickPlace_lib
        VERSION 0.1
        DESCRIPTION "Monitor library for managing warehouse box put-pull mechanism between
                     mobile robot and cobots."
        )

add_library(PickPlace STATIC src/PickPlace.cpp)

target_include_directories(PickPlace
        PUBLIC include
        )

target_link_libraries(PickPlace
        )

add_library(PSE::PickPlace ALIAS PickPlace)