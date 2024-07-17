//
// Created by 20281 on 2024/7/6.
//

#ifndef MATPLY_AUXILIARY_H
#define MATPLY_AUXILIARY_H

// 最小（大）值算法，未来会设置mode参数表示算法模式，目前只用简单遍历算法——默认数据无序
double getMin( double * arr,  int len);
double getMax( double * arr,  int len);

// @test 快速拷贝一个数组
void ** copy_array(void ** datas,  int row,  int column);

// 获取一个开辟内存但是未分配数据的二维浮点数数组
double ** allocateButNoNumbers( int row,  int column);

// 对一个一维数组转成二维数组
double ** oneTotwoArray( double * array,  int row,  int column);

// 插入排序
void insertSorted(double * arr, int len, double value);
#endif //MATPLY_AUXILIARY_H
