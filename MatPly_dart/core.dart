import 'dart:ffi';
import 'package:ffi/ffi.dart';

import 'errors.dart';
import 'matply_api.dart';

final class Alert{
  final String info;
  const Alert(this.info);
}

class MatrixType{
  late Pointer<Matrix> self;
  late List shape;

  void _setSpecialAttributes({
    bool identityMatrix = false,
    bool principalDiagonalMatrix = false,
    bool subDiagonalMatrix = false,
    bool upperTriangularMatrix = false,
    bool lowerTriangularMatrix = false,
    bool singularMatrix = false,
  }) {
    this.self.ref.spc.ref.identityMatrix = identityMatrix;
    this.self.ref.spc.ref.upperTriangularMatrix = upperTriangularMatrix;
    this.self.ref.spc.ref.lowerTriangularMatrix = lowerTriangularMatrix;
    this.self.ref.spc.ref.singularMatrix = singularMatrix;
    this.self.ref.spc.ref.subDiagonalMatrix = subDiagonalMatrix;
    this.self.ref.spc.ref.principalDiagonalMatrix = principalDiagonalMatrix;
  }

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
    this.self = matply__new__(this.shape[0], this.shape[1]);  // 已经对data和spc分配了内存
    for (int r = 0;r < this.shape[0];r++){
      for (int c = 0;c < this.shape[1];c ++){
        this.self.ref.data[r][c] = data[r][c];
      }
    }

    _setSpecialAttributes(
      identityMatrix: identityMatrix,
      principalDiagonalMatrix: principalDiagonalMatrix,
      subDiagonalMatrix: subDiagonalMatrix,
      upperTriangularMatrix: upperTriangularMatrix,
      lowerTriangularMatrix: lowerTriangularMatrix,
      singularMatrix: singularMatrix,
    );
  }

  // 全number的矩阵
  MatrixType.filled(
      {
        required double number,
        required int row,
        required int column,
        bool identityMatrix = false,
        bool principalDiagonalMatrix = false,
        bool subDiagonalMatrix = false,
        bool upperTriangularMatrix = false,
        bool lowerTriangularMatrix = false,
        bool singularMatrix  = false
  }) {
    shape = [row, column];
    this.self = matply__filled(row, column, number);

    _setSpecialAttributes(
      identityMatrix: identityMatrix,
      principalDiagonalMatrix: principalDiagonalMatrix,
      subDiagonalMatrix: subDiagonalMatrix,
      upperTriangularMatrix: upperTriangularMatrix,
      lowerTriangularMatrix: lowerTriangularMatrix,
      singularMatrix: singularMatrix,
    );
  }

  // 全1矩阵
  MatrixType.ones({
      required int row,
      required int column,
      bool identityMatrix = false,
      bool principalDiagonalMatrix = false,
      bool subDiagonalMatrix = false,
      bool upperTriangularMatrix = false,
      bool lowerTriangularMatrix = false,
      bool singularMatrix  = false
    }) {
    shape = [row, column];
    this.self = matply__ones(row, column);

    _setSpecialAttributes(
      identityMatrix: identityMatrix,
      principalDiagonalMatrix: principalDiagonalMatrix,
      subDiagonalMatrix: subDiagonalMatrix,
      upperTriangularMatrix: upperTriangularMatrix,
      lowerTriangularMatrix: lowerTriangularMatrix,
      singularMatrix: singularMatrix,
    );
  }

  // 全0矩阵
  MatrixType.zeros({
    required int row,
    required int column,
    bool identityMatrix = false,
    bool principalDiagonalMatrix = false,
    bool subDiagonalMatrix = false,
    bool upperTriangularMatrix = false,
    bool lowerTriangularMatrix = false,
    bool singularMatrix  = false
  }){
    shape = [row, column];
    this.self = matply__zeros(row, column);

    _setSpecialAttributes(
      identityMatrix: identityMatrix,
      principalDiagonalMatrix: principalDiagonalMatrix,
      subDiagonalMatrix: subDiagonalMatrix,
      upperTriangularMatrix: upperTriangularMatrix,
      lowerTriangularMatrix: lowerTriangularMatrix,
      singularMatrix: singularMatrix,
    );
  }

  // 连续创建
  MatrixType.arrange({
    required double? start,
    required int row,
    required int column
  }){
    shape = [row, column];
    start = start ?? 0.0;
    this.self = matply__arrange(start, row, column);
  }

  // 等差创建
  MatrixType.linspace({
    required double start,
    required double end,
    required int row,
    required int column,
    bool keep = true
  }) : assert(start < end), shape = [row, column], this.self = matply__linspace(start, end, row, column, keep);

  // n阶单位矩阵
  MatrixType.E({required int n}){
    self = matply__E(n);
    shape = [n, n];
    this.identityMatrix = true;
  }

  // 根据已经建立好的Matrix指针初始化
  MatrixType.__fromPointer(this.self, this.shape);

  // 深拷贝矩阵
  factory MatrixType.deepCopy(MatrixType other) => MatrixType.__fromPointer(matply__deepcopy(other.self), other.shape);

  get identityMatrix => this.self.ref.spc.ref.identityMatrix;
  set identityMatrix(value) => this.self.ref.spc.ref.identityMatrix = value;

  get principalDiagonalMatrix => this.self.ref.spc.ref.principalDiagonalMatrix;
  set principalDiagonalMatrix(value) => this.self.ref.spc.ref.principalDiagonalMatrix = value;

  get upperTriangularMatrix => this.self.ref.spc.ref.upperTriangularMatrix;
  set upperTriangularMatrix(value) => this.self.ref.spc.ref.upperTriangularMatrix = value;

  get subDiagonalMatrix => this.self.ref.spc.ref.subDiagonalMatrix;
  set subDiagonalMatrix(value) => this.self.ref.spc.ref.subDiagonalMatrix = value;

  get lowerTriangularMatrix => this.self.ref.spc.ref.lowerTriangularMatrix;
  set lowerTriangularMatrix(value) => this.self.ref.spc.ref.lowerTriangularMatrix = value;

  get singularMatrix => this.self.ref.spc.ref.singularMatrix;
  set singularMatrix(value) => this.self.ref.spc.ref.singularMatrix = value;

  int get size => shape[0] * shape[1];
  bool get isSquare => shape[0] == shape[1];
  MatrixType get T_ => transpose();
  double get trace => matply__trace(self);
  double get det => matply__det(self);
  MatrixType? get inv {
    double value = this.det;
    if (value == 0)
      throw UnsupportedError('The matrix is not invertible.');
    else
      return MatrixType.__fromPointer(matply__inverse(self, det), shape);
  }
  MatrixType get adj => MatrixType.__fromPointer(matply__adjugate(self), shape);


  void visible() {
    matply__VisibleMatrix(this.self);
  }

  void visible_spc(){
    matply__VisibleMatrixSpc(this.self);
  }

  @Alert('Returning a Pointer? or a List? depends on the type you give in.'
      'However in Dart, Using the Pointer type is not a good choice')
  Object row_<T>(int row) {
    if (row < 0 || row >= shape[0]) {
      throw row_outRange;
    } else {
      if (T == Pointer) {
        return matply__row_(row, self);
      } else if (T == List || T == dynamic) {
        return matply__row_(row, self).asTypedList(shape[1]);
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
        return matply__column_(column, self).asTypedList(shape[1]);
      } else {
        throw UnsupportedError('T must be Pointer or List');
      }
    }
  }

  double? at(int row, int column){
    if (column < 0 || column >= shape[1] || row < 0 || row >= shape[0])
      throw random_outRange;
    else{
      return matply__at(row, column, self);
    }
  }
  
  @Alert('Just return a List?, do not support pointer type.')
  List? operator [](int row) {
    if (row < 0 || row >= shape[0]) {
      throw row_outRange;
    } else {
      return matply__row_(row, self).asTypedList(shape[1]);
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

  MatrixType operator +(Object other) {
    if (other is num) {
      return this.add(number: other.toDouble());
    } else if (other is MatrixType) {
      return this.add(other: other);
    } else {
      throw UnsupportedError('Unsupported operand type for +: ${other.runtimeType}');
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

  MatrixType operator -(Object other) {
    if (other is num) {
      return this.minus(number: other.toDouble());
    } else if (other is MatrixType) {
      return this.minus(other: other);
    } else {
      throw UnsupportedError('Unsupported operand type for -: ${other.runtimeType}');
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
      return MatrixType.__fromPointer(matply__matmul(self, other.self), [shape[0], other.shape[1]]);
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

  MatrixType operator * (Object other) {
    if (other is num) {
      return this.multiply(number: other.toDouble());
    } else if (other is MatrixType) {
      return this.multiply(other: other);
    } else {
      throw UnsupportedError('Unsupported operand type for *: ${other.runtimeType}');
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

  MatrixType operator / (double number) => divide(number);

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

}

