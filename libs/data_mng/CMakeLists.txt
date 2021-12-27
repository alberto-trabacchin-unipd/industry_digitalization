cmake_minimum_required( VERSION 3.10.2 )

project(data_mng_lib
        VERSION 0.1
        DESCRIPTION "Class library which contains information of warehouse general item."
        )

add_library(data_mng STATIC src/data_mng.cpp)

target_include_directories(data_mng
        PUBLIC include
        )

target_link_libraries(data_mng
        PUBLIC PSE::Item
        )

add_library(PSE::data_mng ALIAS data_mng)
