//
// Created by 25654 on 24-10-16.
//

#pragma once

#ifndef MP_OMP_H
#define MP_OMP_H

#ifndef MATPLY_API
    #if defined(_WIN32) || defined(_WIN64)
        #define MATPLY_API __declspec(dllexport)
    #else
        #define MATPLY_API __attribute__((visibility("default")))
    #endif
#endif

#include <stdbool.h>
#include <stdio.h>
#include <omp.h>    

////////////////////////////////////////////////////////////////////////////////////////
/// 使用OMP并行化处理MatPly时，
/// 1. 对于复杂计算且在数据量可观的情况下，可以自动转换为多线程计算；
/// 2. 简单操作只在数据量极其可观情况下，可以自动转换为多线程计算
/// 3. 另外，任何支持多线程的操作都可以强制开启多线程模式，忽视数据量判断
/// 多线程设置
// 全局线程最大数，会根据不同电脑配置自动加载
extern int THREADS;
// 安全线程锁，多线程下开启子多线程下的访问锁，仅此一次，也就是说，线程启动数据量只能设置一次
extern bool _threadLocked;
__attribute__((constructor)) void init_threads();
// 设置全局线程最大数，要不大于核线程数，不大于0设置为最大线程
MATPLY_API void set_max_thread_support(int n);
// 获取设置的全局线程最大数
MATPLY_API int get_max_thread_support();
// 获取系统线程最大数
MATPLY_API int get_max_thread_sys();
// 简单计算时启动线程的最小数据量 Data volume control startup thread
extern long SimpleDVCST;
// 复杂计算时启动线程的最小数据量
extern long ComplexDVCST;
// 多线程处理时，简单、复杂计算子线程转多子线程最小数据量
// 已取消设计，原因如下：判断总体数据是否开启足以开启多线程并且将线程平面化更容易实现
// extern long SingleDVCST;
// 设置和获取最小数据量
MATPLY_API void set_simple_dvcst_value(long value);
MATPLY_API void set_complex_dvcst_value(long value);
// MATPLY_API void set_single_dvcst_value(long value);
MATPLY_API long get_simple_dvcst_value();
MATPLY_API long get_complex_dvcst_value();
// MATPLY_API long get_single_dvcst_value();

// 获取时间戳
MATPLY_API double get_time();
// 是否开启多线程的信息展示
extern bool isShowMultp;
MATPLY_API void set_multp_shown(bool _isShowMultp);
MATPLY_API bool get_multp_shown();
// 开启多线程展示时的输出信息
MATPLY_API void multp_msg(long dataCounts, bool multThreads, bool complex, char * name);
// 不规则并行函数展示的输出信息
MATPLY_API void mixin_multp_msg(long dataCounts, bool multThreads, bool complex, char * name);
// 未优化记录
MATPLY_API void no_multp_msg(long dataCounts, bool complex, char * name);

/////////////////DEBYG & Inner TEST & UNSAFE/////////////////////////
// 不安全的线程强制，只能在串行执行每个多线程栅栏时使用，否则会出现最小数据量判断开启多线程的判断异常
MATPLY_API void set_simple_dvcst_value_force(long value);
MATPLY_API void set_complex_dvcst_value_force(long value);
// MATPLY_API void set_single_dvcst_value_force(long value);

/// 测试
// omp是否暴露到别的编程语言
MATPLY_API void testOmp();

#endif //MP_OMP_H
