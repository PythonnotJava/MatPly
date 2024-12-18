//
// Created by 25654 on 24-8-3.
//

#ifndef DEV_MATPLY_CPP_EXTENSION_H
#define DEV_MATPLY_CPP_EXTENSION_H

#ifdef __cplusplus
extern "C" {
#endif
    /// 获取中位数
    extern double * mode(int row, int column, double **data, int dim);

#ifdef __cplusplus
}
#endif

#endif //DEV_MATPLY_CPP_EXTENSION_H
