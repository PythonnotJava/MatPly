//
// Created by 20281 on 24-9-20.
//

#include "mp_manage.h"

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
        MatrixLinked * new = (MatrixLinked *) malloc(sizeof (MatrixLinked));
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
            while (current != __Mp.tail)
            {
                temp = current;
                current = current->next;
                __delete__(temp->matrix);
                printf("Free Memory in location : %lu\n", (void *)temp);
                free(temp);
            }
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