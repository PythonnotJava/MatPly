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

## argmax[new from V1.0.5]
获取最大值索引

## argmin[new from V1.0.5]
获取最小值索引

## flatten[new from V1.0.5]
返回一个1 * size的扁平化矩阵，mode参数决定了从横向开始还是纵向

## flatten_list[new from V1.0.5]
返回一个扁平化后的一维列表

## replace[new from V1.0.5]
获取替换不符合条件的值后的矩阵

## replace_no_returned[new from V1.0.5]
替换矩阵不符合条件的值

## normalization[new from V1.0.5]
获取归一化后的矩阵，0、1、其他值分别对应线性归一化、均值归一化、z-score归一化

## slice[new from V1.0.5]
获取矩阵切片切出的矩阵，如果不指定切到哪，则切至终点行（列）

## clip[new from V1.0.5]
获取一个框住范围的矩阵，矩阵数据满足lb <= x <= ub，小于则变成lb，大于变成ub

## clip_no_returned[new from V1.0.5]
框住矩阵本身范围

## all[new from V1.0.5]
矩阵所有值全满足条件返回true，反之

## any[new from V1.0.5]
矩阵任意值满足条件返回true，反之

## counter[new from V1.0.5]
对矩阵中满足条件的值计数

## reduce[new from V1.0.5]
对矩阵相邻的两个值累计操作

## where[new from V1.0.5]
[condition] 是必须传入的条件函数，也同时添加另一个约束 [any]，但这时候 [obj] 不能为空。只操作满足条件的值
若不传入 [cpl] 参数，则默认返回满足条件的值到一个一维列表；否则，则按照cpl函数更新的值与未满足条件的值一起写入原来矩阵，返回一个矩阵对象

## qr[new from V1.0.5]
获取矩阵QR分解得到的两个矩阵组成的列表

## Hist[new from V1.0.5]
获取未可视化、统计出来的值计数

## Bar[new from V1.0.5]
获取未可视化、根据条件约束分类并且符合生成标签的值计数

## magic[new from V1.0.5] **_!!!_**
[@alert]高自由度地使用抽象出来的方式来自定义抽象地反射矩阵数据

## customize[new from V1.0.6]
相较于矩阵多次创建对象的运算方式，customize可以根据运算流程创建一个矩阵对象

## clip_reverse[new from V1.0.6]
在范围外的数据不发生变化，否则按照条件设置值

## clip_reverse_no_returned[new from V1.0.6]
clip_reverse的无返回值方式

## findIndexs[new from V1.0.6]
查询所有符合条件值的索引，每行都查询，其中prediction是预测平均每行有多少符合条件的值，不传入则设置为行长度的四分之一取整。返回值是包含匹配值索引的二维列表，元素可谓空值一维列表

## rotate[new from V1.0.6]
获取矩阵的旋转矩阵，旋转角度必须是90的整数倍，负值表示逆时针，正值表示顺时针

## mirror[new from V1.0.6]
获取矩阵的镜像，mode == 0表示横向镜像、其他值表示总线镜像

## decentralizate[new from V1.0.7]
获取去中心化的矩阵

## covariance[new from V1.0.7]
计算两个矩阵的协方差值

## cov[new from V1.0.7]
当不传入另一个矩阵时，计算当前矩阵的协方差矩阵，否则获取二者的协方差矩阵。底层实现时，视纵向为变量，横向为特征

## pearsonCoef[new from V1.0.7]
皮尔森系数计算

## MSE[new from V1.0.7]
均方误差。在几个评分标准中，传入的矩阵参数（rea）表示真实数据，而本身表示预测数据

## RMSE[new from V1.0.7]
均方根误差

## MAE[new from V1.0.7]
平均绝对误差

## MAPE[new from V1.0.7]
平均绝对百分比误差

## R2[new from V1.0.7]
决定系数

## SMAPE[new from V1.0.7]
对称平均绝对百分比误差

## fill_diagonal[new from V1.0.7]
对矩阵的最小维度对角上的值换为number

## choice[new from V1.0.7]
如果根据权重获取数据，权重可以是等列长一维列表，也可以是同形状矩阵。视行为样本。其中method方法分别为0、1、其他整数时，权重映射为原值、sigmoid函数值、绝对值；如果不传入权重，则按照等概率处理
