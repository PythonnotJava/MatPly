/// 矩阵相关的线性代数分支

part of 'core.dart';

extension Linalg on MatrixType{
  /// setter && method
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
      return MatrixType.__fromDataPointer(matply__inverse(shape[0], shape[1], self.ref.data, value), shape);
  }
  MatrixType get adj{
    if (isSquare)
      return MatrixType.__fromDataPointer(matply__adjugate(shape[0], shape[1], self.ref.data), shape);
    else
      throw not_a_square;
  }
  int get rank => matply__rank(shape[0], shape[1], self.ref.data);

  /// method
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

  MatrixType transpose() => MatrixType.__fromDataPointer(matply__transpose(shape[0], shape[1], self.ref.data), [shape[1], shape[0]]);

  MatrixType matmul(MatrixType other){
    if (shape[1] != other.shape[0])
      throw matmul_unsupport;
    else
      return MatrixType.__fromDataPointer(
          matply__matmul(shape[0], shape[1], self.ref.data, other.self.ref.data, other.shape[1]), [shape[0], other.shape[1]]
      );
  }

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

  MatrixType divide(double number){
    if (number != 0)
      return MatrixType.__fromDataPointer(matply__divide(shape[0], shape[1], self.ref.data, number), shape);
    else
      throw UnsupportedError('Division by zero');
  }

  MatrixType kronecker(MatrixType other) => MatrixType.__fromDataPointer(
      matply__kronecker(shape[0], shape[1], self.ref.data, other.shape[0], other.shape[1], other.self.ref.data),
      [shape[0] * other.shape[0], shape[1] * other.shape[1]]
  );

  void divide_no_returned(double number) {
    if (number != 0)
      matply__divideNoReturned(shape[0], shape[1], self.ref.data, number);
    else
      throw UnsupportedError('Division by zero');
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

  MatrixType rref() => MatrixType.__fromDataPointer(matply__rref(shape[0], shape[1], self.ref.data), shape);

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
          Pointer<Double> op;
          Object target;
          switch (dim){
            case 0:
              op = matply__norm_zero(shape[0], shape[1], self.ref.data, 0);
              target = op.asTypedList(shape[0]).toList();
              break;
            case 1:
              op = matply__norm_zero(shape[0], shape[1], self.ref.data, 1);
              target = op.asTypedList(shape[1]).toList();
              break;
            default:
              op = matply__norm_zero(shape[0], shape[1], self.ref.data, -1);
              target = op.value.toInt();
              break;
          }
          freeOp(op);
          return target;
        case 1:
          return matply__norm_one(shape[0], shape[1], self.ref.data);
        default:
          Pointer<Double> op;
          Object target;
          switch (dim){
            case 0:
              op = matply__norm(shape[0], shape[1], self.ref.data, n, 0);
              target = op.asTypedList(shape[0]).toList();
              break;
            case 1:
              op = matply__norm(shape[0], shape[1], self.ref.data, n, 1);
              target = op.asTypedList(shape[1]).toList();
              break;
            default:
              op = matply__norm(shape[0], shape[1], self.ref.data, n, -1);
              target = op.value;
              break;
          }
          freeOp(op);
          return target;
      }
    }
  }

  Object norm2({int dim = -1}) => norm(dim: dim, n: 2);
  double norm_inf() => matply__norm_inf(shape[0], shape[1], self.ref.data);
  double norm_negainf() => matply__norm_negainf(shape[0], shape[1], self.ref.data);
  double norm_one() => matply__norm_one(shape[0], shape[1], self.ref.data);
  Object norm_zero({int dim = -1}) => norm(n: 0, dim: dim);

  MatrixType normalization({required int mode, int dim = -1}){
    switch(mode){
      case 0:
        return MatrixType.__fromDataPointer(matply__normalization1(shape[0], shape[1], self.ref.data, dim), shape);
      case 1:
        return MatrixType.__fromDataPointer(matply__normalization2(shape[0], shape[1], self.ref.data, dim), shape);
      default:
        return MatrixType.__fromDataPointer(matply__normalization3(shape[0], shape[1], self.ref.data, dim), shape);
    }
  }

  List<MatrixType> qr(){
    MultiDatas2 lm = matply__qr(shape[0], shape[1], self.ref.data);
    return [
      MatrixType.__fromDataPointer(lm.data1, shape),
      MatrixType.__fromDataPointer(lm.data2, [shape[1], shape[1]])
    ];
  }
}