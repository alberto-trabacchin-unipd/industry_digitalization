cmake_minimum_required( VERSION 3.10.2 )

project(Item_lib
        VERSION 0.1
        DESCRIPTION "Class library which contains information of warehouse general item."
        )

add_library(Item STATIC src/Item.cpp)

target_include_directories(Item
        PUBLIC include
        )

target_link_libraries(Item
        )

add_library(PSE::Item ALIAS Item)
