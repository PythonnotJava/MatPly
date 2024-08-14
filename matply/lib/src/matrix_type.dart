part of 'core.dart';

class MatrixType {
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

  // 根据步长建立[new from 1.0.5]
  MatrixType.range({
    required double start,
    double step = 1.0,
    required int row,
    required int column
  }):assert(row > 0 && column > 0 ){
    this.self = matply__init__point__data__(
        row, column, matply__range(start, step, row, column), nullptr
    );
  }

  MatrixType.E_like({required int row, required int column}) : assert(row > 0 && column > 0){
    this.self = matply__init__point__data__(
      row, column, matply__E_like(row, column), nullptr
    );
  }

  // 生成对角矩阵
  MatrixType.Diag({
    required int n,
    required double start,
    required double end,
    bool sub = false,
    int? seed
  }): assert(n > 0 && start < end){
    this.self = matply__init__point__data__(
      n, n, matply__diagonal(n, n, start, end, sub, seed ?? 0, seed != null), nullptr
    );
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

  /// Overloading Operators
  @Since('1.0.6')
  Object operator [](Object indice){
    if (indice is int){
      if (indice >= 0 && indice < shape[0])
        return matply__row_(indice, shape[1], self.ref.data).asTypedList(shape[1]).toList();
      else
        throw row_outRange;
    }else if (indice is (int, )){
      return slice(from: indice.$1, to: null);
    }else if (indice is (int, int?)){
      return slice(from: indice.$1, to: indice.$2);
    }else if (indice is List && indice.length == 2){
      return at(indice[0], indice[1]);
    }else
      throw UnsupportedError('Unsupported indexing method.');
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

  MatrixType operator -() => this * -1;

  MatrixType operator / (num number) => divide(number.toDouble());

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

  bool hasSameShape(MatrixType other){ return other.shape[0] == shape[0] && shape[1] == other.shape[1];}

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

  MatrixType resize({required int row, required int column, double number = .0, bool horizontal = true}){
    assert(row > 0 && column > 0);
    return horizontal ?
    MatrixType.__fromDataPointer(matply__resizeR(row, column, self.ref.data, shape[0], shape[1], number), [row, column]) :
    MatrixType.__fromDataPointer(matply__resizeC(row, column, self.ref.data, shape[0], shape[1], number), [row, column]);
  }

  void resize_no_returned({required int row, required int column, double number = .0, bool horizontal = true}){
    assert(row > 0 && column > 0);
    Pointer<Pointer<Double>> data = horizontal
        ? matply__resizeR(row, column, self.ref.data, shape[0], shape[1], number)
        : matply__resizeC(row, column, self.ref.data, shape[0], shape[1], number);
    matply__delete__data__(self.ref.data, shape[0]);
    self.ref.data = data;
    self.ref.column = column;
    self.ref.row = row;
  }

  void reshape_no_returned({required int row, required int column}) {
    if (row * column != size)
      throw size_changed;
    else{
      if (row == shape[0])
        return;
      assert(row > 0 && column > 0);
      Pointer<Pointer<Double>> data = matply__reshape(row, column, self.ref.data, shape[1]);
      matply__delete__data__(self.ref.data, shape[0]);
      self.ref.data = data;
      self.ref.column = column;
      self.ref.row = row;
    }
  }

  void sort_no_returned({
    bool reverse = false,
    double mask_nan = 0.0,
    int dim = -1
  }) => matply__sortNoReturned(shape[0], shape[1], self.ref.data, reverse, dim, mask_nan);

  MatrixType sort({
    bool reverse = false,
    double mask_nan = 0.0,
    int dim = -1
  }) => MatrixType.__fromDataPointer(matply__sort(shape[0], shape[1], self.ref.data, reverse, dim, mask_nan), shape);

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
      return List.generate(shape[0], (i) => matply__row_(shape[0], shape[1], self.ref.data).asTypedList(shape[1])).toList();
    } else if (T == int) {
      return List.generate(shape[0], (i) => (this[i] as List).map<int>((e) => e.toInt()).toList());
    } else if (T == String) {
      return List.generate(shape[0], (i) => (this[i] as List).map<String>((e) => e.toString()).toList());
    }else if (T == bool){
      return List.generate(shape[0], (i) => (this[i] as List).map<bool>((e) => (e != 0) ).toList());
    } else {
      throw UnsupportedError('Unsupported type.');
    }
  }

  MatrixType flatten({int mode = 0}) => MatrixType.__fromDataPointer(
      matply__oneTotwoArray(matply__flatten(shape[0], shape[1], self.ref.data, mode), 1, shape[0] * shape[1]),
      [1, shape[0] * shape[1]]
  );

  List<double> flatten_list({int mode = 0}) =>
      matply__flatten(shape[0], shape[1], self.ref.data, mode).asTypedList(shape[0] * shape[1]).toList();
  
  MatrixType slice({required int from, int? to, bool horizontal = true}){
    final int row = shape[0], column = shape[1];
    if (to != null){
      assert(from <= to);
      if (horizontal){
        if (from >= 0 && to < row)
          return MatrixType.__fromDataPointer(matply__sliceR(shape[1], self.ref.data, from, to), [to - from + 1, column]);
        else
          throw row_outRange;
      }else{
        if (from >= 0 && to < column)
          return MatrixType.__fromDataPointer(matply__sliceC(shape[0], self.ref.data, from, to), [row, to - from + 1]);
        else
          throw column_outRange;
      }
    }else{
      if (horizontal){
        if (from >= 0 && from < row)
          return MatrixType.__fromDataPointer(matply__sliceR(shape[1], self.ref.data, from, row - 1), [row - from, column]);
        else
          throw row_outRange;
      }else{
        if (from >= 0 && from < column)
          return MatrixType.__fromDataPointer(matply__sliceC(shape[0], self.ref.data, from, column - 1), [row, column - from]);
        else
          throw column_outRange;
      }
    }
  }

  MatrixType clip({required double lb, required double ub}){
    assert(lb <= ub);
    return MatrixType.__fromDataPointer(matply__clip(shape[0], shape[1], self.ref.data, lb, ub), shape);
  }

  void clip_no_returned({required double lb, required double ub}){
    assert(lb <= ub);
    matply__clipNoReturned(shape[0], shape[1], self.ref.data, lb, ub);
  }

  MatrixType rotate({required int angle}){  // 正数代表顺时针，负数逆时针
    if (angle % 90 != 0)
      throw UnsupportedError('The angle must be an integer multiple of 90.');
    else{
      int mode = angle ~/ 90 % 4;  /// The value of [mode] just in [-3, -2, -1, 0, 1, 2, 3]
      List<int> _shape = mode % 2 == 0 ? shape : [shape[1], shape[0]];
      return MatrixType.__fromDataPointer(matply__rotate(shape[0], shape[1], self.ref.data, mode), _shape);
    }
  }

  MatrixType mirror({int mode = 0}) => MatrixType.__fromDataPointer(matply__mirror(shape[0], shape[1], self.ref.data, mode), shape);

  void fill_diagonal({double number = 0.0}) => matply__fill_diagonal(shape[0], shape[1], self.ref.data, number);
}

