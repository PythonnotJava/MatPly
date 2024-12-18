cmake_minimum_required(VERSION 3.28)
project(matply C)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)

# 启用 OpenMP
find_package(OpenMP REQUIRED)

# 包含头文件目录
include_directories(.)

# 添加可执行文件
add_executable(matply
        matply.c
        matply.h
        mp_omp.c
        mp_omp.h
        mp_random.c
        mp_random.h
        mp_linalg.c
        mp_linalg.h
        mp_point2d.c
        mp_point2d.h
        mp_manage.c
        mp_manage.h
        mp_cfg.c
        mp_cfg.h
        mp_base.c
        mp_base.h
        mp_auxiliary.c
        mp_auxiliary.h
        mp_geometry.c
        mp_geometry.h
        cpp_extension.cpp
        cpp_extension.h
)

# 链接 OpenMP
if(OpenMP_C_FOUND)
    target_link_libraries(matply PUBLIC OpenMP::OpenMP_C)
endif()
