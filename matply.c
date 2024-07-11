//
// Created by 20281 on 2024/7/6.
//

#include "matply.h"

const char * ROUND = "%.5lf\t";  // 输出精度

void set_round(const char* new_round) {
    ROUND = new_round;
}

__attribute__((visibility("default"))) double PI = M_PI;
__attribute__((visibility("default"))) double e = M_E;
__attribute__((visibility("default"))) double _nan = NAN;
__attribute__((visibility("default"))) double inf = INFINITY;

Matrix * __new__(const int row, const int column){
    Matrix * new = (Matrix *) malloc(sizeof (Matrix));
    new->column = column;
    new->row = row;
    new->data = allocateButNoNumbers(row, column);
    new->spc = (Spc *) malloc(sizeof (Spc));;
    *new->spc = (Spc){false, false, false, false, false, false};
    return new;
}

Matrix * __init__(const int row, const int column, double data[][column], Spc * spc){
    Matrix * new = __new__(row, column);
    new->data = (double **) malloc(sizeof (double *) * row);
    for (int r = 0;r < row;r++){
        new->data[r] = (double *) malloc(sizeof (double ) * column);
        memcpy(new->data[r], data[r], column * sizeof(double));
    }
    new->spc = (Spc *) malloc(sizeof (Spc));;
    *new->spc = (Spc){false, false, false, false, false, false};
    if (spc)
        *new->spc = *spc;
    return new;
}

Matrix * __init__point__data__(const int row, const int column, double ** data, Spc * spc)
{
    Matrix * new = __new__(row, column);
    new->data = data;
    new->spc = (Spc *) malloc(sizeof (Spc));
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

void __delete__data__(double ** data, const int row)
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
        memcpy(new->data[r], matrix->data[r], matrix->column * sizeof(double));
    }
    new->spc = (Spc *) malloc(sizeof(Spc));
    *new->spc = *matrix->spc;

    return new;
}

bool ** compare(const Matrix *matrix1, const Matrix *matrix2, const int mode)
{

    #define COMPARE_OP(op, m1, m2, n) {\
        for (int r = 0;r < m1->row;r++)\
        {\
            new[r] = (bool *)malloc(sizeof(bool) * m1->column);\
            for(int c=0;c < m1->column;c ++)\
            {\
                n[r][c] = (m1->data[r][c] op m2->data[r][c]) ? true : false;\
            }\
        }\
    }\

    bool **new = (bool **)malloc(sizeof(bool *) * matrix1->row);

    switch (mode) {
    case 1:
        COMPARE_OP(>, matrix1, matrix2, new);
        break;
    case 2:
        COMPARE_OP(<, matrix1, matrix2, new);
        break;
    case 3:
        COMPARE_OP(<=, matrix1, matrix2, new);
        break;
    case 4:
        COMPARE_OP(>=, matrix1, matrix2, new);
        break;
    default:
        COMPARE_OP(==, matrix1, matrix2, new);
        break;
    }
    #undef COMPARE_OP
    return new;
}

double *sum(const Matrix *matrix, const int dim) {
    double *number = NULL;
    switch (dim) {
    case 0:
        {
            number = (double *)calloc(matrix->row, sizeof(double));
            for (int r = 0; r < matrix->row; r++) {
                for (int c = 0; c < matrix->column; c++) {
                    number[r] += matrix->data[r][c];
                }
            }
            break;
        }
    case 1:
        {
            number = (double *)calloc(matrix->column, sizeof(double));
            for (int c = 0; c < matrix->column; c++) {
                for (int r = 0; r < matrix->row; r++) {
                    number[c] += matrix->data[r][c];
                }
            }
            break;
        }
    default:
        {
            number = (double *)malloc(sizeof(double));
            *number = 0.0;
            for (int r = 0; r < matrix->row; r++) {
                for (int c = 0; c < matrix->column; c++) {
                    *number += matrix->data[r][c];
                }
            }
            break;
        }
    }
    return number;
}


double * mean(const Matrix * matrix, const int dim)
{
    double *number = NULL;
    switch (dim)
    {
    case 0:
        {
            number = sum(matrix, 0);
            for (int r=0;r < matrix->row;r++)
                number[r] /= matrix->column;
            break;
        }
    case 1:
        {
            number = sum(matrix, 1);
            for (int c = 0;c < matrix->column;c ++)
                number[c] /= matrix->row;
            break;
        }
    default:
        {
            double *sumResult = sum(matrix, -1);
            number = (double *)malloc(sizeof(double));
            *number = *sumResult / (matrix->row * matrix->column);
            free(sumResult);
            break;
        }
    }
    return number;
}

double * min(const Matrix * matrix, const int dim)
{
    double * number = NULL;
    switch (dim)
    {
    case 0:
        {
            number = (double *)malloc(sizeof(double) * matrix->row);
            for (int r = 0; r < matrix->row; r++) {
                number[r] = getMin(matrix->data[r], matrix->column);
            }
            break;
        }
    case 1:
        {
            number = (double *)malloc(sizeof(double) * matrix->column);
            for (int c = 0; c < matrix->column; c++) {
                double min = matrix->data[0][c];
                for (int r = 1; r < matrix->row; r++) {
                    if (matrix->data[r][c] < min) {
                        min = matrix->data[r][c];
                    }
                }
                number[c] = min;
            }
            break;
        }
    default:
        {
            number = (double *)malloc(sizeof(double));
            *number = matrix->data[0][0];
            for (int r = 0; r < matrix->row; r++) {
                for (int c = 0; c < matrix->column; c++) {
                    if (matrix->data[r][c] < *number) {
                        *number = matrix->data[r][c];
                    }
                }
            }
            break;
        }
    }
    return number;
}

bool data_isSame(const double ** data1, const double ** data2, const int row, const int column)
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

bool spc_isSame(const Spc * spc1, const Spc * spc2)
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

double * max(const Matrix * matrix, const int dim)
{
    double * number = NULL;
    switch (dim)
    {
    case 0:
        {
            number = (double*)malloc(sizeof(double) * matrix->row);
            for (int r=0;r < matrix->row;r ++)
            {
                number[r] = getMax(matrix->data[r], matrix->column);
            }
            break;
        }
    case 1:
        {
            number = (double*)malloc(sizeof(double) * matrix->column);
            for (int c = 0; c < matrix->column; c++) {
                double max = matrix->data[0][c];
                for (int r = 1; r < matrix->row; r++) {
                    if (matrix->data[r][c] > max) {
                        max = matrix->data[r][c];
                    }
                }
                number[c] = max;
            }
            break;
        }
    default:
        {
            number = (double *)malloc(sizeof(double));
            *number = matrix->data[0][0];
            for(int r=0;r < matrix->row;r++)
            {
                for (int c = 0;c < matrix->column;c ++)
                {
                    if(matrix->data[r][c] > *number)
                        *number = matrix->data[r][c];
                }
            }
            break;
        }
    }
    return number;
}

Matrix * cut(const Matrix * matrix, const int row, const int column, const int width, const int height)
{
    Matrix * new = __new__(height, width);
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c ++)
        {
            new->data[r][c] = matrix->data[row + r][column + c];
        }
    }
    return new;
}

Matrix * cutfree(const Matrix * matrix, const int row, const int column, const int width, const int height, const double number)
{
    Matrix * new = __new__(height, width);
    // 有效部分
    const int valid_rows = (row + height <= matrix->row) ? height : matrix->row - row;
    const int valid_cols = (column + width <= matrix->column) ? width : matrix->column - column;

    for (int r = 0; r < valid_rows; r++) {
        for (int c = 0; c < valid_cols; c++) {
            new->data[r][c] = matrix->data[row + r][column + c];
        }
    }
    // 越界部分
    if (valid_cols < width) {
        for (int r = 0; r < valid_rows; r++) {
            for (int c = valid_cols; c < width; c++) {
                new->data[r][c] = number;
            }
        }
    }
    // 填补下边越界部分
    if (valid_rows < height) {
        for (int r = valid_rows; r < height; r++) {
            for (int c = 0; c < width; c++) {
                new->data[r][c] = number;
            }
        }
    }
    return new;
}

Matrix * concatR(const Matrix * matrix1, const Matrix * matrix2)
{
    Matrix * new = __new__(matrix1->row, matrix1->column + matrix2->column);
    for (int r = 0;r < matrix1->row;r++)
    {
        for (int c = 0;c < matrix1->column;c ++)
        {
            new->data[r][c] = matrix1->data[r][c];
        }
        for (int c = 0;c < matrix2->column;c ++)
        {
            new->data[r][c + matrix1->column] = matrix2->data[r][c];
        }
    }
    return new;
}

Matrix * concatC(const Matrix * matrix1, const Matrix * matrix2)
{
    Matrix * new = __new__(matrix1->row + matrix2->row, matrix1->column);
    for (int r = 0; r < matrix1->row; r++) {
        for (int c = 0; c < matrix1->column; c++) {
            new->data[r][c] = matrix1->data[r][c];
        }
    }
    for (int r = 0; r < matrix2->row; r++) {
        for (int c = 0; c < matrix2->column; c++) {
            new->data[r + matrix1->row][c] = matrix2->data[r][c];
        }
    }
    return new;
}

Matrix * resizeR(const Matrix * matrix, const int row, const int column, const double number)
{
    const int origin_size = matrix->column * matrix->row;
    const int new_size = row * column;
    Matrix * new = __new__(row, column);
    int counter = 0;
    if (origin_size >= new_size)
    {
        for (int r = 0;r < row;r++)
        {
            for (int c = 0;c < column;c ++)
            {
                new->data[r][c] = matrix->data[counter / matrix->column][counter % matrix->column];
                counter++;
            }
        }
    }else
    {
        for (int r = 0;r < matrix->row;r++)
        {
            for (int c = 0;c < matrix->column;c ++)
            {
                new->data[counter / column][counter % column] = matrix->data[r][c];
                counter++;
            }
        }
        while (counter < new_size) {
            new->data[counter / column][counter % column] = number;
            counter++;
        }
    }
    return new;
}

Matrix * resizeC(const Matrix * matrix, const int row, const int column, const double number)
{
    const int origin_size = matrix->column * matrix->row;
    const int new_size = row * column;
    Matrix *new = __new__(row, column);
    int counter = 0;
    if (origin_size >= new_size) {
        for (int c = 0; c < column; c ++) {
             for (int r = 0; r < row; r++){
                new->data[r][c] = matrix->data[counter % matrix->row][counter / matrix->row];
                counter++;
            }
        }
    } else {
        for (int c = 0; c < matrix->column; c ++) {
            for (int r = 0; r < matrix->row; r++) {
                new->data[counter % row][counter / row] = matrix->data[r][c];
                counter++;
            }
        }
        while (counter < new_size) {
            new->data[counter % row][counter / row] = number;
            counter++;
        }
    }
    return new;
}

void resizeRNoReturned(Matrix * matrix, const int row, const int column, const double number)
{
    const int origin_size = matrix->column * matrix->row;
    const int new_size = row * column;
    double ** newdata = (double **)malloc(sizeof(double*) * row);
    for(int r =0;r<row;r++)
        newdata[r] = (double*)malloc(sizeof(double) *column);
    int counter = 0;
    if (origin_size >= new_size)
    {
        for (int r = 0;r < row;r++)
        {
            for (int c = 0;c < column;c ++)
            {
                newdata[r][c] = matrix->data[counter / matrix->column][counter % matrix->column];
                counter++;
            }
        }
    }else
    {
        for (int r = 0;r < matrix->row;r++)
        {
            for (int c = 0;c < matrix->column;c ++)
            {
                newdata[counter / column][counter % column] = matrix->data[r][c];
                counter++;
            }
        }
        while (counter < new_size) {
            newdata[counter / column][counter % column] = number;
            counter++;
        }
    }
    __delete__data__(matrix->data, matrix->row);
    matrix->data = newdata;
    matrix->row = row;
    matrix->column = column;
}

void resizeCNoReturned(Matrix * matrix, const int row, const int column, const double number)
{
    const int origin_size = matrix->column * matrix->row;
    const int new_size = row * column;
    double ** newdata = (double **)malloc(sizeof(double*) * row);
    for(int r =0;r<row;r++)
        newdata[r] = (double*)malloc(sizeof(double) *column);
    int counter = 0;
    if (origin_size >= new_size) {
        for (int c = 0; c < column; c ++) {
            for (int r = 0; r < row; r++){
                newdata[r][c] = matrix->data[counter % matrix->row][counter / matrix->row];
                counter++;
            }
        }
    } else {
        for (int c = 0; c < matrix->column; c ++) {
            for (int r = 0; r < matrix->row; r++) {
                newdata[counter % row][counter / row] = matrix->data[r][c];
                counter++;
            }
        }
        while (counter < new_size) {
            newdata[counter % row][counter / row] = number;
            counter++;
        }
    }
    __delete__data__(matrix->data, matrix->row);
    matrix->data = newdata;
    matrix->row = row;
    matrix->column = column;
}

void reshapeNoReturned(Matrix * matrix, const int row, const int column)
{
    double **newdata = (double**)malloc(sizeof(double *) * row);
    int counter = 0;
    const int origin_row = matrix->row;
    for (int r=0;r < row;r ++)
    {
        newdata[r] = (double*)malloc(sizeof(double) * column);
        for(int c = 0;c <column;c ++)
        {
            newdata[r][c] = matrix->data[counter / matrix->column][counter % matrix->column];
            counter++;
        }
    }
    __delete__data__(matrix->data, origin_row);
    matrix->data = newdata;
    matrix->column = column;
    matrix->row = row;
}

Matrix * reshape(const Matrix * matrix, const int row, const int column)
{
    Matrix * new = __new__(row, column);
    int counter = 0;
    for (int r=0;r < row;r ++)
    {
        for(int c = 0;c <column;c ++)
        {
            new->data[r][c] = matrix->data[counter / matrix->column][counter % matrix->column];
            counter++;
        }
    }
    return new;
}

void setSeed(const int seed) {srand(seed);}

void * mathBasement1(const double ** matrix_array, const int mode, const int row, const int column, const bool returnArray)
{
    double ** new = NULL;

    #define MATCH(n, func, m, _c, _r)                                                  \
        n = (double**)malloc(sizeof(double*) * _r);                                    \
    do {                                                                               \
        for (int r = 0; r < _r; r++) {                                                 \
        n[r] = (double*)malloc(sizeof(double)*_c);                                     \
            for (int c = 0; c < _c; c++) {                                             \
                n[r][c] = func(m[r][c]);                                               \
            }                                                                          \
        }                                                                              \
    } while (0)                                                                        \

    switch (mode) {
    case 0:
        MATCH(new, acos, matrix_array, column, row);
        break;
    case 1:
        MATCH(new, asin, matrix_array, column, row);
        break;
    case 2:
        MATCH(new, atan, matrix_array, column, row);
        break;
    case 3:
        MATCH(new, cos, matrix_array, column, row);
        break;
    case 4:
        MATCH(new, sin, matrix_array, column, row);
        break;
    case 5:
        MATCH(new, tan, matrix_array, column, row);
        break;
    case 6:
        MATCH(new, cosh, matrix_array, column, row);
        break;
    case 7:
        MATCH(new, sinh, matrix_array, column, row);
        break;
    case 8:
        MATCH(new, tanh, matrix_array, column, row);
        break;
    case 9:
        MATCH(new, exp, matrix_array, column, row);
        break;
    case 10:
        MATCH(new, log, matrix_array, column, row);
        break;
    case 11:
        MATCH(new, log10, matrix_array, column, row);
        break;
    case 12:
        MATCH(new, sqrt, matrix_array, column, row);
        break;
    case 13:
        MATCH(new, ceil, matrix_array, column, row);
        break;
    case 14:
        MATCH(new, floor, matrix_array, column, row);
        break;
    case 15:
        MATCH(new, fabs, matrix_array, column, row);
        break;
    default:
        break;
    }
    #undef MATCH
    return returnArray ? (void*)new : __init__point__data__(row, column, new, NULL);
}

void * mathBasement2(const double ** matrix_array, const int mode, const double number,
    const int row, const int column, const bool returnArray)
{
    double ** new = NULL;

    #define MATCH2(m, func, n, _c, _r)                      \
        {new = (double**)malloc(sizeof(double*) * _r);      \
        for (int r = 0;r < _r;r++)                          \
        {new[r]  = (double*)malloc(sizeof(double)*_c);      \
            for (int c = 0;c < _c;c ++)                     \
            {                                               \
                n[r][c] = func(m[r][c], number);            \
            }                                               \
        }                                                   \
    }                                                       \

    switch (mode)
    {
        case 0: MATCH2(matrix_array, pow, new, column, row);break;
        case 1: MATCH2(matrix_array, atan2, new, column, row);break;
        default:break;
    }
    #undef MATCH2
    return returnArray ? (void*)new : __init__point__data__(row, column, new, NULL);
}

void * mathBasement2reverse(const double ** matrix_array, const int mode, const double number,
    const int row, const int column, const bool returnArray)
{
    double **new = NULL;

    #define MATCH3(m, func, n, _c, _r)                      \
        {new = (double**)malloc(sizeof(double*) * _r);      \
        for (int r = 0;r < _r;r++)                          \
        {new[r]  = (double*)malloc(sizeof(double)*_c);      \
            for (int c = 0;c < _c;c ++)                     \
            {                                               \
                n[r][c] = func(number, m[r][c]);            \
            }                                               \
        }                                                   \
    break;}                                                 \

    switch (mode)
    {
        case 0: MATCH3(matrix_array, pow, new, column, row);
        case 1: MATCH3(matrix_array, atan2, new, column, row);
        default:break;
    }
    #undef MATCH3
    return returnArray ? (void*)new : __init__point__data__(row, column, new, NULL);
}

Matrix * uniform(const double start, const double end, const int row, const int column, const int seed, bool use)
{
    if (use)
        srand(seed);
    Matrix * new = __new__(row, column);
    for (int r=0;r < row;r ++)
    {
        for(int c = 0;c < column;c ++)
        {
            new->data[r][c] = start + (end - start) * ((double)rand() / RAND_MAX);
        }
    }
    return new;
}

Matrix * normal(const double mu, const double sigma,
    const int row, const int column, const int start, const int end, const int seed, bool use)
{
    Matrix* new = __new__(row, column);

    return new;
}

Matrix * poisson(const double lambda, const int row, const int column, const int seed, bool use);