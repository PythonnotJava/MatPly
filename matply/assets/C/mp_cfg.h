//
// Created by 25654 on 24-9-20.
//
/// 全局设置
#pragma once

#ifndef MP_CFG_H
#define MP_CFG_H

#ifndef MATPLY_API
    #if defined(_WIN32) || defined(_WIN64)
        #define MATPLY_API __declspec(dllexport)
    #else
        #define MATPLY_API __attribute__((visibility("default")))
    #endif
#endif

#ifndef  _INC_STDLIB
    #define _CRT_RAND_S
    #include <stdlib.h>
    #define __rand_s rand_s;
#endif

#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

extern char * ROUND;
extern double DROUND;

// 设置与获取可视化精度 ROUND
MATPLY_API void set_visible_round( char* new_round);
MATPLY_API char * get_visible_round();

// 设置与获取浮点数误差精度
MATPLY_API void set_round( double number);
MATPLY_API double get_round();

MATPLY_API extern const double PI;
MATPLY_API extern const double e;
MATPLY_API extern const double _nan;
MATPLY_API extern const double inf;
MATPLY_API extern const double euler;

///////////////////////////////////////////////////////////////////////////////////
/// 简易的随机数操作方案
MATPLY_API void initialize_random_seed();
// 设置随机种子
MATPLY_API void setSeed( int seed);
// 实现随机打乱
MATPLY_API void _shuffle(double *arr, int len);
// 随机生成介于0~1之间的数
MATPLY_API double random1();
// 随机生成一个整数
MATPLY_API int randint(double lb, double ub);
// 随机生成一个浮点数
MATPLY_API double randdouble(double lb, double ub);
// 实现random_choice 函数
MATPLY_API double random_choice(double *arr, int len);
// 实现多次random_choice选择，times表示次数，back为false表示无放回抽样。思路：先打乱，然后要几个拿几个
MATPLY_API double * random_choices(double * arr, int len, int times, bool back);
// 根据概率一维数组挑选值。对应系列概率和不一定为1.0，可以是任意数，也就是说，此概率另含有占有权重的意思。
// times表示次数，back为false表示无放回抽样
// method参数用来处理权重情况，比如说出现负数权重。默认 0 时候用原始值，1的时候采用Sigmoid映射概率， 用来处理负数权重，其他整数的时候使用权重的绝对值
MATPLY_API double * perfect_choices(double * arr, double * p, int len, int times, bool back, int method);
///////////////////////////////////////////////////////////////////////////////////

/// 1.10版本开始，Matply强制采用rand_r和rand_s替换rand，也就是说，设置多线程模式来适应omp自动多线程
/// 线程安全随机数
// 设置是否采用线程安全的随机种子
typedef unsigned int (*RandFunc)();
extern unsigned int MAXRAND;
// 返回rand_s（如果返回值是0，否则返回rand），其他系统换成rand_r（报错同样）
extern RandFunc rand_func;

#endif