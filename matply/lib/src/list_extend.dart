part of 'core.dart';

/// extension for List.Test from V1.0.2

// 数据源为一维列表
extension OneDimListExtend on List<double> {
  Pointer<Double> getOnePointer({bool methed_is_malloc = true}){
    Pointer<Double> op = methed_is_malloc ? malloc<Double>(length) : calloc<Double>(length);
    for (int i = 0;i < length;i++)
      op[i] = this[i];
    return op;
  }
  MatrixType reshape({required int row, required int column}) {
    assert(row > 0 && column > 0);
    if (length == column * row) {
      var op = getOnePointer();
      MatrixType mt = MatrixType.__fromDataPointer(matply__oneTotwoArray(op, row, column), [row, column]);
      malloc.free(op);
      return mt;
    }else
      throw different_shape;
  }

  // 仅提供横向重塑
  MatrixType resize({required int row, required int column, double number = .0}){
    assert(row > 0 && column > 0);
    var op = getOnePointer();
    var data = matply__oneTotwoArray(op, 1, length);
    matply__resizeCNoReturned(row, column, data, 1, length, number);
    MatrixType mt = MatrixType.__fromDataPointer(data, [1, length]);
    malloc.free(op);
    return mt;
  }
}

// 数据源为二维列表
extension TwoDimListExtend on List<List<double>>{
  int get row => this.length;
  int get column => this[0].length;
  List<int> get shape => [row, column];

  Pointer<Pointer<Double>> getTwoPointer(){
    var tp = malloc<Pointer<Double>>(row);
    for (int r = 0; r < row; r++) {
      tp[r] = malloc<Double>(column);
      for (int j = 0; j < column; j++) {
        tp[r][j] = this[r][j];
      }
    }
    return tp;
  }

  MatrixType toMatrixType() => MatrixType.__fromDataPointer(getTwoPointer(), this.shape);

  MatrixType matmul({List<List<double>>? list, MatrixType? mt}){
    assert(list != null || mt != null);
    if (list != null){
      if(column != list.row)
        throw matmul_unsupport;
      var tp1 = getTwoPointer();
      var tp2 = list.getTwoPointer();
      MatrixType _mt = MatrixType.__fromDataPointer(
          matply__matmul(row, column, tp1, tp2),
          [row, list.column]
      );
      matply__delete__data__(tp1, row);
      matply__delete__data__(tp2, column);
      return _mt;
    }else {
      if (column != mt!.shape[0])
        throw matmul_unsupport;
      var tp = getTwoPointer();
      MatrixType _mt = MatrixType.__fromDataPointer(
          matply__matmul(row, column, tp, mt.self.ref.data),
          [row, mt.shape[1]]
      );
      matply__delete__data__(tp, row);
      return _mt;
    }
  }

  MatrixType sort({bool reverse = false, int dim = -1, double mask_nan = 0.0}){
    var data = getTwoPointer();
    matply__sortNoReturned(row, column, data, reverse, dim, mask_nan);
    return MatrixType.__fromDataPointer(data, shape);
  }
}