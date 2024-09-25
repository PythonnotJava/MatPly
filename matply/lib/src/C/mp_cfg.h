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

#ifdef _STDBOOL_H
#else
    #include <stdbool.h>
#endif

extern char * ROUND;
extern double DROUND;

// 设置与获取可视化精度 ROUND
MATPLY_API extern void set_visible_round( char* new_round);
MATPLY_API extern char * get_visible_round();

// 设置与获取浮点数误差精度
MATPLY_API extern void set_round( double number);
MATPLY_API extern double get_round();

MATPLY_API extern const double PI;
MATPLY_API extern const double e;
MATPLY_API extern const double _nan;
MATPLY_API extern const double inf;
MATPLY_API extern const double euler;

// 设置随机种子
MATPLY_API void setSeed( int seed);

// 设置是否采用线程安全的随机种子
typedef unsigned int (*RandFunc)();
extern bool use_mult_rand;
extern unsigned int MAXRAND;
MATPLY_API void set_mult_rand(bool use);
MATPLY_API bool get_mult_rand();
// 根据系统和use_mult_rand设置使用哪种模式
// 单线程返回rand，多线程返回rand_s（如果返回值是0，否则返回rand），其他系统换成rand_r（报错同样）
extern RandFunc rand_func;


#endif