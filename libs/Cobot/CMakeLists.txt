cmake_minimum_required( VERSION 3.10.2 )

project(Cobot_lib
        VERSION 0.1
        DESCRIPTION "Class library which contains thread methods for simulating
                     cobots."
        )

add_library(Cobot STATIC src/Cobot.cpp)

target_include_directories(Cobot
        PUBLIC include
        )

target_link_libraries(Cobot
        PUBLIC PSE::RW
        )

add_library(PSE::Cobot ALIAS Cobot)