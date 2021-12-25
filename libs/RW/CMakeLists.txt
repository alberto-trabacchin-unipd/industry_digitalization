cmake_minimum_required( VERSION 3.10.2 )

project(RW_lib
        VERSION 0.1
        DESCRIPTION "Library for managing reader-writer mechanism between
                     machine vision systems and associated cobots."
        )

add_library(RW STATIC src/RW.cpp)

target_include_directories(RW
        PUBLIC include
        )

target_link_libraries(RW
        PUBLIC PSE::Item
        )

add_library(PSE::RW ALIAS RW)