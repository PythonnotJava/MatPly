//
// Created by 25654 on 24-9-20.
//

#include "mp_auxiliary.h"

double getMin(double *arr, int len)
{
    double minValue = arr[0];
    
    bool isMultiple = len >= SimpleDVCST;  // 是否要开启多线程判断
    multp_msg(len, isMultiple, false, "getMin");  // 显示函数调用线程信息

    #pragma omp parallel for reduction(min:minValue) if(isMultiple)
    for (int i = 1; i < len; i++) {
        minValue = fmin(arr[i], minValue);
    }
    return minValue;
}

double getMax(double * arr, int len)
{
    double maxValue = arr[0];

    bool isMultiple = len >= SimpleDVCST; 
    multp_msg(len, isMultiple, false, "getMax");

    #pragma omp parallel for reduction(max:maxValue) if(isMultiple)
    for (int i = 1; i < len; i++) {
        maxValue = fmax(arr[i], maxValue);
    }
    return maxValue;
}

void ** copy_array(void ** datas, int row, int column)
{
    void ** new = (void **)malloc(sizeof(void**) * row);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "copy_array");

    #pragma omp parallel for if(isMultiple)
    for(int r = 0;r < row;r ++) {
        new[r] = malloc(column * sizeof(void *));
        memcpy(new[r], datas[r], column * sizeof(void *));
    }
    return new;
}

double ** allocateButNoNumbers(int row, int column)
{
    double ** new = malloc(sizeof(double *) * row);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "allocateButNoNumbers");

    #pragma omp parallel for if(isMultiple)
    for (int r=0;r < row;r++) {
        new[r] = (double*)malloc(sizeof(double) * column);
    }
    return new;
}

double ** oneTotwoArray( double * array,  int row,  int column)
{
    double ** new = allocateButNoNumbers(row, column);  // 仅先分配内存

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "oneTotwoArray");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row; r++) {
        for (int c = 0;c < column;c ++) {
            new[r][c] = array[r * column + c];
        }
    }
    return new;
}

void insertSorted(double * arr, int len, double value)
{
    int i = len - 1;
    while (i >= 0 && arr[i] > value) {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = value;
}

int find_seq(double * arr, int len, double target, bool reverse)
{
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

void freeppvoid(void ** data, int row){
    if (data){
        for (int r = 0;r < row;r++){
            free(data[r]);
        }
        free(data);
    }
}

double ** genTestdatas(int row, int column, double (*func)(double, double)){
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "genTestdatas");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for(int r = 0; r < row;r++){
        for(int c = 0;c < column;c ++){
            new[r][c] = func(r, c);
        }
    }
    return new;
}

double diffCentral(double x, double (*func)(double)){
    double h = EPSILON;
    double a[4], d[4];

    for (int i = 0; i < 4; i++){
        a[i] = x + (i - 2.0) * h;
        d[i] = func(a[i]);
    }
    for (int k = 1; k < 5; k++) {
        for (int i = 0; i < 4 - k; i++) {
            d[i] = (d[i + 1] - d[i]) / (a[i + k] - a[i]);
        }
    }

    double a3 = fabs(d[0] + d[1] + d[2] + d[3]);

    if (a3 < 100.0 * EPSILON)
        a3 = 100.0 * EPSILON;

    h = pow (EPSILON / (2.0 * a3), 1.0 / 3.0);

    if (h > 100.0 * EPSILON)
        h = 100.0 * EPSILON;
    return (func(x + h) - func(x - h)) / (2.0 * h);
}

void freeOp(void * data) {free(data);}

/// 测试模块
double ** testArray( int row,  int column)
{
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "testArray");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row ;r ++) {
        for (int c = 0;c < column;c ++) {
            new[r][c] = r * c;
        }
    }
    return new;
}

double ** testSingleT(int row, int column, double (*func)(int, int)) {
    double ** new = (double **)malloc(sizeof(double*) * row);
    for (int r = 0;r < row;r ++) {
        new[r] = (double *)malloc(sizeof(double) * column);
        for (int c = 0;c < column;c ++) {
            new[r][c] = func(r, c);
        }
    }
    return new;
}

void testOmpCanRun(int row, int column, double ** data, void (*func)(int, int, double ** data)){
    multp_msg(row * column, true, false, "testOmpCanRun");
    #pragma omp parallel for collapse(2)
    for (int r = 0;r < row;r++) {
        for (int c = 0;c < column;c ++) {
            func(r, c, data);
        }
    }
}

double ** testOmpUniform(int row, int column){
    double ** new = allocateButNoNumbers(row, column);
    multp_msg(row * column, true, false, "testOmpUniform");
    #pragma omp parallel for collapse(2)
    for (int r = 0;r < row;r++) {
        for (int c = 0;c < column;c ++) {
            new[r][c] = random1();
        }
    }
    return new;
}

bool ** allocateTDABools(int row, int column) {
    bool ** new = malloc(sizeof(bool * ) * row);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "allocateTDABools");

    #pragma omp parallel for if(isMultiple)
    for (int r= 0;r < row;r++) {
        new[r] = (bool*)malloc(sizeof(bool) * column);
    }
    return new;
}

double testOut() {
    return 1.23456789;
}

void * allocateOp(int len, int mode) {
    if (mode == 0) {
        return malloc(sizeof(double) * len);
    }else if (mode == 1) {
        return malloc(sizeof(int) * len);
    } else {
        return malloc(sizeof(bool) * len);
    }
}

