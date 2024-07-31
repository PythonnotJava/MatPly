//
// Created by 20281 on 2024/7/6.
//

#ifndef MATPLY_AUXILIARY_H
#define MATPLY_AUXILIARY_H

#ifdef _STDBOOL_H
#else
#include <stdbool.h>
#endif

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

// 顺序查找一维数组中第一个出现的值，没有返回-1。reverse为true表示从后往前查询，但是这样获取的是从后往前第一个匹配数据（如果有）
int find_seq(double * arr, int len, double target, bool reverse);

// 二分查找
int find_bin(double * arr, int len, double target);

// 顺序查找算法，返回一个索引数组，数组第一个数是长度，由于面向矩阵，不同行索引起点不同，故添加 baseIndex参数
int * findall(double * arr, int len, double target, int init, int baseIndex);
int * findall_condition(double * arr, int len, int init, bool (*condition)(double ), int baseIndex);

// 释放泛型二级指针
void freeppvoid(void ** data, int row);
#endif //MATPLY_AUXILIARY_H
