//
// Created by 20281 on 24-9-20.
//
/// 矩阵类统一的内存管理器
#pragma once

#ifndef MP_MANAGE_H
#define MP_MANAGE_H

#include "mp_omp.h"
#include "mp_cfg.h"
#include "mp_auxiliary.h"

#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
#else
   #include <stdint.h>
#endif

// 矩阵是否为特殊矩阵
typedef struct SpecialAttributes{
    bool identityMatrix;  // 单位矩阵
    bool principalDiagonalMatrix; // 主对角矩阵
    bool subDiagonalMatrix; // 副对角矩阵
    bool upperTriangularMatrix; // 上三角矩阵
    bool lowerTriangularMatrix; // 下三角矩阵
    bool singularMatrix; // 奇异矩阵
} Spc;

///////////////////////////////////////////////////////////////////////////////
/// 矩阵包装
// 矩阵本身
typedef struct Matrix{
    int row;  // 行
    int column;  // 列
    Spc * spc;  // 特殊性质
    double ** data;  // 值
} Matrix;

MATPLY_API void visible_data(double**matrix,  int row,  int column);

// 创建所有矩阵都拥有的步骤
MATPLY_API Matrix * __new__( int row,  int column);

// 创建带有数据的矩阵，顺便可以指定特殊属性，如果知道
MATPLY_API Matrix * __init__( int row,  int column,  double** data,  Spc * spc);

// 创建指定地址数据的矩阵，顺便可以指定特殊属性，如果知道
MATPLY_API Matrix * __init__point__data__( int row,  int column, double ** data,  Spc * spc);

// 可视化矩阵
MATPLY_API void VisibleMatrix( Matrix * matrix);

// 释放二维数组
MATPLY_API void __delete__data__(double ** data,  int row);
// 销毁矩阵
MATPLY_API void __delete__(Matrix * matrix);

// 打印矩阵有哪些特殊属性
MATPLY_API void VisibleMatrixSpc( Matrix * matrix);

// 判断是不是方阵
MATPLY_API bool isSquare( Matrix * matrix);

// 判断数据是不是一样
MATPLY_API bool data_isSame( int row,  int column,  double ** data1,  double ** data2);

// 判断属性是不是一样
MATPLY_API bool spc_isSame( Spc * spc1, Spc * spc2);
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// 矩阵管理器
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

static MemoryPool __Mp = (MemoryPool){0, NULL, NULL};

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
///////////////////////////////////////////////////////////////////////////////

#endif //MP_MANAGE_H
