part of 'core.dart';

class MatrixType{
  /// Attributes
  late Pointer<Matrix> self;

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
    this.self = matply__new__(data.length, data[0].length);  // 已经对data和spc分配了内存，并且对spc初始化了
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
    this.self = matply__init__point__data__(row, column, matply__filled(row, column, number), nullptr);
  }

  // 全1矩阵
  MatrixType.ones({
    required int row,
    required int column
  }) :assert(row > 0 && column > 0) {
    this.self = matply__init__point__data__(row, column, matply__ones(row, column), nullptr);
  }

  // 全0矩阵
  MatrixType.zeros({
    required int row,
    required int column
  }):assert(row > 0 && column > 0){
    this.self = matply__init__point__data__(row, column, matply__zeros(row, column), nullptr);
  }

  // 连续创建
  MatrixType.arrange({
    required double? start,
    required int row,
    required int column
  }):assert(row > 0 && column > 0){
    start = start ?? 0.0;
    this.self = matply__init__point__data__(row, column, matply__arrange(start, row, column), nullptr);
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
    this.self = matply__init__point__data__(row, column, matply__linspace(start, end, row, column, keep), nullptr);
  }

  // n阶单位矩阵
  MatrixType.E({required int n}) : assert(n > 0){
    self = matply__init__point__data__(n, n, matply__E(n), nullptr);
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
    this.self = matply__init__point__data__(
        row, column, matply__uniform(row, column, start, end, seed ?? 0, seed != 0), nullptr
    );
  }

  // 正态分布
  MatrixType.normal({
    double mu = 0.0,
    double sigma = 1.0,
    required int row,
    required int column,
    int? seed
  }):assert(sigma >= 0 && row > 0 && column > 0 && row > 0 && column > 0){
    this.self = matply__init__point__data__(
      row, column, matply__normal(row, column, mu, sigma, seed ?? 0, seed != 0), nullptr
    );
  }

  // 泊松分布
  MatrixType.poisson({
    required double lambda,
    required int row,
    required int column,
    int? seed
  }):assert(lambda >= 0 && row > 0 && column > 0){
    this.self = matply__init__point__data__(
      row, column, matply__poisson(row, column, lambda, seed ?? 0, seed != null), nullptr
    );
  }

  // 根据已经建立好的Matrix指针初始化
  MatrixType.__fromPointer(this.self);
  // 根据已经设置完毕的数据指针引用并且初始化
  MatrixType.__fromDataPointer(Pointer<Pointer<Double>> data, List<int> shape) :
        this.self = matply__init__point__data__(shape[0], shape[1], data, nullptr);

  // 深拷贝矩阵
  factory MatrixType.deepCopy(MatrixType other) {
    Pointer<Pointer<Double>> data = matply__deepcopy(other.shape[0], other.shape[1], other.self.ref.data);
    return MatrixType.__fromDataPointer(data, other.shape);
  }

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

  List<int> get shape => [this.self.ref.row, this.self.ref.column];
  int get size => shape[0] * shape[1];
  bool get isSquare => shape[0] == shape[1];
  MatrixType get T_ => transpose();
  double get trace => matply__trace(shape[0], shape[1], self.ref.data);
  double get det{
    if (isSquare)
      return matply__det(shape[0], shape[1], self.ref.data);
    else
      throw not_a_square;
  }
  MatrixType get inv {
    double value = this.det;
    if (value == 0)
      throw UnsupportedError('The matrix is not invertible.');
    else
      return MatrixType.__fromDataPointer(matply__inverse(shape[0], shape[1], self.ref.data), shape);
  }
  MatrixType get adj => MatrixType.__fromDataPointer(matply__adjugate(shape[0], shape[1], self.ref.data), shape);
  int get rank => matply__rank(shape[0], shape[1], self.ref.data);

  MatrixType get acos => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 0), shape);
  MatrixType get asin => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 1), shape);
  MatrixType get atan => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 2), shape);
  MatrixType get cos => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 3), shape);
  MatrixType get sin => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 4), shape);
  MatrixType get tan => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 5), shape);
  MatrixType get cosh => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 6), shape);
  MatrixType get sinh => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 7), shape);
  MatrixType get tanh => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 8), shape);
  MatrixType get exp => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 9), shape);
  MatrixType get log => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 10), shape);
  MatrixType get log10 => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 11), shape);
  MatrixType get sqrt => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 12), shape);
  MatrixType get ceil => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 13), shape);
  MatrixType get floor => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 14), shape);
  MatrixType get fabs => MatrixType.__fromDataPointer(matply_mathBasement1(shape[0], shape[1], self.ref.data, 15), shape);

  /// Overloading Operators
  @Alert('Just return a List?, do not support pointer type.')
  List operator [](int row) {
    if (row < 0 || row >= shape[0]) {
      throw row_outRange;
    } else {
      return matply__row_(row, shape[1], self.ref.data).asTypedList(shape[1]).toList();
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
        matply__data__isSame(shape[0], shape[1], self.ref.data, otherMatrix.self.ref.data) &&
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
        return matply__row_(row, shape[1], self.ref.data);
      } else if (T == List || T == dynamic) {
        return matply__row_(row, shape[1], self.ref.data).asTypedList(shape[1]).toList();
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
        return matply__column_(shape[0], column, self.ref.data);
      } else if (T == List || T == dynamic) {
        return matply__column_(shape[0], column, self.ref.data).asTypedList(shape[1]).toList();
      } else {
        throw UnsupportedError('T must be Pointer or List');
      }
    }
  }

  double at(int row, int column){
    if (column < 0 || column >= shape[1] || row < 0 || row >= shape[0])
      throw random_outRange;
    else{
      return matply__at(row, column, self.ref.data);
    }
  }

  MatrixType transpose() => MatrixType.__fromDataPointer(matply__transpose(shape[0], shape[1], self.ref.data), [shape[1], shape[0]]);

  void exchange_row(int row1, int row2){
    if (row1 < 0 || row1 >= shape[0] || row2 < 0 || row2 >= shape[0])
      throw row_outRange;
    else
      matply__exchangeR(shape[1], self.ref.data, row1, row2);
  }
  void exchange_column(int column1, int column2){
    if (column1 < 0 || column1 >= shape[1] || column2 < 0 || column2 >= shape[1])
      throw column_outRange;
    else
      matply__exchangeC(shape[0], self.ref.data, column1, column2);
  }
  void multiply_row(int row, double size) {
    if (row < 0 || row >= shape[0])
      throw row_outRange;
    else
      matply__multiplyR(shape[0], shape[1], self.ref.data, size);
  }
  void multiply_column(int column, double size) {
    if (column < 0 || column >= shape[1])
      throw column_outRange;
    else
      matply__multiplyC(shape[0], shape[1], self.ref.data, size);
  }
  void add_row(int row1, int row2, double size){
    if (row1 < 0 || row1 >= shape[0] || row2 < 0 || row2 >= shape[0])
      throw row_outRange;
    else
      matply__addR(shape[1], self.ref.data, row1, row2, size);
  }
  void add_column(int column1, int column2, double size) {
    if (column1 < 0 || column1 >= shape[1] || column2 < 0 || column2 >= shape[1])
      throw column_outRange;
    else
      matply__addC(shape[0], self.ref.data, column1, column2, size);
  }

  bool hasSameShape(MatrixType other){ return other.shape[0] == shape[0] && shape[1] == other.shape[1];}

  MatrixType add({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      return MatrixType.__fromDataPointer(matply__addNumber(shape[0], shape[1], self.ref.data, number), shape);
    else {
      if (hasSameShape(other!))
        return MatrixType.__fromDataPointer(matply__addMatrix(shape[0], shape[1], self.ref.data, other.self.ref.data), shape);
      else
        throw different_shape;
    }
  }

  MatrixType minus({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      return MatrixType.__fromDataPointer(matply__addNumber(shape[0], shape[1], self.ref.data, -number), shape);
    else {
      if (hasSameShape(other!))
        return MatrixType.__fromDataPointer(matply__minusMatrix(shape[0], shape[1], self.ref.data, other.self.ref.data), shape);
      else
        throw different_shape;
    }
  }

  void add_no_returned({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      matply__addNumberNoReturned(shape[0], shape[1], self.ref.data, number);
    else {
      if (hasSameShape(other!))
        matply__addMatrixNoReturned(shape[0], shape[1], self.ref.data, other.self.ref.data);
      else
        throw different_shape;
    }
  }

  void minus_no_returned({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      matply__addNumberNoReturned(shape[0], shape[1], self.ref.data, -number);
    else {
      if (hasSameShape(other!))
        matply__minusMatrixNoReturned(shape[0], shape[1], self.ref.data, other.self.ref.data);
      else
        throw different_shape;
    }
  }

  MatrixType matmul(MatrixType other){
    if (shape[1] != other.shape[0])
      throw matmul_unsupport;
    else
      return MatrixType.__fromDataPointer(matply__matmul(shape[0], shape[1], self.ref.data, other.self.ref.data), shape);
  }

  void multiply_no_returned({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      matply__multiplyNumber(shape[0], shape[1], self.ref.data, number);
    else {
      if (hasSameShape(other!))
        matply__multiplyMatrix(shape[0], shape[1], self.ref.data, other.self.ref.data);
      else
        throw different_shape;
    }
  }

  MatrixType multiply({double? number, MatrixType? other}){
    assert(number != null || other != null);
    if (number != null)
      return MatrixType.__fromDataPointer(matply__multiplyNumber(shape[0], shape[1], self.ref.data, number), shape);
    else {
      if (hasSameShape(other!))
        return MatrixType.__fromDataPointer(matply__multiplyMatrix(shape[0], shape[1], self.ref.data, other.self.ref.data), shape);
      else
        throw different_shape;
    }
  }

  MatrixType kronecker(MatrixType other) => MatrixType.__fromDataPointer(
      matply__kronecker(shape[0], shape[1], self.ref.data, other.shape[0], other.shape[1], other.self.ref.data),
      [shape[0] * other.shape[0], shape[1] * shape[1]]
  );

  MatrixType divide(double number){
    if (number != 0)
      return MatrixType.__fromDataPointer(matply__divide(shape[0], shape[1], self.ref.data, number), shape);
    else
      throw UnsupportedError('Division by zero');
  }

  void divide_no_returned(double number) {
    if (number != 0)
      matply__divideNoReturned(shape[0], shape[1], self.ref.data, number);
    else
      throw UnsupportedError('Division by zero');
  }

  MatrixType cofactor(int row, int column) {
    if (row < 0 || row >= shape[0] || column < 0 || column >= shape[1])
      throw random_outRange;
    else {
      if (shape[0] == 1 || shape[1] == 1)
        throw cannot_be_splitt_more;
      else
        return MatrixType.__fromDataPointer(
            matply__cofacto(shape[0], shape[1], self.ref.data, row, column),
            [shape[0] - 1, shape[1] - 1]);
    }
  }

  List<List<bool>> compare(MatrixType other, {int mode = 0}){
    if (hasSameShape(other)){
      Pointer<Pointer<Bool>> results = matply__compare(shape[0], shape[1], self.ref.data, other.self.ref.data, mode);
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
        return matply__sum(shape[0], shape[1], self.ref.data, 0).asTypedList(shape[0]).toList();
      case 1:
        return matply__sum(shape[0], shape[1], self.ref.data, 1).asTypedList(shape[1]).toList();
      default:
        return matply__sum(shape[0], shape[1], self.ref.data, -1).value;
    }
  }

  Object mean({int dim = -1}){
    switch(dim){
      case 0:
        return matply__mean(shape[0], shape[1], self.ref.data,  0).asTypedList(shape[0]).toList();
      case 1:
        return matply__mean(shape[0], shape[1], self.ref.data,  1).asTypedList(shape[1]).toList();
      default:
        return matply__mean(shape[0], shape[1], self.ref.data,  -1).value;
    }
  }

  Object min({int dim = -1}){
    switch(dim){
      case 0:
        return matply__min(shape[0], shape[1], self.ref.data,  0).asTypedList(shape[0]).toList();
      case 1:
        return matply__min(shape[0], shape[1], self.ref.data,  1).asTypedList(shape[1]).toList();
      default:
        return matply__min(shape[0], shape[1], self.ref.data,  -1).value;
    }
  }

  Object max({int dim = -1}){
    switch(dim){
      case 0:
        return matply__max(shape[0], shape[1], self.ref.data, 0).asTypedList(shape[0]).toList();
      case 1:
        return matply__max(shape[0], shape[1], self.ref.data, 1).asTypedList(shape[1]).toList();
      default:
        return matply__max(shape[0], shape[1], self.ref.data,  -1).value;
    }
  }

  MatrixType cut({required int row, required int column, required int width, required int height}){
    assert(width > 0 && height > 0);
    if (row < 0 || row >= shape[0] || column < 0 || column >= shape[1] || column + width > shape[1] || row + height > shape[0])
      throw random_outRange;
    else
      return MatrixType.__fromDataPointer(matply__cut(shape[0], shape[1], self.ref.data, row, column, width, height), shape);
  }

  MatrixType cutfree({required int row, required int column, required int width, required int height, double number = .0}){
    assert(width > 0 && height > 0);
    if (row < 0 || row >= shape[0] || column < 0 || column >= shape[1])
      throw random_outRange;
    else
      return MatrixType.__fromDataPointer(matply__cutfree(shape[0], shape[1], self.ref.data, row, column, width, height, number), shape);
  }

  MatrixType concat({required MatrixType other, required bool horizontal}) {
    if (horizontal ? other.shape[0] == shape[0] : other.shape[1] == shape[1]) {
      return horizontal ? MatrixType.__fromDataPointer(
          matply__concatR(shape[0], shape[1], other.shape[1], self.ref.data, other.self.ref.data),
          [shape[0], shape[1] + other.shape[1]]
      )
          : MatrixType.__fromDataPointer(
          matply__concatC(shape[0], other.shape[0], shape[1], self.ref.data, other.self.ref.data),
          [shape[0] + other.shape[0], shape[1]]
      );
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
      return MatrixType.__fromDataPointer(matply__reshape(row, column, self.ref.data, shape[1]), [row, column]);
    }
  }

  void reshape_no_returned({required int row, required int column}) {
    if (row * column != size)
      throw size_changed;
    else{
      if (row == shape[0])
        return;
      assert(row > 0 && column > 0);
      matply__reshapeNoReturned(row, column, self.ref.data, shape[0], shape[1]);
    }
  }

  MatrixType resize({required int row, required int column, double number = .0, bool horizontal = true}){
    assert(row > 0 && column > 0);
    return horizontal ?
    MatrixType.__fromDataPointer(matply__resizeR(row, column, self.ref.data, shape[0], shape[1], number), [row, column]) :
    MatrixType.__fromDataPointer(matply__resizeC(row, column, self.ref.data, shape[0], shape[1], number), [row, column]);
  }

  void resize_no_returned({required int row, required int column, double number = .0, bool horizontal = true}){
    assert(row > 0 && column > 0);
    horizontal ?
    matply__resizeRNoReturned(row, column, self.ref.data, shape[0], shape[1], number) :
    matply__resizeCNoReturned(row, column, self.ref.data, shape[0], shape[1], number);
  }

  MatrixType power({required double number, bool reverse = false})
    => reverse
        ? MatrixType.__fromDataPointer(matply_mathBasement2reverse(shape[0], shape[1], self.ref.data, 0, number), shape)
        : MatrixType.__fromDataPointer(matply_mathBasement2(shape[0], shape[1], self.ref.data, 0, number), shape);

  MatrixType atan2({required double number, bool reverse = true})
  => reverse
      ? MatrixType.__fromDataPointer(matply_mathBasement2reverse(shape[0], shape[1], self.ref.data, 1, number), shape)
      : MatrixType.__fromDataPointer(matply_mathBasement2(shape[0], shape[1], self.ref.data, 1, number), shape);

  MatrixType sigmoid() => MatrixType.__fromDataPointer(matply__sigmoid(shape[0], shape[1], self.ref.data), shape);

  MatrixType softmax({
    int dim = -1,
    double mask_nan = 0.0,
    double mask_inf = 0.0,
    double mask_neginf = 0.0
  }) => MatrixType.__fromDataPointer(matply__softmax(shape[0], shape[1], self.ref.data, dim, mask_nan, mask_nan, mask_neginf), shape);

  void shuffle() => matply__shuffle(shape[0], shape[1], self.ref.data);

  void sort_no_returned({
    int dim = -1,
    bool reverse = false,
    double mask_nan = 0.0
  }) => matply__sortNoReturned(shape[0], shape[1], self.ref.data, reverse, dim, mask_nan);

  MatrixType sort({
    int dim = -1,
    bool reverse = false,
    double mask_nan = 0.0
  }) => MatrixType.__fromDataPointer(matply__sort(shape[0], shape[1], self.ref.data, reverse, dim, mask_nan), shape);

  MatrixType rref() => MatrixType.__fromDataPointer(matply__rref(shape[0], shape[1], self.ref.data), shape);

  void setMask({double? mask_nan, double? mask_inf, bool isNegativeInf = true, bool both = false}){  // both表示正负无穷大都取值
    if (mask_nan == null && mask_inf == null)
      throw UnsupportedError('At least one of mask_nan or mask_inf cannot be empty.');
    if (mask_nan != null)
      matply__set_mask_nan(shape[0], shape[1], self.ref.data, mask_nan);
    if (mask_inf != null) {
      matply__set_mask_inf(shape[0], shape[1], self.ref.data, mask_inf, isNegativeInf);
    if (both)
      matply__set_mask_inf(shape[0], shape[1], self.ref.data, mask_inf, !isNegativeInf);
    }
  }

  List<List<Object>> toList<T>() {
    if (T == double) {
      return List.generate(shape[0], (i) => matply__row_(shape[0], shape[1], self.ref.data).asTypedList(shape[1]));
    } else if (T == int) {
      return List.generate(shape[0], (i) => this[i].map<int>((e) => e.toInt()).toList());
    } else if (T == String) {
      return List.generate(shape[0], (i) => this[i].map<String>((e) => e.toString()).toList());
    }else if (T == bool){
      return List.generate(shape[0], (i) => this[i].map<bool>((e) => (e != 0) ).toList());
    } else {
      throw UnsupportedError('Unsupported type.');
    }
  }

  Object __variance_std({int dim = -1, bool sample = false, required bool std}){
    switch(dim){
      case 0:
        return matply__variance(shape[0], shape[1], self.ref.data, sample, 0, std).asTypedList(shape[0]);
      case 1:
        return matply__variance(shape[0], shape[1], self.ref.data, sample, 1, std).asTypedList(shape[1]);
      default:
        return matply__variance(shape[0], shape[1], self.ref.data, sample, -1, std).value;
    }
  }

  Object std({int dim = -1, bool sample = false}) => __variance_std(dim: dim, sample: sample, std: true);
  Object variance({int dim = -1, bool sample = false}) => __variance_std(dim: dim, sample: sample, std: false);

  Object median({int dim = -1}){
    switch (dim){
      case 0:
        return matply__median(shape[0], shape[1], self.ref.data, 0).asTypedList(shape[0]);
      case 1:
        return matply__median(shape[0], shape[1], self.ref.data, 1).asTypedList(shape[1]);
      default:
        return matply__median(shape[0], shape[1], self.ref.data, -1).value;
    }
  }

  Object norm({int n = 2, int dim = -1}){
    if (n < -2)
      throw UnsupportedError('Integer n must be no less than -1.');
    else{
      switch(n){
        case -2:
          return matply__norm_negainf(shape[0], shape[1], self.ref.data);
        case -1:
          return matply__norm_inf(shape[0], shape[1], self.ref.data);
        case 0:
          switch (dim){
            case 0:
              return matply__norm_zero(shape[0], shape[1], self.ref.data, 0).asTypedList(shape[0]);
            case 1:
              return matply__norm_zero(shape[0], shape[1], self.ref.data, 1).asTypedList(shape[1]);
            default:
              return matply__norm_zero(shape[0], shape[1], self.ref.data, -1).value.toInt();
          }
        case 1:
          return matply__norm_one(shape[0], shape[1], self.ref.data);
        default:
          switch (dim){
            case 0:
              return matply__norm(shape[0], shape[1], self.ref.data, n, 0).asTypedList(shape[0]);
            case 1:
              return matply__norm(shape[0], shape[1], self.ref.data, n, 1).asTypedList(shape[1]);
            default:
              return matply__norm(shape[0], shape[1], self.ref.data, n, -1).value;
          }
      }
    }
  }

  Object norm2({int dim = -1}) => norm(dim: dim, n: 2);
  double norm_inf() => matply__norm_inf(shape[0], shape[1], self.ref.data);
  double norm_negainf() => matply__norm_negainf(shape[0], shape[1], self.ref.data);
  double norm_one() => matply__norm_one(shape[0], shape[1], self.ref.data);
  Object norm_zero({int dim = -1}) => norm(n: 0, dim: dim);

  Object mode({int dim  = -1}){
    Pointer<Pointer<Double>> data = self.ref.data;

    double value;
    switch(dim){
      case 0:
        List<double> list = [];
        for (int r = 0;r < shape[0];r ++){
        Map<double, int> hist = {};
          for(int c=0;c < shape[1];c ++){
            value = data[r][c];
            if (!hist.containsKey(value))
              hist[value] = 1;
            else
              hist[value] = hist[value]! + 1;
          }
          int maxCount = 0;
          double _k = 0.0;
          hist.forEach((k, v){
            if (v > maxCount) {
              maxCount = v;
              _k = k;
            }
          });
          list.add(_k);
        }
        return list;
      case 1:
        List<double> list = [];
        for (int c = 0;c < shape[1];c ++){
          Map<double, int> hist = {};
          for(int r =0;r < shape[0];r++){
            value = data[r][c];
            if (!hist.containsKey(value))
              hist[value] = 1;
            else
              hist[value] = hist[value]! + 1;
          }
          int maxCount = 0;
          double _k = 0.0;
          hist.forEach((k, v){
            if (v > maxCount) {
              maxCount = v;
              _k = k;
            }
          });
          list.add(_k);
        }
        return list;
      default:
        Map<double, int> hist = {};
        for (int r= 0;r < shape[0];r++){
          for (int c = 0;c < shape[1];c ++){
            value = data[r][c];
            if (hist.containsKey(value))
              hist[value] = hist[value]! + 1;
            else
              hist[value] = 1;
          }
        }
        int maxCount = 0;
        double _k = 0.0;
        hist.forEach((k, v){
          if(maxCount < v){
            _k = k;
            maxCount = v;
          }
        });
        return _k;
    }
  }
}


