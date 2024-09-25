//
// Created by 20281 on 24-9-20.
//
/// Matrix的定义、创建销毁、信息
#pragma once

#ifndef MP_MATRIX_H
#define MP_MATRIX_H

#ifndef MATPLY_API
    #if defined(_WIN32) || defined(_WIN64)
        #define MATPLY_API __declspec(dllexport)
    #else
        #define MATPLY_API __attribute__((visibility("default")))
    #endif
#endif

#ifdef _STDBOOL_H
#else
    #include <stdbool.h>
#endif

#ifdef _INC_STDIO
#else
    #include <stdio.h>
#endif

#ifdef _INC_STDLIB
#else
    #include <stdlib.h>
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

// 矩阵本身
typedef struct Matrix{
    int row;  // 行
    int column;  // 列
    Spc * spc;  // 特殊性质
    double ** data;  // 值
} Matrix;

MATPLY_API void visible_data( double**matrix,  int row,  int column);

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
MATPLY_API bool spc_isSame( Spc * spc1,  Spc * spc2);

#endif //MP_MATRIX_H

