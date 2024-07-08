//
// Created by 20281 on 2024/7/6.
//

#include "matply.h"

Matrix * __new__(const int row, const int column){
    Matrix * new = (Matrix *) malloc(sizeof (Matrix));
    new->column = column;
    new->row = row;
    new->data = (double **) malloc(sizeof (double *) * row);
    for (int r = 0;r < row;r++)
        new->data[r] = (double *) malloc(sizeof (double ) * column);
    new->spc = (Spc *) malloc(sizeof (Spc));;
    *new->spc = (Spc){false, false, false, false, false, false};
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
        *new->spc = *spc;
    return new;
}

void VisibleMatrix(const Matrix *matrix) {
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
    for (int r = 0;r < row;r++)
    {
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
    printf("Matrix subDiagonalMatrix == %s\n", matrix->spc->subDiagonalMatrix ? "true" : "false");
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

Matrix * transpose(const Matrix * matrix)
{
    Matrix * new = __new__(matrix->column, matrix->row);
    for (int r = 0; r < matrix->row; r++) {
        for (int c = 0; c < matrix->column; c++) {
            new->data[c][r] = matrix->data[r][c];
        }
    }
    new->spc->identityMatrix = matrix->spc->identityMatrix;
    new->spc->singularMatrix = matrix->spc->singularMatrix;
    new->spc->lowerTriangularMatrix = matrix->spc->lowerTriangularMatrix;
    new->spc->upperTriangularMatrix = matrix->spc->upperTriangularMatrix;
    new->spc->subDiagonalMatrix = matrix->spc->subDiagonalMatrix;
    new->spc->principalDiagonalMatrix = matrix->spc->principalDiagonalMatrix;
    return new;
}

void exchangeR(const int row1, const int row2, const Matrix * matrix)
{
    if (row1 != row2)
    {
        double temp = 0.;
        for (int c= 0;c < matrix->column;c ++)
        {
            temp = matrix->data[row1][c];
            matrix->data[row1][c] = matrix->data[row2][c];
            matrix->data[row2][c] = temp;
        }
    }
}

void multiplyR(const int row, const double size, const Matrix * matrix)
{
    for (int c = 0;c < matrix->column;c ++)
        matrix->data[row][c] *= size;
}


void addR(const int row1, const int row2, const double size, const Matrix * matrix)
{
    for (int c = 0;c < matrix->column;c ++)
        matrix->data[row1][c] += matrix->data[row2][c] * size;
}

void exchangeC(const int column1, const int column2, const Matrix * matrix)
{
    if (column1 != column2)
    {
        double temp = 0.;
        for (int r= 0;r < matrix->row;r ++)
        {
            temp = matrix->data[r][column1];
            matrix->data[r][column1] = matrix->data[r][column2];
            matrix->data[r][column2] = temp;
        }
    }
}

void multiplyC(const int column, const double size, const Matrix * matrix)
{
    for (int r = 0;r < matrix->row;r ++)
        matrix->data[r][column] *= size;
}

void addC(const int column1, const int column2, const double size, const Matrix * matrix)
{
    for (int r = 0;r < matrix->row;r++)
        matrix->data[r][column1] += matrix->data[r][column2] * size;
}

Matrix * addNumber(const double number, const Matrix * matrix)
{
    Matrix * new = __new__(matrix->row, matrix->column);
    for (int r = 0;r < matrix->row;r++)
    {
        for (int c = 0;c < matrix->column;c ++)
        {
            new->data[r][c] = matrix->data[r][c] + number;
        }
    }
    return new;
}

Matrix * addMatrix(const Matrix * matrix1, const Matrix * matrix2)
{
    Matrix * new = __new__(matrix1->row, matrix1->column);
    for (int r = 0;r < matrix1->row;r++)
    {
        for (int c = 0;c < matrix1->column;c ++)
        {
            new->data[r][c] = matrix1->data[r][c] + matrix2->data[r][c];
        }
    }
    return new;
}

void addNumberNoReturned(const double number, const Matrix * matrix)
{
    for (int r = 0;r < matrix->row;r++)
    {
        for (int c = 0;c < matrix->column;c ++)
        {
            matrix->data[r][c] += number;
        }
    }
}

void addMatrixNoReturned(const Matrix * matrix1, const Matrix * matrix2)
{
    for (int r = 0;r < matrix1->row;r++)
    {
        for (int c = 0;c < matrix1->column;c ++)
        {
            matrix1->data[r][c] += matrix2->data[r][c];
        }
    }
}

Matrix * minusMatrix(const Matrix * matrix1, const Matrix * matrix2)
{
    Matrix * new = __new__(matrix1->row, matrix1->column);
    for (int r = 0;r < matrix1->row;r++)
    {
        for (int c = 0;c < matrix1->column;c ++)
        {
            new->data[r][c] = matrix1->data[r][c] - matrix2->data[r][c];
        }
    }
    return new;
}

void minusMatrixNoReturned(const Matrix * matrix1, const Matrix * matrix2)
{
    for (int r = 0;r < matrix1->row;r++)
    {
        for (int c = 0;c < matrix1->column;c ++)
        {
            matrix1->data[r][c] -= matrix2->data[r][c];
        }
    }
}

Matrix * matmul(const Matrix * matrix1, const Matrix * matrix2)
{
    Matrix * new = __new__(matrix1->row, matrix2->column);
    for (int i = 0; i < matrix1->row; ++i) {
        for (int j = 0; j < matrix2->column; ++j) {
            new->data[i][j] = 0.0;
            for (int k = 0; k < matrix1->column; ++k) {
                new->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
            }
        }
    }
    return new;
}

void multiplyMatrixNoReturned(const Matrix * matrix1, const Matrix * matrix2)
{
    for (int r = 0;r <matrix1->row;r++)
    {
        for (int c =0;c<matrix1->column;c ++)
        {
            matrix1->data[r][c] *= matrix2->data[r][c];
        }
    }
}

Matrix * multiplyMatrix(const Matrix * matrix1, const Matrix * matrix2)
{
    Matrix * new = __new__(matrix1->row, matrix1->column);
    for (int r = 0;r <matrix1->row;r++)
    {
        for (int c =0;c<matrix1->column;c ++)
        {
            new->data[r][c] = matrix1->data[r][c] * matrix2->data[r][c];
        }
    }
    return new;
}

void multiplyNumberNoReturned(const double number, const Matrix * matrix)
{
    for(int r=0;r < matrix->row;r ++)
    {
        for (int c = 0;c < matrix->column;c ++)
        {
            matrix->data[r][c] *= number;
        }
    }
}

Matrix * multiplyNumber(const double number, const Matrix * matrix)
{
    Matrix * new = __new__(matrix->row, matrix->column);
    for (int r = 0;r <matrix->row;r++)
    {
        for (int c =0;c<matrix->column;c ++)
        {
            new->data[r][c] = matrix->data[r][c] * number;
        }
    }
    return new;
}

Matrix * kronecker(const Matrix * matrix1, const Matrix * matrix2)
{
    Matrix * new = __new__(matrix1->row * matrix2->row, matrix1->column * matrix2->column);
    for (int i = 0; i < matrix1->row; ++i) {
        for (int j = 0; j < matrix1->column; ++j) {
            for (int k = 0; k < matrix2->row; ++k) {
                for (int l = 0; l < matrix2->column; ++l) {
                    new->data[i * matrix2->row + k][j * matrix2->column + l] = matrix1->data[i][j] * matrix2->data[k][l];
                }
            }
        }
    }
    return new;
}

Matrix * divide(const double number, const Matrix * matrix)
{
    Matrix * new = __new__(matrix->row, matrix->column);
    for (int r = 0;r <matrix->row;r++)
    {
        for (int c =0;c<matrix->column;c ++)
        {
            new->data[r][c] = matrix->data[r][c] / number;
        }
    }
    return new;
}

void divideNoReturned(const double number, const Matrix * matrix)
{
    for (int r = 0;r <matrix->row;r++)
    {
        for (int c =0;c<matrix->column;c ++)
        {
            matrix->data[r][c] /= number;
        }
    }
}

Matrix * arrange(const double start, const int row, const int column)
{
    Matrix* new = __new__(row, column);
    double counter = start;
    for (int r = 0;r < row;r++)
    {
        for(int c = 0;c < column;c ++)
        {
            new->data[r][c] = counter++;
        }
    }
    return new;
}

Matrix * linspace(const double start, const double end, const int row, const int column, const bool keep)
{
    const int counts = row * column;
    const double step = keep ? (end - start) / (counts - 1) : (end - start) / counts;
    Matrix* matrix = __new__(row, column);
    double value = start;
    for (int r = 0; r < row; r++) {
        for (int c = 0; c< column; c ++) {
            matrix->data[r][c] = value;
            value += step;
        }
    }
    if (keep)
        matrix->data[row - 1][column - 1] = end;
    return matrix;
}

double trace(const Matrix * matrix)
{
    const int n = matrix->row < matrix->column ? matrix->row : matrix->column;
    double sum = 0.;
    for (int r = 0;r < n;r++)
        sum += matrix->data[r][r];
    return sum;
}


double det(const Matrix *matrix) {
    double detValue = 1;
    const int n = matrix->column;
    Matrix * matrixcpy = deepcopy(matrix);

    for (int i = 0; i < n; i++) {
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(matrixcpy->data[k][i]) > fabs(matrixcpy->data[max_row][i])) {
                max_row = k;
            }
        }
        if (matrixcpy->data[max_row][i] == 0) {
            __delete__(matrixcpy);
            return 0;
        }

        if (max_row != i) {
            double *temp = matrixcpy->data[max_row];
            matrixcpy->data[max_row] = matrixcpy->data[i];
            matrixcpy->data[i] = temp;
            detValue = -detValue;
        }
        detValue *= matrixcpy->data[i][i];
        for (int k = i + 1; k < n; k++) {
            const double factor = matrixcpy->data[k][i] / matrixcpy->data[i][i];
            for (int j = i; j < n; j++) {
                matrixcpy->data[k][j] -= factor * matrixcpy->data[i][j];
            }
        }
    }
    __delete__(matrixcpy);
    return detValue;
}

Matrix * E(const int n)
{
    Matrix * new = (Matrix *) malloc(sizeof (Matrix));
    new->column = n;
    new->row = n;
    new->data = (double **)calloc(n, sizeof (double *));
    for (int r = 0;r < n;r++)
    {
        new->data[r] = (double *) calloc(n, sizeof (double ));
        new->data[r][r] = 1.;
    }
    new->spc = (Spc *) malloc(sizeof (Spc));;
    *new->spc = (Spc){false, false, false, false, false, false};
    return new;
}

Matrix * cofactor(const int row, const int column, const Matrix * matrix) {
    Matrix * new = __new__(matrix->row - 1, matrix->column - 1);
    int i = 0, j = 0;
    for (int r = 0; r < matrix->row; r++) {
        for (int c = 0; c < matrix->column; c ++) {
            if (r != row && c != column) {
                new->data[i][j++] = matrix->data[r][c];
                if (j == matrix->column - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
    return new;
}

Matrix * adjugate(const Matrix * matrix)
{
    const int n = matrix->row;
    Matrix * new = __new__(n, n);
    for (int r = 0; r < n;r++)
    {
        for (int c = 0; c< n; c ++)
        {
            Matrix * cof = cofactor(r, c, matrix);
            new->data[c][r] = pow(-1, r + c) * det(cof);
            __delete__(cof);
        }
    }
    return new;
}

Matrix * inverse(const Matrix * matrix, const double det)
{
    const int n = matrix->row;
    Matrix * new = __new__(n, n);

    Matrix * adj = adjugate(matrix);

    for (int r = 0; r < n; r++) {
        for (int c = 0; c< n;  c ++) {
            new->data[r][c] = adj->data[r][c] / det;
        }
    }
    __delete__(adj);
    return new;
}

Matrix * deepcopy(const Matrix * matrix)
{
    Matrix * new = __new__(matrix->row, matrix->column);

    for (int r = 0; r < matrix->row; r++) {
        for (int c = 0; c < matrix->column; c++) {
            new->data[r][c] = matrix->data[r][c];
        }
    }
    new->spc = (Spc *) malloc(sizeof(Spc));
    *new->spc = *matrix->spc;

    return new;
}