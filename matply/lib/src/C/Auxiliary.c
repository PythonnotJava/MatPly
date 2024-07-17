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