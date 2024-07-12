part of 'core.dart';

/// 列表拓展，转换为double为主要类型的矩阵
extension ListExtension on List<num>{
  MatrixType reshape({required int row, required int column}){
    if (this.length != row * column)
      throw different_shape;
    else
      return MatrixType.__fromPointer;
  }
}