//
// Created by 20281 on 24-9-20.
//

#include "mp_linalg.h"

static void __delete__data__inner__(double ** data,  int row)
{
    if(data) {
        #pragma omp parallel for if(row >= SimpleDVCST / 2)
        for (int r=0;r < row;r++) {
            free(data[r]);
        }
        free(data);
    }
}

double ** transpose(int row, int column, double ** data)
{
    double ** new = allocateButNoNumbers(column, row);
    bool isMultiple = row * column >= SimpleDVCST;  
    multp_msg(row * column, isMultiple, false, "transpose"); 

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            new[c][r] = data[r][c];
        }
    }
    return new;
}

void exchangeR(int column, double ** data, int row1, int row2)
{
    bool isMultiple = column >= SimpleDVCST;
    multp_msg(column, isMultiple, false, "exchangeR");

    if (row1 != row2) {
        double temp;
        #pragma omp parallel for if(isMultiple)
        for (int c = 0;c < column;c ++) {
            temp = data[row1][c];
            data[row1][c] = data[row2][c];
            data[row2][c] = temp;
        }
    }
}

void multiplyR( int row, int column, double **data, double size)
{   
    bool isMultiple = column >= SimpleDVCST;
    multp_msg(column, isMultiple, false, "multiplyR");

    #pragma omp simd if(isMultiple)
    for (int c = 0;c < column;c ++){
        data[row][c] *= size;
    }
}


void addR(int column, double **data, int row1, int row2, double size)
{   
    bool isMultiple = column >= SimpleDVCST;
    multp_msg(column, isMultiple, false, "addR");

    #pragma omp simd if(isMultiple)
    for (int c = 0;c < column;c ++){
        data[row1][c] += data[row2][c] * size;
    } 
}

void exchangeC( int row, double ** data,  int column1,  int column2)
{
    bool isMultiple = row >= SimpleDVCST;
    multp_msg(row, isMultiple, false, "exchangeC");

    if (column1 != column2) {
        double temp;
        #pragma omp parallel for if(isMultiple)
        for (int r = 0;r < row;r ++) {
            temp = data[r][column1];
            data[r][column1] = data[r][column2];
            data[r][column2] = temp;
        }
    }
}

void multiplyC( int row, int column, double **data, double size)
{   
    bool isMultiple = row >= SimpleDVCST;
    multp_msg(row, isMultiple, false, "multiplyC");

    #pragma omp simd if(isMultiple)
    for (int r = 0;r < row;r ++){
        data[r][column] *= size;
    }
}

void addC(int row, double **data, int column1, int column2, double size)
{   
    bool isMultiple = row >= SimpleDVCST;
    multp_msg(row, isMultiple, false, "addC");

    #pragma omp simd if(isMultiple)
    for (int r = 0;r < row;r++) { 
        data[r][column1] += data[r][column2] * size;
    }
}

double ** addNumber( int row, int column, double **data, double number)
{
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "addNumber");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        new[i / column][i % column] = data[i / column][i % column] + number;
    }
    return new;
}

double ** addMatrix(int row, int column, double **data1, double **data2)
{
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "addMatrix");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        new[i / column][i % column] = data1[i / column][i % column] + data2[i / column][i % column];
    }

    return new;
}

void addNumberNoReturned(int row, int column, double **data, double number)
{

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "addNumberNoReturned");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        data[i / column][i % column] += number;
    }
}

void addMatrixNoReturned(int row, int column, double **data1, double **data2)
{   
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "addMatrixNoReturned");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        data1[i / column][i % column] += data2[i / column][i % column];
    }
}

double ** minusMatrix(int row, int column, double **data1, double **data2)
{
    double ** new = allocateButNoNumbers(row, column);  
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "minusMatrix");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        new[i / column][i % column] = data1[i / column][i % column] - data2[i / column][i % column];
    }
    return new;
}

void minusMatrixNoReturned(int row, int column, double **data1, double **data2)
{
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "minusMatrixNoReturned");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        data1[i / column][i % column] -= data2[i / column][i % column];
    }
}

double ** matmul(int row, int column, double **data1, double **data2, int column2)
{
    double ** new = allocateButNoNumbers(row, column2);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "matmul");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column2; c ++) {
            double sum = 0.0;
            #pragma omp parallel for reduction(+:sum)
            for (int k = 0; k < column; k++) {
                sum += data1[r][k] * data2[k][c];
            }
            new[r][c] = sum;
        }
    }
    return new;
}

void multiplyMatrixNoReturned(int row, int column, double **data1, double **data2)
{
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "multiplyMatrixNoReturned");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        data1[i / column][i % column] *= data2[i / column][i % column];
    }
}

double ** multiplyMatrix(int row, int column, double **data1, double **data2)
{
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "multiplyMatrix");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        new[i / column][i % column] = data1[i / column][i % column] * data2[i / column][i % column];
    }
    return new;
}

void multiplyNumberNoReturned(int row, int column, double **data, double number)
{
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "multiplyNumberNoReturned");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        data[i / column][i % column] *= number;
    }
}

double ** multiplyNumber(int row, int column, double **data, double number)
{
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "multiplyNumber");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        new[i / column][i % column] = data[i / column][i % column] * number;
    }

    return new;
}

double ** kronecker(int row1, int column1, double **data1, int row2, int column2, double **data2)
{
    double ** new = allocateButNoNumbers(row1 * row2, column1 * column2);
    bool isMultiple = row1 * row2 * column1 * column2 >= SimpleDVCST;
    multp_msg(row1 * row2 * column1 * column2, isMultiple, false, "kronecker");
    
    #pragma omp parallel for collapse(4) if(isMultiple)
    for (int i = 0; i < row1; ++i) {
        for (int k = 0; k < row2; ++k) {
            for (int j = 0; j < column1; ++j) {
                for (int l = 0; l < column2; ++l) {
                    new[i * row2 + k][j * column2 + l] = data1[i][j] * data2[k][l];
                }
            }
        }
    }
    return new;
}

double ** divide(int row, int column, double **data, double number)
{
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "divide");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        new[i / column][i % column] = data[i / column][i % column] / number;
    }
    return new;
}

void divideNoReturned(int row, int column, double **data, double number)
{
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "divideNoReturned");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i++) {
        data[i / column][i % column] /= number;
    }
}

double trace(int row, int column, double **data)
{
    int n = row < column ? row : column;
    double sum = 0.;
    bool isMultiple = n >= SimpleDVCST;
    multp_msg(n, isMultiple, false, "trace");

    #pragma omp parallel for reduction(+ :sum) if(isMultiple)
    for (int r = 0;r < n;r++){
        sum += data[r][r];
    }
    return sum;
}

double det(int row, int column, double **data)
{
    double detValue = 1.0;
    int n = row;
    double ** matrixcpy = malloc(sizeof(double *) * row);
    no_multp_msg(row * column, true, "det");

    for(int r = 0;r < row;r++) {
        matrixcpy[r] = malloc(sizeof(double) * column);
        for (int c = 0;c < column;c ++) {
            matrixcpy[r][c] = data[r][c];
        }
    }

    for (int i = 0; i < n; i++) {
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(matrixcpy[k][i]) > fabs(matrixcpy[max_row][i])) {
                max_row = k;
            }
        }
        if (matrixcpy[max_row][i] == 0) {
            __delete__data__inner__(matrixcpy, row);
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
    __delete__data__inner__(matrixcpy, row);
    return detValue;
}

double ** E(int n)
{
    double ** new = (double **)malloc(n *sizeof (double *));
    bool isMultiple = n * n >= SimpleDVCST;
    multp_msg(n * n, isMultiple, false, "E");

    #pragma omp parallel for if(isMultiple)
    for (int r = 0;r < n;r++) {
        new[r] = (double *) calloc(n, sizeof (double ));
        new[r][r] = 1.;
    }
    return new;
}

double ** cofactor(int row, int column, double ** data, int prow, int pcolumn)
{
    double ** new = allocateButNoNumbers(row - 1, column - 1);
    bool isMultiple = (row - 1) * (column - 1) >= SimpleDVCST;
    multp_msg((row - 1) * (column - 1), isMultiple, false, "cofactor");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row - 1; r++) {
        for (int c = 0; c < column - 1; c ++) {
            int src_r = (r < prow) ? r : r + 1; 
            int src_c = (c < pcolumn) ? c : c + 1; 
            new[r][c] = data[src_r][src_c];
        }
    }

    return new;
}

double ** adjugate(int row, int column, double ** data)
{
    int n = row;
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = n * n >= ComplexDVCST;
    multp_msg(n * n, isMultiple, true, "adjugate");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c ++) {
            double ** cof = cofactor(n, n, data, r, c);  // [n - 1, n - 1]
            new[c][r] = ((r + c) % 2 == 0 ? 1 : -1) * det(n - 1, n - 1, cof);
            __delete__data__inner__(cof, n - 1);
        }
    }
    return new;
}

double ** inverse( int row,  int column,  double ** data, double det)
{
    int n = row;
    double ** new = allocateButNoNumbers(row, column);
    double ** adj = adjugate(row, column, data);

    bool isMultiple = n * n >= SimpleDVCST;
    multp_msg(n * n, isMultiple, false, "inverse");

    #pragma omp simd if(isMultiple)
    for (int i = 0; i < n * n; i++) {
        new[i / n][i % n] = adj[i / n][i % n] / det;
    }
    __delete__data__inner__(adj, row);
    return new;
}

double ** rref(int row, int column, double ** data)
{
    double ** new = (double **)malloc(sizeof(double *) * row);
    for (int r = 0;r < row;r ++) {
        new[r] = (double *)malloc(sizeof(double) * column);
        for (int c = 0;c < column;c ++) {
            new[r][c] = data[r][c];
        }
    }
    no_multp_msg(row * column, true, "rref");

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

int rank(int row, int column, double ** data)
{
    double ** new = rref(row, column, data);
    int counter = 0;
    int n = row > column ?column : row;
    no_multp_msg(row * column, false, "rank");

    for (int r = 0; r < n; r++) {
        int isZeroRow = 1;
        for (int c = 0; c < column; c ++) {
            if (fabs(new[r][c]) > DROUND) {
                isZeroRow = 0;
                break;
            }
        }
        if (!isZeroRow){
            counter++;
        }
    }
    __delete__data__inner__(new, row);
    return counter;
}

double norm_negainf(int row, int column, double ** data)
{
    double * number = (double *)calloc(row, sizeof(double));
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "norm_negainf");

    #pragma omp parallel for schedule(dynamic) if(isMultiple)
    for(int r = 0;r < row;r ++) {
        #pragma omp parallel for reduction(+ : number[r]) if(column >= 0.1 * SimpleDVCST && isMultiple)
        for(int c = 0;c < column;c ++) {
            number[r] += fabs(data[r][c]);
        }
    }
    double value = number[0];
    #pragma omp parallel for reduction(max:value) if(row >= 0.1 * SimpleDVCST && isMultiple)
    for (int r = 1;r < row;r ++) {
        value = fmax(value, number[r]);
    }
    free(number);
    return value;
}

double norm_inf(int row, int column, double ** data)
{
    double * number = (double*)calloc(row, sizeof(double));
    double value = 0.;

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "norm_inf");

    #pragma omp parallel for schedule(dynamic) if(isMultiple)
    for(int r = 0;r < row;r ++) {
        #pragma omp parallel for reduction(+ : number[r]) if(column >= 0.1 * SimpleDVCST && isMultiple)
        for(int c = 0;c < column;c ++) {
            number[r] += fabs(data[r][c]);
        }
        value = fmax(value, number[r]);
    }
    free(number);
    return value;
}

double * norm_zero(int row, int column, double ** data, int dim)
{
    double * number = NULL;
    double value = 0.0;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "norm_zero");

    switch (dim)
    {
    case 0:
        number = (double * )calloc(row, sizeof(double));
        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for(int r = 0;r < row;r ++) {
            #pragma omp parallel for reduction(+ : number[r]) if(column >= 0.1 * SimpleDVCST && isMultiple)
            for (int c = 0;c < column;c ++) {
                value = fabs(data[r][c]);
                if (value < DROUND){
                    number[r]++;
                }
            }
        }
        break;
    case 1:
        number = (double *)calloc(column, sizeof(double));
        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int c = 0;c < column ;c ++) {
            #pragma omp parallel for reduction(+ : number[c]) if(row >= 0.1 * SimpleDVCST && isMultiple)
            for (int r =0;r < row;r++) {
                value = fabs(data[r][c]);
                if (value < DROUND){
                    number[c]++;
                }
            }
        }
        break;
    default:
        number = (double *)calloc(1, sizeof(double));
        #pragma omp parallel for collapse(2) reduction(+ :number[0]) if(isMultiple)
        for (int r = 0;r < row;r ++) {
            for(int c=0;c < column;c ++) {
                value = fabs(data[r][c]);
                if (value < DROUND){
                    number[0]++;
                }
            }
        }
        break;
    }
    return number;
}

double norm_one(int row, int column, double ** data)
{
    double * number = (double *)calloc(column, sizeof(double));
    double value = 0.0;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "norm_one");

    #pragma omp parallel for schedule(dynamic) if(isMultiple)
    for (int c = 0;c < column;c ++) {
        #pragma omp parallel for reduction(+ : number[c]) if(row >= 0.1 * SimpleDVCST && isMultiple)
        for(int r = 0;r < row;r++) {
            number[c] += fabs(data[r][c]);
        }
        value = fmax(value, number[c]);
    }
    free(number);
    return value;
}

double * norm(int row, int column, double ** data, int n, int dim)
{
    double * number = NULL;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "norm");

    switch (dim)
    {
    case 0:
        number = (double *)calloc(row, sizeof(double));
        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int r = 0;r < row;r ++) {
            #pragma omp parallel for reduction(+ : number[r]) if(column >= 0.1 * SimpleDVCST && isMultiple)
            for(int c= 0;c < column;c ++) {
                number[r] += pow(fabs(data[r][c]), n);
            }
            number[r] = pow(number[r], 1.0 / n);
        }
        break;
    case 1:
        number = (double *)calloc(column, sizeof(double));
        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int c = 0;c < column;c ++) {
            #pragma omp parallel for reduction(+ : number[c]) if(row >= 0.1 * SimpleDVCST && isMultiple)
            for(int r = 0;r < row;r ++) {
                number[c] += pow(fabs(data[r][c]), n);
            }
            number[c] = pow(number[c], 1.0 / n);
        }
        break;
    default:
        number = (double *)calloc(1, sizeof(double));
        #pragma omp parallel for collapse(2) reduction(+ :number[0]) if(isMultiple)
        for (int r = 0;r < row;r ++) {
            for(int c = 0;c <column;c ++) {
                number[0] += pow(fabs(data[r][c]), n);
            }
        }
        number[0] = pow(number[0], 1.0 / n);
        break;
    }
    return number;
}

MultiDatas2 qr(int row, int column, double** data) {
    double ** Q = (double**)malloc(row * sizeof(double*));
    double ** R = (double**)malloc(column * sizeof(double*));

    no_multp_msg(row * column, true, "qr");

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
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "divrev");

    #pragma omp simd if(isMultiple)
    for (int i = 0;i < row * column;i ++){
        new[i / column][i % column] = number / data[i / column][i % column];
    }
    return new;
}

// 获取关于对角线对称的随机数矩阵，sub为true表示副对角线对称
double ** diagonal(int row, int column, double start, double end, bool sub, int seed, bool use){
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "diagonal");

    if(!sub) {
        #if defined(_WIN32) || defined(_WIN64)
        {
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r = 0; r < row; r++) {
                for (int c = r; c < column; c ++) {
                    double value = start + ((double) rand_func() / (double) MAXRAND) * (end - start);
                    new[r][c] = value;
                    new[c][r] = value;
                }
            }
        }
        #else
        {
            int total_iterations = (row * (row + 1)) / 2;
            #pragma omp parallel for
            for (int k = 0; k < total_iterations; k++) {
                int r = (int)((-1 + sqrt(1 + 8 * k)) / 2);
                int c = k - r * (r + 1) / 2;
                double value = start + ((double) rand_func() / (double) MAXRAND) * (end - start);
                new[r][c] = value;
                new[c][r] = value;
            }
        }
        return new;
        #endif
    }

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++) {
            double value = start + ((double) rand_func() / (double) MAXRAND) * (end - start);
            new[r][c] = value;
            new[row - 1 - c][column - 1 - r] = value;
        }
    }

    return new;
}

void fill_diagonal(int row, int column, double ** data, double number){
    int n = column < row ? column : row;
    bool isMultiple = n >= SimpleDVCST;
    multp_msg(n, isMultiple, false, "fill_diagonal");

    #pragma omp simd if(isMultiple)
    for(int r = 0;r < n;r ++){
        data[r][r] = number;
    }
}

