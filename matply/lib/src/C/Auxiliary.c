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

double getMin(const double *arr, const int len)
{
    double min = arr[0];

    for (int i = 1; i < len; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

double getMax(const double * arr, const int len)
{
    double max = arr[0];

    for (int i = 1; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void ** copy_array(void ** datas, const int row, const int column)
{
    void ** new = (void **)malloc(sizeof(void**) * row);
    for(int r = 0;r < row;r ++)
    {
        new[r] = malloc(column * sizeof(void *));
        memcpy(new[r], datas[r], column * sizeof(void *));
    }
    return new;
}

double ** allocateButNoNumbers(const int row, const int column)
{
    double ** new = (double**)malloc(sizeof(double *) * row);
    for (int r=0;r < row;r++)
        new[r] = (double*)malloc(sizeof(double) * column);
    return new;
}

double ** oneTotwoArray(const double * array, const int row, const int column)
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