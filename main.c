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
   // double data[3][3] = {
   //     {3., 6., 2.},
   //     {0., 9., 2.},
   //     {1., 1., 6.}
   // };
   // Matrix * matrix = __init__(3, 3, data, NULL);
   // double de = det(matrix);
   // printf("Det == %f\n", de);
   // Matrix * co = cofactor(0,1, matrix);
   // VisibleMatrix(co);
   // printf("Det == %f\n", det(co));
   // __delete__(co);
   //
   // __delete__(matrix);
   //
   // Matrix * e = E(4);
   // VisibleMatrix(e);
   // printf("Det == %.2f\n", det(e));
   // Matrix * e1 = cofactor(3, 2, e);
   // VisibleMatrix(e1);
   // __delete__(e1);
   // __delete__(e);

    // VisibleMatrix(matrix5b);
    // Matrix * cutm = cut(matrix5b, 1, 3, 3,2);
    // VisibleMatrix(cutm);
    // __delete__(cutm);

    // Matrix * matrix7 = resizeR(matrix5b, 1, 1, 11);
    // VisibleMatrix(matrix7);
    // __delete__(matrix7);
    // set_round("%.0f");
    // Matrix * matrix5b = __init__(3, 6, mt4data, NULL);
    // Matrix * matrix8 = resizeC(matrix5b, 5, 4, 11);
    // VisibleMatrix(matrix8);
    // __delete__(matrix8);
    // VisibleMatrix((matrix5b));
    // resizeRNoReturned(matrix5b, 2, 5, 11);
    // VisibleMatrix((matrix5b));
    // resizeRNoReturned(matrix5b, 5, 6, 10);
    // VisibleMatrix(matrix5b);
    // resizeCNoReturned(matrix5b, 2, 2, 111);
    // VisibleMatrix(matrix5b);
    // resizeCNoReturned(matrix5b, 3, 3, 111);
    // VisibleMatrix(matrix5b);
    // __delete__(matrix5b);
    // printf("nan == %f\n", getnan());
    // printf("e^nan == %f\n", exp(INFINITY));
    // printf("%d\n", isnan(NAN));
    double mt4data [][6]=   {
        {3, 6, 2, 10, -34, 2},
        {0, 9, 2, 4, 6, 0},
        {INFINITY, 1, 6, 4, 6, 2}};

    double ** dat = (double**)malloc(sizeof(double*) *3);
    for (int r=0;r<3;r++)
    {
        dat[r] = (double*)malloc(sizeof(double)*6);
        for (int c=0;c<6;c++)
            dat[r][c] = mt4data[r][c];
    }

    Matrix * m11 = log_((void**)dat,true,3 ,6 );
    __delete__data__(dat,3);
    VisibleMatrix(m11);

    Matrix * m12 = log_((void**)m11, false, 3, 6);
    VisibleMatrix(m12);
    __delete__(m12);
    __delete__(m11);
    return 0;
}