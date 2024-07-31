//
// Created by 20281 on 2024/7/6.
//

#include "Auxiliary.h"

#if defined _INC_STDLIB
#else
#include <stdlib.h>
#endif

#if defined _INC_STRING
#else
#include <string.h>
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

// 顺序查找算法，返回一个索引数组，数组第一个数是长度
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

void freeppvoid(void ** data, int row){
    if (data){
        for (int r = 0;r < row;r++)
            free(data[r]);
        free(data);
    }
}