//
// Created by 25654 on 24-9-20.
//

#include "mp_auxiliary.h"

#ifdef MP_CFG_H
#else
    #include "mp_cfg.h"
#endif

#if defined _INC_STDLIB
#else
#include <stdlib.h>
#endif
#if defined _INC_STRING
#else
#include <string.h>
#endif
#if defined _TIME_H_
#else
#include <time.h>
#endif
#ifdef _MATH_H_
#else
#include <math.h>
#endif

double getMin( double *arr,  int len)
{
    double min = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

double getMax( double * arr,  int len)
{
    double max = arr[0];

    for (int i = 1; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void ** copy_array(void ** datas,  int row,  int column)
{
    void ** new = (void **)malloc(sizeof(void**) * row);
    for(int r = 0;r < row;r ++)
    {
        new[r] = malloc(column * sizeof(void *));
        memcpy(new[r], datas[r], column * sizeof(void *));
    }
    return new;
}

double ** allocateButNoNumbers( int row,  int column)
{
    double ** new = (double**)malloc(sizeof(double *) * row);
    for (int r=0;r < row;r++)
        new[r] = (double*)malloc(sizeof(double) * column);
    return new;
}

double ** oneTotwoArray( double * array,  int row,  int column)
{
    double ** new = (double**)malloc(sizeof(double *) * row);
    int counter = 0;
    for (int r = 0;r<row;r++)
    {
        new[r] = (double*)malloc(sizeof(double) *column);
        for (int c = 0;c < column;c ++)
        {
            new[r][c] = array[counter++];
        }
    }
    return new;
}

void insertSorted(double * arr, int len, double value){
    int i = len - 1;
    while (i >= 0 && arr[i] > value) {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = value;
}

int find_seq(double * arr, int len, double target, bool reverse){
    int index = -1;
    if (reverse){
        for (int i = len - 1;i >= 0;i--){
            if (arr[i] == target){
                index = i;
                break;
            }
        }
    } else{
        for (int i = 0;i < len;i++){
            if (arr[i] == target) {
                index = i;
                break;
            }
        }
    }
    return index;
}

// 二分查找
int find_bin(double * arr, int len, double target){
    int left = 0, right = len - 1, index = -1, mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            index = mid;
            break;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return index;
}

void _findall_continue(
        double *arr,
        int * results,
        int len,
        double target,
        int init,
        int * realloc_init,
        int * current,
        int * i,
        int * results_len,
        int * counter,
        int baseIndex
){
    if (*i < len && *counter == 0){
        results = (int*)realloc(results, (*realloc_init) * sizeof(int));
        *counter = init;
        while (*i < len && *counter != 0){
            if (arr[*i] == target){
                (*counter)--;
                (*results_len)++;
                results[(*current)++] = *i + baseIndex;
            }
            (*i)++;
        }
    }
    *realloc_init = *realloc_init + init;
    if (*i < len && *counter == 0)
        _findall_continue(arr, results, len, target, init, realloc_init, current, i, results_len, counter , baseIndex);
}

// 顺序查找算法，返回一个索引数组，数组第一个数是长度
int * findall(double * arr, int len, double target, int init, int baseIndex){
    int counter = init; // 对初始化内存使用量剩余计数
    int size = (init + 1);
    int * results = (int *) malloc(size * sizeof(int));
    int i = 0;
    int results_len = 0;
    int current = 1;
    while (i < len && counter != 0){
        if (arr[i] == target){
            counter--;
            results[current++] = baseIndex + i;
            results_len++;
        }
        i++;
    }
    int realloc_init = size;
    _findall_continue(arr, results, len, target, init, &realloc_init, &current, &i, &results_len, &counter, baseIndex);
    results = (int *) realloc(results, (results_len + 1) * sizeof(int));
    results[0] = results_len;
    return results;
}

void _findall_condition_continue(
        double *arr,
        int * results,
        int len,
        bool (*condition)(double ),
        int init,
        int * realloc_init,
        int * current,
        int * i,
        int * results_len,
        int * counter,
        int baseIndex
){
    if (*i < len && *counter == 0){
        results = (int*)realloc(results, (*realloc_init) * sizeof(int));
        *counter = init;
        while (*i < len && *counter != 0){
            if (condition(arr[*i])){
                (*counter)--;
                (*results_len)++;
                results[(*current)++] = *i + baseIndex;
            }
            (*i)++;
        }
    }
    *realloc_init = *realloc_init + init;
    if (*i < len && *counter == 0)
        _findall_condition_continue(arr, results, len, condition, init, realloc_init, current, i, results_len, counter, baseIndex);
}

int * findall_condition(double * arr, int len, int init, bool (*condition)(double ),   int baseIndex){
    int counter = init; // 对初始化内存使用量剩余计数
    int size = (init + 1);
    int * results = (int *) malloc(size * sizeof(int));
    int i = 0;
    int results_len = 0;
    int current = 1;
    while (i < len && counter != 0){
        if (condition(arr[i])){
            counter--;
            results[current++] = i + baseIndex;
            results_len++;
        }
        i++;
    }
    int realloc_init = size;
    _findall_condition_continue(arr, results, len, condition, init, &realloc_init, &current, &i, &results_len, &counter, baseIndex);
    results = (int *) realloc(results, (results_len + 1) * sizeof(int));
    results[0] = results_len;
    return results;
}

/// 和随机数相关
void initialize_random_seed() {
    static int initialized = 0;
    if (initialized <= 0) {
        srand(time(NULL));
        initialized = 42;
    }
}

void _shuffle(double *arr, int len){
    initialize_random_seed();
    int j;
    double temp;
    for (int i = len - 1; i > 0; i--) {
        j = rand_func() % (i + 1);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int randint(double lb, double ub){
    initialize_random_seed();
    return (int )(lb + random1() * (ub - lb));
}

double random1() {
    return (double)rand_func() / MAXRAND;
}

double randdouble(double lb, double ub){
    initialize_random_seed();
    return lb + random1() * (ub - lb);
}

double random_choice(double *arr, int len) {
    initialize_random_seed();
    return arr[rand_func() % len];
}

double * random_choices(double *arr, int len, int times, bool back) {
    initialize_random_seed();
    double *result = (double *)malloc(times * sizeof(double));
    int index;
    if (back) {
        for (int i = 0; i < times; i++) {
            index = rand_func() % len;
            result[i] = arr[index];
        }
    } else {
        {
            double * temp_arr = (double *)malloc(len * sizeof(double));
            memcpy(temp_arr, arr, sizeof (double )*len);
            _shuffle(temp_arr, len);
            for (int i = 0; i < times; i++)
                result[i] = temp_arr[i];
            free(temp_arr);
        }
    }
    return result;
}

// 根据概率数组挑选一个值
int __select_index(double * p, double total_weight, int len) {
    double r = random1() * total_weight;
    double cumulative_weight = 0.0;
    for (int i = 0; i < len; i++) {
        cumulative_weight += p[i];
        if (r <= cumulative_weight)
            return i;
    }
    return len - 1;
}

static inline double sigmoidfunc(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// 核心选择函数
double * perfect_choices(double *arr, double *p, int len, int times, bool back, int method) {
    initialize_random_seed();
    double *result = malloc(times * sizeof(double));
    double *adjusted_p = malloc(len * sizeof(double));
    double total_weight = 0.0;

    if (method == 0) {
        for (int i = 0; i < len; i++) {
            adjusted_p[i] = p[i];
            total_weight += adjusted_p[i];
        }
    } else if (method == 1) {
        for (int i = 0; i < len; i++) {
            adjusted_p[i] = sigmoidfunc(p[i]);
            total_weight += adjusted_p[i];
        }
    } else {
        for (int i = 0; i < len; i++) {
            adjusted_p[i] = fabs(p[i]);
            total_weight += adjusted_p[i];
        }
    }

    int selected_index;
    for (int t = 0; t < times; t++) {
        selected_index = __select_index(adjusted_p, total_weight, len);
        result[t] = arr[selected_index];

        if (!back) {
            total_weight -= adjusted_p[selected_index];
            adjusted_p[selected_index] = 0.0;
        }
    }

    free(adjusted_p);
    return result;
}

void freeppvoid(void ** data, int row){
    if (data){
        for (int r = 0;r < row;r++)
            free(data[r]);
        free(data);
    }
}

double ** genTestdatas(int row, int column, double (*func)(double, double)){
    double ** new = (double **) malloc(sizeof (double *) * row);
    for(int r = 0; r < row;r++){
        new[r] = (double *) malloc(sizeof (double ) * column);
        for(int c = 0;c < column;c ++)
            new[r][c] = func(r, c);
    }
    return new;
}

double diffCentral(double x, double (*func)(double)){
    int i, k;
    double h = EPSILON;
    double a[4], d[4], a3;

    for (i = 0; i < 4; i++){
        a[i] = x + (i - 2.0) * h;
        d[i] = func(a[i]);
    }
    for (k = 1; k < 5; k++)
        for (i = 0; i < 4 - k; i++)
            d[i] = (d[i + 1] - d[i]) / (a[i + k] - a[i]);

    a3 = fabs(d[0] + d[1] + d[2] + d[3]);

    if (a3 < 100.0 * EPSILON)
        a3 = 100.0 * EPSILON;

    h = pow (EPSILON / (2.0 * a3), 1.0 / 3.0);

    if (h > 100.0 * EPSILON)
        h = 100.0 * EPSILON;
    return (func(x + h) - func(x - h)) / (2.0 * h);
}

void freeOp(void * data) {free(data);}

double ** testArray( int row,  int column)
{
    double ** new = (double **)malloc(sizeof(double *) * row);
    for (int r = 0;r < row ;r ++)
    {
        new[r] = (double *)malloc(sizeof(double) * column);
        for (int c = 0;c < column;c ++)
            new[r][c] = r + c;
    }
    return new;
}


