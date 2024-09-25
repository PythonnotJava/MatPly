//
// Created by 25654 on 24-9-20.
//
#pragma once

#ifndef MP_GEOMETRY_H
#define MP_GEOMETRY_H

#ifndef MATPLY_API
    #if defined(_WIN32) || defined(_WIN64)
        #define MATPLY_API __declspec(dllexport)
    #else
        #define MATPLY_API __attribute__((visibility("default")))
    #endif
#endif

#ifdef MP_POINT2D_H
#else
    #include "mp_point2d.h"
#endif

#ifdef _STDBOOL_H
#else
    #include <stdbool.h>
#endif

// 生成符合椭圆边际的数据——我们规定，size表示每个生成数据数量，size >= 50，a是长轴，b是短轴，最后生成的是size * 2的形状，每行代表一个点
MATPLY_API double ** ellipse_edge(int size, double a, double b, int seed, bool use, double bias);
// 生成组成椭圆区域的数据
MATPLY_API double ** ellipse_area(int size, double a, double b, int seed, bool use, double bias);
// 圆形
MATPLY_API double ** circle_edge(int size, double r, int seed, bool use, double bias);
// 生成组成椭圆区域的数据
MATPLY_API double ** circle_area(int size, double r, int seed, bool use, double bias);
// 直线
MATPLY_API double ** line(int size, Point2D start, Point2D end, int seed, bool use, double bias);
// 三角形边缘
MATPLY_API double ** triangle_edge(int size, Point2D a, Point2D b, Point2D c, int seed, bool use, double bias);
// 三角形区域
MATPLY_API double ** triangle_area(int size, Point2D a, Point2D b, Point2D c, int seed, bool use, double bias);
// 四边形边缘与区域（可以是内凹，也可以是外凸）
MATPLY_API double ** quadrilateral_edge(int size, Point2D a, Point2D b, Point2D c, Point2D d, int seed, bool use, double bias);
MATPLY_API double ** quadrilateral_area(int size, Point2D a, Point2D b, Point2D c, Point2D d, int seed, bool use, double bias);
// 心形线，默认是正向的，旋转请采用旋转变换矩阵自行操作，x是中心对称轴位置
MATPLY_API double ** heart_edge(int size, double x, int seed, bool use, double bias);
MATPLY_API double ** heart_area(int size, double x, int seed, bool use, double bias);
// 曲线生成，x1是起点坐标，x2是终点坐标
MATPLY_API double ** curve(int size, double x1, double x2, double (*func)(double), int seed, bool use, double bias);
// 贝塞尔曲线，start和end分别是起点和终点，ctrl是控制点
MATPLY_API double ** bezier(int size, Point2D start, Point2D end, Point2D ctrl, int seed, bool use, double bias);
// 高定义度的曲线，当面临螺线、摆线等等等复杂曲线的时候
// 参数：数量、函数指针——用于生成每个点的 x 和 y 坐标、曲线所需多个参数的结构体的指针、曲线生成的起始角度——通常设为 0.0、每步增加的角度——控制曲线的细腻程度和总长度
typedef double (*coord_func)(double theta, void * params);
MATPLY_API double ** custom_curve(int size, coord_func x_func, coord_func y_func, void * params, double theta_start, double theta_step, int seed, bool use, double bias);
// 基于均匀分布的数据偏移
MATPLY_API void shake(int row, int column, double ** data, int seed, bool use, double bias);

#endif //MP_GEOMETRY_H
