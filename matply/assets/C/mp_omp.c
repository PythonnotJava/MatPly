//
// Created by 25654 on 24-10-16.
//

#include "mp_omp.h"

int THREADS = 4;
bool _threadLocked = false;
void init_threads() {
    int k = omp_get_num_procs();
    THREADS = k >= 4 ? k / 2 : k;
    omp_set_num_threads(THREADS);
}

void set_max_thread_support(int n) {
    int k = omp_get_num_procs();
    THREADS = (n <= 0 || n > k) ?  k : n;
    omp_set_num_threads(THREADS);
}

long SimpleDVCST = 99999;
long ComplexDVCST = 9999;
bool isShowMultp = false;
// long SingleDVCST = 999;

int get_max_thread_support() {return THREADS;}
int get_max_thread_sys() {return omp_get_num_procs();}
double get_time() {return omp_get_wtime();}
void set_simple_dvcst_value(long value) {
    if (!_threadLocked){
        SimpleDVCST = value <= 999 || value >= 100000 ? 99999: value;
        _threadLocked = true;
    }
}
void set_complex_dvcst_value(long value) {
    if (!_threadLocked){
        ComplexDVCST = value <= 99 || value >= 10000 ? 9999 : value;
        _threadLocked = true;
    }
}
// void set_single_dvcst_value(long value) {
//     if (!_threadLocked){
//         SingleDVCST = value <= 99? 100 : value;
//         _threadLocked = true;
//     }
// }
long get_simple_dvcst_value() {return SimpleDVCST;}
long get_complex_dvcst_value() {return ComplexDVCST;}
// long get_single_dvcst_value() {return SingleDVCST;}
void set_multp_shown(bool _isShowMultp) {isShowMultp = _isShowMultp;}
bool get_multp_shown() {return isShowMultp;}
void multp_msg(long dataCounts, bool multThreads, bool complex, char * name) {
    if(isShowMultp) {
        printf("Function named < %s > infos : \n", name);
        printf("\t- Amount of data processed : %ld.\n", dataCounts);
        printf("\t- Multithreading enabled : %s.\n", multThreads? "true" : "false");
        printf("\t- Max Number of threads : %d.\n", multThreads ? THREADS : 1);
        printf("\t- %s calculation threshold : %ld.\n", complex ? "Complex" : "Simple", complex? ComplexDVCST : SimpleDVCST);
    }
}

void mixin_multp_msg(long dataCounts, bool multThreads, bool complex, char * name) {
    if(isShowMultp) {
        printf("Function named < %s > infos : \n", name);
        printf("\t- It's a mixin thread-model.\n");
        printf("\t- Amount of data processed : %ld.\n", dataCounts);
        printf("\t- Includes multithreading : %s.\n", multThreads? "true" : "false");
        printf("\t- Max Number of threads : %d.\n", multThreads ? THREADS : 1);
        printf("\t- %s calculation threshold : %ld.\n", complex ? "Complex" : "Simple", complex? ComplexDVCST : SimpleDVCST);
    }
}

void no_multp_msg(long dataCounts, bool complex, char * name) {
    if(isShowMultp) {
        printf("Function named < %s > infos : \n", name);
        printf("\t- It's an unoptimized function.\n");
        printf("\t- It's a %s function record.\n", complex? "complex" : "simple");
        printf("\t- Amount of data processed : %ld.\n", dataCounts);
    }
}

void set_simple_dvcst_value_force(long value) {SimpleDVCST = value;}
void set_complex_dvcst_value_force(long value) {ComplexDVCST = value;}
// void set_single_dvcst_value_force(long value) {SingleDVCST = value;}

void testOmp() {
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("Thread Id == %d.\n", id);
        if (id + 1 == get_max_thread_support()) {
            printf("Current total threads == %d.\n", id + 1);
        }
        if (id + 1 == get_max_thread_sys()) {
            printf("The number of threads currently opened is exactly the maximum number of threads in the system == %d.\n", id + 1);
        }
    }
    printf("The maximum number of threads in the system is %d.\n", get_max_thread_sys());
}
