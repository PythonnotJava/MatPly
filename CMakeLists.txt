cmake_minimum_required(VERSION 3.25)
project(MatPly)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(MatPly
        Auxiliary.c
        Auxiliary.h
        main.c
        MatBox.c
        MatBox.h
)
