cmake_minimum_required( VERSION 3.10.2 )

project(MobileRobot_lib
        VERSION 0.1
        DESCRIPTION "Class library which contains thread methods for simulating
                     mobile robot."
        )

add_library(MobileRobot STATIC src/MobileRobot.cpp)

target_include_directories(MobileRobot
        PUBLIC include
        )

target_link_libraries(MobileRobot
        PUBLIC PSE::PickPlace
        PUBLIC PSE::Box
        )

add_library(PSE::MobileRobot ALIAS MobileRobot)