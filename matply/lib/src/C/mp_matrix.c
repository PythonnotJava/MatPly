//
// Created by 20281 on 24-9-20.
//

#include "mp_matrix.h"

#ifdef MP_CFG_H
#else
    #include "mp_cfg.h"
#endif

#ifdef MP_MANAGE_H
#else
    #include "mp_manage.h"
#endif

#ifdef MP_AUXILIARY_H
#else
    #include "mp_auxiliary.h"
#endif

#ifdef _INC_STRING
#else
#include <string.h>
#endif

void visible_data( double**matrix,  int row,  int column) {
    printf("[\n");
    for (int r = 0; r <row; r++) {
        printf(" [");
        for (int c = 0; c < column; c++) {
            printf(ROUND, matrix[r][c]);
            if (c < column - 1) {
                printf(" ");
            }
        }
        printf("]");
        if (r <row - 1) {
            printf("\n");
        }
    }
    printf("\n]\n");
}

// __new__方法类似面向对象中的类初始化方法
Matrix * __new__( int row,  int column){
    Matrix * new = (Matrix *) malloc(sizeof (Matrix));
    new->column = column;
    new->row = row;
    new->data = allocateButNoNumbers(row, column);
    new->spc = (Spc *) malloc(sizeof (Spc));
    *new->spc = (Spc){false, false, false, false, false, false};
    Signal(new)
    return new;
}

Matrix * __init__( int row,  int column,  double ** data,  Spc * spc){
    Matrix * new = __new__(row, column);  // 已经Signal了
    new->data = (double **) malloc(sizeof (double *) * row);
    for (int r = 0;r < row;r++){
        new->data[r] = (double *) malloc(sizeof (double ) * column);
        memcpy(new->data[r], data[r], column * sizeof(double));
    }
    new->spc = (Spc *) malloc(sizeof (Spc));
    if (spc)
        *new->spc = *spc;
    else
        *new->spc = (Spc){false, false, false, false, false, false};
    return new;
}

Matrix * __init__point__data__( int row,  int column, double ** data,  Spc * spc)
{
    Matrix * new = __new__(row, column);  // 已经Signal了
    new->data = data;
    new->spc = (Spc *) malloc(sizeof (Spc));
    if (spc)
        *new->spc = *spc;
    else
        *new->spc = (Spc){false, false, false, false, false, false};
    return new;
}

void VisibleMatrix( Matrix *matrix) {
    printf("[\n");
    for (int r = 0; r < matrix->row; r++) {
        printf(" [");
        for (int c = 0; c < matrix->column; c++) {
            printf(ROUND, matrix->data[r][c]);
            if (c < matrix->column - 1) {
                printf(" ");
            }
        }
        printf("]");
        if (r < matrix->row - 1) {
            printf("\n");
        }
    }
    printf("\n]\n");
}

void __delete__data__(double ** data,  int row)
{
    if(data)
    {
        for (int r=0;r < row;r++)
        {
            free(data[r]);
        }
        free(data);
    }
}

void __delete__(Matrix * matrix){
    if(matrix)
    {
        __delete__data__(matrix->data, matrix->row);
        if (matrix->spc)
            free(matrix->spc);
        free(matrix);
    }
}

void VisibleMatrixSpc( Matrix * matrix)
{
    printf("Matrix identityMatrix == %s\n", matrix->spc->identityMatrix ? "true" : "false");
    printf("Matrix upperTriangularMatrix == %s\n", matrix->spc->upperTriangularMatrix ? "true" : "false");
    printf("Matrix lowerTriangularMatrix == %s\n", matrix->spc->lowerTriangularMatrix ? "true" : "false");
    printf("Matrix singularMatrix == %s\n", matrix->spc->singularMatrix ? "true" : "false");
    printf("Matrix subDiagonalMatrix == %s\n", matrix->spc->subDiagonalMatrix ? "true" : "false");
    printf("Matrix principalDiagonalMatrix == %s\n", matrix->spc->principalDiagonalMatrix ? "true" : "false");
}

bool isSquare( Matrix * matrix) {return matrix->column == matrix->row;}

bool data_isSame( int row,  int column,  double ** data1,  double ** data2)
{
    for (int r = 0;r < row;r ++)
    {
        for (int c=0;c < column;c ++)
        {
            if (data1[r][c] != data2[r][c])
                return false;
        }
    }
    return true;
}

bool spc_isSame( Spc * spc1,  Spc * spc2)
{
    return (
        spc1->identityMatrix == spc2->identityMatrix &&
        spc1->singularMatrix == spc2->singularMatrix &&
        spc1->principalDiagonalMatrix == spc2->principalDiagonalMatrix &&
        spc1->upperTriangularMatrix == spc2->upperTriangularMatrix &&
        spc1->lowerTriangularMatrix == spc2->lowerTriangularMatrix &&
        spc1->subDiagonalMatrix == spc2->subDiagonalMatrix
    );
}
