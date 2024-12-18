//
// Created by 25654 on 24-9-20.
//
/// 矩阵的基础操作

#pragma once

#ifndef MP_BASE_H
#define MP_BASE_H

#include "mp_auxiliary.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// 创建被某个指定值填充的矩阵
MATPLY_API double ** filled( int row,  int column,  double number);

// 0/1 矩阵
MATPLY_API double ** zeros( int row,  int column);
MATPLY_API double ** ones( int row,  int column);

// 获取某行的数组
MATPLY_API double * row_( int row,  int column,  double ** data);

// 获取某列的数组
MATPLY_API double * column_( int row,  int column,  double ** data);

// 获取指定位置
MATPLY_API double at( int row,  int column,  double ** data);

// 生成连续个数后重新布局，从start ~ row*column，间隔为1
MATPLY_API double ** arrange( double start,  int row,  int column);

// 生成连续个数后重新布局，从start ~ end?，期间被分成row * column份，keep为true决定以end结尾，反之
MATPLY_API double ** linspace( double start,  double end,  int row,  int column,  bool keep);

// 深拷贝
MATPLY_API double ** deepcopy( int row,  int column,  double **data);

// 比较模式，对应位置上的数据分别对比
// mode从1~4分别表示：大于、小于、不大于、不小于，其他数表示等于情况
MATPLY_API bool ** compare( int row,  int column,  double **data1,  double ** data2,  int mode);

// 求和。参数dim可以取0、1和其他数，分别表示沿着row、沿着column、整体这三种模式的求和，下同
MATPLY_API double * sum( int row,  int column,  double **data,  int dim);

// 求平均值
MATPLY_API double * mean( int row,  int column,  double **data,  int dim);

// 最小值
MATPLY_API double * min( int row,  int column,  double **data,  int dim);

// 最大值
MATPLY_API double * max( int row,  int column,  double **data,  int dim);

// 内部截取
MATPLY_API double ** cut( int row,  int column,  double ** data,  int prow,  int pcolumn,  int width,  int height);
// 从内部一点开始截取，可以越界，超过部分使用number补全
double ** cutfree( int row,  int column,  double ** data,  int prow,  int pcolumn,  int width,  int height,  double number);

// 合并新的
MATPLY_API double ** concatR( int row,  int column1,  int column2,  double ** data1,  double ** data2);
MATPLY_API double ** concatC( int row1,  int row2,  int column,  double ** data1,  double ** data2);

// 重塑大小——多余的丢掉，缺少的用number补全
// 这个row和column是新尺寸的，别弄混了
MATPLY_API double ** resizeR( int row,  int column,  double ** data,  int origin_row,  int origin_column,  double number);
MATPLY_API double ** resizeC( int row,  int column,  double ** data,  int origin_row,  int origin_column,  double number);

// 重构尺寸，前提是a * b = c * r;
MATPLY_API double ** reshape( int row,  int column,  double ** data,  int origin_column);

// 数学拓展
/*
double acos(double x); mode == 0
double asin(double x);
double atan(double x);
double cos(double x);
double sin(double x);
double tan(double x);
double cosh(double x);
double sinh(double x);
double tanh(double x);
double exp(double x);
double log(double x);
double log10(double x);
double sqrt(double x);
double ceil(double x);
double floor(double x);
double fabs(double x); mode == 15
double degrees(double theta); mode == 16 // 自制，弧度转角度

double pow(double x, double y); 0
double atan2(double y, double x); 1
double frexp(double x, int *exp);  // 不提供
double ldexp(double x, int exp);  // 不提供
double modf(double x, double *iptr);  // 不提供
 */
// 各种数学运算调用——传入1个参数，这么设计泛型是为了节省代码量，同时在一些语言中，如Dart可以轻松使用extension关键字对List拓展
MATPLY_API double ** mathBasement1( int row,  int column,  double ** data,  int mode);
// 各种数学运算调用——传入2个参数，第1个是矩阵的数据，第2个是传入数据
MATPLY_API double ** mathBasement2( int row,  int column,  double ** data,  int mode,  double number);
// 各种数学运算调用——传入2个参数，第2个是矩阵的数据，第1个是传入数据
MATPLY_API double ** mathBasement2reverse( int row,  int column,  double ** data,  int mode,  double number);

// Sigmoid函数
MATPLY_API double ** sigmoid( int row,  int column,  double ** data);

// @extend Softmax函数，归一化指数函数，当数据含有nan或者正负inf任意一种时，可对二者做特殊化处理
MATPLY_API double ** softmax( int row,  int column,  double ** data,  int dim,  double mask_nan,  double mask_inf,  double mask_neginf);

// 排序，reverse为true表示从大到小
MATPLY_API void sortNoReturned( int row,  int column, double ** data,  bool reverse,  int dim,  double mask_nan);
MATPLY_API double ** sort( int row,  int column, double ** data,  bool reverse,  int dim,  double mask_nan);

// 对一个矩阵进行特殊值处理
MATPLY_API void set_mask_nan( int row,  int column, double ** data,  double number);
MATPLY_API void set_mask_inf( int row,  int column, double ** data,  double number,  bool isNegativeInf);

// 最值索引
MATPLY_API int * argmax(int row, int column, double  **data, int dim);
MATPLY_API int * argmin(int row, int column, double  **data, int dim);

// 数组扁平化为1*size（不用reshape实现），mode == 1表示从0列开始并从上到下转换；mode为其他值表示从行开始，从上到下
MATPLY_API double * flatten(int row, int column, double  **data, int mode);

// 指定步长的range
MATPLY_API double ** range(double start, double step, int row, int column);

// 替换不符合条件的值
MATPLY_API double ** replace(int row, int column, double ** data, double number, bool (*condition)(double ));
MATPLY_API void replaceNoReturned(int row, int column, double ** data, double number, bool (*condition)(double ));

// 矩阵切割，to的位置也计入
MATPLY_API double ** sliceR(int column, double ** data, int from, int to);
MATPLY_API double ** sliceC(int row, double ** data, int from, int to);

// 框住范围
MATPLY_API double ** clip(int row, int column, double  **data, double lb, double ub);
MATPLY_API void clipNoReturned(int row, int column, double  **data, double lb, double ub);

// 每个值都满足条件
MATPLY_API bool all(int row, int column, double  ** data, bool (*condition)(double ));
// 任意值满足条件
MATPLY_API bool any(int row, int column, double **data, bool (*condition)(double ));

// 对满足条件的数据计数
MATPLY_API int * counter(int row, int column, double  ** data, int dim, bool (*condition)(double ));

// 自定义两个相邻值的行为，init值是基准值，例如求和可以设置基准从0开始，乘积可以设置基准为1
MATPLY_API double * reduce(int row, int column, double ** data, int dim, double (*condition)(double , double ), double init);

// 获取最小维度下对角线全是1，其他全是0的矩阵
MATPLY_API double ** E_like(int row, int column);

// 反向框住，对于不符合上下限的值，可以根据传入条件设置值，其实就是replace的另一个版本
MATPLY_API double ** clip_reverse(int row, int column, double  **data, double lb, double ub, double (*condition)(double));
MATPLY_API void clip_reverseNoReturned(int row, int column, double  **data, double lb, double ub, double (*condition)(double));

// 在不创多次创建二维数组的前提下，生成一个符合运算的数组
MATPLY_API double ** customize(int row, int column, double ** data, double (*condition)(double ));

// 查询所有符合条件值的索引，每行都查询，其中prediction是预测平均每行有多少符合条件的值
MATPLY_API int ** findIndexs(int row, int column, double **data, bool (*condition)(double ), int prediction);

// 矩阵的旋转，以(0,0)为旋转点
// 顺时针旋转270度的矩阵与逆时针旋转90度
// 逆时针旋转270度的矩阵等同于顺时针旋转90度
// 180顺逆一样
// 0、360都是矩阵的拷贝，这里不实现
MATPLY_API double ** rotate(int row, int column, double ** data, int mode);

// 矩阵的镜像，0表示横向镜像、其他值表示总线镜像
MATPLY_API double ** mirror(int row, int column, double ** data, int mode );

// 去中心化
MATPLY_API double ** decentralizate(int row, int column, double **data, int dim);

// 多拼接，data1是操作发出对象且至少data2不为空
MATPLY_API double ** concatsR(int row,int column1,int column2,int column3,int column4,double ** data1,double ** data2,double ** data3,double ** data4);
MATPLY_API double ** concatsC(int row1,int row2,int row3,int row4,int column,double ** data1,double ** data2,double ** data3,double ** data4);

// 多次任意切分，比如(row, column)形状的数组使用{1, 3, 5}切割表示从0~1、1~3、3~5、5 ~ column切成四份(左闭右开），len是数组长度，mode=true表示横向切
MATPLY_API double *** split(int row, int column, double ** data, int len, int * slices, bool mode);

// 覆盖——两个矩阵重叠的地方会覆盖，data1是被覆盖对象
MATPLY_API double ** cover(int row, int column, double ** data1, int row1, int column1, double ** data2, int rowx, int rowy);

// 矩阵拉伸，方式为重复，hor为true表示横向拉伸，len是拉伸长度
MATPLY_API double ** stretch_repeat(int row, int column, double ** data, int len, bool hor);
// 矩阵拉伸，方式为替换，hor为true表示横向拉伸，len是拉伸长度，number是替换数据
MATPLY_API double ** stretch_replace(int row, int column, double ** data, int len, bool hor, double number);
// 矩阵拉伸，方式为头部延展，hor为true表示横向拉伸，len是拉伸长度
MATPLY_API double ** stretch_head(int row, int column, double ** data, int len, bool hor);
// 矩阵拉伸，方式为尾部延展，hor为true表示横向拉伸，len是拉伸长度
MATPLY_API double ** stretch_end(int row, int column, double ** data, int len, bool hor);
// 矩阵拉伸，方式为镜像延展，hor为true表示横向拉伸，len是拉伸长度
MATPLY_API double ** stretch_mirror(int row, int column, double ** data, int len, bool hor);
// 矩阵拉伸，方式为镜像的镜像，即对前一个轮回镜像再镜像，hor为true表示横向拉伸，len是拉伸长度
MATPLY_API double ** stretch_mirrors(int row, int column, double ** data, int len, bool hor);
// 矩阵拉伸，method表示选用的策略（policies）——重复(0)、替换(1)、头部延展(2)、尾部延展(3)、镜像(4)、镜像的镜像(其他)
MATPLY_API double ** stretch(int row, int column, double ** data, int len, bool hor, double number, int method);

// 在保证传入的是某定义域上的连续函数时，进行中心差分
MATPLY_API double ** diffC(int row, int column, double ** data, double (*func)(double));

// 获取值的上下界
MATPLY_API double ** get_range(int row, int column, double ** data, int dim);

// 累积和
MATPLY_API double ** cumsum(int row, int column, double ** data, int dim, bool flatten);

// 符号函数
MATPLY_API double ** sgn(int row, int column, double ** data);

// 两个矩阵根据操作映射
MATPLY_API double ** confront(int row, int column, double ** data1, double ** data2, double (*func)(double, double));

#endif //MP_BASE_H
