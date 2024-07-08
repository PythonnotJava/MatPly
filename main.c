//
// Created by 20281 on 2024/7/6.
//

#include "matply.h"

int main()
{
    // double data[3][3] = {
    //     {3, 6, 2},
    //     {0, 9, 2},
    //     {1, 1, 6}
    // };
    // Matrix * new = __init__(3, 3, data, NULL);
    // VisibleMatrix(new);
    // double * lis = row_(2, new);
    //
    // double * lis2 = column_(2, new);
    // for (int u = 0;u < 3;u++)
    // {
    //     printf("%f\t", lis[u]);
    // }
    // printf("\n");
    // for (int u = 0;u < 3;u++)
    // {
    //     printf("%f\t", lis2[u]);
    // }
    // printf("\n");
    // __delete__(new);
    // free(lis);
    // free(lis2);
    // Matrix * fill5 = filled(3, 5, 5);
    // VisibleMatrix(fill5);
    // __delete__(fill5);
    //
    // double data2[4][3] = {
    //     {3, 6, 2},
    //     {0, 9, 2},
    //     {1, 1, 6},
    //     {0, 5, 3}
    // };
    // Matrix * matrix1 = __init__(4, 3, data2, NULL);
    // VisibleMatrix(matrix1);
    // Matrix * matrix2 = transpose(matrix1);
    // VisibleMatrix(matrix2);
    // __delete__(matrix1);
    // __delete__(matrix2);
    // double datan[1][1] = {{2}};
    // Matrix * matrix3 = __init__(1, 1, datan, NULL);
    // VisibleMatrix(matrix3);
    // printf("%f\n", det(matrix3));
    // __delete__(matrix3);
    double data[3][3] = {
        {3., 6., 2.},
        {0., 9., 2.},
        {1., 1., 6.}
    };
    Matrix * matrix = __init__(3, 3, data, NULL);
    double de = det(matrix);
    printf("Det == %f\n", de);
    Matrix * co = cofactor(0,1, matrix);
    VisibleMatrix(co);
    printf("Det == %f\n", det(co));
    __delete__(co);

    __delete__(matrix);

    Matrix * e = E(4);
    VisibleMatrix(e);
    printf("Det == %f\n", det(e));
    Matrix * e1 = cofactor(3, 2, e);
    VisibleMatrix(e1);
    __delete__(e1);
    __delete__(e);
    return 0;
}