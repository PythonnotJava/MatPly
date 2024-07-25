/// 矩阵相关的纯粹数学操作分支

part of 'core.dart';

extension PureMath on MatrixType{
  /// setter && getter
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

  /// method
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
    double mask_nan = 0.0,
    double mask_inf = 0.0,
    double mask_neginf = 0.0,
    int dim = -1
  }) => MatrixType.__fromDataPointer(matply__softmax(shape[0], shape[1], self.ref.data, dim, mask_nan, mask_nan, mask_neginf), shape);

  Object argmax({int dim = -1}){
    switch(dim){
      case 0:
        return matply__argmax(shape[0], shape[1], self.ref.data, 0).asTypedList(shape[0]).toList();
      case 1:
        return matply__argmax(shape[0], shape[1], self.ref.data, 1).asTypedList(shape[1]).toList();
      default:
        return matply__argmax(shape[0], shape[1], self.ref.data, -1).value;
    }
  }

  Object argmin({int dim = -1}){
    switch(dim){
      case 0:
        return matply__argmin(shape[0], shape[1], self.ref.data, 0).asTypedList(shape[0]).toList();
      case 1:
        return matply__argmin(shape[0], shape[1], self.ref.data, 1).asTypedList(shape[1]).toList();
      default:
        return matply__argmin(shape[0], shape[1], self.ref.data, -1).value;
    }
  }


}

