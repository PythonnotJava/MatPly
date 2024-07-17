# MatrixType的属性

> 在MatrixType的属性中，仅*shape*和*self*是需要在实例创建时初始化的。

## shape属性

矩阵的形状，是一个包含两个整数的列表

## self属性
self属性是指向**Matrix实例**的指针，虽然self属性是公开属性，然而我并不建议操作它，而是用于管理构建新方法时调用。Matrix类本身即C语言代码中实现的Matrix结构体，它包含二维数组、特殊属性、row、column两个属性，额外声明shape属性是为了更好的在类中实现代码，而不是每次都去访问row、column，在已经实现的方法中，MatrixType实例更新形状时shape也会变化。

## 特殊属性
```text
bool get identityMatrix => this.self.ref.spc.ref.identityMatrix;
set identityMatrix(bool value) => this.self.ref.spc.ref.identityMatrix = value;

bool get principalDiagonalMatrix => this.self.ref.spc.ref.principalDiagonalMatrix;
set principalDiagonalMatrix(bool value) => this.self.ref.spc.ref.principalDiagonalMatrix = value;

bool get upperTriangularMatrix => this.self.ref.spc.ref.upperTriangularMatrix;
set upperTriangularMatrix(bool value) => this.self.ref.spc.ref.upperTriangularMatrix = value;

bool get subDiagonalMatrix => this.self.ref.spc.ref.subDiagonalMatrix;
set subDiagonalMatrix(bool value) => this.self.ref.spc.ref.subDiagonalMatrix = value;

bool get lowerTriangularMatrix => this.self.ref.spc.ref.lowerTriangularMatrix;
set lowerTriangularMatrix(bool value) => this.self.ref.spc.ref.lowerTriangularMatrix = value;

bool get singularMatrix => this.self.ref.spc.ref.singularMatrix;
set singularMatrix(bool value) => this.self.ref.spc.ref.singularMatrix = value;
```
这里不再赘述。

## size
获取矩阵的数据量，它等于row * column

## isSquare
判断是不是方阵

## T_
获取矩阵的转置矩阵，是方法*transpose*的属性版本

## trace
获取矩阵的迹，针对任何矩阵，访问最小维度决定的迹

## det
获取**方阵**的行列式值，对于一般矩阵采用**高斯消元法**

## inv
获取**行列式值不为0的方阵**的逆矩阵

## adj
获取**任意方阵**的伴随矩阵

## rank
获取矩阵的秩，利用高斯消元法化上三角矩阵

## 数学工具封装的属性
```text
acos\asin\atan\cos\sin\tan\cosh\sinh\tanh\exp\log\log10\sqrt\ceil\fabs
```

在利用这些数学方法来处理矩阵中*正负无穷大*和*nan*数据时，可以使用*setMask*来处理这些数据的值变换，但这也会修改矩阵！因此，你可以采用矩阵深拷贝避免。






