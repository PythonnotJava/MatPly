//
// Created by 20281 on 24-9-20.
//

#pragma once

#ifndef MP_POINT2D_H
#define MP_POINT2D_H

#include "mp_auxiliary.h"
#include <math.h>

// 二维点的实现
typedef struct Point2D{
    double x;
    double y;
} Point2D;

// 两点的欧氏距离
MATPLY_API double getEuclideanDistance(Point2D point1, Point2D point2);
// 点到原点的距离
MATPLY_API double getOriginalDistance(Point2D point);
// 生成Point2D
MATPLY_API Point2D xytoPoint2D(double x, double y);


#endif //MP_POINT2D_H
