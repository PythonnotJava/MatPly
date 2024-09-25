//
// Created by 20281 on 24-9-20.
//
#pragma once

#ifndef MP_LINALG_H
#define MP_LINALG_H

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

typedef struct MultiDatas2 {
    double ** data1;
    double ** data2;
} MultiDatas2;

typedef struct MultiDatas3 {
    double ** data1;
    double ** data2;
    double ** data3;
} MultiDatas3;

typedef struct MultiDatas4 {
    double ** data1;
    double ** data2;
    double ** data3;
    double ** data4;
} MultiDatas4;

// 获取对应的转置矩阵
MATPLY_API double ** transpose( int row,  int column,  double ** data);

// 初等行变换：行交换、行扩大（允许0倍）、一行加倍数另一行（把size * row2 加到row1)
MATPLY_API void exchangeR( int column, double ** data,  int row1,  int row2);
MATPLY_API void multiplyR( int row,  int column, double **data,  double size);
MATPLY_API void addR( int column, double **data,  int row1,  int row2,  double size);

// 初等列变换：类似上面
MATPLY_API void exchangeC( int row, double ** data,  int column1,  int column2);
MATPLY_API void multiplyC( int row,  int column, double **data,  double size);
MATPLY_API void addC( int row, double **data,  int column1,  int column2,  double size);

// 矩阵加法
// 1.整体加某个数——创建新对象
MATPLY_API double ** addNumber( int row,  int column,  double **data,  double number);
// 2.矩阵相加——创建新对象
MATPLY_API double ** addMatrix( int row,  int column,  double **data1,  double **data2);
// 3.整体加某个数——自操作
MATPLY_API void addNumberNoReturned( int row,  int column, double **data,  double number);
// 4.矩阵相加——自操作，修改matrix1，下同
MATPLY_API void addMatrixNoReturned( int row,  int column, double **data1,  double **data2);
// 对应的减法
MATPLY_API double ** minusMatrix( int row,  int column,  double **data1,  double **data2);
MATPLY_API void minusMatrixNoReturned( int row,  int column, double **data1,  double **data2);

// 矩阵乘法
// 1.左行右列做内积
MATPLY_API double ** matmul( int row,  int column,  double **data1,  double **data2, int column2);
// 2.哈达马积
MATPLY_API void multiplyMatrixNoReturned( int row,  int column, double **data1,  double **data2);
double ** multiplyMatrix( int row,  int column,  double **data1,  double **data2);
// 3.数值倍乘
MATPLY_API void multiplyNumberNoReturned( int row,  int column, double **data,  double number);
MATPLY_API double ** multiplyNumber( int row,  int column,  double **data,  double number);
// 4.克罗内克积
MATPLY_API double ** kronecker( int row1,  int column1,  double **data1,  int row2,  int column2,  double **data2);
// 矩阵除法
MATPLY_API double ** divide( int row,  int column,  double **data,  double number);
MATPLY_API void divideNoReturned( int row,  int column, double **data,  double number);

// 矩阵求迹，像众多科学计算库一样，只考虑最小维度
MATPLY_API double trace( int row,  int column,  double **data);

// 行列式值，前提是方阵
MATPLY_API double det( int row,  int column,  double **data);

// 获取一个n阶单位矩阵
MATPLY_API double ** E( int n);

// 余子式组成的矩阵
MATPLY_API double ** cofactor( int row,  int column,  double ** data,  int prow,  int pcolumn);

// 伴随矩阵。m * adj(m) = det(m) * E;任意方阵都有伴随矩阵
MATPLY_API double ** adjugate( int row,  int column,  double ** data);

// 逆矩阵（非奇异矩阵），前提是行列式值不能为0，默认可逆，在目标语言中判断，同上面很多的范围判断，都在目标语言，因为C没有较好的报错机制
MATPLY_API double ** inverse( int row,  int column,  double ** data, double det);

// 得到化最简阶梯型矩阵
MATPLY_API double ** rref( int row,  int column,  double ** data);

// 矩阵的秩
MATPLY_API int rank( int row,  int column,  double ** data);

// 矩阵范数
// n == -2表示负无穷范数，即矩阵每行绝对值元素求和取最小
MATPLY_API double norm_negainf(int row, int column, double ** data);
// n == -1表示正无穷范数，即矩阵每行绝对值元素求和取最大
MATPLY_API double norm_inf(int row, int column, double ** data);
// n == 0获取0范数，也是获取数据的稀疏度。数据会与定义的浮点误差比较，而不是直接与0比较，k范数时（k == 0 or k >= 2），程序灵活些，加个dim参数
MATPLY_API double * norm_zero(int row, int column, double ** data, int dim);
// n == 1矩阵的1范数，矩阵每列绝对值元素求和取最大
MATPLY_API double norm_one(int row, int column, double ** data);
MATPLY_API double * norm(int row, int column, double ** data, int n, int dim);

// qr分解
MATPLY_API MultiDatas2 qr(int row, int column, double ** data);

// 反向除法，而不是借助-1次幂
MATPLY_API double ** divrev(int row, int column, double **data, double number);

// 获取关于对角线对称的随机数矩阵，sub为true表示副对角线对称（其实row == column)
MATPLY_API double ** diagonal(int row, int column, double start, double end, bool sub, int seed, bool use);

// 使得矩阵最小维度下主对角线的值全部替换为某个数值
MATPLY_API void fill_diagonal(int row, int column, double ** data, double number);

// 缩放处理，method代表采用的算法，从0、1、2、其他整数分别表示：邻近插值、双线性插值、双三次插值、高斯模糊
// newRow, newColumn是新尺寸，不会写，等待有缘人实现
// MATPLY_API double ** zoom(int row, int column, double ** data, int method, int newRow, int newColumn, int kernel, double sigma);

#endif //MP_LINALG_H
