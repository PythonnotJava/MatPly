part of 'core.dart';

class MatrixType{
  /// Attributes
  late Pointer<Matrix> self;
  late List<int> shape;

  /// Constructors
  // 一般构造
  MatrixType(
      List<List<double>> data, {
        bool identityMatrix = false,
        bool principalDiagonalMatrix = false,
        bool subDiagonalMatrix = false,
        bool upperTriangularMatrix = false,
        bool lowerTriangularMatrix = false,
        bool singularMatrix  = false
      }){
    this.shape = [data.length, data[0].length];
    this.self = matply__new__(this.shape[0], this.shape[1]);  // 已经对data和spc分配了内存，并且对spc初始化了
    for (int r = 0;r < this.shape[0];r++){
      for (int c = 0;c < this.shape[1];c ++){
        this.self.ref.data[r][c] = data[r][c];
      }
    }
    defaultSpc(this);
  }

  @override
  String toString() {
    print("MatrixType:");
    visible();
    return 'shape : [${shape[0]}, ${shape[1]}]';
  }

  // 全number的矩阵
  MatrixType.filled({
    required double number,
    required int row,
    required int column
  }) :assert(row > 0 && column > 0){
    shape = [row, column];
    this.self = matply__filled(row, column, number);
    defaultSpc(this);
  }

  // 全1矩阵
  MatrixType.ones({
    required int row,
    required int column
  }) :assert(row > 0 && column > 0) {
    shape = [row, column];
    this.self = matply__ones(row, column);
    defaultSpc(this);
  }

  // 全0矩阵
  MatrixType.zeros({
    required int row,
    required int column
  }):assert(row > 0 && column > 0){
    shape = [row, column];
    this.self = matply__zeros(row, column);
    defaultSpc(this);
  }

  // 连续创建
  MatrixType.arrange({
    required double? start,
    required int row,
    required int column
  }):assert(row > 0 && column > 0){
    shape = [row, column];
    start = start ?? 0.0;
    this.self = matply__arrange(start, row, column);
    defaultSpc(this);
  }

  // 等差创建
  MatrixType.linspace({
    required double start,
    required double end,
    required int row,
    required int column,
    bool keep = true
  }) : assert(start < end && row > 0 && column > 0)
  {
    shape = [row, column];
    this.self = matply__linspace(start, end, row, column, keep);
    defaultSpc(this);
  }

  // n阶单位矩阵
  MatrixType.E({required int n}) : assert(n > 0){
    self = matply__E(n);
    shape = [n, n];
    this.identityMatrix = true;
  }

  // 均匀分布
  MatrixType.uniform({
    double start = .0,
    double end = 1.0,
    required int row,
    required int column,
    int? seed
  }) : assert(start < end && row > 0 && column > 0){
    this.shape = [row, column];
    this.self = matply__uniform(start, end, row, column, seed ?? 0, seed != null);
  }

  // 正态分布
  MatrixType.normal({
    double mu = 0.0,
    double sigma = 1.0,
    required int row,
    required int column,
    int? seed
  }):assert(sigma >= 0 && row > 0 && column > 0 && row > 0 && column > 0){
    this.shape = [row, column];
    this.self = matply__normal(mu, sigma, row, column, seed ?? 0, seed != null);
  }

  // 泊松分布
  MatrixType.poisson({
    required double lambda,
    required int row,
    required int column,
    int? seed
  }):assert(lambda >= 0 && row > 0 && column > 0){
    this.shape = [row, column];
    this.self = matply__poisson(lambda, row, column, seed ?? 0, seed != null);
  }

  // 根据已经建立好的Matrix指针初始化
  MatrixType.__fromPointer(this.self, this.shape);

  // 深拷贝矩阵
  factory MatrixType.deepCopy(MatrixType other) => MatrixType.__fromPointer(matply__deepcopy(other.self), other.shape);

  /// setter && getter
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

  int get size => shape[0] * shape[1];
  bool get isSquare => shape[0] == shape[1];
  MatrixType get T_ => transpose();
  double get trace => matply__trace(self);
  double get det{
    if (isSquare)
      return matply__det(self);
    else
      throw not_a_square;
  }
  MatrixType get inv {
    double value = this.det;
    if (value == 0)
      throw UnsupportedError('The matrix is not invertible.');
    else
      return MatrixType.__fromPointer(matply__inverse(self, det), shape);
  }
  MatrixType get adj => MatrixType.__fromPointer(matply__adjugate(self), shape);
  int get rank => matply__rank(self);

  MatrixType get acos => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 0, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get asin => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 1, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get atan => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 2, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get cos => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 3, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get sin => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 4, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get tan => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 5, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get cosh => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 6, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get sinh => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 7, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get tanh => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 8, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get exp => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 9, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get log => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 10, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get log10 => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 11, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get sqrt => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 12, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get ceil => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 13, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get floor => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 14, shape[0], shape[1], false).cast<Matrix>(), shape);
  MatrixType get fabs => MatrixType.__fromPointer(matply_mathBasement1(self.ref.data, 15, shape[0], shape[1], false).cast<Matrix>(), shape);

  /// Overloading Operators
  @Alert('Just return a List?, do not support pointer type.')
  List operator [](int row) {
    if (row < 0 || row >= shape[0]) {
      throw row_outRange;
    } else {
      return matply__row_(row, self).asTypedList(shape[1]).toList();
    }
  }

  MatrixType operator +(Object other) {
    if (other is num) {
      return this.add(number: other.toDouble());
    } else if (other is MatrixType) {
      return this.add(other: other);
    } else {
      throw UnsupportedError('Unsupported operand type for +: ${other.runtimeType}');
    }
  }

  MatrixType operator -(Object other) {
    if (other is num) {
      return this.minus(number: other.toDouble());
    } else if (other is MatrixType) {
      return this.minus(other: other);
    } else {
      throw UnsupportedError('Unsupported operand type for -: ${other.runtimeType}');
    }
  }

  MatrixType operator / (double number) => divide(number);

  MatrixType operator * (Object other) {
    if (other is num) {
      return this.multiply(number: other.toDouble());
    } else if (other is MatrixType) {
      return this.multiply(other: other);
    } else {
      throw UnsupportedError('Unsupported operand type for *: ${other.runtimeType}');
    }
  }

  MatrixType operator >> (List<int> shape) => reshape(row: shape[0], column: shape[1]);
  void operator << (List<int> shape) => reshape_no_returned(row:shape[0], column: shape[1]);

  @Alert('The == operator is only used to determine whether the properties of the objects are the same. '
      'If you only want to compare data, use the compare method and set mode to 0.')
  @override
  bool operator ==(Object other) {
    if (identical(this, other)) return true;
    if (other is! MatrixType) return false;
    final MatrixType otherMatrix = other;
    return hasSameShape(otherMatrix) &&
        matply__data__isSame(self.ref.data, otherMatrix.self.ref.data, shape[0], shape[1]) &&
        matply__spc__isSame(self.ref.spc, otherMatrix.self.ref.spc);
  }

  List<List<bool>> operator >(MatrixType other) => compare(other, mode: 1);
  List<List<bool>> operator <(MatrixType other) => compare(other, mode: 2);
  List<List<bool>> operator <=(MatrixType other) => compare(other, mode: 3);
  List<List<bool>> operator >=(MatrixType other) => compare(other, mode: 4);

  /// Methods
  void visible() => matply__VisibleMatrix(this.self);

  void visible_spc() => matply__VisibleMatrixSpc(this.self);

  @Alert('Returning a Pointer? or a List? depends on the type you give in.'
      'However in Dart, Using the Pointer type is not a good choice')
  Object row_<T>(int row) {
    if (row < 0 || row >= shape[0]) {
      throw row_outRange;
    } else {
      if (T == Pointer) {
        return matply__row_(row, self);
      } else if (T == List || T == dynamic) {
        return matply__row_(row, self).asTypedList(shape[1]).toList();
      } else {
        throw UnsupportedError('T must be Pointer or List');
      }
    }
  }

  @Alert('Returning a Pointer? or a List? depends on the type you give in.'
      'However in Dart, using the Pointer type is not a good choice')
  Object column_<T>(int column) {
    if (column < 0 || column >= shape[1]) {
      throw column_outRange;
    } else {
      if (T == Pointer) {
        return matply__column_(column, self);
      } else if (T == List) {
        return matply__column_(column, self).asTypedList(shape[1]).toList();
      } else {
        throw UnsupportedError('T must be Pointer or List');
      }
    }
  }

  double at(int row, int column){
    if (column < 0 || column >= shape[1] || row < 0 || row >= shape[0])
      throw random_outRange;
    else{
      return matply__at(row, column, self);
    }
  }

  MatrixType transpose() => MatrixType.__fromPointer(matply__transpose(self), [shape[1], shape[0]]);

  void exchange_row(int row1, int row2){
    if (row1 < 0 || row1 >= shape[0] || row2 < 0 || row2 >= shape[0])
      throw row_outRange;
    else
      matply__exchangeR(row1, row2, self);
  }
  void exchange_column(int column1, int column2){
    if (column1 < 0 || column1 >= shape[1] || column2 < 0 || column2 >= shape[1])
      throw column_outRange;
    else
      matply__exchangeC(column1, column2, self);
  }
  void multiply_row(int row, double size) {
    if (row < 0 || row >= shape[0])
      throw row_outRange;
    else
      matply__multiplyR(row, size, self);
  }
  void multiply_column(int column, double size) {
    if (column < 0 || column >= shape[1])
      throw column_outRange;
    else
      matply__multiplyC(column, size, self);
  }
  void add_row(int row1, int row2, double size){
    if (row1 < 0 || row1 >= shape[0] || row2 < 0 || row2 >= shape[0])
      throw row_outRange;
    else
      matply__addR(row1, row2, size, self);
  }
  void add_column(int column1, int column2, double size) {
    if (column1 < 0 || column1 >= shape[1] || column2 < 0 || column2 >= shape[1])
      throw column_outRange;
    else
      matply__addC(column1, column2, size, self);
  }

  bool hasSameShape(MatrixType other){ return other.shape[0] == shape[0] && shape[1] == other.shape[1];}

  MatrixType add({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      return MatrixType.__fromPointer(matply__addNumber(number, self), shape);
    else {
      if (hasSameShape(other!))
        return MatrixType.__fromPointer(matply__addMatrix(other.self, self), shape);
      else
        throw different_shape;
    }
  }

  MatrixType minus({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      return MatrixType.__fromPointer(matply__addNumber(-number, self), shape);
    else {
      if (hasSameShape(other!))
        return MatrixType.__fromPointer(matply__minusMatrix(self, other.self), shape);
      else
        throw different_shape;
    }
  }

  void add_no_returned({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      matply__addNumberNoReturned(number, self);
    else {
      if (hasSameShape(other!))
        matply__addMatrixNoReturned(other.self, self);
      else
        throw different_shape;
    }
  }

  void minus_no_returned({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      matply__addNumberNoReturned(-number, self);
    else {
      if (hasSameShape(other!))
        matply__minusMatrix(self, other.self);
      else
        throw different_shape;
    }
  }

  MatrixType matmul(MatrixType other){
    if (shape[1] != other.shape[0])
      throw matmul_unsupport;
    else
      return MatrixType.__fromPointer(matply_matmul(self, other.self), [shape[0], other.shape[1]]);
  }

  void multiply_no_returned({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      matply__multiplyNumber(number, self);
    else {
      if (hasSameShape(other!))
        matply__multiplyMatrix(self, other.self);
      else
        throw different_shape;
    }
  }

  MatrixType multiply({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      return MatrixType.__fromPointer(matply__multiplyNumber(number, self), shape);
    else {
      if (hasSameShape(other!))
        return MatrixType.__fromPointer(matply__multiplyMatrix(self, other.self), shape);
      else
        throw different_shape;
    }
  }

  MatrixType kronecker(MatrixType other) => MatrixType.__fromPointer(
      matply__kronecker(self, other.self),
      [shape[0] * other.shape[0], shape[1] * shape[1]]
  );

  MatrixType divide(double number){
    if (number != 0)
      return MatrixType.__fromPointer(matply__divide(number, self), shape);
    else
      throw UnsupportedError('Division by zero');
  }

  void divide_no_returned(double number) {
    if (number != 0)
      matply__divideNoReturned(number, self);
    else
      throw UnsupportedError('Division by zero');
  }

  MatrixType cofactor(int row, int column){
    if (row < 0 || row >= shape[0] || column < 0 || column >= shape[1])
      throw random_outRange;
    else{
      if (shape[0] == 1 || shape[1] == 1)
        throw cannot_be_splitt_more;
      else
        return MatrixType.__fromPointer(matply__cofacto(row, column, self), [shape[0] - 1, shape[1] - 1]);
    }
  }

  List<List<bool>> compare(MatrixType other, {int mode = 0}){
    if (hasSameShape(other)){
      Pointer<Pointer<Bool>> results = matply__compare(self, other.self, mode);
      return List.generate(
          shape[0],
              (e) {
            Pointer<Bool> rowPointer = (results + e).value;
            return List.generate(shape[1], (j) => (rowPointer + j).value
            );
          });
    }
    else
      throw different_shape;
  }

  Object sum({int dim = -1}){
    switch(dim){
      case 0:
        return matply__sum(self, 0).asTypedList(shape[0]).toList();
      case 1:
        return matply__sum(self, 1).asTypedList(shape[1]).toList();
      default:
        return matply__sum(self, -1).value;
    }
  }

  Object mean({int dim = -1}){
    switch(dim){
      case 0:
        return matply__mean(self, 0).asTypedList(shape[0]).toList();
      case 1:
        return matply__mean(self, 1).asTypedList(shape[1]).toList();
      default:
        return matply__mean(self, -1).value;
    }
  }

  Object min({int dim = -1}){
    switch(dim){
      case 0:
        return matply__min(self, 0).asTypedList(shape[0]).toList();
      case 1:
        return matply__min(self, 1).asTypedList(shape[1]).toList();
      default:
        return matply__min(self, -1).value;
    }
  }

  Object max({int dim = -1}){
    switch(dim){
      case 0:
        return matply__max(self, 0).asTypedList(shape[0]).toList();
      case 1:
        return matply__max(self, 1).asTypedList(shape[1]).toList();
      default:
        return matply__max(self, -1).value;
    }
  }

  MatrixType cut({required int row, required int column, required int width, required int height}){
    assert(width > 0 && height > 0);
    if (row < 0 || row >= shape[0] || column < 0 || column >= shape[1] || column + width > shape[1] || row + height > shape[0])
      throw random_outRange;
    else
      return MatrixType.__fromPointer(matply__cut(self, row, column, width, height), [width, height]);
  }

  MatrixType cutfree({required int row, required int column, required int width, required int height, double number = .0}){
    assert(width > 0 && height > 0);
    if (row < 0 || row >= shape[0] || column < 0 || column >= shape[1])
      throw random_outRange;
    else
      return MatrixType.__fromPointer(matply__cutfree(self, row, column, width, height, number), [width, height]);
  }

  MatrixType concat({required MatrixType other, required bool horizontal}) {
    if (horizontal ? other.shape[0] == shape[0] : other.shape[1] == shape[1]) {
      return horizontal ? MatrixType.__fromPointer(
          matply__concatR(self, other.self),
          [shape[0], shape[1] + other.shape[1]])
          : MatrixType.__fromPointer(
          matply__concatC(self, other.self), [shape[0] + shape[1], shape[1]]);
    } else
      throw row_or_column_not_sampe;
  }

  MatrixType reshape({required int row, required int column}){
    if (row * column != size)
      throw size_changed;
    else{
      if (row == shape[0])
        return MatrixType.deepCopy(this);
      assert (row > 0 && column > 0);
      return MatrixType.__fromPointer(matply__reshape(self, row, column), [row, column]);
    }
  }

  void reshape_no_returned({required int row, required int column}) {
    if (row * column != size)
      throw size_changed;
    else{
      if (row == shape[0])
        return;
      assert(row > 0 && column > 0);
      matply__reshapeNoReturned(self, row, column);
    }
  }

  MatrixType resize({required int row, required int column, double number = .0, bool horizontal = true}){
    assert(row > 0 && column > 0);
    return horizontal ? MatrixType.__fromPointer(matply__resizeR(self, row, column, number), [row, column])
        : MatrixType.__fromPointer(matply__resizeC(self, row, column, number), [row, column]);
  }

  void resize_no_returned({required int row, required int column, double number = .0, bool horizontal = true}){
    assert(row > 0 && column > 0);
    horizontal ? matply__resizeRNoReturned(self, row, column, number)
        : matply__resizeCNoReturned(self, row, column, number);
  }

  MatrixType power({required double number, bool reverse = false})
  => reverse ?
  MatrixType.__fromPointer(matply_mathBasement2reverse(self.ref.data, 0, number, shape[0], shape[1], false).cast<Matrix>(), shape) :
  MatrixType.__fromPointer(matply_mathBasement2(self.ref.data, 0, number, shape[0], shape[1], false).cast<Matrix>(), shape);


  MatrixType atan2({required double number, bool reverse = true})
  => reverse
      ? MatrixType.__fromPointer(matply_mathBasement2(self.ref.data, 1, number, shape[0], shape[1], false).cast<Matrix>(), shape)
      : MatrixType.__fromPointer(matply_mathBasement2reverse(self.ref.data, 1, number,  shape[0], shape[1], false).cast<Matrix>(), shape);

  MatrixType sigmoid() => MatrixType.__fromPointer(matply__sigmoid(self), shape);

  MatrixType softmax({
    int dim = -1,
    double mask_nan = 0.0,
    double mask_inf = 0.0,
    double mask_neginf = 0.0
  }) => MatrixType.__fromPointer(matply__softmax(self, dim, mask_nan, mask_inf, mask_neginf), shape);

  void shuffle() => matply__shuffle(self.ref.data, shape[0], shape[1]);

  void sort_no_returned({
    int dim = -1,
    bool reverse = false,
    double mask_nan = 0.0
  }) => matply__sortNoReturned(self.ref.data, shape[0], shape[1], reverse, dim, mask_nan);

  MatrixType sort({
    int dim = -1,
    bool reverse = false,
    double mask_nan = 0.0
  }) => MatrixType.__fromPointer(matply__sort(self, reverse, dim, mask_nan), shape);

  MatrixType rref() => MatrixType.__fromPointer(matply__rref(self.ref.data, shape[0], shape[1]), shape);

  void setMask({double? mask_nan, double? mask_inf, bool isNegativeInf = true, bool both = false}){  // both表示正负无穷大都取值
    if (mask_nan == null && mask_inf == null)
      throw UnsupportedError('At least one of mask_nan or mask_inf cannot be empty.');
    if (mask_nan != null)
      matply__set_mask_nan(self, mask_nan);
    if (mask_inf != null) {
      matply__set_mask_inf(self, mask_inf, isNegativeInf);
      if (both)
        matply__set_mask_inf(self, mask_inf, !isNegativeInf);
    }
  }

}
