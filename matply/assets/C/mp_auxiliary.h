//
// Created by 25654 on 24-9-20.
//
#pragma once

#ifndef MP_AUXILIARY_H
#define MP_AUXILIARY_H

#include "mp_omp.h"
#include "mp_cfg.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// 最小（大）值算法，未来会设置mode参数表示算法模式，目前只用简单遍历算法——默认数据无序
MATPLY_API double getMin( double * arr,  int len);
MATPLY_API double getMax( double * arr,  int len);

// @test 快速拷贝一个数组
MATPLY_API void ** copy_array(void ** datas, int row,  int column);

// 获取一个开辟内存但是未分配数据的二维浮点数数组
MATPLY_API double ** allocateButNoNumbers( int row,  int column);

// 对一个一维数组转成二维数组
MATPLY_API double ** oneTotwoArray( double * array,  int row,  int column);

// 插入排序
MATPLY_API void insertSorted(double * arr, int len, double value);

// 顺序查找一维数组中第一个出现的值，没有返回-1。reverse为true表示从后往前查询，但是这样获取的是从后往前第一个匹配数据（如果有）
MATPLY_API int find_seq(double * arr, int len, double target, bool reverse);

// 二分查找
MATPLY_API int find_bin(double * arr, int len, double target);

// 顺序查找算法，返回一个索引数组，数组第一个数是长度，由于面向矩阵，不同行索引起点不同，故添加 baseIndex参数
MATPLY_API int * findall(double * arr, int len, double target, int init, int baseIndex);
MATPLY_API int * findall_condition(double * arr, int len, int init, bool (*condition)(double ), int baseIndex);

// 释放泛型二级指针
MATPLY_API void freeppvoid(void ** data, int row);

// 生成二维测试数据
MATPLY_API double ** genTestdatas(int row, int column, double (*func)(double, double));

///////////////////////////////////////////////////////////////////////////////////
/// 微积分领域
// 机器精度机器精度
#define EPSILON 1.4901161193847656e-08
/// 中心差分法，借鉴gsl2.8 的中心差分方法
MATPLY_API double diffCentral(double x, double (*func)(double));
///////////////////////////////////////////////////////////////////////////////////

// 释放泛型一级指针
MATPLY_API void freeOp(void * data);

/// 测试
// 快速生成数据
MATPLY_API double ** testArray( int row,  int column);
// 单线程回调测试
MATPLY_API double ** testSingleT(int row, int column, double (*func)(int, int));
// Openmp多线程解析到别的语言的测试
MATPLY_API void testOmpCanRun(int row, int column, double ** data, void (*func)(int, int, double ** data));
// 测试多线程下的随机生成，以均匀分布为例
MATPLY_API double ** testOmpUniform(int row, int column);

// 申请二维布尔值数组
bool ** allocateTDABools(int row, int column);

// 快速测试链接到
MATPLY_API double testOut();

// 申请一维数组内存，mode 为 0、1、其他 分别表示 申请浮点类、整型类、布尔类
MATPLY_API void * allocateOp(int len, int mode);

#endif //MP_AUXILIARY_H
