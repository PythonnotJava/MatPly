//
// Created by 25654 on 24-9-20.
//

#include "mp_base.h"

double ** filled(int row, int column, double number)
{
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;  
    multp_msg(row * column, isMultiple, false, "filled"); 

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for (int c = 0;c < column;c ++){
            new[r][c] = number;
        }
    }
    return new;
}

double ** zeros(int row, int column){
    double ** new = malloc(sizeof(double *) * row);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "zeros");

    #pragma omp parallel for if(isMultiple)
    for (int r = 0;r < row;r++) {
        new[r] = calloc(column, sizeof(double));
    }
    return new;
}

double ** ones(int row, int column){ return filled(row, column, 1.0); }

double * row_(int row, int column, double ** data)
{
    double * new = (double *)malloc(column * sizeof(double));

    bool isMultiple = column >= SimpleDVCST;
    multp_msg(column, isMultiple, false, "row_");

    #pragma omp parallel for if(isMultiple)
    for (int c = 0;c < column;c ++){
        new[c] = data[row][c];
    }
    return new;
}

double * column_(int row, int column, double ** data)
{
    double * new = (double*)malloc(row *sizeof(double));

    bool isMultiple = row >= SimpleDVCST;
    multp_msg(row, isMultiple, false, "column_");

    #pragma omp parallel for if(isMultiple) 
    for (int r = 0;r < row;r++){
        new[r] = data[r][column];
    }
    return new;
}

double at(int row, int column, double ** data){return data[row][column];}

double ** arrange(double start, int row, int column)
{
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "arrange");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for(int c = 0;c < column;c ++) {
            new[r][c] = start + r * column + c;
        }
    }
    return new;
}

double ** linspace(double start, double end, int row, int column, bool keep)
{
    int counts = row * column;
    double step = keep ? (end - start) / (counts - 1) : (end - start) / counts;
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = counts >= SimpleDVCST;
    multp_msg(counts, isMultiple, false, "linspace");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c< column; c ++) {
            new[r][c] = start + (r * column + c) * step;
        }
    }
    if (keep){
        new[row - 1][column - 1] = end;
    }
    return new;
}

double ** deepcopy( int row,  int column,  double **data)
{
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "deepcopy");

    #pragma omp parallel for if(isMultiple)
    for (int r = 0; r < row; r++) {
        memcpy(new[r], data[r], column * sizeof(double));
    }
    return new;
}

bool ** compare(int row, int column, double **data1, double ** data2, int mode)
{
    bool ** new = allocateTDABools(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "compare");

    switch (mode) {
    case 1:
        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c ++) {
                new[r][c] = data1[r][c] > data2[r][c];
            }
        }
        break;
    case 2:
        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c ++) {
                new[r][c] = data1[r][c] < data2[r][c];
            }
        }
        break;
    case 3:
        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c ++) {
                new[r][c] = data1[r][c] <= data2[r][c];
            }
        }
        break;
    case 4:
        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c ++) {
                new[r][c] = data1[r][c] >= data2[r][c];
            }
        }
        break;
    default:
        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c ++) {
                new[r][c] = data1[r][c] == data2[r][c];
            }
        }
        break;
    }
    return new;
}

double * sum( int row, int column, double **data,  int dim)
{
    double * number = NULL;

    bool isMultiple = row * column >= SimpleDVCST; 
    multp_msg(row * column, isMultiple, false, "sum");  

    switch (dim) {
    case 0:
        number = (double *)calloc(row, sizeof(double));
        #pragma omp parallel for schedule(dynamic) if(isMultiple)  // 考虑到大部分案例都是row远大于column
        for (int r = 0; r < row; r++) {
            double v = 0.0;
            #pragma omp parallel for schedule(static) reduction(+:number[r]) if(column >= 0.1 * SimpleDVCST && isMultiple)
            for (int c = 0; c < column; c ++) {
                v += data[r][c];
            }
            number[r] = v;
        }
        break;
    case 1:
        number = (double *)calloc(column, sizeof(double));
        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int c = 0; c < column; c ++) {
            double v = 0.0;
            #pragma omp parallel for schedule(static) reduction(+:number[c]) if(row >= 0.1 * SimpleDVCST && isMultiple)
            for (int r = 0; r < row; r++) {
                v += data[r][c];
            }
            number[c] = v;
        }
        break;
    default:
        number = (double *)malloc(sizeof(double));
        if(!isMultiple) {
            long double v = 0.0;
            for (int r = 0; r < row; r++) {
                for (int c = 0; c < column; c++) {
                    v += data[r][c];
                }
            }
            *number = (double)v;
            break;
        }else {
            long double v = 0.0;
            #pragma omp parallel for reduction(+:v)
            for (int i = 0;i < row * column;i++) {
                v += data[i / column][i % column];
            }
            *number = (double)v;
        }
    }
    return number;
}

double * mean( int row,  int column,  double **data,  int dim)
{
    double * number = NULL;
    bool isMultiple = false;
    switch (dim)
    {
    case 0:
        number = sum(row, column, data, 0);
        
        isMultiple = row >= SimpleDVCST;
        multp_msg(row, isMultiple, false, "mean");

        #pragma omp parallel for if(isMultiple)
        for (int r=0;r < row;r++){
            number[r] /=  column;
        }
        break;
    case 1:
        number = sum(row, column, data, 1);

        isMultiple = column >= SimpleDVCST;
        multp_msg(column, isMultiple, false, "mean");

        #pragma omp parallel for if(isMultiple)
        for (int c = 0;c < column;c ++){
            number[c] /= row;
        }
        break;
    default:
        multp_msg(1, isMultiple, false, "mean");
        number = sum(row, column, data, -1);
        *number = *number / (row * column);
        break;
    }
    return number;
}

double * min( int row,  int column,  double **data,  int dim)
{
    double * number = NULL;

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "min");

    switch (dim)
    {
    case 0:
        number = (double *)malloc(sizeof(double) * row);

        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int r = 0; r < row; r++) {
            double min = data[r][0];
            #pragma omp parallel for schedule(static) reduction(min:min) if(column >= 0.1 * SimpleDVCST && isMultiple)
            for (int c = 1; c < column; c ++) {
                min = fmin(min, data[r][c]);
            }
            number[r] = min;
        }
        break;
    case 1:
        number = (double *)malloc(sizeof(double) * column);

        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int c = 0; c < column; c ++) {
            double min = data[0][c];
            #pragma omp parallel for schedule(static) reduction(min:min) if(row >= 0.1 * SimpleDVCST && isMultiple)
            for (int r = 1; r < row; r++) {
                min = fmin(min, data[r][c]);
            }
            number[c] = min;
        }
        break;
    default:
        number = (double *)malloc(sizeof(double));
        double v = data[0][0];
        #pragma omp parallel for collapse(2) reduction(min:v) if(isMultiple)
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c ++) {
                v = fmin(v, data[r][c]);
            }
        }
        *number = v;
        break;
    }
    return number;
}

double * max(int row, int column, double **data, int dim)
{
    double * number = NULL;

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "max");

    switch (dim)
    {
    case 0:
        number = (double*)malloc(sizeof(double) * row);
        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int r=0;r < row;r++) {
            double max = data[r][0];
            #pragma omp parallel for schedule(static) reduction(max:max) if(column >= 0.1 * SimpleDVCST && isMultiple)
            for (int c = 1; c < column; c ++) {
                max = fmax(max, data[r][c]);
            }
            number[r] = max;
        }
        break;
    case 1:
        number = (double*)malloc(sizeof(double) * column);
        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int c = 0; c < column; c++) {
            double max = data[0][c];
            #pragma omp parallel for schedule(static) reduction(max:max) if(row >= 0.1 * SimpleDVCST && isMultiple)
            for (int r = 1; r < row; r++) {
                max = fmax(max, data[r][c]);
            }
            number[c] = max;
        }
        break;
    default:
        number = (double *)malloc(sizeof(double));
        double v = data[0][0];
        #pragma omp parallel for collapse(2) reduction(max:v) if(isMultiple)
        for(int r=0;r < row;r++) {
            for (int c = 0;c < column;c ++) {
                v = fmax(v, data[r][c]);    
            }
        }
        *number = v;
        break;
    }
    return number;
}

double ** cut(int row, int column, double ** data, int prow, int pcolumn, int width, int height)
{
    double ** new = allocateButNoNumbers(height, width);  

    bool isMultiple = height * width >= SimpleDVCST;
    multp_msg(height * width, isMultiple, false, "cut");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c ++) {
            new[r][c] = data[prow + r][pcolumn + c];
        }
    }
    return new;
}

double ** cutfree(int row, int column, double ** data, int prow, int pcolumn, int width, int height, double number)
{
    double ** new = allocateButNoNumbers(height, width);  
    // 有效部分
    int valid_rows = (prow + height <= row) ? height : row - prow;
    int valid_cols = (pcolumn + width <=  column) ? width : column - pcolumn;

    bool bound = SimpleDVCST / 2;
    bool task1 = valid_rows * valid_cols >= bound;
    bool task2 = (width - valid_cols) * valid_rows >= bound;
    bool task3 = (height - valid_rows) * width >= bound;
    bool isMultiple =  task1 || task2 || task3;
    mixin_multp_msg(height * width, isMultiple, false, "cutfree");

    #pragma omp task if(isMultiple)
    {
        #pragma omp parallel for collapse(2) if(task1)
        for (int r = 0; r < valid_rows; r++) {
            for (int c = 0; c < valid_cols; c ++) {
                new[r][c] = data[prow + r][pcolumn + c];
            }
        }
        // 越界部分
        if (valid_cols < width) {
            #pragma omp parallel for collapse(2) if(task2)
            for (int r = 0; r < valid_rows; r++) {
                for (int c = valid_cols; c < width; c ++) {
                    new[r][c] = number;
                }
            }
        }
        // 填补下边越界部分
        if (valid_rows < height) {
            #pragma omp parallel for collapse(2) if(task3)
            for (int r = valid_rows; r < height; r++) {
                for (int c = 0; c < width; c ++) {
                    new[r][c] = number;
                }
            }
        }
    }
    return new;
}

double ** concatR(int row, int column1, int column2, double ** data1, double ** data2)
{
    double ** new = allocateButNoNumbers(row, column1 + column2);
    bool task1 = row * column1 >= SimpleDVCST / 2;
    bool task2 = row * column2 >= SimpleDVCST / 2;
    bool isMultiple = task1 || task2;
    mixin_multp_msg(row * (column1 + column2), isMultiple, false, "concatR");
    
    if(!isMultiple){
        for (int r = 0;r < row;r++) {
            for (int c = 0;c < column1;c ++) {
                new[r][c] = data1[r][c];
            }
            for (int c = 0;c < column2;c ++) {
                new[r][c + column1] = data2[r][c];
            }
        }
    }else{
        #pragma omp parallel for collapse(2) if(task1)
        for (int r = 0;r < row;r++) {
            for (int c = 0;c < column1;c ++) {
                new[r][c] = data1[r][c];
            }
        }
        #pragma omp parallel for collapse(2) if(task2)
        for (int r = 0;r < row;r++) {
            for (int c = 0;c < column2;c ++) {
                new[r][c + column1] = data2[r][c];
            }
        }
    }
 
    return new;
}

double ** concatC(int row1, int row2, int column, double ** data1, double ** data2)
{
    double ** new = allocateButNoNumbers(row1 + row2, column);
    bool task1 = row1 * column >= SimpleDVCST / 2;
    bool task2 = row1 * column >= SimpleDVCST / 2;
    bool isMultiple = task1 || task2;
    mixin_multp_msg((row1 + row2) * column, isMultiple, false, "concatC");

    #pragma omp parallel for collapse(2) if(task1)
    for (int r = 0; r < row1; r++) {
        for (int c = 0; c < column; c ++) {
            new[r][c] = data1[r][c];
        }
    }
    #pragma omp parallel for collapse(2) if(task2)
    for (int r = 0; r < row2; r++) {
        for (int c = 0; c < column; c ++) {
            new[r + row1][c] = data2[r][c];
        }
    }
    return new;
}

double ** resizeR(int row, int column, double ** data, int origin_row, int origin_column, double number)
{
    int origin_size = origin_column * origin_row;
    int new_size = row * column;
    double ** new = allocateButNoNumbers(row, column);
    int counter;
    if (origin_size >= new_size) {
        bool isMultiple = new_size >= SimpleDVCST;
        multp_msg(new_size, isMultiple, false, "resizeR");

        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0;r < row;r++) {
            for (int c = 0;c < column;c ++) {
                counter = r * column + c;
                new[r][c] = data[counter / origin_column][counter % origin_column];
            }
        }
    } else {
        bool task1 = origin_size >= SimpleDVCST / 2;
        bool task2 = new_size - origin_size >= SimpleDVCST / 2;
        bool isMultiple = task1 || task2;
        mixin_multp_msg(new_size, isMultiple, false, "resizeR");

        #pragma omp parallel for collapse(2) if(task1)
        for (int r = 0;r < origin_row;r++) {
            for (int c = 0;c < origin_column;c ++) {
                counter = r * origin_column + c;
                new[counter / column][counter % column] = data[r][c];
            }
        }
        #pragma omp parallel for if(task2)
        for (counter = origin_size;counter < new_size;counter++){
            new[counter / column][counter % column] = number;
        }
    }
    return new;
}

double ** resizeC(int row, int column, double ** data, int origin_row, int origin_column, double number)
{
    int origin_size = origin_column * origin_row;
    int new_size = row * column;
    double ** new = allocateButNoNumbers(row, column);
    int counter;

    if (origin_size >= new_size) {
        bool isMultiple = new_size >= SimpleDVCST;
        multp_msg(new_size, isMultiple, false, "resizeC");

        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int c = 0; c < column; c ++) {
             for (int r = 0; r < row; r++){
                counter = r * column + c;
                new[r][c] = data[counter % origin_row][counter / origin_row];
            }
        }
    } else {
        bool task1 = origin_size >= SimpleDVCST / 2;
        bool task2 = new_size - origin_size >= SimpleDVCST / 2;

        bool isMultiple = task1 || task2;
        mixin_multp_msg(new_size, isMultiple, false, "resizeC");

        #pragma omp parallel for collapse(2) if(task1)
        for (int c = 0; c < origin_column; c ++) {
            for (int r = 0; r < origin_row; r++) {
                counter = r * origin_column + c;
                new[counter % row][counter / row] = data[r][c];
            }
        }
        #pragma omp parallel for if(task2)
        for (counter = origin_size; counter < new_size; counter++){
            new[counter % row][counter / row] = number;
        }
    }
    return new;
}

double ** reshape(int row, int column, double ** data, int origin_column)
{
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "reshape");

    int counter;

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r ++) {
        for(int c = 0;c <column;c ++) {
            counter = r * column + c;
            new[r][c] = data[counter / origin_column][counter % origin_column];
        }
    }
    return new;
}

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

static double degrees(double theta) {
    return theta * (180.0 / M_PI);
}

static double (*_MathBasement1funcs[])(double) = {
    acos, asin, atan, cos, sin,
    tan, cosh, sinh, tanh, exp,
    log, log10, sqrt, ceil, floor,
    fabs, degrees  // 17
};

static char * _MathBasement1func_names[] = {
    "acos", "asin", "atan", "cos", "sin",
    "tan", "cosh", "sinh", "tanh", "exp",
    "log", "log10", "sqrt", "ceil", "floor",
    "fabs", "degrees" // 17
};

static int _MathBasement1funcsLength = sizeof(_MathBasement1funcs) / sizeof(_MathBasement1funcs[0]);

static double (*_MathBasement2funcs[])(double, double) = {
    pow, atan2  // 2
};

static char * _MathBasement2funcs_names[] = {
    "pow", "atan2" // 17
};

static int _MathBasement2funcsLength = sizeof(_MathBasement2funcs) / sizeof(_MathBasement2funcs[0]);

#define GetFuncName(x) #x

double ** mathBasement1(int row, int column, double ** data, int mode){
    double ** new = allocateButNoNumbers(row, column);
    double (*func)(double) = mode < _MathBasement1funcsLength ? _MathBasement1funcs[mode] : NULL;
    if (func) {
        bool isMultiple = row * column >= SimpleDVCST;
        multp_msg(row * column, isMultiple, false, _MathBasement1func_names[mode]);

        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0;r < row;r ++) {
            for(int c = 0;c < column;c ++) {
                new[r][c] = func(data[r][c]);
            }
        }
        return new;
    }
    return data;
}

double ** mathBasement2(int row, int column, double ** data, int mode, double number){
    double ** new = allocateButNoNumbers(row, column);
    double (*func)(double, double) = mode < _MathBasement2funcsLength ? _MathBasement2funcs[mode] : NULL;
    if (func) {
        bool isMultiple = row * column >= SimpleDVCST;
        multp_msg(row * column, isMultiple, false, _MathBasement2funcs_names[mode]);

        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0;r < row;r ++) {
            for(int c = 0;c < column;c ++) {
                new[r][c] = func(data[r][c], number);
            }
        }
        return new;
    }
    return data;
}

double ** mathBasement2reverse(int row, int column, double ** data, int mode, double number)
{                                      
    double ** new = allocateButNoNumbers(row, column);
    double (*func)(double, double) = mode < _MathBasement2funcsLength ? _MathBasement2funcs[mode] : NULL;
    if (func) {
        bool isMultiple = row * column >= SimpleDVCST;
        multp_msg(row * column, isMultiple, false, _MathBasement2funcs_names[mode]);

        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0;r < row;r ++) {
            for(int c = 0;c < column;c ++) {
                new[r][c] = func(number, data[r][c]);
            }
        }
        return new;
    }
    return data;
}

double ** sigmoid(int row, int column, double ** data)
{
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "sigmoid");

    #pragma omp parallel for if (isMultiple)
    for (int r=0;r < row;r ++) {
        for (int c = 0;c < column;c ++) {
            new[r][c] = 1.0 / (1.0 + exp(-data[r][c]));
        }
    }
    return new;
}

double ** softmax( int row,  int column,  double ** data,  int dim,  double mask_nan,  double mask_inf,  double mask_neginf)
{
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= ComplexDVCST;
    multp_msg(row * column, isMultiple, true, "softmax");

    double dat = 0.;
    #pragma omp parallel for if (isMultiple)
    for (int r = 0;r < row;r ++) {
        for (int c = 0;c < column;c ++) {
            dat = data[r][c];
            if (!isnan(dat) && !isinf(dat))
                new[r][c] = exp(dat);
            else {
                if (isnan(dat))
                    new[r][c] = exp(mask_nan);
                else if (isinf(dat) && dat > 0)
                    new[r][c] = exp(mask_inf);
                else
                    new[r][c] = exp(mask_neginf);
            }
        }
    }

    double * sums = NULL;
    switch (dim)
    {
    case 0:
        sums = sum(row, column, new, 0);
        #pragma omp parallel for collapse(2) if (isMultiple)
        for(int r = 0;r < row;r++) {
            for (int c = 0;c < column;c ++) {
                new[r][c] /= sums[r];
            }
        }
        break;
    case 1:
        sums = sum(row, column, new, 1);
        #pragma omp parallel for collapse(2) if (isMultiple)
        for(int r=0;r < row;r ++) {
            for (int c = 0;c < column;c ++) {
                new[r][c] /= sums[c];
            }
        }
        break;
    default:
        sums = sum(row, column, new, -1);
        #pragma omp parallel for collapse(2) if (isMultiple)
        for(int r=0;r < row;r ++) {
            for (int c = 0;c < column;c ++) {
                new[r][c] /= *sums;
            }
        }
        break;
    }
    free(sums);
    return new;
}

static int __compare(const void* a, const void* b) {
    double diff = *(double*)a - *(double*)b;
    return (diff > 0) - (diff < 0);
}

static int __reverse_compare(const void* a, const void* b) {
    double diff = *(double*)b - *(double*)a;
    return (diff > 0) - (diff < 0);
}

void sortNoReturned( int row,  int column, double ** data,  bool reverse,  int dim,  double mask_nan)
{
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "sortNoReturned");

    #pragma omp parallel for  collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++){
        for(int c = 0;c < column;c ++){
            if (isnan(data[r][c])){
                data[r][c] = mask_nan;
            }
        }
    }
    switch (dim) {
        case 0:
            #pragma omp parallel for if (isMultiple)
            for (int r = 0; r < row;r++) {
                reverse ?
                qsort(data[r], column, sizeof(double), __reverse_compare) :
                qsort(data[r], column, sizeof(double), __compare);
            }
            break;
        case 1:
            #pragma omp parallel for if (isMultiple)
            for (int c = 0; c < column;c ++) {
                double * col = (double*)malloc(row * sizeof(double));
                for (int r = 0; r < row;r++) {
                    col[r] = data[r][c];
                }
                reverse?
                    qsort(col, row, sizeof(double), __reverse_compare) :
                    qsort(col, row, sizeof(double), __compare);
                for (int r = 0; r< row;r++) {
                    data[r][c] = col[r];
                }
                free(col);
            }
            break;
        default: {
            double * flat = malloc(row * column * sizeof(double));
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r= 0; r < row; r++) {
                for (int c = 0; c < column; c ++) {
                    flat[r * column + c] = data[r][c];
                }
            }
            reverse?
                qsort(flat, row * column, sizeof(double), __reverse_compare) :
                qsort(flat, row * column, sizeof(double), __compare);

            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r = 0; r < row; r ++) {
                for (int c= 0; c < column;c++) {
                    data[r][c] = flat[r * column + c];
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

void set_mask_nan(int row, int column, double ** data, double number)
{   
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "set_mask_nan");

    #pragma omp parallel for if (isMultiple)
    for(int r = 0;r < row;r ++) {
        for (int c = 0;c < column;c ++) {
            if (isnan(data[r][c])){
                data[r][c] = number;
            }
        }
    }
}

void set_mask_inf(int row, int column, double ** data, double number, bool isNegativeInf)
{
    double dat = 0.;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "set_mask_inf");

    #pragma omp parallel for if (isMultiple)
    for(int r = 0;r < row;r ++)  {
        for (int c = 0;c < column;c ++) {
            dat = data[r][c];
            if (isinf(dat) && dat > 0 && !isNegativeInf)
                data[r][c] = number;
            else if (isinf(dat) && dat < 0 && isNegativeInf)
                data[r][c] = number;
        }
    }
}

int * argmax(int row, int column, double ** data, int dim){
    int * number = NULL;
    double value;

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "argmax");

    switch (dim) {
        case 0:
            number = (int *) calloc(row, sizeof (int ) );
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for(int r = 0;r < row;r++){
                value = data[r][0];
                #pragma omp parallel for schedule(static) reduction(max: value) if (column >= 0.1 * SimpleDVCST && isMultiple)
                for(int c = 1;c < column;c ++){
                    if (value < data[r][c]) {
                        value = data[r][c];
                        number[r] = c;
                    }
                }
            }
            break;
        case 1:
            number = (int *) calloc(column, sizeof (int ));
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int c = 0;c < column;c ++){
                value = data[0][c];
                #pragma omp parallel for schedule(static) reduction(max: value) if (row >= 0.1 * SimpleDVCST && isMultiple)
                for(int r = 0;r < row;r ++){
                    if (value < data[r][c]){
                        value = data[r][c];
                        number[c] = r;
                    }
                }
            }
            break;
        default:
            number = (int *) calloc(1, sizeof (int ));
            value = data[0][0];
            #pragma omp parallel for if (isMultiple)
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
    return number;
}

int * argmin(int row, int column, double  **data, int dim){
    int * number = NULL;

    bool isMultiple = row * column >= SimpleDVCST;  
    multp_msg(row * column, isMultiple, false, "argmin");

    double value;
    switch (dim) {
        case 0:
            number = (int *) calloc(row,  sizeof (int ) );
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for(int r = 0;r < row;r++){
                value = data[r][0];
                #pragma omp parallel for schedule(static) reduction(min: value) if (column >= 0.1 * SimpleDVCST && isMultiple)
                for(int c = 1;c < column;c ++){
                    if (value > data[r][c]) {
                        value = data[r][c];
                        number[r] = c;
                    }
                }
            }
            break;
        case 1:
            number = (int *) calloc(column, sizeof (int ));
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int c = 0;c < column;c ++){
                value = data[0][c];
                #pragma omp parallel for schedule(static) reduction(min: value) if (row >= 0.1 * SimpleDVCST && isMultiple)
                for(int r = 0;r < row;r ++){
                    if (value > data[r][c]){
                        value = data[r][c];
                        number[c] = r;
                    }
                }
            }
            break;
        default:
            number = (int *) calloc(1, sizeof (int ));
            value = data[0][0];
            #pragma omp parallel for collapse(2) reduction(+ : value) if (isMultiple)
            for(int r = 0;r < row;r++){
                for(int  c=0;c < column;c ++){
                    if (value > data[r][c]){
                        value = data[r][c];
                        *number = column * r + c;
                    }
                }
            }
            break;
    }
    return number;
}

double * flatten(int row, int column, double ** data, int mode){
    double * new = (double *) malloc(sizeof (double) * (column * row));

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "flatten");

    if (mode == 1){
        #pragma omp parallel for collapse(2) if(isMultiple)
        for(int c = 0;c < column;c ++){
            for (int r = 0;r < row;r ++){
                new[c * row + r] = data[r][c];
            }
        }
    } else{ 
        #pragma omp parallel for collapse(2) if(isMultiple)
        for(int r = 0;r < row;r ++){
            for(int c= 0;c < column;c ++){
                new[r * column + c] = data[r][c];
            }
        }
    }
    return new;
}

double ** range(double start, double step, int row, int column){
    double  **new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "range");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++){
        for(int c= 0;c < column;c ++){
            new[r][c] = start + step * r * column + c;
        }
    }
    return new;
}

double ** replace(int row, int column, double ** data, double number, bool (*condition)(double )){
    double **new = allocateButNoNumbers(row, column);

    no_multp_msg(row * column, false, "replace");

    for (int r = 0;r < row;r ++){
        for (int c = 0;c < column;c ++){
            new[r][c] = (condition(data[r][c])) ? data[r][c] : number;
        }
    }
    return new;
}

void replaceNoReturned(int row, int column, double ** data, double number, bool (*condition)(double )){
    no_multp_msg(row * column, false, "replaceNoReturned");
    for (int r = 0;r < row;r ++){
        for(int c = 0;c < column;c ++){
            if (!condition(data[r][c])){
                data[r][c] = number;
            }
        }
    }
}

double ** sliceR(int column, double ** data, int from, int to){
    int row = to - from + 1;
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "sliceR");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++){
        for (int c = 0;c < column;c ++){
            new[r][c] = data[r + from][c];
        }
    }
    return new;
}

double ** sliceC(int row, double ** data, int from, int to){
    int column = to - from + 1;
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "sliceC");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int c = 0;c< column; c ++){
        for(int r = 0; r< row;r ++){
            new[r][c] = data[r][c + from];
        }
    }
    return new;
}

double ** clip(int row, int column, double  **data, double lb, double ub){
    double ** new = allocateButNoNumbers(row, column);
    double value;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "clip");
    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row; r++){
        for (int c = 0;c < column;c ++){
            value = data[r][c];
            new[r][c] = (value < lb) ? lb : (value > ub) ? ub : value;
        }
    }
    return new;
}

void clipNoReturned(int row, int column, double  **data, double lb, double ub){
    double value;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "clipNoReturned");
    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row; r++){
        for (int c = 0;c < column;c ++){
            value = data[r][c];
            if (value < lb)
                data[r][c] = lb;
            else if (value > ub)
                data[r][c] = ub;
        }
    }
}

bool all(int row, int column, double ** data, bool (*condition)(double)){
    no_multp_msg(row * column, false, "all");

    for (int r = 0;r < row;r ++){
        for (int c =0;c < column;c ++){
            if (!condition(data[r][c]))
                return false;
        }
    }
    return true;
}

bool any(int row, int column, double **data, bool (*condition)(double )){
    no_multp_msg(row * column, false, "any");

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
    no_multp_msg(row * column, false, "counter");

    switch (dim) {
        case 0:
            number = (int *) calloc(row, sizeof (int ));
            for (int r = 0;r < row;r ++){
                for(int c =0;c < column;c ++){
                    if (condition(data[r][c]))
                        number[r]++;
                }
            }
            break;
        case 1:
            number = (int *) calloc(column, sizeof (int ));
            for (int c = 0;c < column;c ++){
                for(int r=0;r< row;r++){
                    if (condition(data[r][c]))
                        number[c]++;
                }
            }
            break;
        default:
            number = (int *) calloc(1, sizeof (int ));
            for (int r = 0;r < row;r ++){
                for(int c =0;c < column;c ++){
                    if (condition(data[r][c]))
                        (*number)++;
                }
            }
            break;
    }
    return number;
}

double * reduce(int row, int column, double ** data, int dim, double (*condition)(double , double ), double init){
    double * number = NULL;
    no_multp_msg(row * column, false, "reduce");
    double value = init;
    switch (dim) {
        case 0:
            number = (double *) malloc(sizeof (double )*row);
            for (int r = 0;r < row;r++){
                for (int c = 0;c < column;c ++){
                    value = condition(value, data[r][c]);  // 这里与condition(data[r][c], value)效果不一样
                }
                number[r] = value;
                value = init;
            }
            break;
        case 1:
            number = (double *) malloc(sizeof (double )*column );
            for (int c =0;c < column;c ++){
                for(int r = 0;r < row;r++){
                    value = condition(value, data[r][c]);
                }
                number[c] = value;
                value = init;
            }
            break;
        default:
            number = (double *) malloc(sizeof (double ));
            for (int r = 0;r < row;r++){
                for (int c = 0;c < column;c ++){
                    value = condition(value, data[r][c]);
                }
            }
            *number = value;
            break;
    }
    return number;
}

double ** E_like(int row, int column){
    double ** new = zeros(row, column);
    int n = row < column ? row : column;
    bool isMultiple = n >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "E_like");

    #pragma omp parallel for if(isMultiple)
    for (int r = 0;r < n;r++){
        new[r][r] = 1.0;
    }
    return new;
}

double ** clip_reverse(int row, int column, double  **data, double lb, double ub, double (*condition)(double)){
    double ** new = (double **) malloc(sizeof (double *) * row);
    no_multp_msg(row * column, false, "clip_reverse");

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
    no_multp_msg(row * column, false, "clip_reverseNoReturned");

    for (int r = 0;r < row;r++){
        for (int c = 0;c < column;c ++){
            value = data[r][c];
            if (value > lb && value < ub){
                data[r][c] = condition(value);
            }
        }
    }
}

double ** customize(int row, int column, double ** data, double (*condition)(double )){
    double ** new = (double **) malloc(sizeof (double *) * row);
    no_multp_msg(row * column, false, "customize");

    for (int r = 0;r < row;r ++){
        new[r] = (double *) malloc(sizeof (double) * column);;
        for (int c = 0;c < column;c ++){
            new[r][c] = condition(data[r][c]);
        }
    }
    return new;
}

int ** findIndexs(int row, int column, double **data, bool (*condition)(double ), int prediction){
    int ** new = (int **) malloc(sizeof (int *) * row);
    no_multp_msg(row * column, false, "findIndexs");

    for (int r = 0;r < row;r++){
        int baseIndex = r * column;
        new[r] = findall_condition(data[r], column, prediction, condition, baseIndex);
    }
    return new;
}

double ** rotate(int row, int column, double ** data, int mode){
    double ** new = NULL;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "rotate");

    switch (mode) {
        case -3: label0: {  // 顺90/逆270
            new = allocateButNoNumbers(column, row);
            
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r = 0; r < column; r++) {
                for (int c = 0; c < row; c++) {
                    new[r][c] = data[row - c - 1][r];
                }
            }
            return new;
        }
        case -2: label1 : {  // 顺逆180
            new = allocateButNoNumbers(row, column);
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r = 0; r < row; r++) {
                for (int c = 0; c < column; c++) {
                    new[r][c] = data[row - r - 1][column - c - 1];
                }
            }
            return new;
        }
        case -1: label2:{  // 逆90/顺270
            {
                new = allocateButNoNumbers(column, row);
                #pragma omp parallel for collapse(2) if(isMultiple)
                for (int r = 0; r < column; r++) {
                    for (int c = 0; c < row; c++) {
                        new[r][c] = data[c][column - r - 1];
                    }
                }
                return new;
            }
        }
        case 0: goto label4;
        case 1: goto label0;
        case 2: goto label1;
        case 3: goto label2;
        default: label4 :{
            new = deepcopy(row, column, data);
            return new;
        }
    }
}

double ** mirror(int row, int column, double ** data, int mode) {
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "mirror");
    
    if (mode == 0) {
        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column;c ++) {
                new[r][c] = data[r][column - c - 1];
            }
        }
    } else {
        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int c = 0; c < column; c ++) {
            for (int r = 0; r < row; r++) {
                new[r][c] = data[row - r - 1][c];
            }
        }
    }
    return new;
}

double ** decentralizate(int row, int column, double **data, int dim){
    double ** new = allocateButNoNumbers(row, column);

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "decentralizate");
    double * means = mean(row, column, data, dim);
    switch (dim) {
        case 0:{
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r = 0;r < row;r++){
                for (int c  =0;c < column;c ++){
                    new[r][c] = data[r][c] - means[r];
                }
            }
            break;
        }
        case 1:{
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int c = 0;c < column;c ++){
                for (int r  = 0;r < row;r++){
                    new[r][c] = data[r][c] - means[c];
                }
            }
            break;
        }
        default:{
            #pragma omp parallel for collapse(2) if(isMultiple)
            for (int r = 0;r < row;r++){
                for (int c  =0;c < column;c ++){
                    new[r][c] = data[r][c] - *means;
                }
            }
            break;
        }
    }
    free(means);
    return new;
}

double ** concatsR(
    int row, int column1, int column2, int column3, int column4, 
    double ** data1, double ** data2, double ** data3, double ** data4
){
    double ** new = NULL;
    int totalColumn = column1 + column2;
    if (data3 != NULL && data4 == NULL){
        totalColumn += column3;

        new = allocateButNoNumbers(row, totalColumn);
        bool isMultiple = row * totalColumn >= SimpleDVCST;
        mixin_multp_msg(row * totalColumn, isMultiple, false, "concatsR");

        if (!isMultiple){
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
        }else{
            #pragma omp parallel for collapse(2) 
            for(int r = 0;r < row;r++){
                for (int c = 0;c < totalColumn;c ++){
                    if (c < column1){
                        new[r][c] = data1[r][c];
                    } else if (c < column1 + column2){
                        new[r][c] = data2[r][c - column1];
                    } else {
                        new[r][c] = data3[r][c - column1 - column2];
                    }
                }
            }
        }
    } else {        // 只考虑data3 != NULL && data4 != NULL
        totalColumn += column4 + column3;

        new = allocateButNoNumbers(row, totalColumn);
        bool isMultiple = row * totalColumn >= SimpleDVCST;
        multp_msg(row * totalColumn, isMultiple, false, "concatsR");

        if (!isMultiple){
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
        }else{
            #pragma omp parallel for collapse(2) 
            for(int r = 0;r < row;r++){
                for (int c = 0;c < totalColumn;c ++){
                    if (c < column1){
                        new[r][c] = data1[r][c];
                    } else if (c < column1 + column2){
                        new[r][c] = data2[r][c - column1];
                    } else if (c < totalColumn - column4){
                        new[r][c] = data3[r][c - column1 - column2];
                    } else {
                        new[r][c] = data4[r][c - column1 - column2 - column3];
                    }
                }
            }
        }
    }
    return new;
}

double ** concatsC(
    int row1, int row2, int row3, int row4, int column,
    double ** data1, double ** data2, double ** data3, double ** data4
){
    int totalRow = row1 + row2;
    double ** new = NULL;
    if (data3 != NULL && data4 == NULL){
        totalRow += row3;
        new = allocateButNoNumbers(totalRow, column);

        bool isMultiple = totalRow * column >= SimpleDVCST;
        multp_msg(totalRow * column, isMultiple, false, "concatsC");

        if (!isMultiple){
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
        }else{
            #pragma omp parallel for collapse(2) 
            for(int r = 0;r < totalRow;r++){
                for (int c = 0;c < column;c ++){
                    if (r < row1){
                        new[r][c] = data1[r][c];
                    } else if (r < row1 + row2){
                        new[r][c] = data2[r - row1][c];
                    } else {
                        new[r][c] = data3[r - row1 - row2][c];
                    }
                }
            }
        }
        
    } else{
        totalRow += row3 + row4;
        new = allocateButNoNumbers(totalRow, column);

        bool isMultiple = (totalRow + row3 + row4) * column >= SimpleDVCST; 
        multp_msg(totalRow * column, isMultiple, false, "concatsC");

        if (!isMultiple){
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
        }else{
            #pragma omp parallel for collapse(2)
            for(int r = 0;r < totalRow;r++){
                for (int c = 0;c < column;c ++){
                    if (r < row1){
                        new[r][c] = data1[r][c];
                    } else if (r < row1 + row2){
                        new[r][c] = data2[r - row1][c];
                    } else if (r < totalRow - row4){
                        new[r][c] = data3[r - row1 - row2][c];
                    } else {
                        new[r][c] = data4[r - row1 - row2 - row3][c];
                    }
                }
            }
        }
    }
    return new;
}

double *** split(int row, int column, double ** data, int len, int * slices, bool mode) {
    int num_splits = len + 1;
    double *** new = (double ***)malloc(num_splits * sizeof(double **));

    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "split");

    if (mode) {
        if (!isMultiple) {
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
        }else{
            #pragma omp parallel for schedule(dynamic) if(num_splits >= 0.1 * SimpleDVCST)
            for (int i = 0; i < num_splits; i++) {
                int start = (i == 0) ? 0 : slices[i - 1];
                int end = (i == len) ? column : slices[i];
                int dim1 = row;
                int dim2 = end - start;
                new[i] = allocateButNoNumbers(dim1, dim2);
                #pragma omp parallel for collapse(2)
                for (int r = 0; r < dim1; r++) {
                    for (int c = 0; c < dim2; c ++) {
                        new[i][r][c] = data[r][start + c];
                    }
                }
            }
        }
    } else {
        if(!isMultiple){
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
        }else{
            #pragma omp parallel for schedule(dynamic) if(num_splits >= 0.1 * SimpleDVCST)
            for (int i = 0; i < num_splits; i++) {
                int start = (i == 0) ? 0 : slices[i - 1];
                int end = (i == len) ? row : slices[i];
                int dim1 = end - start;
                int dim2 = column;
                new[i] = allocateButNoNumbers(dim1, dim2);
                #pragma omp parallel for collapse(2)
                for (int r = 0; r < dim1; r++) {
                    for (int c = 0; c < dim2; c ++) {
                        new[i][r][c] = data[start + r][c];
                    }
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
    bool isMultiple = needRow * needColumn >= SimpleDVCST;
    multp_msg(needRow * needColumn, isMultiple, false, "cover");

    #pragma omp parallel for collapse(2) if(isMultiple)
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
        int newColumn = len + column;
        new = allocateButNoNumbers(row, newColumn);
        bool isMultiple = row * newColumn >= SimpleDVCST;
        multp_msg(row * newColumn, isMultiple, false, "stretch_repeat");
        
        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0;r < row;r++){
            for (int c = 0;c < newColumn;c ++) {
                new[r][c] = data[r][c % column];
            }
        }
    } else{
        int newRow = row + len;
        new = allocateButNoNumbers(newRow, column);
        bool isMultiple = newRow * column >= SimpleDVCST;
        multp_msg(newRow * column, isMultiple, false, "stretch_repeat");

        #pragma omp parallel for if(isMultiple)
        for (int r = 0;r < newRow;r++){
            memcpy(new[r], data[r % row], column * sizeof (double ));
        }
    }
    return new;
}

double ** stretch_replace(int row, int column, double ** data, int len, bool hor, double number){
    double ** new = NULL;
    if (hor){
        int newColumn = column + len;
        new = allocateButNoNumbers(row, newColumn);
        bool isMultiple = row * newColumn >= SimpleDVCST;
        multp_msg(row * newColumn, isMultiple, false, "stretch_replace");

        if(!isMultiple){
            for(int r = 0;r < row;r++){
                int c = 0;
                for (;c < column;c ++){
                    new[r][c] = data[r][c];
                }
                for (;c < newColumn;c ++){
                    new[r][c] = number;
                }
            }
        }else{
            #pragma omp parallel for collapse(2) 
            for(int r = 0;r < row;r++){
                for (int c = 0;c < newColumn;c ++){
                    new[r][c] = c < column?  data[r][c] : number;
                }
            }
        }
    } else{
        int newRow = len + row;
        new = allocateButNoNumbers(newRow, column);
        bool isMultiple = newRow * column >= SimpleDVCST;
        multp_msg(newRow * column, isMultiple, false, "stretch_replace");

        if(!isMultiple){
            int r = 0;
            for (;r < row;r++){
                memcpy(new[r], data[r], column * sizeof (double ));
            }
            for (;r < row + 1;r++){
                for (int c = 0;c < column;c ++){
                    new[r][c] = number;
                }
            }
            for (;r < newRow;r++){
                memcpy(new[r], new[row], column * sizeof (double ));
            }
        }else{
            #pragma omp simd if(column >= 0.1 * SimpleDVCST)
            for (int c = 0;c < column;c ++){
                new[row][c] = number;
            } 
            #pragma omp parallel for  
            for (int r = 0;r < newRow;r++){
                if (r < row){
                    memcpy(new[r], data[r], column * sizeof (double ));
                }else if (r == row){
                    continue;
                }else{
                    memcpy(new[r], new[row], column * sizeof (double ));
                }
            }
        }
    }
    return new;
}

double ** stretch_head(int row, int column, double ** data, int len, bool hor){
    double ** new = NULL;
    if (hor){
        int newColumn = column + len, c;
        new = allocateButNoNumbers(row, newColumn);
        bool isMultiple = row * newColumn >= SimpleDVCST;
        multp_msg(row * newColumn, isMultiple, false, "stretch_head");

        if (!isMultiple){
            for (int r = 0;r < row;r++){
                c = 0;
                for(;c < column;c ++){
                    new[r][c] = data[r][c];
                }
                for(;c < newColumn;c ++){
                    new[r][c] = data[r][0];
                }
            }
        }else{
            #pragma omp parallel for collapse(2)
            for (int r = 0;r < row;r++){
                for(int c = 0;c < newColumn;c ++){
                    new[r][c] = c < column? data[r][c] :data[r][0];
                }
            }
        } 
    } else{
        int newRow = row + len;
        new = allocateButNoNumbers(newRow, column);

        #pragma omp parallel for 
        for(int r = 0;r < newRow;r++){
            r < row ? 
                memcpy(new[r], data[r], column * sizeof (double )) :
                memcpy(new[r], data[0], column * sizeof (double ));
        }
    }
    return new;
}

double ** stretch_end(int row, int column, double ** data, int len, bool hor){
    double ** new = NULL;
    if (hor){
        int newColumn = column + len, c, last = column - 1;
        new = allocateButNoNumbers(row, newColumn);

        bool isMultiple = row * newColumn >= SimpleDVCST;   
        multp_msg(row * newColumn, isMultiple, false, "stretch_end");

        if (!isMultiple){
            for (int r = 0;r < row;r++){
                c = 0;
                for(;c < column;c ++){
                    new[r][c] = data[r][c];
                }
                for(;c < newColumn;c ++){
                    new[r][c] = data[r][last];
                }
            }
        }else{
            #pragma omp parallel for collapse(2)
            for (int r = 0;r < row;r++){
                for(int c = 0;c < newColumn;c ++){
                    new[r][c] = c < column? data[r][c] : data[r][last];
                }
            }
        }
    } else{
        int newRow = row + len, r = 0, last = row - 1;
        new = allocateButNoNumbers(newRow, column);
        bool isMultiple = newRow * column >= SimpleDVCST;
        multp_msg(newRow * column, isMultiple, false, "stretch_end");

        if (!isMultiple){
            for(;r < row;r++ ){
            memcpy(new[r], data[r], column * sizeof (double ));
            }
            for (;r < newRow;r++){
                memcpy(new[r], data[last], column * sizeof (double ));
            }
        }else{
            #pragma omp parallel for
            for(int r = 0;r < newRow;r++){
                r < row?
                    memcpy(new[r], data[r], column * sizeof (double )) :
                    memcpy(new[r], data[last], column * sizeof (double ));
            }
        }
    }
    return new;
}

double ** stretch_mirror(int row, int column, double ** data, int len, bool hor){
    double ** new = NULL;
    if (hor){
        int newColumn = column + len, c;
        new = allocateButNoNumbers(row, newColumn);

        bool isMultiple = row * newColumn >= SimpleDVCST;   
        multp_msg(row * newColumn, isMultiple, false, "stretch_mirror");

        if(!isMultiple){
            for (int r = 0;r < row;r++){
                c = 0;
                for(;c < column;c ++){
                    new[r][c] = data[r][c];
                }
                for(;c < newColumn;c ++){
                    new[r][c] = data[r][column - 1 - c % column];
                }
            }
        }else{
            #pragma omp parallel for collapse(2)
            for (int r = 0;r < row;r++){
                for(int c = 0;c < newColumn;c ++){
                    new[r][c] = c < column? data[r][c] : data[r][column - 1 - c % column];
                }
            }
        }
    } else{
        int newRow = row + len;
        new = allocateButNoNumbers(newRow, column);
        bool isMultiple = newRow * column >= SimpleDVCST;
        multp_msg(newRow * column, isMultiple, false, "stretch_mirror");

        if (!isMultiple){
            for(int r = 0;r < row;r++){
                memcpy(new[r], data[r], sizeof (double ) * column);
            }
            for (int r = row;r< newRow;r++){
                memcpy(new[r], data[row - 1 - r % row], sizeof (double ) * column);
            }
        }else{
            #pragma omp parallel for
            for(int r = 0;r < newRow;r++){
                r < row?
                    memcpy(new[r], data[r], sizeof (double ) * column) :
                    memcpy(new[r], data[row - 1 - r % row], sizeof (double ) * column);
            }
        }
    }
    return new;
}

double ** stretch_mirrors(int row, int column, double **data, int len, bool hor) {
    double **new = NULL;
    if (hor) {
        int newColumn = column + len;
        new = allocateButNoNumbers(row, newColumn);
        bool isMultiple = row * newColumn >= SimpleDVCST;
        multp_msg(row * newColumn, isMultiple, false, "stretch_mirrors");

        #pragma omp parallel for collapse(2) if(isMultiple)
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < newColumn; c++) {
                new[r][c] = data[r][(c / column) % 2 ? column - 1 - c % column : c % column];
            }
        }
    } else {
        int newRow = row + len;
        new = allocateButNoNumbers(newRow, column);
        bool isMultiple = newRow * column >= SimpleDVCST;
        multp_msg(newRow * column, isMultiple, false, "stretch_mirrors");
        
        #pragma omp parallel for if(isMultiple)
        for (int r = 0; r < newRow; r++) {
            memcpy(new[r], data[(r / row) % 2 ? row - 1 - r % row: r % row], sizeof(double) * column);
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
    no_multp_msg(row * column, true, "diffC");

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
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "get_range");

    switch (dim) {
    case 0: 
        new = allocateButNoNumbers(row, 2);
        if (!isMultiple) {
            double value;
            for (int r = 0; r < row; r++) {
                new[r][0] = new[r][1] = data[r][0];
                for (int c = 1; c < column; c ++) {
                    value = data[r][c];
                    new[r][0] = fmin(new[r][0], value);
                    new[r][1] = fmax(new[r][1], value);
                }
            }
        }else{
            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    for (int r = 0; r < row; r++) {
                        new[r][0] = data[r][0]; 
                        for (int c = 1; c < column; c ++) {
                            new[r][0] = fmin(new[r][0], data[r][c]);
                        }
                    }
                }
                #pragma omp section
                {
                    for (int r = 0; r < row; r++) {
                        new[r][1] = data[r][0]; 
                        for (int c = 1; c < column; c ++) {
                            new[r][1] = fmax(new[r][1], data[r][c]);
                        }
                    }
                }
            }
        }
        return new;
    case 1: 
        new = allocateButNoNumbers(column, 2);
        if (!isMultiple) {
            double value;
            for (int c = 0; c < column; c ++) {
                new[c][0] = new[c][1] = data[0][c];
                for (int r = 1; r < row; r++) {
                    value = data[r][c];
                    new[c][0] = fmin(new[c][0], value);
                    new[c][1] = fmax(new[c][1], value);
                }
            }
        }else{
            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    for (int c = 0; c < column; c ++) {
                        new[c][0] = data[0][c]; 
                        for (int r = 1; r < row; r++) {
                            new[c][0] = fmin(new[c][0], data[r][c]);
                        }
                    }
                }
                #pragma omp section
                {
                    for (int c = 0; c < column; c ++) {
                        new[c][1] = data[0][c];
                        for (int r = 1; r < row; r++) {  
                            new[c][1] = fmax(new[c][1], data[r][c]);
                        }
                    }
                }
            }
        }
        return new;
    default: {
        new = (double **)malloc(sizeof(double *));
        new[0] = (double *)malloc(sizeof(double) * 2);
        new[0][0] = new[0][1] = data[0][0];
        double v1 = data[0][0], v2 = data[0][0];
        if(isMultiple) {
            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    #pragma omp parallel for reduction(min:v1)
                    for (int r = 0; r < row; r++) {
                        for (int c = 0; c < column; c++) {
                            v1 = fmin(v1, data[r][c]);
                        }
                    }
                }
                #pragma omp section
                {
                    #pragma omp parallel for reduction(max:v2)
                    for (int r = 0; r < row; r++) {
                        for (int c = 0; c < column; c++) {
                            v2 = fmax(v2, data[r][c]);
                        }
                    }
                }
            }
        }else{
            for (int r = 0; r < row; r++) {
                for (int c = 0; c < column; c++) {
                    v1 = fmin(new[0][0], data[r][c]);
                    v2 = fmax(new[0][1], data[r][c]);
                }
            }
        }
        new[0][0] = v1;
        new[0][1] = v2;
        return new;
    }
    }
}

double ** cumsum(int row, int column, double ** data, int dim, bool flatten) {
    double ** new = NULL;
    double sums;
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "cumsum");

    switch (dim) {
    case 0: 
        new = allocateButNoNumbers(row, column);
        
        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int r = 0; r < row; r++) {
            sums = 0.0;
            for (int c = 0; c < column; c ++) {
                sums += data[r][c];
                new[r][c] = sums;
            }
        }
        break;
    case 1: 
        new = allocateButNoNumbers(row, column);
        
        #pragma omp parallel for schedule(dynamic) if(isMultiple)
        for (int c = 0; c < column; c ++) {
            sums = 0.0;
            for (int r = 0; r < row; r++) {
                sums += data[r][c];
                new[r][c] = sums;
            }
        }
        break;
    default: 
        if (flatten) {
            new = allocateButNoNumbers(1, row * column);
            sums = 0.0;
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int r = 0; r < row; r++) {
                for (int c = 0; c < column; c++) {
                    sums += data[r][c];
                    new[0][r * column + c] = sums;
                }
            }
        }else {
            new = allocateButNoNumbers(row, column);
            sums = 0.0;
            #pragma omp parallel for schedule(dynamic) if(isMultiple)
            for (int r = 0;r < row;r++) {
                for (int c = 0;c < column;c ++) {
                    sums += data[r][c];
                    new[r][c] = sums;
                }
            }
        }
        break;
    }
    return new;
}

int _sgn(double x) {return (x > 0.0) - (x < 0.0);}

double ** sgn(int row, int column, double ** data) {
    double ** new = allocateButNoNumbers(row, column);
    bool isMultiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMultiple, false, "sgn");

    #pragma omp parallel for collapse(2) if(isMultiple)
    for (int r = 0;r < row;r++) {
        for(int c = 0;c < column;c ++) {
            new[r][c] = _sgn(data[r][c]);
        }
    }
    return new;
}

double ** confront(int row, int column, double ** data1, double ** data2, double (*func)(double, double)) {
    double ** new = malloc(sizeof(double *) * row);
    no_multp_msg(row * column, false, "confront");

    for (int r = 0;r < row;r++) {
        new[r] = malloc(sizeof(double) * column);
        for(int c = 0;c < column;c ++) {
            new[r][c] = func(data1[r][c], data2[r][c]);
        }
    }
    return new;
}