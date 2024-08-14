//
// Created by 20281 on 2024/7/6.
//

#include "matply.h"
#include "Auxiliary.h"

static  char * ROUND = "%.5lf\t";
static double DROUND = 1e-10;

void set_visible_round( char* new_round)
{
    ROUND = new_round;
}
char * get_visible_round()
{
    return ROUND;
}
void set_round( double number)
{
    DROUND = number;
}
 double get_round()
{
    return DROUND;
}

__attribute__((visibility("default"))) const double PI = M_PI;
__attribute__((visibility("default"))) const double e = M_E;
__attribute__((visibility("default"))) const double _nan = NAN;
__attribute__((visibility("default"))) const double inf = INFINITY;

///////////////////////////////////////////////////////////////////////////////////////

void initMp(Matrix * matrix)
{
    if (matrix && __Mp.instances == 0)
    {
        MatrixLinked *matrix_linked = (MatrixLinked *)malloc(sizeof(MatrixLinked));
        matrix_linked->matrix = matrix;
        matrix_linked->next = NULL;
        __Mp.matrix_linked = matrix_linked;
    }
}

void addToMp(Matrix * matrix)
{
    MatrixLinked *matrix_linked = (MatrixLinked *)malloc(sizeof(MatrixLinked));
    matrix_linked->matrix = matrix;
    matrix_linked->next = NULL;
    if (__Mp.instances == 0)
        __Mp.matrix_linked = matrix_linked;
    else
    {
        MatrixLinked *current = __Mp.matrix_linked;
        while (current->next)
            current = current->next;
        current->next = matrix_linked;
    }
    __Mp.instances++;
}

void freeMp(bool visible)
{
    MatrixLinked * current = __Mp.matrix_linked;
    MatrixLinked * temp = NULL;
    if (visible)
    {
        while (current)
        {
            temp = current;
            current = current->next;
            __delete__(temp->matrix);
            printf("Free Memory in location : %p\n", (void *)temp);
            free(temp);
        }
    }else
    {
        while (current)
        {
            temp = current;
            current = current->next;
            __delete__(temp->matrix);
            free(temp);
        }
    }
    __Mp.instances = 0;
}

int getInstances() {return __Mp.instances;}
///////////////////////////////////////////////////////////////////////////////////////

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
    new->spc = (Spc *) malloc(sizeof (Spc));;
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
    new->spc = (Spc *) malloc(sizeof (Spc));;
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

double ** filled( int row,  int column,  double number)
{
    double ** new = (double **)malloc(sizeof(double *) * row);
    for (int r = 0;r < row;r++)
    {
        new[r] = (double * )malloc(sizeof(double ) * column);
        for (int c = 0;c < column;c ++)
            new[r][c] = number;
    }
    return new;
}

double ** zeros( int row,  int column){return filled(row, column, 0.);}
double ** ones( int row,  int column){return filled(row, column, 1.);}

void VisibleMatrixSpc( Matrix * matrix)
{
    printf("Matrix identityMatrix == %s\n", matrix->spc->identityMatrix ? "true" : "false");
    printf("Matrix upperTriangularMatrix == %s\n", matrix->spc->upperTriangularMatrix ? "true" : "false");
    printf("Matrix lowerTriangularMatrix == %s\n", matrix->spc->lowerTriangularMatrix ? "true" : "false");
    printf("Matrix singularMatrix == %s\n", matrix->spc->singularMatrix ? "true" : "false");
    printf("Matrix subDiagonalMatrix == %s\n", matrix->spc->subDiagonalMatrix ? "true" : "false");
    printf("Matrix principalDiagonalMatrix == %s\n", matrix->spc->principalDiagonalMatrix ? "true" : "false");
}

double * row_( int row,  int column,  double ** data)
{
    double *new = (double *)malloc(column * sizeof(double));
    for (int c = 0;c < column;c ++)
        new[c] = data[row][c];
    return new;
}

double * column_( int row,  int column,  double ** data)
{
    double *new = (double*)malloc(row *sizeof(double));
    for (int r = 0;r < row;r++)
        new[r] = data[r][column];
    return new;
}

double at( int row,  int column,  double ** data){return data[row][column];}

bool isSquare( Matrix * matrix) {return matrix->column == matrix->row;}

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
        double temp = 0.;
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
        double temp = 0.;
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

double ** arrange( double start,  int row,  int column)
{
    double ** new = (double **)malloc(sizeof(double *) * row);
    double counter = start;
    for (int r = 0;r < row;r++)
    {
        new[r] = (double *)malloc(sizeof(double) * column);
        for(int c = 0;c < column;c ++)
        {
            new[r][c] = counter++;
        }
    }
    return new;
}

double ** linspace( double start,  double end,  int row,  int column,  bool keep)
{
     int counts = row * column;
     double step = keep ? (end - start) / (counts - 1) : (end - start) / counts;
    double ** new = (double **)malloc(sizeof(double *) * row);
    double value = start;
    for (int r = 0; r < row; r++) {
        new[r] = (double *) malloc(sizeof (double ) * column);
        for (int c = 0; c< column; c ++) {
            new[r][c] = value;
            value += step;
        }
    }
    if (keep)
        new[row - 1][column - 1] = end;
    return new;
}

double trace( int row,  int column,  double **data)
{
     int n = row < column ? row : column;
    double sum = 0.;
    for (int r = 0;r < n;r++)
        sum += data[r][r];
    return sum;
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

double ** deepcopy( int row,  int column,  double **data)
{
    double ** new = (double**)malloc(sizeof(double*)*row);
    for (int r = 0; r <row; r++) {
        new[r] = (double*)malloc(sizeof(double) * column);
        memcpy(new[r], data[r],  column * sizeof(double));
    }
    return new;
}

bool ** compare( int row,  int column,  double **data1,  double ** data2,  int mode)
{

    #define COMPARE_OP(op, d1, d2, col, ro, n) {\
        for (int r = 0;r < ro;r++)\
        {\
            n[r] = (bool *)malloc(sizeof(bool) * col);\
            for(int c=0;c < col;c ++)\
            {\
                n[r][c] = (d1[r][c] op d2[r][c]) ? true : false;\
            }\
        }\
    }\

    bool **new = (bool **)malloc(sizeof(bool *) * row);

    switch (mode) {
    case 1:
        COMPARE_OP(>, data1, data2, column, row, new);
        break;
    case 2:
        COMPARE_OP(<, data1, data2, column, row, new);
        break;
    case 3:
        COMPARE_OP(<=, data1, data2, column, row, new);
        break;
    case 4:
        COMPARE_OP(>=, data1, data2, column, row, new);
        break;
    default:
        COMPARE_OP(==, data1, data2, column, row, new);
        break;
    }
    #undef COMPARE_OP
    return new;
}

double * sum( int row,  int column,  double **data,  int dim)
{
    double *number = NULL;
    switch (dim) {
    case 0:
        {
            number = (double *)calloc(row, sizeof(double));
            for (int r = 0; r < row; r++) {
                for (int c = 0; c < column; c++) {
                    number[r] += data[r][c];
                }
            }
            break;
        }
    case 1:
        {
            number = (double *)calloc(column, sizeof(double));
            for (int c = 0; c < column; c++) {
                for (int r = 0; r < row; r++) {
                    number[c] += data[r][c];
                }
            }
            break;
        }
    default:
        {
            number = (double *)malloc(sizeof(double));
            *number = 0.0;
            for (int r = 0; r < row; r++) {
                for (int c = 0; c < column; c++) {
                    *number += data[r][c];
                }
            }
            break;
        }
    }
    return number;
}

double * mean( int row,  int column,  double **data,  int dim)
{
    double *number = NULL;
    switch (dim)
    {
    case 0:
        {
            number = sum(row, column, data, 0);
            for (int r=0;r < row;r++)
                number[r] /=  column;
            break;
        }
    case 1:
        {
            number = sum(row, column, data, 1);
            for (int c = 0;c < column;c ++)
                number[c] /= row;
            break;
        }
    default:
        {
            number = sum(row, column, data, -1);
            *number = *number / (row * column);
            break;
        }
    }
    return number;
}

double * min( int row,  int column,  double **data,  int dim)
{
    double * number = NULL;
    switch (dim)
    {
    case 0:
        {
            number = (double *)malloc(sizeof(double) * row);
            for (int r = 0; r < row; r++) {
                number[r] = getMin(data[r], column);
            }
            break;
        }
    case 1:
        {
            number = (double *)malloc(sizeof(double) * column);
            for (int c = 0; c < column; c++) {
                double min = data[0][c];
                for (int r = 1; r < row; r++) {
                    if (data[r][c] < min) {
                        min = data[r][c];
                    }
                }
                number[c] = min;
            }
            break;
        }
    default:
        {
            number = (double *)malloc(sizeof(double));
            *number = data[0][0];
            for (int r = 0; r < row; r++) {
                for (int c = 0; c < column; c++) {
                    if (data[r][c] < *number) {
                        *number = data[r][c];
                    }
                }
            }
            break;
        }
    }
    return number;
}

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

double * max( int row,  int column,  double **data,  int dim)
{
    double * number = NULL;
    switch (dim)
    {
    case 0:
        {
            number = (double*)malloc(sizeof(double) * row);
            for (int r=0;r < row;r ++)
            {
                number[r] = getMax(data[r], column);
            }
            break;
        }
    case 1:
        {
            number = (double*)malloc(sizeof(double) * column);
            for (int c = 0; c < column; c++) {
                double max = data[0][c];
                for (int r = 1; r < row; r++) {
                    if (data[r][c] > max) {
                        max = data[r][c];
                    }
                }
                number[c] = max;
            }
            break;
        }
    default:
        {
            number = (double *)malloc(sizeof(double));
            *number = data[0][0];
            for(int r=0;r < row;r++)
            {
                for (int c = 0;c < column;c ++)
                {
                    if(data[r][c] > *number)
                        *number = data[r][c];
                }
            }
            break;
        }
    }
    return number;
}

double** cut( int row,  int column,  double ** data,  int prow,  int pcolumn,  int width,  int height)
{
    double ** new = (double ** )malloc(sizeof(double *) *height);
    for (int r = 0; r < height; r++)
    {
        new[r] = (double * )malloc(sizeof(double) * width);
        for (int c = 0; c < width; c ++)
        {
            new[r][c] = data[prow + r][pcolumn + c];
        }
    }
    return new;
}

double ** cutfree( int row,  int column,  double ** data,
     int prow,  int pcolumn,  int width,  int height,  double number)
{
    double ** new = (double **)malloc(sizeof(double *) * height);
    for (int r = 0;r < row;r++)
        new[r] = (double *)malloc(sizeof(double) *width);
    // 有效部分
     int valid_rows = (prow + height <= row) ? height : row - prow;
     int valid_cols = (pcolumn + width <=  column) ? width : column - pcolumn;

    for (int r = 0; r < valid_rows; r++) {
        for (int c = 0; c < valid_cols; c ++) {
            new[r][c] = data[prow + r][pcolumn + c];
        }
    }
    // 越界部分
    if (valid_cols < width) {
        for (int r = 0; r < valid_rows; r++) {
            for (int c = valid_cols; c < width; c ++) {
                new[r][c] = number;
            }
        }
    }
    // 填补下边越界部分
    if (valid_rows < height) {
        for (int r = valid_rows; r < height; r++) {
            for (int c = 0; c < width; c ++) {
                new[r][c] = number;
            }
        }
    }
    return new;
}

double ** concatR( int row,  int column1,  int column2,  double ** data1,  double ** data2)
{
    double ** new = (double**)malloc(sizeof(double*) *row);
    for (int r = 0;r < row;r++)
    {
        new[r] = (double *)malloc(sizeof(double) * (column2 + column1));
        for (int c = 0;c < column1;c ++)
        {
            new[r][c] = data1[r][c];
        }
        for (int c = 0;c < column2;c ++)
        {
            new[r][c + column1] = data2[r][c];
        }
    }
    return new;
}

double ** concatC( int row1,  int row2,  int column,  double ** data1,  double ** data2)
{
    double ** new = (double**)malloc(sizeof(double*) *(row1 + row2));
    for (int r = 0; r < row1; r++) {
        new[r] = (double *) malloc(sizeof (double )* column);
        for (int c = 0; c < column; c ++) {
            new[r][c] =data1[r][c];
        }
    }
    int rownow;
    for (int r = 0; r < row2; r++) {
        rownow = r + row1;
        new[rownow] = (double *) malloc(sizeof (double )* column);
        for (int c = 0; c < column; c ++) {
            new[rownow][c] = data2[r][c];
        }
    }
    return new;
}

double ** resizeR( int row,  int column,  double ** data,  int origin_row,  int origin_column,  double number)
{
     int origin_size = origin_column * origin_row;
     int new_size = row * column;
    double ** new = (double **)malloc(sizeof(double*) * row);
    for (int r = 0;r < row;r++)
        new[r] = (double *)malloc(sizeof(double) * column);
    int counter = 0;
    if (origin_size >= new_size)
    {
        for (int r = 0;r < row;r++)
        {
            for (int c = 0;c < column;c ++)
            {
                new[r][c] = data[counter / origin_column][counter % origin_column];
                counter++;
            }
        }
    }else
    {
        for (int r = 0;r < origin_row;r++)
        {
            for (int c = 0;c < origin_column;c ++)
            {
                new[counter / column][counter % column] = data[r][c];
                counter++;
            }
        }
        while (counter < new_size) {
            new[counter / column][counter % column] = number;
            counter++;
        }
    }
    return new;
}

double ** resizeC( int row,  int column,  double ** data,  int origin_row,  int origin_column,  double number)
{
     int origin_size = origin_column * origin_row;
     int new_size = row * column;
    double ** new = (double **)malloc(sizeof(double*) * row);
    for (int r = 0;r < row;r++)
        new[r] = (double *)malloc(sizeof(double) * column);
    int counter = 0;
    if (origin_size >= new_size) {
        for (int c = 0; c < column; c ++) {
             for (int r = 0; r < row; r++){
                new[r][c] = data[counter % origin_row][counter / origin_row];
                counter++;
            }
        }
    } else {
        for (int c = 0; c < origin_column; c ++) {
            for (int r = 0; r < origin_row; r++) {
                new[counter % row][counter / row] = data[r][c];
                counter++;
            }
        }
        while (counter < new_size) {
            new[counter % row][counter / row] = number;
            counter++;
        }
    }
    return new;
}

double ** reshape( int row,  int column,  double ** data,  int origin_column)
{
    double ** new = (double **)malloc(sizeof(double *) * row);
    int counter = 0;
    for (int r=0;r < row;r ++)
    {
        new[r] = (double*)malloc(sizeof(double) * column);
        for(int c = 0;c <column;c ++)
        {
            new[r][c] = data[counter / origin_column][counter % origin_column];
            counter++;
        }
    }
    return new;
}

void setSeed( int seed) {
    seed > 0 ? srand(seed):  initialize_random_seed();;
}

double ** mathBasement1( int row,  int column,  double ** data,  int mode)
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
        MATCH(new, acos, data, column, row);
        break;
    case 1:
        MATCH(new, asin, data, column, row);
        break;
    case 2:
        MATCH(new, atan, data, column, row);
        break;
    case 3:
        MATCH(new, cos, data, column, row);
        break;
    case 4:
        MATCH(new, sin, data, column, row);
        break;
    case 5:
        MATCH(new, tan, data, column, row);
        break;
    case 6:
        MATCH(new, cosh, data, column, row);
        break;
    case 7:
        MATCH(new, sinh, data, column, row);
        break;
    case 8:
        MATCH(new, tanh, data, column, row);
        break;
    case 9:
        MATCH(new, exp, data, column, row);
        break;
    case 10:
        MATCH(new, log, data, column, row);
        break;
    case 11:
        MATCH(new, log10, data, column, row);
        break;
    case 12:
        MATCH(new, sqrt, data, column, row);
        break;
    case 13:
        MATCH(new, ceil, data, column, row);
        break;
    case 14:
        MATCH(new, floor, data, column, row);
        break;
    case 15:
        MATCH(new, fabs, data, column, row);
        break;
    default:
        break;
    }
    #undef MATCH
    return new;
}

double ** mathBasement2( int row,  int column,  double ** data,  int mode,  double number)
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
        case 0: MATCH2(data, pow, new, column, row);break;
        case 1: MATCH2(data, atan2, new, column, row);break;
        default:break;
    }
    #undef MATCH2
    return new;
}

double ** mathBasement2reverse( int row,  int column,  double ** data,  int mode,  double number)
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
        case 0: MATCH3(data, pow, new, column, row);
        case 1: MATCH3(data, atan2, new, column, row);
        default:break;
    }
    #undef MATCH3
    return new;
}

double ** sigmoid( int row,  int column,  double ** data)
{
    double ** new = (double **)malloc(sizeof(double *) * row);
    for (int r=0;r < row;r ++)
    {
        new[r] = (double *)malloc(sizeof(double) * column);
        for (int c = 0;c < column;c ++)
        {
            new[r][c] = 1.0 / (1.0 + exp(-data[r][c]));
        }
    }
    return new;
}

double ** softmax( int row,  int column,  double ** data,  int dim,  double mask_nan,  double mask_inf,  double mask_neginf)
{
    double ** new = (double **)malloc(sizeof(double *) * row);
    double dat = 0.;
    for (int r = 0;r < row;r ++)
    {
        new[r] = (double *)malloc(sizeof(double) * column);
        for (int c = 0;c <column;c ++)
        {
            dat = data[r][c ];
            if (!isnan(dat) && !isinf(dat))
                new[r][c ] = exp(dat);
            else
            {
                if (isnan(dat))
                    new[r][c] = exp(mask_nan);
                else if (isinf(dat) && dat > 0)
                    new[r][c] = exp(mask_inf);
                else
                    new[r][c] = exp(mask_neginf);
            }
        }
    }

    switch (dim)
    {
    case 0:
        {
            double * sums = sum(row, column, new, 0);
            for(int r=0;r < row;r ++)
            {
                for (int c = 0;c < column;c ++)
                {
                    new[r][c] /= sums[r];
                }
            }
            free(sums);
            break;
        }
    case 1:
        {
            double * sums = sum(row, column, new, 1);
            for(int r=0;r < row;r ++)
            {
                for (int c = 0;c < column;c ++)
                {
                    new[r][c] /= sums[c];
                }
            }
            free(sums);
            break;
        }
    default:
        {
            double * sums = sum(row, column, new, -1);
            for(int r=0;r < row;r ++)
            {
                for (int c = 0;c < column;c ++)
                {
                    new[r][c] /= *sums;
                }
            }
            free(sums);
            break;
        }
    }
    return new;
}

void shuffle(  int row,  int column, double ** data)
{
    srand(time(NULL));
    int ri = 0, rj = 0, temp = 0;
    for (int r = row - 1; r > 0; r--) {
        for (int c = column - 1; c > 0; c--) {
            ri = rand() % (r + 1);
            rj = rand() % (c + 1);
            temp = data[r][c];
            data[r][c] = data[ri][rj];
            data[ri][rj] = temp;
        }
    }
}

int __compare(const void* a, const void* b) {
    double diff = *(double*)a - *(double*)b;
    return (diff > 0) - (diff < 0);
}

int __reverse_compare(const void* a, const void* b) {
     double diff = *(double*)b - *(double*)a;
    return (diff > 0) - (diff < 0);
}

void sortNoReturned( int row,  int column, double ** data,  bool reverse,  int dim,  double mask_nan)
{
    for (int r = 0;r < row;r ++)
    {
        for(int c = 0;c < column;c ++)
        {
            if (isnan(data[r][c]))
                data[r][c] = mask_nan;
        }
    }
    switch (dim) {
        case 0:
            {
                for (int r = 0; r < row;r++) {
                    if (reverse) {
                        qsort(data[r], column, sizeof(double), __reverse_compare);
                    } else {
                        qsort(data[r], column, sizeof(double), __compare);
                    }
                }
                break;
            }
        case 1:
            {
                for (int c = 0; c < column;c ++) {
                    double* col = (double*)malloc(row * sizeof(double));
                    for (int r = 0; r < row;r++) {
                        col[r] = data[r][c];
                    }
                    if (reverse) {
                        qsort(col, row, sizeof(double), __reverse_compare);
                    } else {
                        qsort(col, row, sizeof(double), __compare);
                    }
                    for (int r = 0; r< row;r++) {
                        data[r][c] = col[r];
                    }
                    free(col);
                }
                break;
            }
        default:
            {
                double* flat = (double*)malloc(row * column * sizeof(double));
                int index = 0;
                for (int r= 0; r < row; r++) {
                    for (int c = 0; c < column; c ++) {
                        flat[index++] = data[r][c];
                    }
                }
                if (reverse) {
                    qsort(flat, row * column, sizeof(double), __reverse_compare);
                } else {
                    qsort(flat, row * column, sizeof(double), __compare);
                }
                index = 0;
                for (int r = 0; r < row; r ++) {
                    for (int c= 0; c < column;c++) {
                        data[r][c] = flat[index++];
                    }
                }
                free(flat);
                break;
            }
    }
}

double ** sort( int row,  int column, double ** data,  bool reverse,  int dim,  double mask_nan)
{
    double ** new = deepcopy(row, column, data);
    sortNoReturned(row, column, data, reverse, dim, mask_nan);
    return new;
}

double ** uniform( int row,  int column,  double start,  double end,  int seed,  bool use)
{
    if (use) setSeed(seed);
    double ** new = (double **)malloc(sizeof(double *) *row);
    for (int r=0;r < row;r ++)
    {
        new[r] = (double *)malloc(sizeof(double) * column);
        for(int c = 0;c < column;c ++)
        {
            new[r][c] = start + (end - start) * ((double)rand() / RAND_MAX);
        }
    }
    return new;
}

double ** normal( int row,  int column,  double mu,  double sigma,  int seed,  bool use )
{
    if (use) setSeed(seed);
    double ** new = (double **)malloc(sizeof(double *) *row);
    for(int r = 0; r < row; ++r){
        new[r] = (double *)malloc(sizeof(double) * column);
        for(int c = 0; c < column; ++c){
            new[r][c] = sqrt(-2 * log((double)rand() / RAND_MAX)) * cos(M_PI * 2 * (double)rand() / RAND_MAX) * sigma + mu;
        }
    }
    return new;
}

double ** poisson( int row,  int column,  double lambda,  int seed,  bool use){
    if (use) setSeed(seed);
    double ** new = (double **)malloc(sizeof(double *) *row);
    double p = 1.0;
    int k = 0;
     double L  = exp(-lambda);
    for(int r = 0; r < row; ++r){
        new[r] = (double *)malloc(sizeof(double) * column);
        for(int c = 0; c < column; ++c){
            p = 1.0;
            k = 0;
            while(p >= L) {
                ++k;
                p *= (double)rand() / RAND_MAX;
            }
            new[r][c] = k;
        }
    }
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

void set_mask_nan( int row,  int column, double ** data,  double number)
{
    for(int r = 0;r < row;r ++)
    {
        for (int c = 0;c < column;c ++)
        {
            if (isnan(data[r][c]))
                data[r][c] = number;
        }
    }
}

void set_mask_inf( int row,  int column, double ** data,  double number,  bool isNegativeInf)
{
    double dat = 0.;
    for(int r = 0;r <  row;r ++)
    {
        for (int c = 0;c < column;c ++)
        {
            dat = data[r][c];
            if (isinf(dat) && dat > 0 && !isNegativeInf)
                data[r][c] = number;
            else if (isinf(dat) && dat < 0 && isNegativeInf)
                data[r][c] = number;
            else {}
        }
    }
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

double ** testArray( int row,  int column)
{
    double ** new = (double **)malloc(sizeof(double *) * row);
    for (int r = 0;r < row ;r ++)
    {
        new[r] = (double *)malloc(sizeof(double) * column);
        for (int c = 0;c < column;c ++)
            new[r][c] = r + c;
    }
    return new;
}

double* variance(int row, int column, double** data, bool sample, int dim, bool std) {
    double* number = NULL;
    double* means = means = mean(row, column, data, dim);;
    double diff, _mean;
    int size;

    switch (dim) {
    case 0:
        {
            size = sample ? column - 1 : column;
            number = (double*)calloc(row, sizeof(double));
            for (int r = 0; r < row; ++r) {
                _mean = means[r];
                for (int c = 0; c < column; ++c) {
                    diff = data[r][c] - _mean;
                    number[r] += diff * diff;
                }
                number[r] /= size;
                if (std)
                    number[r] = sqrt(number[r]);
            }
            break;
        }
    case 1:
        {
            size = sample ? row - 1: row;
            number = (double*)calloc(column, sizeof(double));
            for (int c = 0; c < column; ++c) {
                _mean = means[c];
                for (int r = 0; r < row; ++r) {
                    diff = data[r][c] - _mean;
                    number[c] += diff * diff;
                }
                number[c] /= size;
                if (std)
                    number[c] = sqrt(number[c]);
            }
            break;
        }
    default:
        {
            size = sample ? (row * column - 1) : row * column;
            number = (double*)calloc(1, sizeof(double));
            _mean = *means;
            for (int r = 0; r < row; ++r) {
                for (int c = 0; c < column; ++c) {
                    diff = data[r][c] - _mean;
                    *number += diff * diff;
                }
            }
            *number /= size;
            if (std)
                *number = sqrt(*number);
            break;
        }
    }
    free(means);
    return number;
}

double * median(int row, int column, double ** data, int dim)
{
    double * number = NULL;
    double * tempArr = NULL;
    switch (dim)
    {
    case 0:
        {
            number = (double*)malloc(sizeof(double) * row);
            for(int r = 0;r < row;r ++)
            {
                tempArr = (double *)malloc(sizeof(double) * column);
                for (int c = 0;c  < column;c ++)
                    insertSorted(tempArr, c , data[r][c]);
                if (column % 2 == 0)
                    number[r] = (tempArr[(column - 1) / 2] + tempArr[column / 2]) / 2.0;
                else
                    number[r] = tempArr[column / 2];
                free(tempArr);
            }
            break;
        }
    case 1:
        {
            number = (double *)malloc(sizeof(double) * column);
            for(int c=0;c < column;c ++)
            {
                tempArr = (double *)malloc(sizeof(double) * row);
                for(int r = 0;r < row;r ++)
                    insertSorted(tempArr, r, data[r][c]);
                if (column % 2 == 0)
                    number[c] = (tempArr[(row - 1) / 2] + tempArr[row / 2]) / 2.0;
                else
                    number[c] = tempArr[row / 2];
                free(tempArr);
            }
            break;
        }
    default:
        number = (double*)malloc(sizeof(double  ));
        int size = row * column;
        tempArr = (double*)malloc(sizeof(double  ) * size);
        int counter = 0;
        for (int r = 0;r < row;r ++)
        {
            for (int c= 0;c < column;c ++)
            {
                insertSorted(tempArr, counter++, data[r][c]);
            }
        }
        if (column % 2 == 0)
            *number = (tempArr[(size - 1) / 2] + tempArr[size / 2]) / 2.0;
        else
            *number = tempArr[size / 2];
        free(tempArr);
        break;
    }
    return number;
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

int * argmax(int row, int column, double  **data, int dim){
    int * number = NULL;
    double value;
    switch (dim) {
        case 0:{
            number = (int *) calloc(row,  sizeof (int ) );
            for(int r = 0;r < row;r++){
                value = data[r][0];
                for(int c = 1;c < column;c ++){
                    if (value < data[r][c]) {
                        value = data[r][c];
                        number[r] = c;
                    }
                }
            }
            break;
        }
        case 1:{
            number = (int *) calloc(column, sizeof (int ));
            for (int c = 0;c < column;c ++){
                value = data[0][c];
                for(int r = 0;r < row;r ++){
                    if (value < data[r][c]){
                        value = data[r][c];
                        number[c] = r;
                    }
                }
            }
            break;
        }
        default:{
            number = (int *) calloc(1, sizeof (int ));
            value = data[0][0];
            for(int r =0;r < row;r++){
                for(int  c=0;c < column;c ++){
                    if (value < data[r][c]){
                        value = data[r][c];
                        *number = column * r + c;
                    }
                }
            }
            break;
        }
    }
    return number;
}

int * argmin(int row, int column, double  **data, int dim){
    int * number = NULL;
    double value;
    switch (dim) {
        case 0:{
            number = (int *) calloc(row,  sizeof (int ) );
            for(int r = 0;r < row;r++){
                value = data[r][0];
                for(int c = 1;c < column;c ++){
                    if (value > data[r][c]) {
                        value = data[r][c];
                        number[r] = c;
                    }
                }
            }
            break;
        }
        case 1:{
            number = (int *) calloc(column, sizeof (int ));
            for (int c = 0;c < column;c ++){
                value = data[0][c];
                for(int r = 0;r < row;r ++){
                    if (value > data[r][c]){
                        value = data[r][c];
                        number[c] = r;
                    }
                }
            }
            break;
        }
        default:{
            number = (int *) calloc(1, sizeof (int ));
            value = data[0][0];
            for(int r =0;r < row;r++){
                for(int  c=0;c < column;c ++){
                    if (value > data[r][c]){
                        value = data[r][c];
                        *number = column * r + c;
                    }
                }
            }
            break;
        }
    }
    return number;
}

double * flatten(int row, int column, double  **data, int mode){
    double * new = (double  *) malloc(sizeof (double ) * (column * row));
    int counter = 0;
    if (mode == 1){
        for(int c = 0;c < column;c ++){
            for (int r = 0;r < row;r ++){
                new[counter++] = data[r][c];
            }
        }
    } else{
        for(int r =0;r < row;r ++){
            for(int c= 0;c < column;c ++){
                new[counter++] = data[r][c];
            }
        }
    }
    return new;
}

double ** range(double start, double step, int row, int column){
    double  **new = (double **) malloc(sizeof (double *  )*row);
    int counter = 0;
    for (int r = 0;r < row;r++){
        new[r] = (double *) malloc(sizeof (double ) *column);
        for(int c=0;c < column;c ++){
            new[r][c] = start + step * counter++;
        }
    }
    return new;
}

double ** replace(int row, int column, double ** data, double number,  bool (*condition)(double )){
    double **new = (double  **) malloc(sizeof (double *) * row);
    for (int r = 0;r < row;r ++){
        new[r] = (double  *) malloc(sizeof (double ) * column);
        for (int c = 0;c < column;c ++){
            new[r][c] = (condition(data[r][c])) ? data[r][c] : number;
        }
    }
    return new;
}

void replaceNoReturned(int row, int column, double ** data, double number, bool (*condition)(double )){
    for (int r =0;r < row;r ++){
        for(int c=0;c < column;c ++){
            if (!condition(data[r][c]))
                data[r][c] = number;
        }
    }
}

double ** normalization1(int row, int column, double  **data, int dim){
    double ** new = allocateButNoNumbers(row, column);
    double * mins = min(row, column, data, dim);
    double * maxs = max(row, column, data, dim);
    double value;
    switch (dim) {
        case 0:{
            for (int r = 0;r <row;r++ ){
                value = maxs[r] - mins[r];
                for (int c = 0;c < column;c ++){
                    new[r][c] = (data[r][c] - mins[r]) / value;
                }
            }
            break;
        }
        case 1:{
            for (int c = 0;c < column;c ++){
                value = maxs[c] - mins[c];
                for (int r = 0;c < row;r ++){
                    new[r][c] = (data[r][c] - mins[c]) / value;
                }
            }
            break;
        }
        default:{
            value = *maxs - *mins;
            for (int r = 0;r < row;r ++){
                for (int c =0;c < column;c ++){
                    new[r][c] = (data[r][c] - *mins) / value;
                }
            }
            break;
        }

    }
    free(mins);
    free(maxs);
    return new;
}

double ** normalization2(int row, int column, double  **data, int dim){
    double ** new = allocateButNoNumbers(row, column);
    double * mins = min(row, column, data, dim);
    double * maxs = max(row, column, data, dim);
    double * means = mean(row, column, data, dim);
    double  value;
    switch (dim) {
        case 0:{
            for (int r = 0;r < row;r++){
                value = maxs[r] - mins[r];
                for (int c = 0;c < column;c ++){
                    new[r][c] = (data[r][c] - means[r]) / value;
                }
            }
            break;
        }
        case 1:{
            for (int c =0;c <column;c ++){
                value = maxs[c] - mins[c];
                for (int r = 0;r < row;r ++){
                    new[r][c] = (data[r][c] - means[c]) / value;
                }
            }
            break;
        }
        default:{
            value = *maxs - *mins;
            for (int r=0;r <row;r++){
                for(int c = 0;c < column; c ++){
                    new[r][c] = (data[r][c] - *means) / value;
                }
            }
            break;
        }
    }
    free(mins);
    free(maxs);
    free(means);
    return new;
}

double ** normalization3(int row, int column, double  **data, int dim){
    double * sigmas = variance(row, column, data, false, dim, true);
    double * mus = mean(row, column, data, dim);
    double ** new = allocateButNoNumbers(row , column);
    switch (dim) {
        case 0:{
            for (int r = 0;r < row;r ++){
                for (int c=0;c  <column;c ++){
                    new[r][c] = (data[r][c] - mus[r]) / sigmas[r];
                }
            }
            break;
        }
        case 1:{
            for(int c=0;c < column;c ++){
                for (int r = 0;r < row;r ++){
                    new[r][c] = (data[r][c] - mus[c]) / sigmas[c];
                }
            }
            break;
        }
        default:{
            for (int r =0;r < row;r++){
                for(int c = 0;c < column;c ++){
                    new[r][c] = (data[r][c] - *mus) / *sigmas;
                }
            }
            break;
        }
    }
    free(sigmas);
    free(mus);
    return new;
}

double ** sliceR(int column, double ** data, int from, int to){
    int row = to - from + 1;
    double ** new = (double  **) malloc(sizeof (double *) * row);
    for (int r = 0;r < row;r++){
        new[r] = (double *) malloc(sizeof (double )* column);
        for (int c = 0;c < column;c ++){
            new[r][c] = data[r + from][c];
        }
    }
    return new;
}

double ** sliceC(int row, double ** data, int from, int to){
    int column = to - from + 1;
    double ** new = allocateButNoNumbers(row, column);
    for (int c = 0;c< column; c ++){
        for(int r = 0; r< row;r ++){
            new[r][c] = data[r][c + from];
        }
    }
    return new;
}

double ** clip(int row, int column, double  **data, double lb, double ub){
    double ** new = (double **) malloc(sizeof (double *) * row);
    double value;
    for (int r = 0;r < row; r++){
        new[r] = (double *) malloc(sizeof (double )*column);
        for (int c = 0;c < column;c ++){
            value = data[r][c];
            new[r][c] = (value < lb) ? lb : (value > ub) ? ub : value;
        }
    }
    return new;
}

void clipNoReturned(int row, int column, double  **data, double lb, double ub){
    double value;
    for (int r = 0;r < row; r++){
        for (int c = 0;c < column;c ++){
            value = data[r][c];
            if (value < lb)
                data[r][c] = lb;
            else if (value > ub)
                data[r][c] = ub;
            else{}
        }
    }
}

bool all(int row, int column, double  ** data, bool (*condition)(double )){
    for (int r = 0;r < row;r ++){
        for (int c =0;c < column;c ++){
            if (!condition(data[r][c]))
                return false;
        }
    }
    return true;
}

bool any(int row, int column, double **data, bool (*condition)(double )){
    for (int r = 0;r < row;r ++){
        for (int c =0;c < column;c ++){
            if (condition(data[r][c]))
                return true;
        }
    }
    return false;
}

int * counter(int row, int column, double  ** data, int dim, bool (*condition)(double )){
    int * number = NULL;
    switch (dim) {
        case 0:{
            number = (int *) calloc(row, sizeof (int ));
            for (int r = 0;r < row;r ++){
                for(int c =0;c < column;c ++){
                    if (condition(data[r][c]))
                        number[r]++;
                }
            }
            break;
        }
        case 1:
            number = (int *) calloc(column, sizeof (int ));
            for (int c = 0;c < column;c ++){
                for(int r=0;r< row;r++){
                    if (condition(data[r][c]))
                        number[c]++;
                }
            }
            break;
        default:{
            number = (int *) calloc(1, sizeof (int ));
            for (int r = 0;r < row;r ++){
                for(int c =0;c < column;c ++){
                    if (condition(data[r][c]))
                        *number++;
                }
            }
            break;
        }
    }
    return number;
}

double * reduce(int row, int column, double ** data, int dim, double (*condition)(double , double ), double init){
    double * number = NULL;
    double value = init;
    switch (dim) {
        case 0:{
            number = (double *) malloc(sizeof (double )*row);
            for (int r = 0;r < row;r++){
                for (int c = 0;c < column;c ++){
                    value = condition(value, data[r][c]);  // 这里与condition(data[r][c], value)效果不一样
                }
                number[r] = value;
                value = init;
            }
            break;
        }
        case 1:{
            number = (double *) malloc(sizeof (double )*column );
            for (int c =0;c < column;c ++){
                for(int r = 0;r < row;r++){
                    value = condition(value, data[r][c]);
                }
                number[c] = value;
                value = init;
            }
            break;
        }
        default:{
            number = (double *) malloc(sizeof (double ));
            for (int r = 0;r < row;r++){
                for (int c = 0;c < column;c ++){
                    value = condition(value, data[r][c]);
                }
            }
            *number = value;
        }
    }
    return number;
}

double ** E_like(int row, int column){
    double ** new = (double **) calloc(row, sizeof (double *) );
    for (int r = 0;r < row;r++)
        new[r] = (double *)calloc(column, sizeof (double ) );
    int n = row < column ? row : column;
    for (int r = 0;r < n;r++)
        new[r][r] = 1.0;
    return new;
}

double *** qr(int row, int column, double** data) {
    double *** new = (double***)malloc(2 * sizeof(double**));
    new[0] = (double**)malloc(row * sizeof(double*));
    new[1] = (double**)malloc(column * sizeof(double*));

    for (int i = 0; i < row; ++i) {
        new[0][i] = (double*)calloc(column, sizeof(double));
    }
    for (int i = 0; i < column; ++i) {
        new[1][i] = (double*)calloc(column, sizeof(double));
    }

    double ** Q = new[0];
    double ** R = new[1];

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

    return new;
}

double ** clip_reverse(int row, int column, double  **data, double lb, double ub, double (*condition)(double)){
    double ** new = (double **) malloc(sizeof (double *) * row);
    double value;
    for (int r = 0;r < row;r++){
        new[r] = (double *) malloc(sizeof (double ) * column);
        for (int c = 0;c < column;c ++){
            value = data[r][c];
            new[r][c] = (value <= lb || value >= ub) ? value : condition(value);
        }
    }
    return new;
}

void clip_reverseNoReturned(int row, int column, double  **data, double lb, double ub, double (*condition)(double)){
    double value;
    for (int r = 0;r < row;r++){
        for (int c = 0;c < column;c ++){
            value = data[r][c];
            if (value > lb && value < ub)
                data[r][c] = condition(value);
        }
    }
}

double ** customize(int row, int column, double ** data, double (*condition)(double )){
    double ** new = (double **) malloc(sizeof (double *) * row);
    for (int r = 0;r < row;r ++){
        new[r] = (double *) malloc(sizeof (double) * column);;
        for (int c = 0;c < column;c ++){
            new[r][c] = condition(data[r][c]);
        }
    }
    return new;
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

int ** findIndexs(int row, int column, double **data, bool (*condition)(double ), int prediction){
    int**new = (int **) malloc(sizeof (int *) * row);
    for (int r = 0;r < row;r++){
        int baseIndex = r * column;
        new[r] = findall_condition(data[r], column, prediction, condition, baseIndex);
    }
    return new;
}

double ** rotate(int row, int column, double ** data, int mode){
    double ** new = NULL;
    int counter = 0;
    switch (mode) {
        case -3: label0: {  // 顺90/逆270
            new = (double **) malloc(sizeof(double *) * column);
            for (int r = 0; r < column; r++) {
                new[r] = (double *) malloc(sizeof(double) * row);
                for (int c = 0; c < row; c++) {
                    new[r][c] = data[row - c - 1][r];
                }
            }
            break;
        }
        case -2: label1 : {  // 顺逆180
            new = (double**)malloc(sizeof(double*) * row);
            for (int r = 0; r < row; r++) {
                new[r] = (double*)malloc(sizeof(double) * column);
                for (int c = 0; c < column; c++) {
                    new[r][c] = data[row - r - 1][column - c - 1];
                }
            }
            return new;
        }
        case -1: label2:{  // 逆90/顺270
            {
                new = (double **) malloc(sizeof(double *) * column);
                for (int r = 0; r < column; r++) {
                    new[r] = (double *) malloc(sizeof(double) * row);
                    for (int c = 0; c < row; c++) {
                        new[r][c] = data[c][column - r - 1];
                    }
                }
                break;
            }
        }
        case 0: goto label4;
        case 1: goto label0;
        case 2: goto label1;
        case 3: goto label2;
        default: label4 :{
            new = deepcopy(row, column, data);
            break;
        }
    }
    return new;
}

double ** mirror(int row, int column, double ** data, int mode) {
    double ** new = (double**)malloc(row * sizeof(double*));
    if (mode == 0) {
        for (int r = 0; r < row; r++) {
            new[r] = (double*)malloc(column * sizeof(double));
            for (int c = 0; c < column;c ++) {
                new[r][c] = data[r][column - c - 1];
            }
        }
    } else {
        for (int r = 0; r < row; r++)
            new[r] = (double*)malloc(column * sizeof(double));
        for (int c = 0; c < column; c ++) {
            for (int r = 0; r < row; r++) {
                new[r][c] = data[row - r - 1][c];
            }
        }
    }
    return new;
}

double ** decentralizate(int row, int column, double **data, int dim){
    double * means = mean(row, column, data, dim);
    double ** new = (double **) malloc(sizeof (double* ) * row);
    double m;
    switch (dim) {
        case 0:{
            for (int r = 0;r < row;r++){
                m = means[r];
                new[r] = (double *) malloc(sizeof (double )*column);
                for (int c  =0;c < column;c ++){
                    new[r][c] = data[r][c] - m;
                }
            }
            break;
        }
        case 1:{
            for (int r = 0;r < row;r++)
                new[r] = (double *) malloc(sizeof (double )*column);
            for (int c = 0;c < column;c ++){
                m = means[c];
                for (int r  = 0;r < row;r++){
                    new[r][c] = data[r][c] - m;
                }
            }
            break;
        }
        default:{
            m = *means;
            for (int r = 0;r < row;r++){
                new[r] = (double *) malloc(sizeof (double )*column);
                for (int c  =0;c < column;c ++){
                    new[r][c] = data[r][c] - m;
                }
            }
            break;
        }
    }
    free(means);
    return new;
}

double * covariance(int row, int column, double ** data1, double ** data2, bool sample, int dim){
    double * number = NULL;
    double * means1 = mean(row, column, data1, dim);
    double * means2 = mean(row, column, data2, dim);
    double value, xm, ym;
    double n;
    switch (dim) {
        case 0:{
            n = sample ? (double)(column - 1) : (double)column;
            number = (double *) malloc(sizeof (double ) * row);
            for (int r = 0;r < row;r++){
                value = 0.;
                xm = means1[r];
                ym = means2[r];
                for(int c = 0;c < column;c ++){
                    value += (data1[r][c] - xm) * (data2[r][c] - ym);
                }
                number[r] = value / n;
            }
            break;
        }
        case 1:{
            n = sample ? (double)(row - 1) :(double) row;
            number = (double *) malloc(sizeof (double ) * column);
            for (int c = 0;c < column; c ++){
                value = 0.;
                xm = means1[c];
                ym = means2[c];
                for (int r = 0;r < row;r++){
                    value += (data1[r][c] - xm) * (data2[r][c] - ym);
                }
                number[c] = value / n;
            }
            break;
        }
        default: {
            xm = *means1;
            ym = *means2;
            n = sample ? (double)(row * column - 1) :(double)( row * column);
            number = (double *) calloc(1, sizeof(double));
            for (int r = 0; r < row; r++) {
                for (int c = 0; c < column; c++) {
                    *number += (data1[r][c] - xm) * (data2[r][c] - ym);
                }
            }
            *number /= n;
            break;
        }
    }
    free(means1);
    free(means2);
    return number;
}

double ** cov1(int row, int column, double ** data, bool sample){
    double n = sample ? (double)(column - 1):(double)column;
    double sum;
    double ** A = decentralizate(row, column, data, 0);  // 获取去中心化的矩阵
    double ** A_T = transpose(row, column, A);  // [column, row]
    double ** new = (double **) malloc(sizeof (double *) * row);
    for (int r = 0; r < row; r++) {
        new[r] = (double *) malloc(sizeof (double )*row);
        for (int j = 0; j < row; j++) {
            sum = 0.0;
            for (int k = 0; k < column; k++) {
                sum += A[r][k] * A_T[j][k];
            }
            new[r][j] = sum / n;
        }
    }
    __delete__data__(A, row);
    __delete__data__(A_T, column);
    return new;
}

double ** cov2(int row, int column, double ** data1, double ** data2, bool sample){
    double n = sample ? (double)(column - 1) : (double)column;
    double ** A = decentralizate(row, column, data1, 0);
    double ** B = decentralizate(row, column, data2, 0);
    double ** A_T = transpose(row, column, A);
    double ** B_T = transpose(row, column, B);
    // 实现矩阵左行右列内积
    double ** covaat = matmul(row, column, A, A_T, row);  // [row, row]
    double ** covabt = matmul(row, column, A, B_T, row);  // [row, row]
    double ** covbat = matmul(row, column, B, A_T, row);  // [row, row]
    double ** covbbt = matmul(row, column, B, B_T, row);  // [row, row]
    double ** new = (double **) malloc(sizeof (double *)*(row * 2));
    for (int r = 0;r < row;r++){
        new[r] = (double *) malloc(sizeof (double ) * (row * 2));
        for (int c = 0;c < row;c ++){
            new[r][c] = covaat[r][c] / n;
        }
        for (int c = 0;c < row;c ++){
            new[r][c + row] = covabt[r][c] / n;
        }
    }
    for (int r = 0;r < row;r++){
        new[r + row] = (double *) malloc(sizeof (double ) * (row * 2));
        for (int c = 0;c < row;c ++){
            new[r + row][c] = covbat[r][c] / n;
        }
        for (int c = 0;c < row;c ++){
            new[r + row][c + row] = covbbt[r][c] / n;
        }
    }

    __delete__data__(A, row);
    __delete__data__(B, row);
    __delete__data__(A_T, column);
    __delete__data__(B_T, column);
    __delete__data__(covaat, row);
    __delete__data__(covabt, row);
    __delete__data__(covbat, row);
    __delete__data__(covbbt, row);
    return new;
}

double * pearsonCoef(int row, int column, double ** data1, double ** data2, bool sample, int dim){
    double * number = NULL;
    double * xstd = variance(row, column, data1, sample, dim, true);
    double * ystd = variance(row, column, data2, sample, dim, true);
    double * covxy = covariance(row, column, data1, data2, sample, dim);
    switch (dim) {
        case 0:{
            number = (double *) malloc(sizeof (double )*row);
            for (int r = 0;r < row;r++)
                number[r] = covxy[r] / (xstd[r] * ystd[r]);
            break;
        }
        case 1:{
            number = (double *) malloc(sizeof (double ) * column);
            for (int c = 0;c < column;c ++)
                number[c] = covxy[c] / (xstd[c] * ystd[c]);
            break;
        }
        default:{
            number = (double *) malloc(sizeof (double ));
            *number = *covxy / (*xstd * *ystd);
            break;
        }
    }
    free(xstd);
    free(ystd);
    free(covxy);
    return number;
}

double * MSE(int row, int column, double ** data1, double ** data2, int dim, bool rmse){
    double * number = NULL;
    double sum;
    switch (dim) {
        case 0:{
            number = (double *) malloc(sizeof (double ) * row);
            for (int r = 0;r < row;r++){
               sum = 0.;
               for(int c = 0;c < column;c ++){
                   sum += pow(data1[r][c] - data2[r][c], 2.0);
               }
               number[r] = rmse ? sqrt(sum / column) : sum / column;
            }
            break;
        }
        case 1:{
            number = (double *) malloc(sizeof (double ) * column);
            for (int c = 0; c < column;c ++){
                sum = 0.;
                for (int r = 0;r < row;r++){
                    sum += pow(data1[r][c] - data2[r][c], 2.);
                }
                number[c] = rmse? sqrt(sum / row) : sum / row;
            }
            break;
        }
        default:{
            number = (double *) malloc(sizeof (double ));
            sum = 0.;
            for (int r = 0;r < row;r++){
                for (int c = 0;c < column;c++){
                    sum += pow(data1[r][c] - data2[r][c], 2.);
                }
            }
            number[0] = rmse? sqrt(sum / (column * row)) : sum / (column * row);
            break;
        }
    }
    return number;
}

double * MAE(int row, int column, double ** data1, double ** data2, int dim){
    double * number = NULL;
    double sum;
    switch (dim) {
        case 0:{
            number = (double *) malloc(sizeof (double ) * row);
            for (int r = 0;r < row;r++){
                sum = 0.;
                for(int c = 0;c < column;c ++){
                    sum += fabs(data1[r][c] - data2[r][c]);
                }
                number[r] = sum / column;
            }
            break;
        }
        case 1:{
            number = (double *) malloc(sizeof (double ) * column);
            for (int c = 0; c < column;c ++){
                sum = 0.;
                for (int r = 0;r < row;r++){
                    sum += fabs(data1[r][c] - data2[r][c]);
                }
                number[c] = sum / row;
            }
            break;
        }
        default:{
            number = (double *) malloc(sizeof (double ));
            sum = 0.;
            for (int r = 0;r < row;r++){
                for (int c = 0;c < column;c++){
                    sum += fabs(data1[r][c] - data2[r][c]);
                }
            }
            number[0] = sum / (column * row);
            break;
        }
    }
    return number;
}

double * MAPE(int row, int column, double ** pre, double ** rea, int dim){
    double * number = NULL;
    double sum, value;
    switch (dim) {
        case 0:{
            number = (double *) malloc(sizeof (double ) * row);
            for (int r = 0;r < row;r++){
                sum = 0.;
                for (int c = 0;c < column;c ++){
                    value = rea[r][c];
                    sum += fabs((pre[r][c] - value) / value);
                }
                number[r] = sum / column;
            }
            break;
        }
        case 1:{
            number = (double *) malloc(sizeof (double )* column);
            for (int c =0;c< column;c ++){
                sum = 0.;
                for (int r = 0;r < row;r++){
                    value =rea[r][c];
                    sum += fabs((pre[r][c] - value) / value);
                }
                number[c] = sum / row;
            }
            break;
        }
        default:{
            number = (double *) malloc(sizeof (double ));
            sum = 0.;
            for (int r = 0;r < row;r++) {
                for (int c = 0; c < column; c++) {
                    value = rea[r][c];
                    sum += fabs((pre[r][c] - value) / value);
                }
            }
            *number = sum / (column * row);
            break;
        }
    }
    return number;
}

double * R2(int row, int column, double ** pre, double ** rea, int dim){
    double * number = NULL;
    double sum1, sum2, value;
    double * means = mean(row, column, rea, dim);
    switch (dim) {
        case 0:{
            number = (double *) malloc(sizeof (double ) * row);
            for (int r = 0;r < row;r++){
                sum1 = 0.;
                sum2 = 0.;
                for (int c = 0;c < column;c ++){
                    value = rea[r][c];
                    sum1 += pow(pre[r][c] - value, 2.);
                    sum2 += pow(means[r] - value, 2.);
                }
                number[r] = 1 - sum1 / sum2;
            }
            break;
        }
        case 1:{
            number = (double *) malloc(sizeof (double ) * column);
            for (int c = 0;c <column;c ++){
                sum1 = 0.;
                sum2 = 0.;
                for (int r = 0;r < row;r++){
                    value = rea[r][c];
                    sum1 += pow(pre[r][c] - value, 2.);
                    sum2 += pow(means[c] - value, 2.);
                }
                number[c] = 1 - sum1 / sum2;
            }
            break;
        }
        default:{
            number = (double *) malloc(sizeof (double ));
            sum2 = 0.;
            sum1 = 0.;
            double _mean = *means;
            for (int r = 0;r < row;r++){
                for (int c = 0;c < column;c ++ ){
                    value = rea[r][c];
                    sum1 += pow(pre[r][c] - value, 2.);
                    sum2 += pow(_mean - value, 2.);
                }
            }
            number[0] = 1 - sum1 / sum2;
            break;
        }
    }
    free(means);
    return number;
}

double * SMAPE(int row, int column, double ** data1, double ** data2, int dim){
    double * number = NULL;
    double sum, value1, value2;
    switch (dim) {
        case 0:{
            number = (double *) malloc(sizeof (double ) * row);
            for (int r = 0;r < row;r++){
                sum = 0.;
                for (int c = 0;c < column;c ++){
                    value1 = data1[r][c];
                    value2 = data2[r][c];
                    sum += 2 * fabs(value2 - value1) / (fabs(value1) + fabs(value2));
                }
                number[r] = sum / column;
            }
            break;
        }
        case 1:{
            number = (double *) malloc(sizeof (double ) * column);
            for (int c = 0;c < column;c ++){
                sum = 0.;
                for(int r = 0;r < row;r++){
                    value1 = data1[r][c];
                    value2 = data2[r][c];
                    sum += 2 * fabs(value2 - value1) / (fabs(value1) + fabs(value2));
                }
                number[c] = sum / row;
            }
            break;
        }
        default:{
            number = (double *) malloc(sizeof (double ));
            sum = 0.;
            for (int r = 0;r < row;r++){
                for(int c = 0;c < column;c ++){
                    value1 = data1[r][c];
                    value2 = data2[r][c];
                    sum += 2 * fabs(value2 - value1) / (fabs(value1) + fabs(value2));
                }
            }
            *number = sum / (row * column);
            break;
        }
    }
    return number;
}

// 获取关于对角线对称的随机数矩阵，sub为true表示副对角线对称
double ** diagonal(int row, int column, double start, double end, bool sub, int seed, bool use){
    if (use) setSeed(seed);
    double ** new = allocateButNoNumbers(row, column);
    double value;
    if(!sub) {
        for (int r = 0; r < row; r++) {
            for (int c = r; c < column; c ++) {
                value = start + ((double) rand() / (double) RAND_MAX) * (end - start);
                new[r][c] = value;
                new[c][r] = value;
            }
        }
        return new;
    } else{
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c ++) {
                value = start + ((double)rand() / (double)RAND_MAX) * (end - start);
                new[r][c] = value;
                new[column - c - 1][row - r - 1] = value;
            }
        }
        return new;
    }
}

void fill_diagonal(int row, int column, double ** data, double number){
    int n = column < row ? column : row;
    for(int r = 0;r < n;r ++)
        data[r][r] = number;
}

double ** choice1(int row, int column, double ** data, double ** p, int times, bool back, int method) {
    double ** new = (double **)malloc(sizeof(double *) * row);
    for (int r = 0; r < row; r++)
        new[r] = perfect_choices(data[r], p[r], column, times, back, method);
    return new;
}

double ** choice2(int row, int column, double ** data, double * p, int times, bool back, int method){
    double ** new = (double **) malloc(sizeof (double *) * row);
    for(int r = 0;r < row;r++)
        new[r] = perfect_choices(data[r], p, column, times, back, method);
    return new;
}

double ** choice3(int row, int column, double ** data, int times, bool back){
    double ** new = (double **) malloc(sizeof (double *) * row);
    for(int r = 0;r < row;r++)
        new[r] = random_choices(data[r], column, times, back);
    return new;
}