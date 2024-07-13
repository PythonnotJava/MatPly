part of 'core.dart';

// 对一个已经申请好空间的二维数组指针填充数据，数据源为一维列表
void __putOneinTwoArray(Pointer<Pointer<Double>> data, List<double> list, int row, int column){
  int counter = 0;
  for (int r = 0;r < row;r++){
    for (int c = 0;c < column;c ++){
      data[r][c] = list[counter++];
    }
  }
}

/// 列表拓展，转换为矩阵
extension ListExtension on List<double>{
  MatrixType reshape({required int row, required int column}){
    assert(row > 0 && column > 0);
    if (this.length != row * column)
      throw different_shape;
    else{
      Pointer<Matrix> self = matply__new__(row, column);
      __putOneinTwoArray(self.ref.data, this, row, column);
      return MatrixType.__fromPointer(self, [row, column]);
    }
  }

  MatrixType resize({required int row, required int column, double number = .0}){
    assert(row > 0 && column > 0);
    Pointer<Matrix> self = matply__new__(1, this.length);
    return MatrixType.__fromPointer(matply__resizeR(self, row, column, number), [row, column]);
  }

  MatrixType power({required int row, required int column, required double number}){
    assert(row > 0 && column > 0);
    Pointer<Matrix> self = matply__new__(row, column);
    __putOneinTwoArray(self.ref.data, this, row, column);
    return MatrixType.__fromPointer(matply_mathBasement2(self.ref.data, 0, number, row, column, false).cast<Matrix>(), [row, column]);
  }

}