//
// Created by 20281 on 24-9-20.
//
#pragma once

#ifndef MP_RANDOM_H
#define MP_RANDOM_H

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

// 随机打乱
MATPLY_API void shuffle(  int row,  int column, double ** data, int seed, bool use);

// 均匀分，如果未来实现了写了向量类，可能还会修改，一般生成是一个向量
MATPLY_API double ** uniform( int row,  int column,  double start,  double end,  int seed,  bool use);

// 正态分布，基于Box-Muller变换
MATPLY_API double ** normal( int row,  int column,  double mu,  double sigma,  int seed,  bool use );

// 泊松分布
MATPLY_API double ** poisson( int row,  int column,  double lambda,  int seed,  bool use);

// @ignore 数学期望不需要实现，因为数学期望是随机变量 * 概率，可以使用哈达玛积表示
// 方差，如果声明sample则表示样本方差；标准差开根号就行
MATPLY_API double * variance(int row, int column, double ** data, bool sample, int dim, bool std);

// 中位数
MATPLY_API double * median(int row, int column, double ** data, int dim);

// 数据归一化
// 分别是线性归一化、均值归一化、标准化
MATPLY_API double ** normalization1(int row, int column, double  **data, int dim);
MATPLY_API double ** normalization2(int row, int column, double  **data, int dim);
MATPLY_API double ** normalization3(int row, int column, double  **data, int dim);

// 协方差
MATPLY_API double * covariance(int row, int column, double ** data1, double ** data2, bool sample, int dim);
// 一个矩阵的协方差矩阵计算。视为：每一列是一个样本，每一行就是一个随机变量（特征）
MATPLY_API double ** cov1(int row, int column, double ** data, bool sample);
// 两个矩阵的协方差矩阵计算，以行为特征。
MATPLY_API double ** cov2(int row, int column, double ** data1, double ** data2, bool sample);
// 皮尔逊相关系数
MATPLY_API double * pearsonCoef(int row, int column, double ** data1, double ** data2, bool sample, int dim);

// 均方误差, rmse为true表示均方根误差
MATPLY_API double * MSE(int row, int column, double ** data1, double ** data2, int dim, bool rmse);

// 平均绝对误差
MATPLY_API double * MAE(int row, int column, double ** data1, double ** data2, int dim);

// 平均绝对百分比误差
// 当真实值有数据等于0时，存在分母0除问题，该公式不可用！
MATPLY_API double * MAPE(int row, int column, double ** pre, double ** rea, int dim);

// 决定系数
MATPLY_API double * R2(int row, int column, double ** pre, double ** rea, int dim);

// 对称平均绝对百分比误差
// 当真实值有数据等于0，而预测值也等于0时，存在分母0除问题，该公式不可用！
MATPLY_API double * SMAPE(int row, int column, double ** data1, double ** data2, int dim);

// 在行方向上，根据概率一维数组挑选值。对应系列概率和不一定为1.0，可以是任意数，也就是说，此概率另含有占有权重的意思
MATPLY_API double ** choice1(int row, int column, double ** data, double ** p, int times, bool back, int method);
MATPLY_API double ** choice2(int row, int column, double ** data, double * p, int times, bool back, int method);
// 等概率版本
MATPLY_API double ** choice3(int row, int column, double ** data, int times, bool back);

// 指数分布，scale是大于的正实数。
MATPLY_API double ** exponential(int row, int column, double scale, int seed, bool use);
// 伽玛分布，shape和scale必须都是正实数
MATPLY_API double ** gamma_(int row, int column, double shape, double scale, int seed, bool use);
// 二项式分布，n是正整数、p是概率，二项式分布得到的正整数集，但是由于MatPly的实现原因……
MATPLY_API double ** binomial(int row, int column, int n, double p, int seed, bool use);
// 卡方分布，k是自由度，正整数
MATPLY_API double ** chisquare(int row, int column, int k, int seed, bool use);
// t分布
MATPLY_API double ** tdis(int row, int column, int k, int seed, bool use);
// F分布
MATPLY_API double ** fdis(int row, int column, int k1, int k2, int seed, bool use);
// 几何分布
MATPLY_API double ** geometric(int row, int column, double p, int seed, bool use);
// 负二项分布
MATPLY_API double ** nbinomial(int row, int column, int n, double p, int seed, bool use);
// 对数正态分布
MATPLY_API double ** lognormal(int row, int column, double mu, double sigma, int seed, bool use);
// 柯西分布，data是位置参数的组成
MATPLY_API double ** cauchydis(int row, int column, double base, double gamma, int seed, bool use);
// 多项式分布，本质仍是整数集，最后获取的是size * len形状的矩阵
MATPLY_API double ** multinomial(double * p, int len, int n, int size, int seed, bool use);
// 贝塔分布
MATPLY_API double ** beta(int row, int column, double a, double b, int seed, bool use);
// 维纳过程（布朗运动），T 表示终止时间或总时间长度
MATPLY_API double ** wiener_process(int row, int column, double t, int seed, bool use);
// 维纳过程，从某时间开始到某时间结束，base表示开始时间的值
MATPLY_API double ** wiener_process_stage(int row, int column, double t0, double t1, double base, int seed, bool use);
// 狄利克雷分布，alpha必须是正实数向量，最后获取的是size * len形状的矩阵
MATPLY_API double ** dirichlet(double * alpha, int len, int size, int seed, bool use);
// 拉普拉斯分布，其中b是正实数
MATPLY_API double ** laplacedis(int row, int column, double mu, double b, int seed, bool use);
// 耿贝尔分布，beta是正实数、left表示是不是左偏（也就是建模极小值）
MATPLY_API double ** gumbel(int row, int column, double mu, double beta, bool left, int seed, bool use);
// 超几何分布，expected是目标的数目、unexpected是非目标个数、n是抽取样本个数，本质仍是整数集
MATPLY_API double ** hypergeometric(int row, int column, int expected, int unexpected, int n, int seed, bool use);
// 对数分布
MATPLY_API double ** logseries(int row, int column, double p, int seed, bool use);
// 韦伯分布，lambda是尺度参数、k是形状参数、这两个都是正实数
MATPLY_API double ** weibull(int row, int column, double lambda, double k, int seed, bool use);
// 三角分布
MATPLY_API double ** triangular(int row, int column, double left, double middle, double right, int seed, bool use);
// 幂定律分布，xmin是数据的下界，为正实数，alpha是指数部分，大于0
MATPLY_API double ** power_law(int row, int column, double xmin, double alpha, int seed, bool use);
// 瑞利分布
MATPLY_API double ** rayleigh(int row, int column, double sigma, int seed, bool use);
// 稳定分布
MATPLY_API double ** stabledis(int row, int column, double alpha, double beta, double gamma, double delta, int seed, bool use);
// 帕累托分布
MATPLY_API double ** pareto(int row, int column, double xmin, double alpha, int seed, bool use);
// 莱斯分布
MATPLY_API double ** rice(int row, int column, double v, double sigma, int seed, bool use);
// 逆高斯分布（沃德分布）
MATPLY_API double ** wald(int row, int column, double mu, double sigma, int seed, bool use);

#endif //MP_RANDOM_H
