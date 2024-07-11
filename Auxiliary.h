//
// Created by 20281 on 2024/7/6.
//

#ifndef MATPLY_AUXILIARY_H
#define MATPLY_AUXILIARY_H

// 最小（大）值算法，未来会设置mode参数表示算法模式，目前只用简单遍历算法——默认数据无序
double getMin(const double * arr, const int len);
double getMax(const double * arr, const int len);

// @test 快速拷贝一个数组
void ** copy_array(void ** datas, const int row, const int column);

// 获取一个开辟内存但是未分配数据的二维浮点数数组
double ** allocateButNoNumbers(const int row, const int column);

#endif //MATPLY_AUXILIARY_H
