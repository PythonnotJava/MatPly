# MatrixType的方法

## visible
可视化矩阵的数据， 数据的精确度可以通过**set_visible_round**方法设置

## visible_spc
查看矩阵有哪些特殊属性

## row_ | column_
获取矩阵的某行（列），调用该函数时，同时也可以声明Pointer或者List两种类型（不声明按照List类型处理），表明要获取哪种类型，不声明会按照list类型返回，建议是不声明。

## at
获取指定位置的数据

## transpose
获取转置矩阵

## 初等变换——无返回值
1. exchange_row/exchange_column 交换变换
2. multiply_row/multiply_column 倍乘变换
3. add_row/add_column 把倍乘行（列）加到另一行（列）

## hasSameShape
判断两个矩阵是不是形状一样

## add
`+`操作

## minus
`-`操作

## multiply
`*`操作

## divide
`/`操作

## add_no_returned
`+`操作，但是改变矩阵本身

## minus_no_returned
`-`操作，但是改变矩阵本身

## multiply_no_returned
`*`操作，但是改变矩阵本身

## divide_no_returned
`/`操作，但是改变矩阵本身

## matmul
左行乘右列做内积，并且返回一个新的矩阵对象

## kronecker
两个任意形状的矩阵做kronecker积

## cofactor
获取余子式矩阵

## compare
比较两个一样形状的矩阵的数据，并且返回矩阵形状大小的List<List<bool>>

## sum
矩阵求和，如果dim=0，则按照行求，返回数组；如果dim=1，则按照列求，返回数组；dim为其他值则返回整体的和

## mean
矩阵均值，原理同sum

## min | max
矩阵最值，原理同sum

## cut
获取矩阵的内部裁剪矩阵

## cutfree
获取从矩阵内部一点开始自由裁剪尺寸的矩阵，外部用number补齐

## concat
获取两个矩阵的横（纵）拼接的矩阵

## reshape
获取矩阵size不变重塑形状的矩阵

## reshape_no_returned
矩阵本身size不变，重塑形状

## resize
获取矩阵更改尺寸后的新矩阵，若尺寸增大，则用number补齐。从上到下、从左往右取值，horizontal为true，从每行开始，反之从每列开始。

## resize_no_returned
重塑本身尺寸

## power
如果reverse为true，获取number为底， 矩阵每个数据为幂次方的新矩阵，反之。

## atan2
获取切角大小。reverse原理同上。

## sigmoid
获取矩阵对应的sigmoid映射矩阵

## softmax
dim=0时，按行求和进行softmax映射；dim=1，按列求和进行softmax映射；dim为其他整数则整体求和做softmax映射。最后返回新矩阵

## shuffle
数据打乱

## sort_no_returned
dim=0时，按行排序；dim=1，按列排序；dim为其他整数则整体排序。

## sort
dim=0时，按行排序；dim=1，按列排序；dim为其他整数则整体排序，然后得到排序好的新矩阵。

## rref
获取矩阵的最简阶梯型

## setMask
设置矩阵nan和正负无穷大数据的替换值，会改变矩阵本身。

## toList[new from V1.0.2]
根据传入的类型，返回对应形状的二维列表。对于泊松分布这样的数据非常有用。

## std[new from V1.0.2]
求解标准差，如果设置sample为true，则视为样本标准差

## variance[new from V1.0.2]
求解方差，，如果设置sample为true，则视为样本标准方差

## median[new from V1.0.2]
求解中位数

## norm[new from V1.0.2]
求解矩阵范数。如果n==-2，则返回矩阵的负无穷范数；如果n==-1，则返回矩阵的正无穷范数；如果设置n==1，则返回矩阵的L1范数，如果n==0或者其他不小于2的正整数，则返回范数（包含行列向量的范数模型、矩阵范数模式），注意这里L0范数是一个整数返回值

## norm2[new from V1.0.2]
L2范数。即欧氏距离

## norm_inf[new from V1.0.2]
矩阵的正无穷范数

## norm_negainf[new from V1.0.2]
矩阵的负无穷范数

## norm_one[new from V1.0.2]
矩阵的L1范数

## norm_zero[new from V1.0.2]
L0范数

## mode[new from V1.0.2]
求解众数（此方法没有基于C-API）

