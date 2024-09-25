//
// Created by 20281 on 24-9-20.
//

#include "mp_linalg.h"

#ifdef MP_AUXILIARY_H
#else
    #include "mp_auxiliary.h"
#endif

#ifdef MP_CFG_H
#else
    #include "mp_cfg.h"
#endif

#ifdef MP_MATRIX_H
#else
    #include "mp_matrix.h"
#endif

#ifdef MP_BASE_H
#else
    #include "mp_base.h"
#endif

#ifdef _TIME_H_
#else
   #include <time.h>
#endif

#ifdef _MATH_H_
#else
    #include <math.h>
#endif

double ** transpose( int row,  int column,  double ** data)
{
    double ** new = allocateButNoNumbers(column, row);
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            new[c][r] = data[r][c];
        }
    }
    return new;
}

void exchangeR( int column, double ** data,  int row1,  int row2)
{
    if (row1 != row2)
    {
        double temp;
        for (int c= 0;c < column;c ++)
        {
            temp = data[row1][c];
            data[row1][c] = data[row2][c];
            data[row2][c] = temp;
        }
    }
}

void multiplyR( int row,  int column, double **data,  double size)
{
    for (int c = 0;c < column;c ++)
        data[row][c] *= size;
}


void addR( int column, double **data,  int row1,  int row2,  double size)
{
    for (int c = 0;c < column;c ++)
        data[row1][c] += data[row2][c] * size;
}

void exchangeC( int row, double ** data,  int column1,  int column2)
{
    if (column1 != column2)
    {
        double temp;
        for (int r= 0;r < row;r ++)
        {
            temp = data[r][column1];
            data[r][column1] = data[r][column2];
            data[r][column2] = temp;
        }
    }
}

void multiplyC( int row,  int column, double **data,  double size)
{
    for (int r = 0;r < row;r ++)
        data[r][column] *= size;
}

void addC( int row, double **data,  int column1,  int column2,  double size)
{
    for (int r = 0;r < row;r++)
        data[r][column1] += data[r][column2] * size;
}

double ** addNumber( int row,  int column,  double **data,  double number)
{
    double ** new = (double **)malloc(sizeof(double *) * row);
    for (int r = 0;r < row;r++)
    {
        new[r] = (double *)malloc(sizeof(double) * column);
        for (int c = 0;c < column;c ++)
        {
            new[r][c] = data[r][c] + number;
        }
    }
    return new;
}

double ** addMatrix( int row,  int column,  double **data1,  double **data2)
{
    double ** new = (double **)malloc(sizeof(double *) * row);
    for (int r = 0;r < row;r++)
    {
        new[r] = (double *)malloc(sizeof(double) * column);
        for (int c = 0;c < column;c ++)
        {
            new[r][c] = data1[r][c] + data2[r][c];
        }
    }
    return new;
}

void addNumberNoReturned( int row,  int column, double **data,  double number)
{
    for (int r = 0;r < row;r++)
    {
        for (int c = 0;c < column;c ++)
        {
            data[r][c] += number;
        }
    }
}

void addMatrixNoReturned( int row,  int column, double **data1,  double **data2)
{
    for (int r = 0;r < row;r++)
    {
        for (int c = 0;c < column;c ++)
        {
            data1[r][c] += data2[r][c];
        }
    }
}

double ** minusMatrix( int row,  int column,  double **data1,  double **data2)
{
    double ** new = (double **)malloc(sizeof(double *) * row);
    for (int r = 0;r < row;r++)
    {
        new[r] = (double *)malloc(sizeof(double) * column);
        for (int c = 0;c < column;c ++)
        {
            new[r][c] = data1[r][c] - data2[r][c];
        }
    }
    return new;
}

void minusMatrixNoReturned( int row,  int column, double **data1,  double **data2)
{
    for (int r = 0;r < row;r++)
    {
        for (int c = 0;c < column;c ++)
        {
            data1[r][c] -= data2[r][c];
        }
    }
}

double ** matmul( int row,  int column,  double **data1,  double **data2, int column2)
{
    double ** new = (double **)malloc(sizeof(double*) * row);
    for (int r = 0; r < row; r++) {
        new[r] = (double *) calloc(column2, sizeof (double ));
        for (int c = 0; c < column2;c ++) {
            for (int k = 0; k < column;k++) {
                new[r][c] += data1[r][k] * data2[k][c];
            }
        }
    }
    return new;
}

void multiplyMatrixNoReturned( int row,  int column, double **data1,  double **data2)
{
    for (int r = 0;r <row;r++)
    {
        for (int c =0;c<column;c ++)
        {
            data1[r][c] *= data2[r][c];
        }
    }
}

double ** multiplyMatrix( int row,  int column,  double **data1,  double **data2)
{
    double ** new = (double**)malloc(sizeof(double *) * row);
    for (int r = 0;r <row;r++)
    {
        new[r] = (double*)malloc(sizeof(double ) * column);
        for (int c =0;c<column;c ++)
        {
            new[r][c] = data1[r][c] * data2[r][c];
        }
    }
    return new;
}

void multiplyNumberNoReturned( int row,  int column, double **data,  double number)
{
    for(int r=0;r < row;r ++)
    {
        for (int c = 0;c < column;c ++)
        {
            data[r][c] *= number;
        }
    }
}

double ** multiplyNumber( int row,  int column,  double **data,  double number)
{
    double ** new = (double**)malloc(sizeof(double*) *row);
    for (int r = 0;r < row;r++)
    {
        new[r] = (double*)malloc(sizeof(double) * column);
        for (int c =0;c< column;c ++)
        {
            new[r][c] = data[r][c] * number;
        }
    }
    return new;
}

double ** kronecker( int row1,  int column1,  double **data1,  int row2,  int column2,  double **data2)
{
    double **new = (double **)malloc(sizeof(double *) * (row1 * row2));
    for (int i = 0; i < row1; ++i) {
        for (int k = 0; k < row2; ++k) {
            new[i * row2 + k] = (double *)malloc(sizeof(double) * (column1 * column2));
            for (int j = 0; j < column1; ++j) {
                for (int l = 0; l < column2; ++l) {
                    new[i * row2 + k][j * column2 + l] = data1[i][j] * data2[k][l];
                }
            }
        }
    }
    return new;
}

double ** divide( int row,  int column,  double **data,  double number)
{
    double ** new = (double **)malloc(sizeof(double*) * row);
    for (int r = 0;r <row;r++)
    {
        new[r] = (double *) malloc(sizeof (double ) * column);
        for (int c =0;c<column;c ++)
        {
            new[r][c] = data[r][c] / number;
        }
    }
    return new;
}

void divideNoReturned( int row,  int column, double **data,  double number)
{
    for (int r = 0;r <row;r++)
    {
        for (int c =0;c < column;c ++)
        {
            data[r][c] /= number;
        }
    }
}

double trace( int row,  int column,  double **data)
{
    int n = row < column ? row : column;
    double sum = 0.;
    for (int r = 0;r < n;r++)
        sum += data[r][r];
    return sum;
}

double det( int row,  int column,  double **data)
{
    double detValue = 1;
    int n = row;
    double ** matrixcpy = deepcopy(row, column, data);

    for (int i = 0; i < n; i++) {
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(matrixcpy[k][i]) > fabs(matrixcpy[max_row][i])) {
                max_row = k;
            }
        }
        if (matrixcpy[max_row][i] == 0) {
            __delete__data__(matrixcpy, row);
            return 0;
        }

        if (max_row != i) {
            double *temp = matrixcpy[max_row];
            matrixcpy[max_row] = matrixcpy[i];
            matrixcpy[i] = temp;
            detValue = -detValue;
        }
        detValue *= matrixcpy[i][i];
        for (int k = i + 1; k < n; k++) {
            double factor = matrixcpy[k][i] / matrixcpy[i][i];
            for (int j = i; j < n; j++) {
                matrixcpy[k][j] -= factor * matrixcpy[i][j];
            }
        }
    }
    __delete__data__(matrixcpy, row);
    return detValue;
}

double ** E( int n)
{
    double**new = (double **)calloc(n, sizeof (double *));
    for (int r = 0;r < n;r++)
    {
        new[r] = (double *) calloc(n, sizeof (double ));
        new[r][r] = 1.;
    }
    return new;
}



double ** cofactor( int row,  int column,  double ** data,  int prow,  int pcolumn)
{
    double **new = (double **)malloc(sizeof(double *) * (row - 1));
    int i = 0, j = 0;
    for (int r = 0; r < row; r++) {
        new[r] = (double*)malloc(sizeof(double) *(column - 1));
        for (int c = 0; c < column; c ++) {
            if (r != prow && c != pcolumn) {
                new[i][j++] = data[r][c];
                if (j == column - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
    return new;
}

double ** adjugate( int row,  int column,  double ** data)
{
    int n = row;
    double ** new = allocateButNoNumbers(row, column);
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c ++)
        {
            double ** cof = cofactor(n, n, data, r, c);  // [n - 1, n - 1]

            new[c][r] = pow(-1, r + c) * det(n - 1, n - 1, cof);
            __delete__data__(cof, n - 1);
        }
    }
    return new;
}

double ** inverse( int row,  int column,  double ** data, double det)
{
    int n = row;
    double ** new = (double**)malloc(sizeof(double *) * row);
    double ** adj = adjugate(row, column, data);
    for (int r = 0; r < n; r++) {
        new[r] = (double *) malloc(sizeof (double ) *n) ;
        for (int c = 0; c< n;  c ++) {
            new[r][c] = adj[r][c] / det;
        }
    }
    __delete__data__(adj, row);
    return new;
}

double ** rref( int row,  int column,  double ** data)
{
    double ** new = (double **)malloc(sizeof(double *) *row);
    for (int r = 0;r < row;r ++)
    {
        new[r] = (double *)malloc(sizeof(double) * column);
        for (int c = 0;c < column;c ++)
        {
            new[r][c] = data[r][c];
        }
    }
    int lead = 0;
    for (int r = 0; r < row; r++) {
        if (lead >= column) {
            return new;
        }

        int i = r;
        while (fabs(new[i][lead]) < DROUND) { // 这里不能设置!=0，因为计算精度问题
            i++;
            if (i == row) {
                i = r;
                lead++;
                if (lead == column) {
                    return new;
                }
            }
        }

        if (i != r) {
            double temp = 0.;
            for (int c= 0;c< column; c ++) {
                temp = new[i][c];
                new[i][c] = new[r][c];
                new[r][c] = temp;
            }
        }

        double lv = new[r][lead];
        for (int c= 0; c < column; c ++) {
            new[r][c] /= lv;
        }

        for (int r1= 0; r1 < row; r1++) {
            if (r1!= r) {
                lv = new[r1][lead];
                for (int c = 0; c< column; c ++) {
                    new[r1][c] -= lv * new[r][c];
                }
            }
        }
        lead++;
    }
    return new;
}

int rank( int row,  int column,  double ** data)
{
    double  **new = rref(row, column, data);
    int counter = 0;
    int n = row > column ?column : row;
    for (int r = 0; r < n; r++) {
        int isZeroRow = 1;
        for (int c = 0; c < column; c ++) {
            if (fabs(new[r][c]) > DROUND)
            {
                isZeroRow = 0;
                break;
            }
        }
        if (!isZeroRow)
            counter++;
    }
    __delete__data__(new, row);
    return counter;
}

double norm_negainf(int row, int column, double ** data)
{
    double * number = (double*)calloc(row, sizeof(double));
    for(int r=  0;r < row;r ++)
    {
        for(int c = 0;c < column;c ++)
        {
            number[r] += fabs(data[r][c]);
        }
    }
    double value = number[0 ];
    for (int r = 1;r < row;r ++)
    {
        if (value > number[r])
            value = number[r];
    }
    free(number);
    return value;
}

double norm_inf(int row, int column, double ** data)
{
    double * number = (double*)calloc(row, sizeof(double));
    double value = 0.;
    for(int r=  0;r < row;r ++)
    {
        for(int c = 0;c < column;c ++)
        {
            number[r] += fabs(data[r][c]);
        }
        if (number[r] > value)
            value = number[r];
    }
    free(number);
    return value;
}

double * norm_zero(int row, int column, double ** data, int dim)
{
    double * number = NULL;
    double value = .0;
    switch (dim)
    {
    case 0:
        {
            number = (double * )calloc(row, sizeof(double) );
            for(int r = 0;r < row;r ++)
            {
                for (int c = 0;c < column;c ++)
                {
                    value = fabs(data[r][c]);
                    if (value < DROUND)
                        number[r]++;
                }
            }
            break;
        }
    case 1:
        {
            number = (double *)calloc(column, sizeof(double));
            for (int c = 0;c < column ;c ++)
            {
                for (int r =0;r < row;r++)
                {
                    value = fabs(data[r][c]);
                    if (value < DROUND)
                        number[c]++;
                }
            }
            break;
        }
    default:
        {
            number = (double *)calloc(1, sizeof(double));
            for (int r= 0;r < row;r ++)
            {
                for(int c=0;c < column;c ++)
                {
                    value = fabs(data[r][c]);
                    if (value < DROUND)
                        number[0]++;
                }
            }
            break;
        }
    }
    return number;
}

double norm_one(int row, int column, double ** data)
{
    double * number = (double *)calloc(column, sizeof(double));
    double value = 0.;
    for (int c=0;c < column;c ++)
    {
        for(int r=0;r < row;r++)
        {
            number[c] += fabs(data[r][c]);
        }
        if (value < number[c])
            value = number[c];
    }
    free(number);
    return value;
}

double * norm(int row, int column, double ** data, int n, int dim)
{
    double * number = NULL;
    switch (dim)
    {
    case 0:
        {
            number = (double *)calloc(row, sizeof(double));
            for (int r = 0;r <row;r ++)
            {
                for(int c= 0;c < column;c ++)
                {
                    number[r] += pow(fabs(data[r][c]), n);
                }
                number[r] = pow(number[r], 1. / n);
            }
            break;
        }
    case 1:
        {
            number = (double *)calloc(column, sizeof(double));
            for (int c=0;c<column;c ++)
            {
                for(int r= 0;r <row;r ++)
                {
                    number[c] += pow(fabs(data[r][c]), n);
                }
                number[c] = pow(number[c], 1. / n);
            }
            break;
        }
    default:
        {
            number = (double *)calloc(1, sizeof(double));
            for (int r = 0;r < row;r ++)
            {
                for(int c = 0;c <column;c ++)
                {
                    number[0] += pow(fabs(data[r][c]), n);
                }
                number[0] = pow(number[0], 1. / n);
            }
            break;
        }
    }
    return number;
}

MultiDatas2 qr(int row, int column, double** data) {
    double ** Q = (double**)malloc(row * sizeof(double*));
    double ** R = (double**)malloc(column * sizeof(double*));

    for (int i = 0; i < row; ++i) {
        Q[i] = (double*)calloc(column, sizeof(double));
    }
    for (int i = 0; i < column; ++i) {
        R[i] = (double*)calloc(column, sizeof(double));
    }

    for (int j = 0; j < column; ++j) {
        for (int i = 0; i < row; ++i) {
            Q[i][j] = data[i][j];
        }

        for (int k = 0; k < j; ++k) {
            double dotProduct = 0.0;
            for (int i = 0; i < row; ++i) {
                dotProduct += Q[i][j] * Q[i][k];
            }

            R[k][j] = dotProduct;
            for (int i = 0; i < row; ++i) {
                Q[i][j] -= dotProduct * Q[i][k];
            }
        }
        R[j][j] = 0.0;
        for (int i = 0; i < row; ++i) {
            R[j][j] += Q[i][j] * Q[i][j];
        }
        R[j][j] = sqrt(R[j][j]);
        for (int i = 0; i < row; ++i) {
            Q[i][j] /= R[j][j];
        }
    }

    return (MultiDatas2){Q, R};
}

double ** divrev(int row, int column, double **data, double number){
    double ** new = (double **) malloc(row * sizeof (double *));
    for(int r = 0;r < row;r++){
        new[r] = (double *) malloc(sizeof (double ) * column);
        for (int c = 0;c < column;c ++){
            new[r][c] = number / new[r][c];
        }
    }
    return new;
}

// 获取关于对角线对称的随机数矩阵，sub为true表示副对角线对称
double ** diagonal(int row, int column, double start, double end, bool sub, int seed, bool use){
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    double value;
    if(!sub) {
        for (int r = 0; r < row; r++) {
            for (int c = r; c < column; c ++) {
                value = start + ((double) rand_func() / (double) MAXRAND) * (end - start);
                new[r][c] = value;
                new[c][r] = value;
            }
        }
        return new;
    }
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++) {
            value = start + ((double)rand_func() / (double)MAXRAND) * (end - start);
            new[r][c] = value;
            new[column - c - 1][row - r - 1] = value;
        }
    }
    return new;
}

void fill_diagonal(int row, int column, double ** data, double number){
    int n = column < row ? column : row;
    for(int r = 0;r < n;r ++)
        data[r][r] = number;
}

