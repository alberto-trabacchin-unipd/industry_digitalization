cmake_minimum_required( VERSION 3.10.2 )

project(monitor_lib
        VERSION 0.1
        DESCRIPTION "Defines a machine vision system."
        )

add_library(Monitor STATIC src/Monitor.cpp)

target_include_directories(Monitor
        PUBLIC include
        )

target_link_libraries(Monitor
        PUBLIC PSE::Item
        PUBLIC PSE::Box
        )

add_library(PSE::Monitor ALIAS Monitor)