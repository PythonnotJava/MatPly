//
// Created by 20281 on 2024/7/6.
//

#include "Auxiliary.h"

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