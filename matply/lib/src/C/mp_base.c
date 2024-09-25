//
// Created by 25654 on 24-9-20.
//

#include "mp_base.h"

#ifdef MP_AUXILIARY_H
#else
    #include "mp_auxiliary.h"
#endif

#ifdef MP_CFG_H
#else
    #include "mp_cfg.h"
#endif

#ifdef _INC_STDLIB
#else
#include <stdlib.h>
#endif

#ifdef _INC_STRING
#else
#include <string.h>
#endif

#ifdef _MATH_H_
#else
#include <math.h>
#endif

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
    #define COMPARE_OP(op, d1, d2, col, ro, n) {                \
    for (int r = 0;r < ro;r++)                                  \
    {                                                           \
        n[r] = (bool *)malloc(sizeof(bool) * col);              \
        for(int c=0;c < col;c ++)                               \
        {                                                       \
            n[r][c] = (d1[r][c] op d2[r][c]) ? true : false;    \
            }                                                   \
        }                                                       \
    }
    bool ** new = (bool **)malloc(sizeof(bool *) * row);
    switch (mode) {
    case 1:
        COMPARE_OP(>, data1, data2, column, row, new)
        break;
    case 2:
        COMPARE_OP(<, data1, data2, column, row, new)
        break;
    case 3:
        COMPARE_OP(<=, data1, data2, column, row, new)
        break;
    case 4:
        COMPARE_OP(>=, data1, data2, column, row, new)
        break;
    default:
        COMPARE_OP(==, data1, data2, column, row, new)
        break;
    }
    #undef COMPARE_OP
    return new;
}

double * sum( int row,  int column,  double **data,  int dim)
{
    double * number = NULL;
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
    double ** new = (double **)malloc(sizeof(double *) *height);
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
        case 0:
            MATCH2(data, pow, new, column, row)
            break;
        case 1:
            MATCH2(data, atan2, new, column, row)
            break;
        default:
            break;
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
        case 0: MATCH3(data, pow, new, column, row)
        case 1: MATCH3(data, atan2, new, column, row)
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
    sortNoReturned(row, column, new, reverse, dim, mask_nan);
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
                        (*number)++;
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

double ** concatsR(
        int row,
        int column1,
        int column2,
        int column3,
        int column4,
        double ** data1,
        double ** data2,
        double ** data3,
        double ** data4
){
    double ** new = (double **) malloc(sizeof (double *) * row);
    int totalColumn = column1 + column2;
    if (data3 != NULL && data4 == NULL){
        totalColumn += column3;
        for(int r = 0;r < row;r++){
            new[r] = (double *) malloc(sizeof (double ) * totalColumn);
            int currentIndex = 0, c;
            for (c = 0;c < column1;c ++)
                new[r][currentIndex++] = data1[r][c];
            for (c = 0;c < column2;c ++)
                new[r][currentIndex++] = data2[r][c];
            for (c = 0;c < column3;c ++)
                new[r][currentIndex++] = data3[r][c];
        }
    } else {        // 只考虑data3 != NULL && data4 != NULL
        totalColumn += column4 + column3;
        for(int r = 0;r < row;r++){
            new[r] = (double *) malloc(sizeof (double ) * totalColumn);
            int currentIndex = 0, c;
            for (c = 0;c < column1;c ++)
                new[r][currentIndex++] = data1[r][c];
            for (c = 0;c < column2;c ++)
                new[r][currentIndex++] = data2[r][c];
            for (c = 0;c < column3;c ++)
                new[r][currentIndex++] = data3[r][c];
            for (c = 0;c < column4;c ++)
                new[r][currentIndex++] = data4[r][c];
        }
    }
    return new;
}

double ** concatsC(
        int row1,
        int row2,
        int row3,
        int row4,
        int column,
        double ** data1,
        double ** data2,
        double ** data3,
        double ** data4
){
    int totalRow = row1 + row2;
    double ** new = NULL;
    if (data3 != NULL && data4 == NULL){
        totalRow += row3;
        new = allocateButNoNumbers(totalRow, column);
        int currentIndex = 0;
        for(int r = 0;r < row1;r ++){
            for (int c = 0;c < column;c ++)
                new[currentIndex][c] = data1[r][c];
            currentIndex++;
        }
        for(int r = 0;r < row2;r ++){
            for (int c = 0;c < column;c ++)
                new[currentIndex][c] = data2[r][c];
            currentIndex++;
        }
        for(int r = 0;r < row3;r ++){
            for (int c = 0;c < column;c ++)
                new[currentIndex][c] = data3[r][c];
            currentIndex++;
        }
    } else{
        new = allocateButNoNumbers(totalRow + row3 + row4, column);
        int currentIndex = 0;
        for(int r = 0;r < row1;r ++){
            for (int c = 0;c < column;c ++)
                new[currentIndex][c] = data1[r][c];
            currentIndex++;
        }
        for(int r = 0;r < row2;r ++){
            for (int c = 0;c < column;c ++)
                new[currentIndex][c] = data2[r][c];
            currentIndex++;
        }
        for(int r = 0;r < row3;r ++){
            for (int c = 0;c < column;c ++)
                new[currentIndex][c] = data3[r][c];
            currentIndex++;
        }
        for(int r = 0;r < row4;r ++){
            for (int c = 0;c < column;c ++)
                new[currentIndex][c] = data4[r][c];
            currentIndex++;
        }
    }
    return new;
}

double *** split(int row, int column, double ** data, int len, int * slices, bool mode) {
    int num_splits = len + 1;
    double *** new = (double ***)malloc(num_splits * sizeof(double **));
    if (mode) {
        for (int i = 0; i < num_splits; i++) {
            int start = (i == 0) ? 0 : slices[i - 1];
            int end = (i == len) ? column : slices[i];
            int dim1 = row;
            int dim2 = end - start;
            new[i] = (double **)malloc(dim1 * sizeof(double *));
            for (int r = 0; r < dim1; r++) {
                new[i][r] = (double *)malloc(dim2 * sizeof(double));
                for (int c = 0; c < dim2; c ++) {
                    new[i][r][c] = data[r][start + c];
                }
            }
        }
    } else {
        for (int i = 0; i < num_splits; i++) {
            int start = (i == 0) ? 0 : slices[i - 1];
            int end = (i == len) ? row : slices[i];
            int dim1 = end - start;
            int dim2 = column;
            new[i] = (double **)malloc(dim1 * sizeof(double *));
            for (int r = 0; r < dim1; r++) {
                new[i][r] = (double *)malloc(dim2 * sizeof(double));
                for (int c = 0; c < dim2; c ++) {
                    new[i][r][c] = data[start + r][c];
                }
            }
        }
    }
    return new;
}

double ** cover(int row, int column, double ** data1, int row1, int column1, double ** data2, int rowx, int rowy){
    double ** new = deepcopy(row, column, data1);
    int needColumn = column1 + rowy <= column ? column1 : column - rowy;
    int needRow = row1 + rowx <= row ? row1 : row - rowx;
    for (int r = 0;r < needRow;r++){
        for(int c = 0;c < needColumn;c ++){
            new[r + rowx][c + rowy] = data2[r][c];
        }
    }
    return new;
}

double ** stretch_repeat(int row, int column, double ** data, int len, bool hor){
    double ** new = NULL;
    if (hor){
        new = (double **) malloc(sizeof (double *) * row);
        int newColumn = len + column;
        for (int r = 0;r < row;r++){
            new[r] = (double *) malloc(sizeof (double ) * newColumn);
            for (int c = 0;c < newColumn;c ++) {
                new[r][c] = data[r][c % column];
            }
        }
    } else{
        int newRow = row + len;
        new = (double ** ) malloc(sizeof (double *) * newRow);
        for (int r = 0;r < newRow;r++){
            new[r] = (double *) malloc(sizeof (double )* column);
            memcpy(new[r], data[r % row], column * sizeof (double ));
        }
    }
    return new;
}

double ** stretch_replace(int row, int column, double ** data, int len, bool hor, double number){
    double ** new = NULL;
    if (hor){
        int newColumn = column + len, c;
        new = (double **) malloc(sizeof (double *) * row);
        for(int r = 0;r < row;r++){
            new[r] = (double *) malloc(sizeof (double ) * newColumn);
            c = 0;
            for (;c < column;c ++)
                new[r][c] = data[r][c];
            for (;c < newColumn;c ++)
                new[r][c] = number;
        }
    } else{
        int newRow = len + row;
        new = (double **) malloc(sizeof (double *) * newRow);
        int r = 0;
        for (;r < row;r++){
            new[r] = (double *) malloc(sizeof (double ) * column);
            memcpy(new[r], data[r], column * sizeof (double ));
        }
        for (;r < row + 1;r++){
            new[row] = (double *) malloc(sizeof (double ) * column);
            for (int c = 0;c < column;c ++)
                new[r][c] = number;
        }
        for (;r < newRow;r++){
            new[r] = (double *) malloc(sizeof (double ) * column);
            memcpy(new[r], new[row], column * sizeof (double ));
        }
    }
    return new;
}

double ** stretch_head(int row, int column, double ** data, int len, bool hor){
    double ** new = NULL;
    if (hor){
        int newColumn = column + len, c;
        new = (double **) malloc(sizeof (double ) * row);
        for (int r = 0;r < row;r++){
            new[r] = (double *) malloc(sizeof (double ) * newColumn);
            c = 0;
            for(;c < column;c ++)
                new[r][c] = data[r][c];
            for(;c < newColumn;c ++)
                new[r][c] = data[r][0];
        }
    } else{
        int newRow = row + len, r = 0;
        new = (double **) malloc(sizeof (double *)*newRow);
        for(;r < row;r++ ){
            new[r] = (double *) malloc(sizeof (double ) * column);
            memcpy(new[r], data[r], column * sizeof (double ));
        }
        for (;r < newRow;r++){
            new[r] = (double *) malloc(sizeof (double ) * column);
            memcpy(new[r], data[0], column * sizeof (double ));
        }
    }
    return new;
}

double ** stretch_end(int row, int column, double ** data, int len, bool hor){
    double ** new = NULL;
    if (hor){
        int newColumn = column + len, c, last = column - 1;
        new = (double **) malloc(sizeof (double ) * row);
        for (int r = 0;r < row;r++){
            new[r] = (double *) malloc(sizeof (double ) * newColumn);
            c = 0;
            for(;c < column;c ++)
                new[r][c] = data[r][c];
            for(;c < newColumn;c ++)
                new[r][c] = data[r][last];
        }
    } else{
        int newRow = row + len, r = 0, last = row - 1;
        new = (double **) malloc(sizeof (double *)*newRow);
        for(;r < row;r++ ){
            new[r] = (double *) malloc(sizeof (double ) * column);
            memcpy(new[r], data[r], column * sizeof (double ));
        }
        for (;r < newRow;r++){
            new[r] = (double *) malloc(sizeof (double ) * column);
            memcpy(new[r], data[last], column * sizeof (double ));
        }
    }
    return new;
}

double ** stretch_mirror(int row, int column, double ** data, int len, bool hor){
    double ** new = NULL;
    if (hor){
        new = (double **) malloc(sizeof (double *) * row);
        int newColumn = column + len, c;
        for (int r = 0;r < row;r++){
            new[r] = (double *) malloc(sizeof (double ) * newColumn);
            c = 0;
            for(;c < column;c ++)
                new[r][c] = data[r][c];
            for(;c < newColumn;c ++)
                new[r][c] = data[r][column - 1 - c % column];
        }
    } else{
        int newRow = row + len;
        new = (double **) malloc(sizeof (double *) * newRow);
        for(int r = 0;r < row;r++){
            new[r] = (double *) malloc(sizeof (double ) * column);
            memcpy(new[r], data[r], sizeof (double ) * column);
        }
        for (int r = row;r< newRow;r++){
            new[r] = (double *) malloc(sizeof (double ) * column);
            memcpy(new[r], data[row - 1 - r % row], sizeof (double ) * column);
        }
    }
    return new;
}

double ** stretch_mirrors(int row, int column, double **data, int len, bool hor) {
    double **new = NULL;
    if (hor) {
        new = (double **) malloc(sizeof(double *) * row);
        int newColumn = column + len;
        for (int r = 0; r < row; r++) {
            new[r] = (double *) malloc(sizeof(double) * newColumn);
            for (int c = 0; c < newColumn; c++) {
                int index = c % column;
                bool reverse = (c / column) % 2;
                new[r][c] = data[r][reverse ? column - 1 - index : index];
            }
        }
    } else {
        int newRow = row + len;
        new = (double **) malloc(sizeof(double *) * newRow);
        for (int r = 0; r < newRow; r++) {
            int index = r % row;
            bool reverse = (r / row) % 2;
            new[r] = (double *) malloc(sizeof(double) * column);
            memcpy(new[r], data[reverse ? row - 1 - index : index], sizeof(double) * column);
        }
    }
    return new;
}

double ** stretch(int row, int column, double ** data, int len, bool hor, double number, int method){
    switch (method) {
        case 0:
            return stretch_repeat(row, column, data, len, hor);
        case 1:
            return stretch_replace(row, column, data, len, hor, number);
        case 2:
            return stretch_head(row, column, data, len, hor);
        case 3:
            return stretch_end(row, column, data, len, hor);
        case 4:
            return stretch_mirror(row, column, data, len, hor);
        default:
            return stretch_mirrors(row, column, data, len, hor);
    }
}

double ** diffC(int row, int column, double ** data, double (*func)(double)) {
    double ** new = (double**)malloc(sizeof(double *) * row);
    for (int r = 0;r < row;r++) {
        new[r] = (double *)malloc(sizeof(double) * column);
        for (int c = 0;c < column;c ++) {
            new[r][c] = diffCentral(data[r][c], func);
        }
    }
    return new;
}

double ** get_range(int row, int column, double ** data, int dim) {
    double ** new = NULL;
    double value;
    switch (dim) {
    case 0: {
        new = (double **)malloc(sizeof(double *) * row);
        for (int r = 0; r < row; r++) {
            new[r] = (double *)malloc(sizeof(double) * 2);
            new[r][0] = new[r][1] = data[r][0];
            for (int c = 1; c < column; c ++) {
                value = data[r][c];
                if (value < new[r][0]) new[r][0] = value;
                if (value > new[r][1]) new[r][1] = value;
            }
        }
        return new;
    }
    case 1: {
        new = (double **)malloc(sizeof(double *) * column);
        for (int c = 0; c < column; c ++) {
            new[c] = (double *)malloc(sizeof(double) * 2);
            new[c][0] = new[c][1] = data[0][c];
            for (int r = 1; r < row; r++) {
                value = data[r][c];
                if (value < new[c][0]) new[c][0] = value;
                if (value > new[c][1]) new[c][1] = value;
            }
        }
        return new;
    }
    default: {
        new = (double **)malloc(sizeof(double *));
        new[0] = (double *)malloc(sizeof(double) * 2);
        new[0][0] = new[0][1] = data[0][0];
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c++) {
                value = data[r][c];
                if (value < new[0][0]) new[0][0] = value;
                if (value > new[0][1]) new[0][1] = value;
            }
        }
        return new;
    }
    }
}

double ** cumsum(int row, int column, double ** data, int dim, bool flatten) {
    double ** new = NULL;
    double sums;
    switch (dim) {
    case 0: {
        new = (double **)malloc(sizeof(double *) * row);
        for (int r = 0; r < row; r++) {
            new[r] = (double *)malloc(sizeof(double) * column);
            sums = 0.0;
            for (int c = 0; c < column; c++) {
                sums += data[r][c];
                new[r][c] = sums;
            }
        }
        break;
    }
    case 1: {
        new = (double **)malloc(sizeof(double *) * row);
        for (int r = 0; r < row; r++) {
            new[r] = (double *)malloc(sizeof(double) * column);
        }
        for (int c = 0; c < column; c++) {
            sums = 0.0;
            for (int r = 0; r < row; r++) {
                sums += data[r][c];
                new[r][c] = sums;
            }
        }
        break;
    }
    default: {
        if (flatten) {
            new = (double **)malloc(sizeof(double *));
            new[0] = (double *)malloc(sizeof(double) * (row * column));
            sums = 0.0;
            int index = 0;
            for (int r = 0; r < row; r++) {
                for (int c = 0; c < column; c++) {
                    sums += data[r][c];
                    new[0][index++] = sums;
                }
            }
        }else {
            new = (double **)malloc(sizeof(double *) * row);
            sums = 0.;
            for (int r = 0;r < row;r++) {
                new[r] = (double *)malloc(sizeof(double) * column);
                for (int c = 0;c < column;c ++) {
                    sums += data[r][c];
                    new[r][c] = sums;
                }
            }
        }
        break;
    }
    }
    return new;
}

int _sgn(double x) {return (x > 0) - (x < 0);}


double ** sgn(int row, int column, double ** data) {
    double ** new = (double **)malloc(sizeof(double*) * row);
    for (int r = 0;r < row;r++) {
        new[r] = (double *)malloc(sizeof(double) * column);
        for(int c = 0;c < column;c ++) {
            new[r][c] = _sgn(data[r][c]);
        }
    }
    return new;
}





