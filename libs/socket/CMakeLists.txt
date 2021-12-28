cmake_minimum_required( VERSION 3.10.2 )

project(socket_lib
        VERSION 0.1
        DESCRIPTION "Defines a machine vision system."
        )

add_library(Client STATIC src/Client.cpp)

target_include_directories(Client
        PUBLIC include
        )

target_link_libraries(Client
        )

add_library(PSE::Client ALIAS Client)