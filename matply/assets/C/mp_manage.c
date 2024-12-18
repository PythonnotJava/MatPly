//
// Created by 20281 on 24-9-20.
//

#include "mp_manage.h"

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
Matrix * __new__(int row, int column){
    Matrix * new = (Matrix *) malloc(sizeof (Matrix));
    new->column = column;
    new->row = row;
    new->data = NULL;  // 1.0.x的修改——不预先申请数据内存
    new->spc = (Spc *) malloc(sizeof (Spc));
    *new->spc = (Spc){false, false, false, false, false, false};
    Signal(new)
    return new;
}

Matrix * __init__(int row, int column, double ** data, Spc * spc){
    Matrix * new = __new__(row, column);  // 已经Signal了
    bool isMutiple = row * column >= SimpleDVCST;

    if(!isMutiple){
        new->data = (double **) malloc(sizeof (double *) * row);
        for (int r = 0;r < row;r++){
            new->data[r] = (double *) malloc(sizeof (double ) * column);
            memcpy(new->data[r], data[r], column * sizeof(double));
        }
    }else{
        multp_msg(row * column, true, false, "__init__");

        new->data = allocateButNoNumbers(row, column);
        #pragma omp parallel for
        for (int r = 0;r < row;r++){
            memcpy(new->data[r], data[r], column * sizeof(double));
        }
    }
    if (spc)
        *new->spc = *spc;
    return new;
}

Matrix * __init__point__data__(int row, int column, double ** data, Spc * spc)
{
    Matrix * new = __new__(row, column);  // 已经Signal了
    new->data = data;
    if (spc)
        *new->spc = *spc;
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
        #pragma omp parallel for if(row >= SimpleDVCST / 2)
        for (int r=0;r < row;r++) {
            free(data[r]);
        }
        free(data);
    }
}

void __delete__(Matrix * matrix){
    if(matrix) {
        __delete__data__(matrix->data, matrix->row);
        if (matrix->spc){
            free(matrix->spc);
        }
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

bool data_isSame(int row, int column, double **data1, double **data2)
{
    bool isMutiple = row * column >= SimpleDVCST;
    multp_msg(row * column, isMutiple, false, "data_isSame");
    if (!isMutiple) {
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c ++) {
                if (data1[r][c] != data2[r][c]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool same = true;
    #pragma omp parallel
    {
        for (int i = 0;i < row * column;i++){
            int r = i / column;
            int c = i % column;
            #pragma omp cancellation point parallel
            same = same && data1[r][c] == data2[r][c];
            if(!same) {
                #pragma omp cancel parallel
            }
            #pragma omp cancellation point parallel
        }
    }
    return same;
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

void initMp(Matrix * matrix)
{
    if (matrix && __Mp.instances == 0)
    {
        MatrixLinked * head = (MatrixLinked*) malloc(sizeof (MatrixLinked));
        MatrixLinked * tail = (MatrixLinked*) malloc(sizeof (MatrixLinked));
        head->matrix = matrix;
        head->next = tail;
        tail->matrix = NULL;
        tail->next = NULL;
        __Mp.head = head;
        __Mp.tail = tail;
        __Mp.instances++;
    }
}

void addToMp(Matrix * matrix)
{
    if (matrix && __Mp.instances == 0)
        initMp(matrix);
    else{
        MatrixLinked * new = malloc(sizeof (MatrixLinked));
        new->next = NULL;
        new->matrix = matrix;
        __Mp.tail->next = new;
        __Mp.tail = __Mp.tail->next;
        __Mp.instances++; // 不记录尾节点
    }
}

void freeMp(bool visible, bool hex)
{
    MatrixLinked * current = __Mp.head;
    MatrixLinked * temp = NULL;
    if (visible)
    {
        if (hex) {
            while (current != __Mp.tail)
            {
                temp = current;
                current = current->next;
                __delete__(temp->matrix);
                printf("Free Memory in location : %p\n", (void *)temp);
                free(temp);
            }
        }
        else{
            #if defined(_WIN32) || defined(_WIN64)
            {
                while (current != __Mp.tail)
                {
                    temp = current;
                    current = current->next;
                    __delete__(temp->matrix);
                    printf("Free Memory in location : %llu\n", (uintptr_t)temp);
                    free(temp);
                }
            }
            #else
            {
                while (current != __Mp.tail)
                {
                    temp = current;
                    current = current->next;
                    __delete__(temp->matrix);
                    printf("Free Memory in location : %lu\n", (uintptr_t)temp);
                    free(temp);
                }
            }
            #endif
        }
        free(__Mp.tail);
    }else
    {
        while (current != __Mp.tail)
        {
            temp = current;
            current = current->next;
            __delete__(temp->matrix);
            free(temp);
        }
        free(__Mp.tail);
    }
    __Mp.instances = 0;
}

int getInstances() {return __Mp.instances;}