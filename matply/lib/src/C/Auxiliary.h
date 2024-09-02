//
// Created by 20281 on 2024/7/6.
//

#ifndef MATPLY_AUXILIARY_H
#define MATPLY_AUXILIARY_H

#ifdef _STDBOOL_H
#else
#include <stdbool.h>
#endif

#ifndef MATPLY_API
    #if defined(_WIN32)
        #define MATPLY_API __declspec(dllexport)
    #else
        #define MATPLY_API __attribute__((visibility("default")))
    #endif
#endif

// 最小（大）值算法，未来会设置mode参数表示算法模式，目前只用简单遍历算法——默认数据无序
MATPLY_API double getMin( double * arr,  int len);
MATPLY_API double getMax( double * arr,  int len);

// @test 快速拷贝一个数组
MATPLY_API void ** copy_array(void ** datas,  int row,  int column);

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

///////////////////////////////////////////////////////////////////////////////////
/// simple--random--module
MATPLY_API void initialize_random_seed();
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
// method参数用来处理权重情况，比如说出现负数权重。默认0时候用原始值，1的时候采用Sigmoid映射概率， 用来处理负数权重，其他整数的时候使用权重的绝对值
MATPLY_API double * perfect_choices(double * arr, double * p, int len, int times, bool back, int method);

///////////////////////////////////////////////////////////////////////////////////
// 释放泛型二级指针
MATPLY_API void freeppvoid(void ** data, int row);

// 生成二维测试数据
MATPLY_API double ** genTestdatas(int row, int column, double (*func)(double, double));

///////////////////////////////////////////////////////////////////////////////////
/// 微积分领域
// 机器精度机器精度
#define EPSILON 1.4901161193847656e-08
/// 中心差分法
double diffCentral(double x, double (*func)(double));


///////////////////////////////////////////////////////////////////////////////////
#endif //MATPLY_AUXILIARY_H
