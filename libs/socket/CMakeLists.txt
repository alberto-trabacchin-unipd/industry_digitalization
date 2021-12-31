cmake_minimum_required( VERSION 3.10.2 )

project(socket_lib
        VERSION 0.1
        DESCRIPTION "Defines a machine vision system."
        )

add_library(Socket STATIC src/Socket.c)

target_include_directories(Socket
        PUBLIC include
        )

target_link_libraries(Socket
        )

add_library(PSE::Socket ALIAS Socket)