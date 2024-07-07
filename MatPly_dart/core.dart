import 'dart:ffi';
import 'package:ffi/ffi.dart';

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
    bool subdiagonalMatrix = false,
    bool upperTriangularMatrix = false,
    bool lowerTriangularMatrix = false,
    bool singularMatrix = false,
  }) {
    this.self.ref.spc = malloc<SpecialAttributes>();
    this.self.ref.spc.ref.identityMatrix = identityMatrix;
    this.self.ref.spc.ref.upperTriangularMatrix = upperTriangularMatrix;
    this.self.ref.spc.ref.lowerTriangularMatrix = lowerTriangularMatrix;
    this.self.ref.spc.ref.singularMatrix = singularMatrix;
    this.self.ref.spc.ref.subdiagonalMatrix = subdiagonalMatrix;
    this.self.ref.spc.ref.principalDiagonalMatrix = principalDiagonalMatrix;
  }

  // 一般构造
  MatrixType(
      List<List<double>> data, {
        bool identityMatrix = false,
        bool principalDiagonalMatrix = false,
        bool subdiagonalMatrix = false,
        bool upperTriangularMatrix = false,
        bool lowerTriangularMatrix = false,
        bool singularMatrix  = false
      }){
    this.shape = [data.length, data[0].length];
    this.self = matply__new__(this.shape[0], this.shape[1]);
    this.self.ref.data = toMatrixPPointerData(data, this.shape[0], this.shape[1]);

    _setSpecialAttributes(
      identityMatrix: identityMatrix,
      principalDiagonalMatrix: principalDiagonalMatrix,
      subdiagonalMatrix: subdiagonalMatrix,
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
        bool subdiagonalMatrix = false,
        bool upperTriangularMatrix = false,
        bool lowerTriangularMatrix = false,
        bool singularMatrix  = false
  }) {
    shape = [row, column];
    this.self = matply__filled(row, column, number);

    _setSpecialAttributes(
      identityMatrix: identityMatrix,
      principalDiagonalMatrix: principalDiagonalMatrix,
      subdiagonalMatrix: subdiagonalMatrix,
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
      bool subdiagonalMatrix = false,
      bool upperTriangularMatrix = false,
      bool lowerTriangularMatrix = false,
      bool singularMatrix  = false
    }) {
    shape = [row, column];
    this.self = matply__ones(row, column);

    _setSpecialAttributes(
      identityMatrix: identityMatrix,
      principalDiagonalMatrix: principalDiagonalMatrix,
      subdiagonalMatrix: subdiagonalMatrix,
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
    bool subdiagonalMatrix = false,
    bool upperTriangularMatrix = false,
    bool lowerTriangularMatrix = false,
    bool singularMatrix  = false
  }){
    shape = [row, column];
    this.self = matply__zeros(row, column);

    _setSpecialAttributes(
      identityMatrix: identityMatrix,
      principalDiagonalMatrix: principalDiagonalMatrix,
      subdiagonalMatrix: subdiagonalMatrix,
      upperTriangularMatrix: upperTriangularMatrix,
      lowerTriangularMatrix: lowerTriangularMatrix,
      singularMatrix: singularMatrix,
    );
  }

  // 深拷贝矩阵
  factory MatrixType.deepCopy(MatrixType other) {
    List<List<double>> newData = List.generate(
      other.shape[0],
          (row) => List.generate(
        other.shape[1],
            (col) => other.at(row, col)!,
      ),
    );
    return MatrixType(
      newData,
      identityMatrix: other.identityMatrix,
      principalDiagonalMatrix: other.principalDiagonalMatrix,
      subdiagonalMatrix: other.subdiagonalMatrix,
      upperTriangularMatrix: other.upperTriangularMatrix,
      lowerTriangularMatrix: other.lowerTriangularMatrix,
      singularMatrix: other.singularMatrix,
    );
  }

  get identityMatrix => this.self.ref.spc.ref.identityMatrix;
  set identityMatrix(value) => this.self.ref.spc.ref.identityMatrix = value;

  get principalDiagonalMatrix => this.self.ref.spc.ref.principalDiagonalMatrix;
  set principalDiagonalMatrix(value) => this.self.ref.spc.ref.principalDiagonalMatrix = value;

  get upperTriangularMatrix => this.self.ref.spc.ref.upperTriangularMatrix;
  set upperTriangularMatrix(value) => this.self.ref.spc.ref.upperTriangularMatrix = value;

  get subdiagonalMatrix => this.self.ref.spc.ref.subdiagonalMatrix;
  set subdiagonalMatrix(value) => this.self.ref.spc.ref.subdiagonalMatrix = value;

  get lowerTriangularMatrix => this.self.ref.spc.ref.lowerTriangularMatrix;
  set lowerTriangularMatrix(value) => this.self.ref.spc.ref.lowerTriangularMatrix = value;

  get singularMatrix => this.self.ref.spc.ref.singularMatrix;
  set singularMatrix(value) => this.self.ref.spc.ref.singularMatrix = value;

  get size => shape[0] * shape[1];
  get isSquare => shape[0] == shape[1];

  void visible() {
    matply__VisibleMatrix(this.self);
  }

  void visible_spc(){
    matply__VisibleMatrixSpc(this.self);
  }

  Object row_<T>(int row) {
    if (row < 0 || row >= shape[0]) {
      throw RangeError('The row is out of range');
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

  Object column_<T>(int column) {
    if (column < 0 || column >= shape[1]) {
      throw RangeError('The column is out of range');
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
      throw RangeError('You are out of range');
    else{
      return matply__at(row, column, self);
    }
  }
  
  @Alert('Just return a List?, do not support pointer type.')
  List? operator [](int row) {
    if (row < 0 || row >= shape[0]) {
      throw RangeError('The row is out of range');
    } else {
      return matply__row_(row, self).asTypedList(shape[1]);
    }
  }

}

