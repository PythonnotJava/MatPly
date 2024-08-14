//
// Created by 25654 on 24-8-3.
//

#include "cpp_extension.h"

#ifdef _UNORDERED_MAP_
#else
#include <unordered_map>
#endif

#ifdef _INC_STDLIB
#else
#include <stdlib.h>
#endif

//g++ -shared -o cpp_extension.dll cpp_extension.cpp

using namespace std;

extern "C" double * mode(int row, int column, double **data, int dim){
    double * number = nullptr;
    std::unordered_map<double, int> dict = {};
    double value, current;
    int maxCount;
    switch (dim) {
        case 0:{
            number = (double *) malloc(row * sizeof(double));
            for (int r = 0; r < row; r++) {
                dict.clear();
                maxCount = 0;
                current = data[r][0];
                for (int c = 0; c < column; c ++) {
                    value = data[r][c];
                    dict[value]++;  // unordered_map中不需要检查键是不是存储，没有可以自动初始化
                    if (dict[value] > maxCount) {
                        maxCount = dict[value];
                        current = value;
                    }
                }
                number[r] = current;
            }
            break;
        }
        case 1:{
            number = (double *) malloc(column * sizeof(double));
            for (int c = 0; c < column;c ++) {
                dict.clear();
                maxCount = 0;
                current = data[0][c];
                for (int r = 0; r < row;r++) {
                    value = data[r][c];
                    dict[value]++;
                    if (dict[value] > maxCount) {
                        maxCount = dict[value];
                        current = value;
                    }
                }
                number[c] = current;
            }
            break;
        }
        default:{
            maxCount = 0;
            current = data[0][0];
            for (int r = 0; r < row; ++r) {
                for (int c = 0; c < column; ++c) {
                    value = data[r][c];
                    dict[value]++;
                    if (dict[value] > maxCount) {
                        maxCount = dict[value];
                        current = value;
                    }
                }
            }
            number = (double *) malloc(sizeof(double));
            number[0] = current;
            break;
        }
    }
    return number;
}