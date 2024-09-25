//
// Created by 25654 on 24-9-20.
//

#include "mp_cfg.h"

#ifdef MP_AUXILIARY_H
#else
    #include "mp_auxiliary.h"
#endif

#ifndef  _INC_STDLIB
    #define _CRT_RAND_S
    #include <stdlib.h>
    #define __rand_s rand_s;
#endif

#ifdef _MATH_H_
#else
    #include <math.h>
#endif

char * ROUND = "%.5lf\t";
double DROUND = 1e-10;
void set_visible_round( char* new_round){ROUND = new_round;}
char * get_visible_round(){return ROUND;}
void set_round( double number) {DROUND = number;}
double get_round(){return DROUND;}

const double PI = M_PI;
const double e = M_E;
const double _nan = NAN;
const double inf = INFINITY;
const double euler = 0.57721566490153286060651209;

void setSeed( int seed) {seed >= 0 ? srand(seed):  initialize_random_seed();}

bool use_mult_rand = true;
unsigned int MAXRAND = RAND_MAX;

#if defined(_WIN32) || defined(_WIN64)
#else
#include <limits.h>
#endif

MATPLY_API void set_mult_rand(bool use) {
    use_mult_rand = use;
    #if defined(_WIN32) || defined(_WIN64)
        MAXRAND = use ? UINT_MAX : RAND_MAX;
    #else
        MAXRAND = RAND_MAX;
    #endif
}
MATPLY_API bool get_mult_rand() {return use_mult_rand;}

// 范围请看：https://linux.die.net/man/3/rand_r
#if defined(_WIN32) || defined(_WIN64)
unsigned int rand_wrapper() {
    if (!use_mult_rand) {
        MAXRAND = RAND_MAX;
        return rand();
    }
    unsigned int ri;
    if (rand_s(&ri) == 0) {
        MAXRAND = UINT_MAX;
        return ri;
    }
    MAXRAND = RAND_MAX;
    return rand();
}
#else
unsigned int rand_wrapper() {
    MAXRAND = RAND_MAX;
    if (!use_mult_rand) {
        return rand();
    }
    else {
        int ri;
        #define _CRT_RAND_S
        if (rand_r(&ri) == 0) {
            return ri;
        }
        else {
            return rand();
        }
    }
}
#endif

RandFunc rand_func = rand_wrapper;