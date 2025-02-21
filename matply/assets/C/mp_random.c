//
// Created by 20281 on 24-9-20.
//

#include "mp_random.h"

#ifndef _sgn
    static inline int _sgn(double x) {return (x > 0) - (x < 0);}
#endif

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

void shuffle(int row, int column, double ** data, int seed, bool use)
{
    use ? setSeed(seed) : setSeed(time(NULL));
    int ri = 0, rj = 0, temp = 0; // 隐式强制转换
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "shuffle");
    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = row - 1; r > 0; r--) {
        for (int c = column - 1; c > 0; c--) {
            ri = rand_func() % (r + 1);
            rj = rand_func() % (c + 1);
            temp = data[r][c];
            data[r][c] = data[ri][rj];
            data[ri][rj] = temp;
        }
    }
}

static double _uniform(double start, double end) {
    return start + (end - start) * ((double)rand_func() / MAXRAND);
}

static double _standard_uniform() {
    return (double)rand_func() / MAXRAND;
}

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

static double _standard_normal() {
    double u1 = _standard_uniform();
    double u2 = _standard_uniform();
    return sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}

double ** uniform(int row, int column, double start, double end, int seed, bool use)
{
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "uniform");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r= 0;r < row;r ++) {
        for(int c = 0;c < column;c ++){
            new[r][c] = _uniform(start, end);
        }
    }
    return new;
}

static double _normal(double mu, double sigma) {
    double u1 = _standard_uniform();
    double u2 = _standard_uniform();
    double z = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return z * sigma + mu;
}

double ** normal(int row, int column, double mu, double sigma, int seed, bool use)
{
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "normal");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for(int r = 0; r < row; r++){
        for(int c = 0; c < column; c ++){
            new[r][c] = _normal(mu, sigma);
        }
    }
    return new;
}

double ** poisson(int row, int column, double lambda, int seed, bool use){
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    double p = 1.0;
    int k = 0;
    double L = exp(-lambda);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "poisson");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for(int r = 0; r < row; r++){
        for(int c = 0; c < column; c ++){
            p = 1.0;
            k = 0;
            while(p >= L) {
                ++k;
                p *= _standard_uniform();
            }
            new[r][c] = k;
        }
    }
    return new;
}

double * variance(int row, int column, double** data, bool sample, int dim, bool std) {
    double * number = NULL;
    double * means = mean(row, column, data, dim);
    double diff, _mean;
    int size;

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "variance");

    switch (dim) {
    case 0:
        size = sample ? column - 1 : column;
        number = (double*)calloc(row, sizeof(double));
        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int r = 0; r < row; ++r) {
            _mean = means[r];
            #pragma omp simd if(column >= 0.1 * SimpleDVCST && SimpleDVCST)
            for (int c = 0; c < column; ++c) {
                diff = data[r][c] - _mean;
                number[r] += diff * diff;
            }
            number[r] /= size;
            if (std){
                number[r] = sqrt(number[r]);
            }
        }
        break;
    case 1:
        size = sample ? row - 1: row;
        number = (double*)calloc(column, sizeof(double));
        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int c = 0; c < column; ++c) {
            _mean = means[c];
            #pragma omp simd if(row >= 0.1 * SimpleDVCST && SimpleDVCST)
            for (int r = 0; r < row; ++r) {
                diff = data[r][c] - _mean;
                number[c] += diff * diff;
            }
            number[c] /= size;
            if (std){
                number[c] = sqrt(number[c]);
            }
        }
        break;
    default:
        size = sample ? (row * column - 1) : row * column;
        number = (double*)calloc(1, sizeof(double));
        _mean = *means;
        #pragma omp parallel for collapse(2) reduction(+:number[0]) if(isMultiple)
        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < column; ++c) {
                diff = data[r][c] - _mean;
                number[0] += diff * diff;
            }
        }
        *number /= size;
        if (std){
            *number = sqrt(*number);
        }
        break;
    }
    free(means);
    return number;
}

static int __compare(const void *a, const void *b) {
    double diff = *(double*)a - *(double*)b;
    return (diff > 0) - (diff < 0);
}

double * median(int row, int column, double ** data, int dim)
{
    double * number = NULL;
    double * tempArr = NULL;
    bool isMultiple = false;
    switch (dim)
    {
    case 0:
        number = (double*)malloc(sizeof(double) * row);
        isMultiple = row * column >= ComplexDVCST;
        multp_msg(row * column, isMultiple, true, "median");

        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for(int r = 0;r < row;r ++) {
            tempArr = (double *)malloc(sizeof(double) * column);
            #pragma omp parallel for if(column >= 0.1 * ComplexDVCST && isMultiple)
            for (int c = 0;c  < column;c ++){
                insertSorted(tempArr, c, data[r][c]);
            }
            number[r] = column % 2 == 0 ? 
                (tempArr[(column - 1) / 2] + tempArr[column / 2]) / 2.0 : 
                tempArr[column / 2];
            free(tempArr);
        }
        break;
    case 1:
        number = (double *)malloc(sizeof(double) * column);
        isMultiple = row * column >= ComplexDVCST;
        multp_msg(row * column, isMultiple, true, "median");

        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for(int c = 0;c < column;c ++) {
            tempArr = (double *)malloc(sizeof(double) * row);
            #pragma omp parallel for if(row >= 0.1 * ComplexDVCST && isMultiple)
            for(int r = 0;r < row;r ++){
                insertSorted(tempArr, r, data[r][c]);
            }
            number[c] = column % 2 == 0 ? 
                (tempArr[(row - 1) / 2] + tempArr[row / 2]) / 2.0 : 
                tempArr[row / 2];
            free(tempArr);
        }
        break;
    default:
        multp_msg(1, isMultiple, false, "median");
        number = (double *)malloc(sizeof(double));
        double * flattenArr = flatten(row, column, data, 0);
        qsort(flattenArr, row * column, sizeof(double), __compare);
        number[0] = column % 2 == 0 ? 
            (flattenArr[(row * column - 1) / 2] + flattenArr[row * column / 2]) / 2.0 :
            flattenArr[row * column / 2];
        break;
    }
    return number;
}

double ** normalization1(int row, int column, double  ** data, int dim){
    double ** new = allocateButNoNumbers(row, column);
    double * mins = min(row, column, data, dim);
    double * maxs = max(row, column, data, dim);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "normalization1");

    switch (dim) {
        case 0:
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r = 0;r <row;r++ ){
                for (int c = 0;c < column;c ++){
                    new[r][c] = (data[r][c] - mins[r]) / (maxs[r] - mins[r]);
                }
            }
            break;
        case 1:
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int c = 0;c < column;c ++){
                for (int r = 0;r < row;r ++){
                    new[r][c] = (data[r][c] - mins[c]) / (maxs[c] - mins[c]);
                }
            }
            break;
        default: {
            double value = *maxs - *mins;
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r = 0;r < row;r ++){
                for (int c = 0;c < column;c ++){
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

double ** normalization2(int row, int column, double ** data, int dim){
    double ** new = allocateButNoNumbers(row, column);
    double * mins = min(row, column, data, dim);
    double * maxs = max(row, column, data, dim);
    double * means = mean(row, column, data, dim);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "normalization2");
    switch (dim) {
        case 0:
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r = 0;r < row;r++){
                for (int c = 0;c < column;c ++){
                    new[r][c] = (data[r][c] - means[r]) / (maxs[r] - mins[r]);
                }
            }
            break;
        case 1:
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int c =0;c <column;c ++){
                for (int r = 0;r < row;r ++){
                    new[r][c] = (data[r][c] - means[c]) / (maxs[c] - mins[c]);
                }
            }
            break;
        default: {
            double value = *maxs - *mins;
            #pragma omp parallel for collapse(2) if(isMultiple)
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
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "normalization3");

    switch (dim) {
        case 0:
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r = 0;r < row;r ++){
                for (int c=0;c  <column;c ++){
                    new[r][c] = (data[r][c] - mus[r]) / sigmas[r];
                }
            }
            break;
        case 1:
            #pragma omp parallel for collapse(2) if(isMultiple)
            for(int c=0;c < column;c ++){
                for (int r = 0;r < row;r ++){
                    new[r][c] = (data[r][c] - mus[c]) / sigmas[c];
                }
            }
            break;
        default:
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r =0;r < row;r++){
                for(int c = 0;c < column;c ++){
                    new[r][c] = (data[r][c] - *mus) / *sigmas;
                }
            }
            break;
    }
    free(sigmas);
    free(mus);
    return new;
}

double * covariance(int row, int column, double ** data1, double ** data2, bool sample, int dim){
    double * number = NULL;
    double * means1 = mean(row, column, data1, dim);
    double * means2 = mean(row, column, data2, dim);
    double value, xm, ym;
    double n;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "covariance");

    switch (dim) {
        case 0:
            n = sample ? (double)(column - 1) : (double)column;
            number = (double *) malloc(sizeof (double ) * row);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int r = 0;r < row;r++){
                value = 0.0;
                xm = means1[r];
                ym = means2[r];
                #pragma omp parallel for reduction(+:value) if(column >= 0.1 * SimpleDVCST && isMultiple)
                for(int c = 0;c < column;c ++){
                    value += (data1[r][c] - xm) * (data2[r][c] - ym);
                }
                number[r] = value / n;
            }
            break;
        case 1:
            n = sample ? (double)(row - 1) :(double) row;
            number = (double *) malloc(sizeof (double ) * column);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int c = 0;c < column; c ++){
                value = 0.;
                xm = means1[c];
                ym = means2[c];
                #pragma omp parallel for reduction(+:value) if(row >= 0.1 * SimpleDVCST && isMultiple)
                for (int r = 0;r < row;r++){
                    value += (data1[r][c] - xm) * (data2[r][c] - ym);
                }
                number[c] = value / n;
            }
            break;
        default: 
            xm = *means1;
            ym = *means2;
            n = sample ? (double)(row * column - 1) :(double)( row * column);
            number = (double *) calloc(1, sizeof(double));
            #pragma omp parallel for collapse(2) reduction(+:number[0]) if(isMultiple)
            for (int r = 0; r < row; r++) {
                for (int c = 0; c < column; c ++) {
                    number[0] += (data1[r][c] - xm) * (data2[r][c] - ym);
                }
            }
            *number /= n;
            break;
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
    double ** new = allocateButNoNumbers(row, row);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "cov1");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int j = 0; j < row; j++) {
            sum = 0.0;
            #pragma omp parallel for reduction(+ : sum) if(column >= 0.1 * SimpleDVCST && isMultiple)
            for (int k = 0; k < column; k++) {
                sum += A[r][k] * A_T[j][k];
            }
            new[r][j] = sum / n;
        }
    }
    __delete__data__inner__(A, row);
    __delete__data__inner__(A_T, column);
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
    
    double ** new = allocateButNoNumbers(row * 2, row * 2);
    bool isMultiple = row * row >= SimpleDVCST;
    multp_msg(row * row, isMultiple, false, "cov2");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < row; c ++) {
            new[r][c] = covaat[r][c] / n;  // 填充左上部分
            new[r][c + row] = covabt[r][c] / n;  // 填充右上部分
            new[r + row][c] = covbat[r][c] / n;  // 填充左下部分
            new[r + row][c + row] = covbbt[r][c] / n;  // 填充右下部分
        }
    }

    __delete__data__inner__(A, row);
    __delete__data__inner__(B, row);
    __delete__data__inner__(A_T, column);
    __delete__data__inner__(B_T, column);
    __delete__data__inner__(covaat, row);
    __delete__data__inner__(covabt, row);
    __delete__data__inner__(covbat, row);
    __delete__data__inner__(covbbt, row);
    return new;
}

double * pearsonCoef(int row, int column, double ** data1, double ** data2, bool sample, int dim){
    double * number = NULL;
    double * xstd = variance(row, column, data1, sample, dim, true);
    double * ystd = variance(row, column, data2, sample, dim, true);
    double * covxy = covariance(row, column, data1, data2, sample, dim);
    bool isMultiple = false;

    switch (dim) {
        case 0:
            number = (double *) malloc(sizeof (double )*row);
            isMultiple = row >= SimpleDVCST;
            multp_msg(row, isMultiple, false, "pearsonCoef");

            #pragma omp simd if(isMultiple)
            for (int r = 0;r < row;r++){
                number[r] = covxy[r] / (xstd[r] * ystd[r]);
            }
            break;
        case 1:
            number = (double *) malloc(sizeof (double ) * column);
            isMultiple = column >= SimpleDVCST;
            multp_msg(column, isMultiple, false, "pearsonCoef");

            #pragma omp simd if(isMultiple)
            for (int c = 0;c < column;c ++){
                number[c] = covxy[c] / (xstd[c] * ystd[c]);
            }
            break;
        default:
            multp_msg(1, isMultiple, false, "pearsonCoef");
            number = (double *) malloc(sizeof (double ));
            *number = *covxy / (*xstd * *ystd);
            break;
    }
    free(xstd);
    free(ystd);
    free(covxy);
    return number;
}

double * MSE(int row, int column, double ** data1, double ** data2, int dim, bool rmse){
    double * number = NULL;
    double sum, v;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "MSE");

    switch (dim) {
        case 0:
            number = (double *) malloc(sizeof (double ) * row);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int r = 0;r < row;r++){
               sum = 0.0;
               #pragma omp parallel for reduction(+ : sum) if(column >= 0.1 * SimpleDVCST && isMultiple)
               for(int c = 0;c < column;c ++){
                    v = data1[r][c] - data2[r][c];
                    sum += v * v;
               }
               number[r] = rmse ? sqrt(sum / column) : sum / column;
            }
            break;
        case 1:
            number = (double *) malloc(sizeof (double ) * column);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int c = 0; c < column;c ++){
                sum = 0.0;
                #pragma omp parallel for reduction(+ : sum) if(row >= 0.1 * SimpleDVCST && isMultiple)
                for (int r = 0;r < row;r++){
                    v = data1[r][c] - data2[r][c];
                    sum += v * v;
                }
                number[c] = rmse? sqrt(sum / row) : sum / row;
            }
            break;
        default:
            number = (double *) malloc(sizeof (double ));
            sum = 0.0;
            #pragma omp parallel for collapse(2) reduction(+ : sum) if(isMultiple)
            for (int r = 0;r < row;r++){
                for (int c = 0;c < column;c++){
                    v = data1[r][c] - data2[r][c];
                    sum += v * v;
                }
            }
            number[0] = rmse? sqrt(sum / (column * row)) : sum / (column * row);
            break;
    }
    return number;
}

double * MAE(int row, int column, double ** data1, double ** data2, int dim){
    double * number = NULL;
    double sum;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "MAE");
    switch (dim) {
        case 0:
            number = (double *) malloc(sizeof (double ) * row);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int r = 0;r < row;r++){
                sum = 0.0;
                #pragma omp parallel for reduction(+ : sum) if(column >= 0.1 * SimpleDVCST && isMultiple)
                for(int c = 0;c < column;c ++){
                    sum += fabs(data1[r][c] - data2[r][c]);
                }
                number[r] = sum / column;
            }
            break;
        case 1:
            number = (double *) malloc(sizeof (double ) * column);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int c = 0; c < column;c ++){
                sum = 0.0;
                #pragma omp parallel for reduction(+ : sum) if(row >= 0.1 * SimpleDVCST && isMultiple)
                for (int r = 0;r < row;r++){
                    sum += fabs(data1[r][c] - data2[r][c]);
                }
                number[c] = sum / row;
            }
            break;
        default:
            number = (double *) malloc(sizeof (double ));
            sum = 0.0;
            #pragma omp parallel for collapse(2) reduction(+ : sum) if(isMultiple)
            for (int r = 0;r < row;r++){
                for (int c = 0;c < column;c ++){
                    sum += fabs(data1[r][c] - data2[r][c]);
                }
            }
            number[0] = sum / (column * row);
            break;
    }
    return number;
}

double * MAPE(int row, int column, double ** pre, double ** rea, int dim){
    double * number = NULL;
    double sum, value;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "MAPE");
    switch (dim) 
        case 0:{
            number = (double *) malloc(sizeof (double ) * row);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int r = 0;r < row;r++){
                sum = 0.0;
                #pragma omp parallel for reduction(+ : sum) if(column >= 0.1 * SimpleDVCST && isMultiple)
                for (int c = 0;c < column;c ++){
                    value = rea[r][c];
                    sum += fabs((pre[r][c] - value) / value);
                }
                number[r] = sum / column;
            }
            break;
        case 1:
            number = (double *) malloc(sizeof (double ) * column);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int c = 0;c< column;c ++){
                sum = 0.0;
                #pragma omp parallel for reduction(+ : sum) if(row >= 0.1 * SimpleDVCST && isMultiple)
                for (int r = 0;r < row;r++){
                    value = rea[r][c];
                    sum += fabs((pre[r][c] - value) / value);
                }
                number[c] = sum / row;
            }
            break;
        default:
            number = (double *) malloc(sizeof (double ));
            sum = 0.0;
            #pragma omp parallel for collapse(2) reduction(+ : sum) if(isMultiple)
            for (int r = 0;r < row;r++) {
                for (int c = 0; c < column; c++) {
                    value = rea[r][c];
                    sum += fabs((pre[r][c] - value) / value);
                }
            }
            *number = sum / (column * row);
            break;
    }
    return number;
}

double * R2(int row, int column, double ** pre, double ** rea, int dim){
    double * number = NULL;
    double sum1, sum2, v0, v1, v2;
    double * means = mean(row, column, rea, dim);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "R2");
    switch (dim) {
        case 0:{
            number = (double *) malloc(sizeof (double ) * row);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int r = 0;r < row;r++){
                sum1 = 0.0;
                sum2 = 0.0;
                #pragma omp parallel for reduction(+ : sum1, sum2) if(column >= 0.1 * SimpleDVCST && isMultiple)
                for (int c = 0;c < column;c ++){
                    v0 = rea[r][c];
                    v1 = pre[r][c] - v0;
                    v2 = means[r] - v0;
                    sum1 += v1 * v1;
                    sum2 += v2 * v2;
                }
                number[r] = 1.0 - sum1 / sum2;
            }
            break;
        }
        case 1:{
            number = (double *) malloc(sizeof (double ) * column);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int c = 0;c <column;c ++){
                sum1 = 0.0;
                sum2 = 0.0;
                #pragma omp parallel for reduction(+ : sum1, sum2) if(row >= 0.1 * SimpleDVCST && isMultiple)
                for (int r = 0;r < row;r++){
                    v0 = rea[r][c];
                    v1 = pre[r][c] - v0;
                    v2 = means[c] - v0;
                    sum1 += v1 * v1;
                    sum2 += v2 * v2;
                }
                number[c] = 1.0 - sum1 / sum2;
            }
            break;
        }
        default:{
            number = (double *) malloc(sizeof (double ));
            sum2 = 0.0;
            sum1 = 0.0;
            double _mean = *means;
            #pragma omp parallel for collapse(2) reduction(+ : sum1, sum2) if(isMultiple)
            for (int r = 0;r < row;r++){
                for (int c = 0;c < column;c ++ ){
                    v0 = rea[r][c];
                    v1 = pre[r][c] - v0;
                    v2 = _mean - v0;
                    sum1 += v1 * v1;
                    sum2 += v2 * v2;
                }
            }
            number[0] = 1.0 - sum1 / sum2;
            break;
        }
    }
    free(means);
    return number;
}

double * SMAPE(int row, int column, double ** data1, double ** data2, int dim){
    double * number = NULL;
    double sum, value1, value2;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "SMAPE");
    switch (dim) {
        case 0:
            number = (double *) malloc(sizeof (double ) * row);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int r = 0;r < row;r++){
                sum = 0.0;
                #pragma omp parallel for reduction(+ : sum) if(column >= 0.1 * SimpleDVCST && isMultiple)
                for (int c = 0;c < column;c ++){
                    value1 = data1[r][c];
                    value2 = data2[r][c];
                    sum += 2.0 * fabs(value2 - value1) / (fabs(value1) + fabs(value2));
                }
                number[r] = sum / column;
            }
            break;
        case 1:
            number = (double *) malloc(sizeof (double ) * column);
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int c = 0;c < column;c ++){
                sum = 0.0;
                #pragma omp parallel for reduction(+ : sum) if(row >= 0.1 * SimpleDVCST && isMultiple)
                for(int r = 0;r < row;r++){
                    value1 = data1[r][c];
                    value2 = data2[r][c];
                    sum += 2.0 * fabs(value2 - value1) / (fabs(value1) + fabs(value2));
                }
                number[c] = sum / row;
            }
            break;
        default:
            number = (double *) malloc(sizeof (double ));
            sum = 0.0;
            #pragma omp parallel for collapse(2) reduction(+ : sum) if(isMultiple)
            for (int r = 0;r < row;r++){
                for(int c = 0;c < column;c ++){
                    value1 = data1[r][c];
                    value2 = data2[r][c];
                    sum += 2.0 * fabs(value2 - value1) / (fabs(value1) + fabs(value2));
                }
            }
            *number = sum / (row * column);
            break;
    }
    return number;
}

double ** choice1(int row, int column, double ** data, double ** p, int times, bool back, int method) {
    double ** new = (double **)malloc(sizeof(double *) * row);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "choice1");
    
    #pragma omp parallel for if(isMultiple)
    for (int r = 0; r < row; r++){
        new[r] = perfect_choices(data[r], p[r], column, times, back, method);
    }
    return new;
}

double ** choice2(int row, int column, double ** data, double * p, int times, bool back, int method){
    double ** new = (double **) malloc(sizeof (double *) * row);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "choice2");

    #pragma omp parallel for if(isMultiple)
    for(int r = 0;r < row;r++){
        new[r] = perfect_choices(data[r], p, column, times, back, method);
    }
    return new;
}

double ** choice3(int row, int column, double ** data, int times, bool back){
    double ** new = (double **) malloc(sizeof (double *) * row);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "choice3");

    #pragma omp parallel for if(isMultiple)
    for(int r = 0;r < row;r++){
        new[r] = random_choices(data[r], column, times, back);
    }
    return new;
}

double ** exponential(int row, int column, double scale, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double coef = - 1.0 / scale;
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "exponential");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r ++) {
        for(int c = 0;c < column;c ++){
            new[r][c] = coef * log(1.0 - _uniform(0, 1));
        }
    }
    return new;
}

static double gamma_shape_gt_1(double shape, double scale) {
    double d = shape - 1.0;
    double c = (d < 1.0) ? (d + 1.0) / (d + 1.0) : (d / (d + 1.0));
    double beta = 1.0 / (d + 1.0);
    double gamma_value = 1.0;
    while (gamma_value > beta) {
        double x = _standard_uniform();
        double y = _standard_uniform();
        double z = 2.0 * x - 1.0;
        gamma_value = z > 0 ? exp(-z / d) * y : 0;
    }
    return scale * gamma_value;
}

static double gamma_shape_eq_1(double scale, double _) {
    return scale * -log(1.0 - _standard_uniform());
}

static double gamma_shape_lt_1(double shape, double scale) {
    double u = _standard_uniform();
    return scale * pow(u, 1.0 / shape);
}

double ** gamma_(int row, int column, double shape, double scale, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "gamma_");

    double (*gamma_func)(double, double);
    if (shape > 1.0)
        gamma_func = gamma_shape_gt_1;
    else if (shape == 1.0)
        gamma_func = gamma_shape_eq_1;
    else
        gamma_func = gamma_shape_lt_1;
    
    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++){
            new[r][c] = gamma_func(shape, scale);
        }
    }
    return new;
}

static double _binomial(int n, double p) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += _standard_uniform() < p;
    }
    return count;
}

double ** binomial(int row, int column, int n, double p, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "binomial");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for (int c = 0;c < column;c ++){
            new[r][c] = _binomial(n, p);
        }
    }
    return new;
}

static double _chisquare(int k) {
    double sums = 0.0, n;
    for (int i = 0; i < k; i++) {
        n = _standard_normal();
        sums += n * n;
    }
    return sums;
}

double ** chisquare(int row, int column, int k, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "chisquare");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for(int c = 0;c < column;c ++){
            new[r][c] = _chisquare(k);
        }
    }
    return new;
}

static double _tdis(int k) {
    double z = _standard_normal();
    double v = _chisquare(k);
    return z / sqrt(v / k);
}

double ** tdis(int row, int column, int k, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "tdis");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for (int c = 0;c < column;c ++){
            new[r][c] = _tdis(k);
        }
    }
    return new;
}

static double _fdis(int k1, int k2) {
    double x = _chisquare(k1);
    double y = _chisquare(k2);
    return (x / k1) / (y / k2);
}

double ** fdis(int row, int column, int k1, int k2, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "fdis");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for (int c = 0;c < column;c ++){
            new[r][c] = _fdis(k1, k2);
        }
    }
    return new;
}

static double _geometric(double p) {
    double u = _standard_uniform();
    double x = floor(log(1.0 - u) / log(1.0 - p));
    return x;
}

double ** geometric(int row, int column, double p, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "geometric");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for (int c = 0;c < column;c ++){
            new[r][c] = _geometric(p);
        }
    }
    return new;
}

static double _nbinomial(int n, double p) {
    double sums = 0.0;
    for (int i = 0; i < n; i++) {
        sums += _geometric(p);
    }
    return sums;
}

double ** nbinomial(int row, int column, int n, double p, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "nbinomial");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for (int c = 0;c < column;c ++){
            new[r][c] = _nbinomial(n, p);
        }
    }
    return new;
}

static double _lognormal(double mu, double sigma) {
    return exp(mu + sigma *_standard_normal());
}

double ** lognormal(int row, int column, double mu, double sigma, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);  
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "lognormal");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for (int c = 0;c < column;c ++){
            new[r][c] = _lognormal(mu, sigma);
        }
    }
    return new;
}

static double _cauchydis(double base, double gamma) {
    return base + gamma * tan(M_PI * (_standard_uniform() - 0.5));
}

double ** cauchydis(int row, int column, double base, double gamma, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "cauchydis");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for (int c = 0;c < column;c ++){
            new[r][c] = _cauchydis(base, gamma);
        }
    }
    return new;
}

static void multinomial_sample(double * p, int len, int n, int *result) {
    double * cumulative_prob = (double *)malloc(len * sizeof(double));
    double u;
    cumulative_prob[0] = p[0];
    for (int i = 1; i < len; i++){
        cumulative_prob[i] = cumulative_prob[i - 1] + p[i];
    }
    for (int i = 0; i < len; i++){
        result[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        u = _standard_uniform();
        for (int j = 0; j < len; j++) {
            if (u < cumulative_prob[j]) {
                result[j]++;
                break;
            }
        }
    }
    free(cumulative_prob);
}

double ** multinomial(double * p, int len, int n, int size, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(size, len);
    bool isMultiple = size * len >= ComplexDVCST;
    multp_msg(size * len, isMultiple, true, "multinomial");

    #pragma omp parallel for schedule(dynamic) if(isMultiple)
    for (int r = 0; r < size; r++) {
        int * result = (int *)malloc(len * sizeof(int));
        multinomial_sample(p, len, n, result);
        #pragma omp simd if(len >= 0.1 * ComplexDVCST && isMultiple)
        for (int c = 0; c < len; c ++){
            new[r][c] = result[c];
        }
        free(result);
    }
    return new;
}

double ** beta(int row, int column, double a, double b, int seed, bool use) {
    double (* gamma1)(double, double), (* gamma2)(double, double);
    if (a > 1)
        gamma1 = gamma_shape_gt_1;
    else if (a == 1)
        gamma1 = gamma_shape_eq_1;
    else
        gamma1 = gamma_shape_eq_1;
    if (b > 1)
        gamma2 = gamma_shape_gt_1;
    else if (b == 1)
        gamma2 = gamma_shape_eq_1;
    else
        gamma2 = gamma_shape_eq_1;
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "beta");

    double x, y;
    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for (int c = 0;c < column;c ++) {
            x = gamma1(a, 1.0);
            y = gamma2(b, 1.0);
            new[r][c] = x / (x + y);
        }
    }
    return new;
}

double ** wiener_process(int row, int column, double t, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double dt = t / column, delta;
    double ** new = allocateButNoNumbers(row, column);  
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "wiener_process");

    #pragma omp parallel for if(isMultiple)
    for (int r = 0; r < row; r++) {
        new[r][0] = 0.0;
        for (int c = 1; c < column; c ++) {
            delta = _standard_normal() * sqrt(dt);
            new[r][c] = new[r][c - 1] + delta;
        }
    }
    return new;
}

static double wiener_increment(double base, double t, double t1) {
    double delta = t1 - t;
    return base + sqrt(delta) * _standard_normal();
}

double ** wiener_process_stage(int row, int column, double t0, double t1, double base, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    double delta = (t1 - t0) / (column - 1), t_current, t_next;
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "wiener_process_stage");

    #pragma omp parallel for if(isMultiple)
    for (int r = 0; r < row; r++) {
        new[r][0] = base;
        for (int c = 1; c < column; c ++) {
            t_current = t0 + (c - 1) * delta;
            t_next = t0 + c * delta;
            new[r][c] = wiener_increment(new[r][c - 1], t_current, t_next);
        }
    }
    return new;
}

double ** dirichlet(double * alpha, int len, int size, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(size, len);
    double alpha_value;
    bool isMultiple = size * len >= ComplexDVCST;
    multp_msg(size * len, isMultiple, true, "dirichlet");

    #pragma omp parallel for schedule(dynamic) if(isMultiple)
    for (int s = 0; s < size; s++) {
        double * gamma_samples = (double *)malloc(sizeof(double) * len);
        double sum = 0.0;
        #pragma omp parallel for reduction(+ :sum) if(len >= 0.1 * ComplexDVCST && isMultiple)
        for (int i = 0; i < len; i++) {
            alpha_value = alpha[i];
            if (alpha_value > 1.0) {
                gamma_samples[i] = gamma_shape_gt_1(alpha_value, 1.0);
            } else if (alpha_value == 1.0) {
                gamma_samples[i] = gamma_shape_eq_1(1.0, 0.0);
            } else {
                gamma_samples[i] = gamma_shape_lt_1(alpha_value, 1.0);
            }
            sum += gamma_samples[i];
        }
        #pragma omp simd if(len >= 0.1 * ComplexDVCST && isMultiple)
        for (int i = 0; i < len; i++){
            new[s][i] = gamma_samples[i] / sum;
        }
        free(gamma_samples);
    }
    return new;
}

double ** laplacedis(int row, int column, double mu, double b, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double **new = allocateButNoNumbers(row, column);
    double u;
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "laplacedis_stage");
    
    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++) {
            u = _standard_uniform() - 0.5;
            new[r][c] = mu - b * _sgn(u) * log(1.0 - 2.0 * fabs(u));
        }
    }
    return new;
}

static double _gumbel_r(double mu, double beta) {
    double u = _standard_uniform();
    return mu - beta * log(-log(u));
}

static double _gumbel_l(double mu, double beta) {
    double u = _standard_uniform();
    return mu + beta * log(-log(u));
}

double ** gumbel(int row, int column, double mu, double beta, bool left, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    double (* _func)(double, double);
    _func = left ? _gumbel_l : _gumbel_r;
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "gumbel");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++) {
            new[r][c] = _func(mu, beta);
        }
    }
    return new;
}

double ** hypergeometric(int row, int column, int expected, int unexpected, int n, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    int sample_count, draw;
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "hypergeometric");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++) {
            sample_count = 0;
            for (int i = 0; i < n; i++) {
                draw = rand() % (expected + unexpected);
                sample_count += draw < expected;
            }
            new[r][c] = (double)sample_count;
        }
    }
    return new;
}

static double _logseries(double p) {
    return log(1.0 - _standard_uniform() * log(1.0 - p)) / log(p) + 1.0;
}

double ** logseries(int row, int column, double p, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "logseries");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++) {
            new[r][c] = _logseries(p);
        }
    }
    return new;
}

static double _weibull(double lambda, double k) {
    return lambda * pow((-log(_standard_uniform())), 1.0 / k);
}

double ** weibull(int row, int column, double lambda, double k, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "weibull");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++) {
            new[r][c] = _weibull(lambda, k);
        }
    }
    return new;
}

static double _triangular(double left, double middle, double right) {
    double U = _standard_uniform();
    if (U < (middle - left) / (right - left))
        return left + sqrt(U * (right - left) * (middle - left));
    return right - sqrt((1 - U) * (right - left) * (right - middle));
}

double ** triangular(int row, int column, double left, double middle, double right, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "triangular");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++){
            new[r][c] = _triangular(left, middle, right);
        }
    }
    return new;
}

static double _power_law(double xmin, double alpha) {
    return xmin * pow(1.0 - _standard_uniform(), -1.0 / (alpha - 1.0));
}

double ** power_law(int row, int column, double xmin, double alpha, int seed, bool use){
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "power_law");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++){
            new[r][c] = _power_law(xmin, alpha);
        }
    }
    return new;
}

static double _rayleigh(double sigma) {
    return sigma * sqrt(-2.0 * log(1.0 - _standard_uniform()));
}

double ** rayleigh(int row, int column, double sigma, int seed, bool use){
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "rayleigh");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++){
            new[r][c] = _rayleigh(sigma);
        }
    }
    return new;
}

static double _stabledis(double alpha, double beta, double gamma, double delta) {
    double U = _uniform(-M_PI / 2.0, M_PI / 2.0);
    double W = -log(_standard_uniform());
    double c_alpha = beta * tan(M_PI * alpha / 2.0);
    double part1 = sin(alpha * U + c_alpha) / pow(cos(U), 1.0 / alpha);
    double part2 = pow(cos(U - alpha * U) / W, (1.0 - alpha) / alpha);
    return gamma * part1 * part2 + delta;
}

double ** stabledis(int row, int column, double alpha, double beta, double gamma, double delta, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "stabledis");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++){
            new[r][c] = _stabledis(alpha, beta, gamma, delta);
        }
    }
    return new;
}

static double _pareto(double xmin, double alpha) {
    return xmin * pow(1.0 - _standard_uniform(), -1.0 / alpha);
}

double ** pareto(int row, int column, double xmin, double alpha, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "pareto");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++){
            new[r][c] = _pareto(xmin, alpha);
        }
    }
    return new;
}

static double _rice(double v, double sigma) {
    double X1 = _normal(v, sigma);
    double X2 = _normal(0.0, sigma);
    return sqrt(X1 * X1 + X2 * X2);
}

double ** rice(int row, int column, double v, double sigma, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "rice");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c ++){
            new[r][c] = _rice(v, sigma);
        }
    }
    return new;
}

static double _wald(double mu, double sigma) {
    double z, w, x, y, denominator;
    while (true) {
        z = _standard_normal();
        w = -log(1.0 - _standard_uniform());
        y = (mu * mu) / (2.0 * sigma * w);
        denominator = (mu + mu * mu * z * z / (2.0 * sigma * w));
        if (w <= y / denominator) {
            x = mu + (mu * mu * z * z) / (2.0 * sigma * w) - (mu / 2.0);
            return x;
        }
    }
}

double ** wald(int row, int column, double mu, double sigma, int seed, bool use) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = allocateButNoNumbers(row, column);  
    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "wald");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++){
            new[r][c] = _wald(mu, sigma);
        }
    }
    return new;
}

