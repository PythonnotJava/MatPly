//// Created by 20281 on 2024/7/6.//#ifndef MATPLY_MATBOX_H#define MATPLY_MATBOX_H#if defined _STDBOOL_H#else#include <stdbool.h>#endif#if defined _INC_STDIO#else#include <stdio.h>#endif#if defined _MATH_H_#else#include <math.h>#endif#if defined _INC_STDLIB#else#include <stdlib.h>#endif#if defined _INC_STRING#else#include <string.h>#endif#if defined _TIME_H_#else#include <time.h>#endif// 设置与获取可视化精度 ROUNDextern void set_visible_round( char* new_round);extern  char * get_visible_round();// 设置与获取浮点数误差精度extern void set_round( double number);extern  double get_round();extern double PI;extern double e;extern double _nan;extern double inf;// 矩阵是否为特殊矩阵typedef struct SpecialAttributes{    bool identityMatrix;  // 单位矩阵    bool principalDiagonalMatrix; // 主对角矩阵    bool subDiagonalMatrix; // 副对角矩阵    bool upperTriangularMatrix; // 上三角矩阵    bool lowerTriangularMatrix; // 下三角矩阵    bool singularMatrix; // 奇异矩阵} Spc;typedef struct Matrix{    int row;  // 行    int column;  // 列    Spc * spc;  // 特殊性质    double ** data;  // 值} Matrix;// 内存管理，使用一个单例内存池。防止内存泄漏。///////////////////////////////////////////////////////////////////////////////////////typedef struct MatrixLinked{    struct MatrixLinked * next;    Matrix * matrix;}MatrixLinked;typedef struct MemoryPool{    int instances;  // 存储实例个数    struct MatrixLinked * matrix_linked;} MemoryPool;static struct MemoryPool __Mp = (MemoryPool){0, NULL};// 添加到内存池// 选择性初始化，matrix可以为空，只是为了更好的提示矩阵操作的开始；另外，内存池真的为空的话，则可以把非空的matrix设置为第一个void initMp(Matrix * matrix);void addToMp(Matrix * matrix);void freeMp(bool visible);int getInstances();#define Signal(m) addToMp(m);///////////////////////////////////////////////////////////////////////////////////////void visible_data( double**matrix,  int row,  int column);// 创建所有矩阵都拥有的步骤Matrix * __new__( int row,  int column);// 创建带有数据的矩阵，顺便可以指定特殊属性，如果知道Matrix * __init__( int row,  int column,  double** data,  Spc * spc);// 创建指定地址数据的矩阵，顺便可以指定特殊属性，如果知道Matrix * __init__point__data__( int row,  int column, double ** data,  Spc * spc);// 可视化矩阵void VisibleMatrix( Matrix * matrix);// 释放二维数组void __delete__data__(double ** data,  int row);// 销毁矩阵void __delete__(Matrix * matrix);// 创建被某个指定值填充的矩阵double ** filled( int row,  int column,  double number);// 0/1矩阵double ** zeros( int row,  int column);double ** ones( int row,  int column);// 打印矩阵有哪些特殊属性void VisibleMatrixSpc( Matrix * matrix);// 获取某行的数组double * row_( int row,  int column,  double ** data);// 获取某列的数组double * column_( int row,  int column,  double ** data);// 获取指定位置double at( int row,  int column,  double ** data);// 判断是不是方阵bool isSquare( Matrix * matrix);// 获取对应的转置矩阵double ** transpose( int row,  int column,  double ** data);// 初等行变换：行交换、行扩大（允许0倍）、一行加倍数另一行（把size * row2 加到row1)void exchangeR( int column, double ** data,  int row1,  int row2);void multiplyR( int row,  int column, double **data,  double size);void addR( int column, double **data,  int row1,  int row2,  double size);// 初等列变换：类似上面void exchangeC( int row, double ** data,  int column1,  int column2);void multiplyC( int row,  int column, double **data,  double size);void addC( int row, double **data,  int column1,  int column2,  double size);// 矩阵加法// 1.整体加某个数——创建新对象double ** addNumber( int row,  int column,  double **data,  double number);// 2.矩阵相加——创建新对象double ** addMatrix( int row,  int column,  double **data1,  double **data2);// 3.整体加某个数——自操作void addNumberNoReturned( int row,  int column, double **data,  double number);// 4.矩阵相加——自操作，修改matrix1，下同void addMatrixNoReturned( int row,  int column, double **data1,  double **data2);// 对应的减法double ** minusMatrix( int row,  int column,  double **data1,  double **data2);void minusMatrixNoReturned( int row,  int column, double **data1,  double **data2);// 矩阵乘法// 1.左行右列做内积double ** matmul( int row,  int column,  double **data1,  double **data2, int column2);// 2.哈达马积void multiplyMatrixNoReturned( int row,  int column, double **data1,  double **data2);double ** multiplyMatrix( int row,  int column,  double **data1,  double **data2);// 3.数值倍乘void multiplyNumberNoReturned( int row,  int column, double **data,  double number);double ** multiplyNumber( int row,  int column,  double **data,  double number);// 4.克罗内克积double ** kronecker( int row1,  int column1,  double **data1,  int row2,  int column2,  double **data2);// 矩阵除法double ** divide( int row,  int column,  double **data,  double number);void divideNoReturned( int row,  int column, double **data,  double number);// 生成连续个数后重新布局，从start ~ row*column，间隔为1double ** arrange( double start,  int row,  int column);// 生成连续个数后重新布局，从start ~ end?，期间被分成row * column份，keep为true决定以end结尾，反之double ** linspace( double start,  double end,  int row,  int column,  bool keep);// 矩阵求迹，像众多科学计算库一样，只考虑最小维度double trace( int row,  int column,  double **data);// 行列式值，前提是方阵double det( int row,  int column,  double **data);// 获取一个n阶单位矩阵double ** E( int n);// 余子式组成的矩阵double ** cofactor( int row,  int column,  double ** data,  int prow,  int pcolumn);// 伴随矩阵。m * adj(m) = det(m) * E;任意方阵都有伴随矩阵double ** adjugate( int row,  int column,  double ** data);// 逆矩阵（非奇异矩阵），前提是行列式值不能为0，默认可逆，在目标语言中判断，同上面很多的范围判断，都在目标语言，因为C没有较好的报错机制double ** inverse( int row,  int column,  double ** data);// 深拷贝double ** deepcopy( int row,  int column,  double **data);// 比较模式，对应位置上的数据分别对比// mode从1~4分别表示：大于、小于、不大于、不小于，其他数表示等于情况bool ** compare( int row,  int column,  double **data1,  double ** data2,  int mode);// 求和。参数dim可以取0、1和其他数，分别表示沿着row、沿着column、整体这三种模式的求和，下同double * sum( int row,  int column,  double **data,  int dim);// 求平均值double * mean( int row,  int column,  double **data,  int dim);// 最小值double * min( int row,  int column,  double **data,  int dim);// 最大值double * max( int row,  int column,  double **data,  int dim);// 判断数据是不是一样bool data_isSame( int row,  int column,  double ** data1,  double ** data2);// 判断属性是不是一样bool spc_isSame( Spc * spc1,  Spc * spc2);// 内部截取double ** cut( int row,  int column,  double ** data,  int prow,  int pcolumn,  int width,  int height);// 从内部一点开始截取，可以越界，超过部分使用number补全double ** cutfree( int row,  int column,  double ** data,  int prow,  int pcolumn,  int width,  int height,  double number);// 合并新的double ** concatR( int row,  int column1,  int column2,  double ** data1,  double ** data2);double ** concatC( int row1,  int row2,  int column,  double ** data1,  double ** data2);// 重塑大小——多余的丢掉，缺少的用number补全// 这个row和column是新尺寸的，别弄混了double ** resizeR( int row,  int column,  double ** data,  int origin_row,  int origin_column,  double number);double ** resizeC( int row,  int column,  double ** data,  int origin_row,  int origin_column,  double number);// 重构尺寸，前提是a * b = c * r;double ** reshape( int row,  int column,  double ** data,  int origin_column);// 设置随机种子void setSeed( int seed);// 数学拓展/*double acos(double x); mode == 0double asin(double x);double atan(double x);double cos(double x);double sin(double x);double tan(double x);double cosh(double x);double sinh(double x);double tanh(double x);double exp(double x);double log(double x);double log10(double x);double sqrt(double x);double ceil(double x);double floor(double x);double fabs(double x); mode == 15double pow(double x, double y); 0double atan2(double y, double x); 1double frexp(double x, int *exp);  // 不提供double ldexp(double x, int exp);  // 不提供double modf(double x, double *iptr);  // 不提供 */// 各种数学运算调用——传入1个参数，这么设计泛型是为了节省代码量，同时在一些语言中，如Dart可以轻松使用extension关键字对List拓展double ** mathBasement1( int row,  int column,  double ** data,  int mode);// 各种数学运算调用——传入2个参数，第1个是矩阵的数据，第2个是传入数据double ** mathBasement2( int row,  int column,  double ** data,  int mode,  double number);// 各种数学运算调用——传入2个参数，第2个是矩阵的数据，第1个是传入数据double ** mathBasement2reverse( int row,  int column,  double ** data,  int mode,  double number);// Sigmoid函数double ** sigmoid( int row,  int column,  double ** data);// @extend Softmax函数，归一化指数函数，当数据含有nan或者正负inf任意一种时，可对二者做特殊化处理double ** softmax( int row,  int column,  double ** data,  int dim,  double mask_nan,  double mask_inf,  double mask_neginf);// 随机打乱void shuffle(  int row,  int column, double ** data);// 排序，reverse为true表示从大到小void sortNoReturned( int row,  int column, double ** data,  bool reverse,  int dim,  double mask_nan);double ** sort( int row,  int column, double ** data,  bool reverse,  int dim,  double mask_nan);// 均匀分，如果未来实现了写了向量类，可能还会修改，一般生成是一个向量double ** uniform( int row,  int column,  double start,  double end,  int seed,  bool use);// 正态分布，基于Box-Muller变换double ** normal( int row,  int column,  double mu,  double sigma,  int seed,  bool use );// 泊松分布double ** poisson( int row,  int column,  double lambda,  int seed,  bool use);// 得到化最简阶梯型矩阵double ** rref( int row,  int column,  double ** data);// 对一个矩阵进行特殊值处理void set_mask_nan( int row,  int column, double ** data,  double number);void set_mask_inf( int row,  int column, double ** data,  double number,  bool isNegativeInf);// 矩阵的秩int rank( int row,  int column,  double ** data);double ** testArray( int row,  int column);// 方差，如果声明sample则表示样本方差；标准差开根号就行double * variance(int row, int column, double ** data, bool sample, int dim, bool std);// 中位数double * median(int row, int column, double ** data, int dim);// @ignore 数学期望不需要实现，因为数学期望是随机变量 * 概率，可以使用哈达玛积表示// 矩阵范数// n == -2表示负无穷范数，即矩阵每行绝对值元素求和取最小double norm_negainf(int row, int column, double ** data);// n == -1表示正无穷范数，即矩阵每行绝对值元素求和取最大double norm_inf(int row, int column, double ** data);// n == 0获取0范数，也是获取数据的稀疏度。数据会与定义的浮点误差比较，而不是直接与0比较，k范数时（k == 0 or k >= 2），程序灵活些，加个dim参数double * norm_zero(int row, int column, double ** data, int dim);// n == 1矩阵的1范数，矩阵每列绝对值元素求和取最大double norm_one(int row, int column, double ** data);double * norm(int row, int column, double ** data, int n, int dim);// 最值索引int * argmax(int row, int column, double  **data, int dim);int * argmin(int row, int column, double  **data, int dim);// 数组扁平化为1*size（不用reshape实现），mode == 1表示从0列开始并从上到下转换；mode为其他值表示从行开始，从上到下double * flatten(int row, int column, double  **data, int mode);// 指定步长的rangedouble ** range(double start, double step, int row, int column);// 替换不符合条件的值double ** replace(int row, int column, double ** data, double number, bool (*condition)(double ));void replaceNoReturned(int row, int column, double ** data, double number, bool (*condition)(double ));// 数据归一化// 分别是线性归一化、均值归一化、标准化double ** normalization1(int row, int column, double  **data, int dim);double ** normalization2(int row, int column, double  **data, int dim);double ** normalization3(int row, int column, double  **data, int dim);// 矩阵切割，to的位置也计入double ** sliceR(int column, double ** data, int from, int to);double ** sliceC(int row, double ** data, int from, int to);// 框住范围double ** clip(int row, int column, double  **data, double lb, double ub);void clipNoReturned(int row, int column, double  **data, double lb, double ub);// 每个值都满足条件bool all(int row, int column, double  ** data, bool (*condition)(double ));// 任意值满足条件bool any(int row, int column, double **data, bool (*condition)(double ));// 对满足条件的数据计数int * counter(int row, int column, double  ** data, int dim, bool (*condition)(double ));// 自定义两个相邻值的行为，init值是基准值，例如求和可以设置基准从0开始，乘积可以设置基准为1double * reduce(int row, int column, double ** data, int dim, double (*condition)(double , double ), double init);// 获取最小维度下对角线全是1，其他全是0的矩阵double ** E_like(int row, int column);// qr分解double *** qr(int row, int column, double ** data);#endif //MATPLY_MATBOX_H