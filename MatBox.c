//
// Created by 20281 on 2024/7/6.
//

#include "MatBox.h"

Matrix * __new__(const int row, const int column){
    Matrix * new = (Matrix *) malloc(sizeof (Matrix));
    new->column = column;
    new->row = row;
    new->data = NULL;
    new->spc = NULL;
    return new;
}

Matrix * __init__(const int row, const int column, double data[][column], Spc * spc){
    Matrix * new = __new__(row, column);
    new->data = (double **) malloc(sizeof (double *) * row);
    for (int r = 0;r < row;r++){
        new->data[r] = (double *) malloc(sizeof (double ) * column);
        for (int c = 0; c < column;c ++){
            new->data[r][c] = data[r][c];
        }
    }
    new->spc = (Spc *) malloc(sizeof (Spc));;
    *new->spc = (Spc){false, false, false, false, false, false};
    if (spc)
    {
        new->spc->identityMatrix = spc->identityMatrix;
        new->spc->lowerTriangularMatrix = spc->lowerTriangularMatrix;
        new->spc->principalDiagonalMatrix = spc->principalDiagonalMatrix;
        new->spc->singularMatrix = spc->singularMatrix;
        new->spc->upperTriangularMatrix = spc->upperTriangularMatrix;
        new->spc->subdiagonalMatrix = spc->subdiagonalMatrix;
    }
    return new;
}

void VisibleMatrix(const Matrix * matrix){
    printf("[\n");
    for (int r = 0;r < matrix->row;r++){
        for (int c = 0;c < matrix->column;c ++){
            printf(ROUND, matrix->data[r][c]);
        }
        printf("\n");
    }
    printf("]\n");
}

void __delete__(Matrix * matrix){
    if (matrix->data){
        for (int r = 0;r < matrix->row;r++)
            free(matrix->data[r]);
        free(matrix->data);
    }
    if (matrix->spc)
        free(matrix->spc);
    free(matrix);
}

Matrix * filled(const int row, const int column, const double number)
{
    Matrix * new = __new__(row, column);
    new->data = (double **)malloc(sizeof(double*)*row);
    for (int r = 0;r < row;r++)
    {
        new->data[r] = (double*)malloc(sizeof(double)*column);
        for (int c = 0;c < column;c ++)
            new->data[r][c] = number;
    }
    return new;
}

Matrix * zeros(const int row, const int column){return filled(row, column, 0.);}
Matrix * ones(const int row, const int column){return filled(row, column, 1.);}

void VisibleMatrixSpc(const Matrix * matrix)
{
    printf("Matrix identityMatrix == %s\n", matrix->spc->identityMatrix ? "true" : "false");
    printf("Matrix upperTriangularMatrix == %s\n", matrix->spc->upperTriangularMatrix ? "true" : "false");
    printf("Matrix lowerTriangularMatrix == %s\n", matrix->spc->lowerTriangularMatrix ? "true" : "false");
    printf("Matrix singularMatrix == %s\n", matrix->spc->singularMatrix ? "true" : "false");
    printf("Matrix subdiagonalMatrix == %s\n", matrix->spc->subdiagonalMatrix ? "true" : "false");
    printf("Matrix principalDiagonalMatrix == %s\n", matrix->spc->principalDiagonalMatrix ? "true" : "false");
}

double * row_(const int row, const Matrix * matrix)
{
    double *arr = (double *)malloc(matrix->column * sizeof(double));
    for (int c = 0;c < matrix->column;c ++)
        arr[c] = matrix->data[row][c];
    return arr;
}

double * column_(const int column, const Matrix * matrix)
{
    double *arr = (double*)malloc(matrix->row *sizeof(double));
    for (int r = 0;r < matrix->row;r++)
        arr[r] = matrix->data[r][column];
    return arr;
}

double at(const int row, const int column, const Matrix * matrix) {return matrix->data[row][column];}

bool isSquare(const Matrix * matrix) {return matrix->column == matrix->row;}

