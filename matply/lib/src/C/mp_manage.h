//
// Created by 20281 on 24-9-20.
//
/// 矩阵类统一的内存管理器
#pragma once

#ifndef MP_MANAGE_H
#define MP_MANAGE_H

#ifndef MATPLY_API
    #if defined(_WIN32) || defined(_WIN64)
        #define MATPLY_API __declspec(dllexport)
    #else
        #define MATPLY_API __attribute__((visibility("default")))
    #endif
#endif

#ifdef MP_MATRIX_H
#else
    #include "mp_matrix.h"
#endif

#ifdef _INC_STDIO
#else
    #include <stdio.h>
#endif

struct MatrixLinked
{
    struct MatrixLinked * next;
    Matrix * matrix;
};

typedef struct MatrixLinked MatrixLinked;

typedef struct MemoryPool
{
    int instances;  // 存储实例个数
    MatrixLinked * head;
    MatrixLinked * tail;
} MemoryPool;

static struct MemoryPool __Mp = (MemoryPool){0, NULL, NULL};

// 添加到内存池
// 选择性初始化，matrix可以为空，只是为了更好的提示矩阵操作的开始；另外，内存池真的为空的话，则可以把非空的matrix设置为第一个
// 头节点包含第一个实例、尾节点不包含最后一个实例而作为最后一个节点
MATPLY_API void initMp(Matrix * matrix);
// 尾部添加
MATPLY_API void addToMp(Matrix * matrix);
// 释放——是否可视化地址、可视化地址是否输出为十六进制地址（false为十进制）。另外，可视化地址不设为矩阵的，而是节点的
MATPLY_API void freeMp(bool visible, bool hex);
MATPLY_API int getInstances();

#define Signal(m) addToMp(m);

#endif //MP_MANAGE_H
