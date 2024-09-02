/// 矩阵相关的函数式条件处理分支

part of 'core.dart';

typedef Condition = bool Function(double); // 任意条件
typedef AnyCondition = bool Function(double, Object?); // 附加条件
typedef CplCondition = double Function(double); // 不满足所有条件时，补全的方案

extension Functools on MatrixType{
  MatrixType replace(Condition condition, {double number = .0}) {
    NativeCallable<Bool Function(Double)> func = NativeCallable<
        Bool Function(Double)>
        .isolateLocal(condition, exceptionalReturn: false);
    MatrixType mt = MatrixType.__fromDataPointer(matply__replace(
        shape[0], shape[1], self.ref.data, number, func.nativeFunction), shape);
    func.close();
    return mt;
  }

  void replace_no_returned(Condition condition, {double number = .0}) {
    NativeCallable<Bool Function(Double)> func = NativeCallable<
        Bool Function(Double)>
        .isolateLocal(condition, exceptionalReturn: false);
    matply__replaceNoReturned(
        shape[0], shape[1], self.ref.data, number, func.nativeFunction);
    func.close();
  }

  /// [condition] 是必须传入的条件函数，也同时添加另一个约束 [any]，但这时候 [obj] 不能为空。只操作满足条件的值
  /// 若不传入 [cpl] 参数，则默认返回满足条件的值到一个一维列表；否则，则按照cpl函数更新的值与未满足条件的值一起写入原来矩阵，返回一个矩阵对象
  Object where(Condition condition,
      {AnyCondition? any, Object? obj, CplCondition? cpl}) {
    final data = self.ref.data;
    double value;
    int row = shape[0],
        column = shape[1];
    if (any != null) {
      assert (obj != null);
      if (cpl != null) {
        Pointer<Pointer<Double>> newData = matply__allocateButNoNumbers(
            row, column);
        for (int r = 0; r < row; r++) {
          for (int c = 0; c < column; c ++) {
            value = data[r][c];
            newData[r][c] =
            (condition(value) && any(value, obj)) ? cpl(value) : value;
          }
        }
        return MatrixType.__fromDataPointer(newData, shape);
      } else {
        List<double> list = [];
        for (int r = 0; r < row; r++) {
          for (int c = 0; c < column; c ++) {
            value = data[r][c];
            if (condition(value) && any(value, obj))
              list.add(value);
          }
        }
        return list;
      }
    } else {
      if (cpl != null) {
        Pointer<Pointer<Double>> newData = matply__allocateButNoNumbers(
            row, column);
        for (int r = 0; r < row; r++) {
          for (int c = 0; c < column; c ++) {
            value = data[r][c];
            newData[r][c] = condition(value) ? cpl(value) : value;
          }
        }
        return MatrixType.__fromDataPointer(newData, shape);
      } else {
        List<double> list = [];
        for (int r = 0; r < row; r++) {
          for (int c = 0; c < column; c ++) {
            value = data[r][c];
            if (condition(value))
              list.add(value);
          }
        }
        return list;
      }
    }
  }

  bool all(Condition condition) {
    NativeCallable<Bool Function(Double)> func = NativeCallable<
        Bool Function(Double)>
        .isolateLocal(condition, exceptionalReturn: false);
    final bl = matply__all(
        shape[0], shape[1], self.ref.data, func.nativeFunction);
    func.close();
    return bl;
  }

  bool any(Condition condition) {
    NativeCallable<Bool Function(Double)> func = NativeCallable<
        Bool Function(Double)>
        .isolateLocal(condition, exceptionalReturn: false);
    final bl = matply__any(
        shape[0], shape[1], self.ref.data, func.nativeFunction);
    func.close();
    return bl;
  }

  Object counter(Condition condition, {int dim = -1}) {
    NativeCallable<Bool Function(Double)> func = NativeCallable<
        Bool Function(Double)>
        .isolateLocal(condition, exceptionalReturn: false);
    late Pointer<Int32> ct;
    switch (dim) {
      case 0:
        ct = matply__counter(
            shape[0], shape[1], self.ref.data, 0, func.nativeFunction);
        func.close();
        return ct.asTypedList(shape[0]).toList();
      case 1:
        ct = matply__counter(
            shape[0], shape[1], self.ref.data, 1, func.nativeFunction);
        func.close();
        return ct.asTypedList(shape[1]).toList();
      default:
        ct = matply__counter(
            shape[0], shape[1], self.ref.data, -1, func.nativeFunction);
        func.close();
        return ct.value;
    }
  }

  Object reduce(double Function(double, double) condition,
      {required double init, int dim = -1}) {
    NativeCallable<Double Function(Double, Double)> func = NativeCallable<
        Double Function(Double, Double)>
        .isolateLocal(condition, exceptionalReturn: double.nan);
    late Pointer<Double> ct;
    switch (dim) {
      case 0:
        ct = matply__reduce(
            shape[0], shape[1], self.ref.data, 0, func.nativeFunction, init);
        func.close();
        return ct.asTypedList(shape[0]);
      case 1:
        ct = matply__reduce(
            shape[0], shape[1], self.ref.data, 1, func.nativeFunction, init);
        func.close();
        return ct.asTypedList(shape[1]);
      default:
        ct = matply__reduce(
            shape[0], shape[1], self.ref.data, -1, func.nativeFunction, init);
        func.close();
        return ct.value;
    }
  }

  /// 抽象反射矩阵数据
  dynamic magic(
    dynamic Function(double) condition, {
    dynamic Function(dynamic condition_result)? reflect,  // 单体映射
    dynamic Function(dynamic reflect_all)? reflect_all, // 整体映射
    required dynamic init, // 处理单体值之前的初始方式
    required dynamic Function(dynamic, dynamic) cope_value, // 处理单体值的方式
    required dynamic Function(dynamic) returned,
    int dim = -1
  }){
    final data = self.ref.data;
    dynamic value;
    dynamic current = init;
    switch (dim){
      case 0:
        List<dynamic> list = [];
        for (int r = 0; r < shape[0]; r++) {
          for (int c = 0; c < shape[1]; c++) {
            value = reflect == null
                ? condition(data[r][c])
                : reflect(condition(data[r][c])); // 不这么细致的将空判断分开了
            current = cope_value(current, value);
          }
          list.add(reflect_all == null ? current : reflect_all(current));
        }
        return returned(list);
      case 1:
        List<dynamic> list = [];
        for (int c = 0; c < shape[1]; c ++) {
          for (int r = 0; r < shape[0]; r++) {
            value = reflect == null
                ? condition(data[r][c])
                : reflect(condition(data[r][c]));
            current = cope_value(current, value);
          }
          list.add(reflect_all == null ? current : reflect_all(current));
        }
        return returned(list);
      default:
        for (int r = 0; r < shape[0]; r++) {
          for (int c = 0; c < shape[1]; c++) {
            value = reflect == null
                ? condition(data[r][c])
                : reflect(condition(data[r][c]));
            current = cope_value(current, value);
          }
        }
        return returned(reflect_all == null? current : reflect_all(current));
    }
  }

  MatrixType clip_reverse(double Function(double) condition, {required double lb, required double ub}){
    assert(lb <= ub);
    NativeCallable<Double Function(Double)> func = NativeCallable<Double Function(Double)>
        .isolateLocal(condition, exceptionalReturn: double.nan);
    MatrixType mt = MatrixType.__fromDataPointer(
        matply__clip_reverse(shape[0], shape[1], self.ref.data, lb, ub, func.nativeFunction),
        shape
    );
    func.close();
    return mt;
  }

  void clip_reverse_no_returned(double Function(double) condition, {required double lb, required double ub}){
    assert(lb <= ub);
    NativeCallable<Double Function(Double)> func = NativeCallable<Double Function(Double)>
        .isolateLocal(condition, exceptionalReturn: double.nan);
    matply__clip_reverseNoReturned(shape[0], shape[1], self.ref.data, lb, ub, func.nativeFunction);
    func.close();
  }

  MatrixType customize(double Function(double) condition){
    NativeCallable<Double Function(Double)> func = NativeCallable<Double Function(Double)>
        .isolateLocal(condition, exceptionalReturn: double.nan);
    MatrixType mt = MatrixType.__fromDataPointer(
        matply__customize(shape[0], shape[1], self.ref.data, func.nativeFunction),
        shape
    );
    func.close();
    return mt;
  }

  List<List<int>> findall(bool Function(double) condition, {int? prediction}){
    NativeCallable<Bool Function(Double)> func = NativeCallable<Bool Function(Double)>
        .isolateLocal(condition, exceptionalReturn: false);
    Pointer<Pointer<Int32>> ls = matply__findIndexs(
        shape[0], shape[1], self.ref.data, func.nativeFunction, prediction ?? shape[1] ~/ 4);
    late Pointer<Int32> lr;
    List<List<int>> list = [];
    for (int r = 0;r < shape[0];r++){
      lr = ls[r];
      list.add(lr.asTypedList(1 + lr[0]).toList()..removeAt(0));
    }
    func.close();
    matply__freeppvoid(ls.cast<Pointer<Void>>(), shape[0]);
    return list;
  }
}