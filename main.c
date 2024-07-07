//
// Created by 20281 on 2024/7/6.
//

#include "matbox.h"

int main()
{
    double data[3][3] = {
        {3, 6, 2},
        {0, 9, 2},
        {1, 1, 6}
    };
    Matrix * new = __init__(3, 3, data, NULL);
    VisibleMatrix(new);
    double * lis = row_(2, new);

    double * lis2 = column_(2, new);
    for (int u = 0;u < 3;u++)
    {
        printf("%f\t", lis[u]);
    }
    printf("\n");
    for (int u = 0;u < 3;u++)
    {
        printf("%f\t", lis2[u]);
    }
    printf("\n");
    __delete__(new);
    free(lis);
    free(lis2);
    Matrix * fill5 = filled(3, 5, 5);
    VisibleMatrix(fill5);
    __delete__(fill5);
    return 0;
}