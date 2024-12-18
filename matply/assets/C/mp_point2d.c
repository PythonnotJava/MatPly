//
// Created by 20281 on 24-9-20.
//

#include "mp_point2d.h"

double getEuclideanDistance(Point2D point1, Point2D point2){
    return sqrt(pow(point1.x - point2.x, 2.0) + pow(point1.y - point2.y, 2.0));
}

double getOriginalDistance(Point2D point) {
    return sqrt(pow(point.x, 2.0) + pow(point.y, 2.0));
}

Point2D xytoPoint2D(double x, double y) {
    return (Point2D){x, y};
}