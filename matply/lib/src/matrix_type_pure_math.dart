/// 矩阵相关的纯粹数学操作分支

part of 'core.dart';
/// 关于二维点的操作拓展
extension Point2D<T extends num> on math.Point<T> {
  // 二次线性变换
  math.Point<T> transform(Object mt) {
    if (mt is MatrixType){
      assert(mt.shape[0] == 2 && mt.shape[1] == 2);
      var x = mt.at(0, 0) * this.x.toDouble() + mt.at(0, 1) * this.y.toDouble();
      var y = mt.at(1, 0) * this.x.toDouble() + mt.at(1, 1) * this.y.toDouble();
      return math.Point(x as T, y as T);
    }else if (mt is List<List<num>>){
      assert(mt.length == 2 && mt[0].length == 2);
      var x = mt[0][0] * this.x.toDouble() + mt[0][1] * this.y.toDouble();
      var y = mt[1][0] * this.x.toDouble() + mt[1][1] * this.y.toDouble();
      return math.Point(x as T, y as T);
    }else
      throw UnsupportedError('Unsupported Type!');
  }

  // 旋转变换
  math.Point<T> rotate(num angle) => transform(
      [[math.cos(angle), -math.sin(angle)],
        [math.sin(angle), math.cos(angle)]]
  );
  // 缩放变换
  math.Point<T> scale(num sx, num sy) => transform([[sx, 0.0], [0.0, sy]]);
}

// 生成笛卡尔积
Iterable<math.Point<num>> getCartesianProduct(List<num> list1, List<num> list2) sync* {
  assert(list1.isNotEmpty && list2.isNotEmpty);
  for (num value1 in list1) {
    for (num value2 in list2) {
      yield math.Point<num>(value1, value2);
    }
  }
}

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

  MatrixType diff_center(double Function(double) condition){
    NativeCallable<Double Function(Double)> func = NativeCallable<
        Double Function(Double)>
        .isolateLocal(condition, exceptionalReturn: 0.0);
    var mt = matply__diffC(shape[0], shape[1], self.ref.data, func.nativeFunction);
    func.close();
    return MatrixType.__fromDataPointer(mt, shape);
  }

  List get_range({int dim = -1}){
    late final List list;
    var [row, column] = shape;
    Pointer<Pointer<Double>> dataOp = matply__get_range(row, column, self.ref.data, dim);
    switch (dim) {
      case 0:
        list = List.generate(row, (i) => dataOp[i].asTypedList(2).toList());
        matply__delete__data__(dataOp, row);
        return list;
      case 1:
        list = List.generate(column, (i) => dataOp[i].asTypedList(2).toList());
        matply__delete__data__(dataOp, column);
        return list;
      default:
        list = dataOp[0].asTypedList(2).toList();
        matply__delete__data__(dataOp, 1);
        return list;
    }
  }
}

