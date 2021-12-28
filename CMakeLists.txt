cmake_minimum_required( VERSION 3.10.2 )

project( industry_digitalization
         VERSION 0.1
         DESCRIPTION "Industry digitalization simulation for packaging systems using cobots and machine vision."
         )

if (MSVC)
        # warning level 4 and all warnings as errors
        add_compile_options(/W4 /WX)
else()
        # lots of warnings and all warnings as errors
        add_compile_options(-Wall -g -Wextra -pedantic)
endif()

set(TARGET_GROUP production CACHE STRING "Group to build")


#Include below libraries you want to implement

add_subdirectory(libs/Box)
add_subdirectory(libs/Item)
add_subdirectory(libs/Monitor)
add_subdirectory(libs/data_mng)
#add_subdirectory(libs/socket)



if(TARGET_GROUP STREQUAL production)
        add_subdirectory(app)
else()
        message(FATAL_ERROR "Given TARGET_GROUP unknown")
endif()