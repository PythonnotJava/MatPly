cmake_minimum_required(VERSION 3.25)
project(MatPly_Dart)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(MatPly
        Auxiliary.c
        Auxiliary.h
        main.c
        matply.c
        matply.h
        vector_extend.c
        vector_extend.h
)
