//
// Created by 25654 on 24-9-20.
//

#include "mp_cfg.h"

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

/// 和随机数相关

void setSeed(int seed) {
    seed >= 0 ? srand(seed):  initialize_random_seed();
}

void initialize_random_seed() {
    static int initialized = 0;
    if (initialized <= 0) {
        srand(time(NULL));
        initialized = 42;
    }
}

void _shuffle(double *arr, int len){
    initialize_random_seed();
    int j;
    double temp;
    for (int i = len - 1; i > 0; i--) {
        j = rand_func() % (i + 1);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int randint(double lb, double ub){
    initialize_random_seed();
    return (int )(lb + random1() * (ub - lb));
}

double random1() {
    return (double)rand_func() / MAXRAND;
}

double randdouble(double lb, double ub){
    initialize_random_seed();
    return lb + random1() * (ub - lb);
}

double random_choice(double *arr, int len) {
    initialize_random_seed();
    return arr[rand_func() % len];
}

double * random_choices(double *arr, int len, int times, bool back) {
    initialize_random_seed();
    double *result = (double *)malloc(times * sizeof(double));
    int index;
    if (back) {
        for (int i = 0; i < times; i++) {
            index = rand_func() % len;
            result[i] = arr[index];
        }
    } else {
        {
            double * temp_arr = (double *)malloc(len * sizeof(double));
            memcpy(temp_arr, arr, sizeof (double )*len);
            _shuffle(temp_arr, len);
            for (int i = 0; i < times; i++)
                result[i] = temp_arr[i];
            free(temp_arr);
        }
    }
    return result;
}


// 根据概率数组挑选一个值
int __select_index(double * p, double total_weight, int len) {
    double r = random1() * total_weight;
    double cumulative_weight = 0.0;
    for (int i = 0; i < len; i++) {
        cumulative_weight += p[i];
        if (r <= cumulative_weight)
            return i;
    }
    return len - 1;
}

static inline double sigmoidfunc(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double * perfect_choices(double *arr, double *p, int len, int times, bool back, int method) {
    initialize_random_seed();
    double *result = malloc(times * sizeof(double));
    double *adjusted_p = malloc(len * sizeof(double));
    double total_weight = 0.0;

    if (method == 0) {
        for (int i = 0; i < len; i++) {
            adjusted_p[i] = p[i];
            total_weight += adjusted_p[i];
        }
    } else if (method == 1) {
        for (int i = 0; i < len; i++) {
            adjusted_p[i] = sigmoidfunc(p[i]);
            total_weight += adjusted_p[i];
        }
    } else {
        for (int i = 0; i < len; i++) {
            adjusted_p[i] = fabs(p[i]);
            total_weight += adjusted_p[i];
        }
    }

    int selected_index;
    for (int t = 0; t < times; t++) {
        selected_index = __select_index(adjusted_p, total_weight, len);
        result[t] = arr[selected_index];

        if (!back) {
            total_weight -= adjusted_p[selected_index];
            adjusted_p[selected_index] = 0.0;
        }
    }

    free(adjusted_p);
    return result;
}

/// 初始化随机数
#if defined(_WIN32) || defined(_WIN64)
    unsigned int MAXRAND = UINT_MAX;
#else
    unsigned int MAXRAND = RAND_MAX;
#endif

#if defined(_WIN32) || defined(_WIN64)
#else
    #include <limits.h>
#endif

// 范围请看：https://linux.die.net/man/3/rand_r
#if defined(_WIN32) || defined(_WIN64)
unsigned int rand_wrapper() {
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
    int ri;
    #define _CRT_RAND_S
    if (rand_r(&ri) == 0) {
        return ri;
    }
    else {
        return rand();
    }
}
#endif

RandFunc rand_func = rand_wrapper;
