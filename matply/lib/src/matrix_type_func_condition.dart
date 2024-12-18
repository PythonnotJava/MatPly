/// 矩阵相关的函数式条件处理分支
part of 'core.dart';

extension Functools on MatrixType{
  MatrixType replace(bool Function(double) condition, {double number = 0.0}) {
    NativeCallable<Bool Function(Double)> func = NativeCallable<
        Bool Function(Double)>
        .isolateLocal(condition, exceptionalReturn: false);
    MatrixType mt = MatrixType.__fromDataPointer(matply__replace(
        shape[0], shape[1], self.ref.data, number, func.nativeFunction), shape);
    func.close();
    return mt;
  }

  Future<MatrixType> replace_async(
    bool Function(double) condition, {
    double number = 0.0
  }) async {
    var [row, column] = shape;
    async_model_showm(row * column, 'replace_async');

    final data = matply__allocateButNoNumbers(row, column);
    final dataSelf = self.ref.data;
    double v;
    List<Future<void>> futures = List.generate(row, (r) async {
      for (int c = 0;c < column;c++){
        v = dataSelf[r][c];
        data[r][c] = condition(v)? number: v;
      }
    });
    await Future.wait(futures);
    return MatrixType.__fromDataPointer(data, shape);
  }

  void replace_no_returned(bool Function(double) condition, {double number = 0.0}) {
    NativeCallable<Bool Function(Double)> func = NativeCallable<
        Bool Function(Double)>
        .isolateLocal(condition, exceptionalReturn: false);
    matply__replaceNoReturned(
        shape[0], shape[1], self.ref.data, number, func.nativeFunction);
    func.close();
  }

  Future<void> replace_no_returned_async(
      bool Function(double) condition, {
      double number = 0.0
  }) async {
    var [row, column] = shape;
    async_model_showm(row * column, 'replace_no_returned_async');

    final data = self.ref.data;
    List<Future<void>> futures = List.generate(row, (r) async {
      for (int c = 0; c < column; c++) {
        if (condition(data[r][c])) {
          data[r][c] = number;
        }
      }
    });
    await Future.wait(futures);
  }

  /// [condition] 是必须传入的条件函数，也同时添加另一个约束 [any]，但这时候 [obj] 不能为空。只操作满足条件的值
  /// 若不传入 [cpl] 参数，则默认返回满足条件的值到一个一维列表；否则，则按照cpl函数更新的值与未满足条件的值一起写入原来矩阵，返回一个矩阵对象
  Object where(
    bool Function(double) condition, {
    bool Function(double, Object?)? any,
    Object? obj,
    double Function(double)? cpl
  }) {
    final data = self.ref.data;
    double value;
    var [row, column] = shape;
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

  Future<Object> where_async(
      bool Function(double) condition, {
      bool Function(double, Object?)? any,
      Object? obj,
      double Function(double)? cpl,
  }) async {
    var [row, column] = shape;
    async_model_showm(row * column, 'where_async');

    final data = self.ref.data;
    double value;
    // 创建用于存储异步任务的 Future 列表
    List<Future<void>> futures = [];
    Pointer<Pointer<Double>> newData = matply__allocateButNoNumbers(row, column);
    List<double> resultList = [];

    // 异步执行遍历矩阵的操作
    if (any != null) {
      assert(obj != null);
      // 使用异步操作处理每个矩阵元素
      futures.add(Future(() async {
        for (int r = 0; r < row; r++) {
          for (int c = 0; c < column; c++) {
            value = data[r][c];
            if (condition(value) && any(value, obj!)) {
              if (cpl != null) {
                newData[r][c] = cpl(value);
              } else {
                newData[r][c] = value;
              }
            }
          }
        }
      }));
      // 等待所有异步任务完成
      await Future.wait(futures);
      return MatrixType.__fromDataPointer(newData, shape);
    } else {
      // 处理不带 `any` 的情况
      futures.add(Future(() async {
        for (int r = 0; r < row; r++) {
          for (int c = 0; c < column; c++) {
            value = data[r][c];
            if (condition(value)) {
              if (cpl != null) {
                newData[r][c] = cpl(value);
              } else {
                newData[r][c] = value;
              }
            }
          }
        }
      }));
      // 处理符合条件的值并加入列表
      futures.add(Future(() async {
        for (int r = 0; r < row; r++) {
          for (int c = 0; c < column; c++) {
            value = data[r][c];
            if (condition(value) && (any == null || any(value, obj))) {
              resultList.add(value);
            }
          }
        }
      }));
      // 等待所有任务完成
      await Future.wait(futures);
      if (cpl != null) {
        return MatrixType.__fromDataPointer(newData, shape);
      } else {
        return resultList;
      }
    }
  }

  bool all(bool Function(double) condition) {
    NativeCallable<Bool Function(Double)> func = NativeCallable<
        Bool Function(Double)>
        .isolateLocal(condition, exceptionalReturn: false);
    final bl = matply__all(
        shape[0], shape[1], self.ref.data, func.nativeFunction);
    func.close();
    return bl;
  }

  Future<bool> all_async(bool Function(double) condition) async {
    var [row, column] = shape;
    async_model_showm(row * column, 'all_async');

    final data = self.ref.data;
    return Stream.fromFutures(
      List<Future<bool>>.generate(row, (r) async {
        for (int c = 0;c < column;c ++){
          if (!condition(data[r][c])){
            return false;
          }
        }
        return true;
      })
    ).any((e) => e == true);
  }

  bool any(bool Function(double) condition) {
    NativeCallable<Bool Function(Double)> func = NativeCallable<
        Bool Function(Double)>
        .isolateLocal(condition, exceptionalReturn: false);
    final bl = matply__any(
        shape[0], shape[1], self.ref.data, func.nativeFunction);
    func.close();
    return bl;
  }

  Future<bool> any_async(bool Function(double) condition) async {
    var [row, column] = shape;
    async_model_showm(row * column, 'any_async');

    final data = self.ref.data;
    return await Stream.fromIterable(List.generate(row, (r) async {
      for (int c = 0; c < column; c++) {
        if (condition(data[r][c])) {
          return true;
        }
      }
      return false;
    })).any((e) => e == true);
  }

  Object counter(bool Function(double) condition, {int dim = -1}) {
    NativeCallable<Bool Function(Double)> func = NativeCallable<
        Bool Function(Double)>
        .isolateLocal(condition, exceptionalReturn: false);
    late Pointer<Int32> ct;
    Object target;
    switch (dim) {
      case 0:
        ct = matply__counter(shape[0], shape[1], self.ref.data, 0, func.nativeFunction);
        func.close();
        target = ct.asTypedList(shape[0]).toList();
        freeOp(ct);
        return target;
      case 1:
        ct = matply__counter(shape[0], shape[1], self.ref.data, 1, func.nativeFunction);
        func.close();
        target = ct.asTypedList(shape[1]).toList();
        freeOp(ct);
        return target;
      default:
        ct = matply__counter(shape[0], shape[1], self.ref.data, -1, func.nativeFunction);
        func.close();
        target = ct.value;
        freeOp(ct);
        return target;
    }
  }

  Future<Object> counter_async(bool Function(double) condition, {int dim = -1}) async {
    var [row, column] = shape;
    async_model_showm(row * column, 'counter_async');

    final data = self.ref.data;
    switch(dim){
      case 0:
        List<Future<int>> futures = List.generate(row, (r) async {
          int count = 0;
          for (int c = 0;c < column;c ++){
            if (condition(data[r][c])){
              count++;
            }
          }
          return count;
        });
        return await Future.wait(futures);
      case 1:
        List<Future<int>> futures = List.generate(column, (c) async {
          int count = 0;
          for (int r = 0;r < row;r++){
            if (condition(data[r][c])){
              count++;
            }
          }
          return count;
        });
        return await Future.wait(futures);
      default:
        int totalCount = 0;
        await Future.wait(List.generate(row, (r) async {
          for (int c = 0; c < column; c++) {
            if (condition(data[r][c])) {
              totalCount++;
            }
          }
        }));
        return totalCount;
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

  Future<Object> reduce_async(
      double Function(double, double) condition, {
      required double init, int dim = -1
  }) async {
    var [row, column] = shape;
    async_model_showm(row * column, 'reduce_async');

    final data = self.ref.data;
    switch (dim) {
      case 0:
        return await Future.wait(
          List.generate(row, (r) async {
            double accumulator = init;
            for (int c = 0; c < column; c++) {
              accumulator = condition(accumulator, data[r][c]);
            }
            return accumulator;
          }),
        );
      case 1:
        return await Future.wait(
          List.generate(column, (c) async {
            double accumulator = init;
            for (int r = 0; r < row; r++) {
              accumulator = condition(accumulator, data[r][c]);
            }
            return accumulator;
          }),
        );
      default:
        await Future.wait(
          List.generate(row, (r) async {
            for (int c = 0; c < column; c++) {
              init = condition(init, data[r][c]);
            }
          }),
        );
        return init;
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

  Future<dynamic> magic_async(
    dynamic Function(double) condition, {
    dynamic Function(dynamic conditionResult)? reflect,
    dynamic Function(dynamic reflectAll)? reflectAll,
    required dynamic init,
    required dynamic Function(dynamic, dynamic) copeValue,
    required dynamic Function(dynamic) returned,
    int dim = -1
  }) async {
    final data = self.ref.data;
    dynamic value;
    dynamic current = init;
    var [row, column] = shape;
    async_model_showm(row * column, 'magic_async');

    switch (dim) {
      case 0:
        List<Future<dynamic>> futures = List.generate(row, (r) async {
          for (int c = 0;c < column;c++){
            value = reflect == null
                ? condition(data[r][c])
                : reflect(condition(data[r][c]));
            current = copeValue(current, value);
          }
          return reflectAll == null ? current : reflectAll(current);
        });
        return returned(await Future.wait(futures));
      case 1:
        List<Future<dynamic>> futures = List.generate(column, (c) async {
          for (int r = 0;r < row;r++){
            value = reflect == null
                ? condition(data[r][c])
                : reflect(condition(data[r][c]));
            current = copeValue(current, value);
          }
          return reflectAll == null ? current : reflectAll(current);
        });
        return returned(await Future.wait(futures));
      default:
        return returned(await Future(() async {
          for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c++) {
              value = reflect == null
                  ? condition(data[r][c])
                  : reflect(condition(data[r][c]));
              current = copeValue(current, value);
            }
          }
          return reflectAll == null ? current : reflectAll(current);
        }));
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

  Future<MatrixType> clip_reverse_async(
      double Function(double) condition, {
      required double lb, required double ub
  }) async {
    assert(lb <= ub);
    var [row, column] = shape;
    async_model_showm(row * column, 'clip_reverse_async');

    Pointer<Pointer<Double>> data = matply__allocateButNoNumbers(row, column);
    final dataSelf = self.ref.data;
    double v;
    List<Future<void>> futures = List.generate(row, (r) async {
      for (int c = 0;c < column;c++){
        v = dataSelf[r][c];
        data[r][c] = (v <= lb || v >= ub) ? v : condition(v);
      }
      return;
    });
    await Future.wait(futures);
    return MatrixType.__fromDataPointer(data, shape);
  }

  void clip_reverse_no_returned(double Function(double) condition, {required double lb, required double ub}){
    assert(lb <= ub);
    NativeCallable<Double Function(Double)> func = NativeCallable<Double Function(Double)>
        .isolateLocal(condition, exceptionalReturn: double.nan);
    matply__clip_reverseNoReturned(shape[0], shape[1], self.ref.data, lb, ub, func.nativeFunction);
    func.close();
  }

  Future<void> clip_reverse_no_returned_async(
    double Function(double) condition, {
    required double lb,
    required double ub
  }) async {
    assert(lb <= ub);
    var [row, column] = shape;
    async_model_showm(row * column, 'clip_reverse_no_returned_async');

    final data = self.ref.data;
    double v;
    await Future.wait(List.generate(row, (r) async {
      for (int c = 0;c < column;c++){
        v = data[r][c];
        data[r][c] = (v <= lb || v >= ub) ? v : condition(v);
      }
      return;
    }));
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

  Future<MatrixType> customize_async(double Function(double) condition) async {
    var [row, column] = shape;
    async_model_showm(row * column, 'customize_async');

    final dataSelf = self.ref.data;
    final data = matply__allocateButNoNumbers(row, column);
    await Future.wait(List.generate(row, (r) async {
      for (int c = 0;c < column;c ++){
        data[r][c] = condition(dataSelf[r][c]);
      }
      return;
    }));
    return MatrixType.__fromDataPointer(data, shape);
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

  Future<List<List<int>>> findall_async(bool Function(double) condition) async {
    var [row, column] = shape;
    async_model_showm(row * column, 'findall_async');

    List<List<int>> ls = [];
    final data = self.ref.data;
    await Future.wait(List.generate(row, (r) async {
      List<int> list = [];
      int index = 0;
      for (int c = 0; c < column; c++) {
        if (condition(data[r][c])) {
          list.add(index);
        }
        index++;
      }
      ls.add(list);
    }));
    return ls;
  }

  MatrixType confront(double Function(double, double) func, {required MatrixType other}){
    if (!hasSameShape(other)){
      throw different_shape;
    }
    NativeCallable<Double Function(Double, Double)> _func = NativeCallable<Double Function(Double, Double)>
        .isolateLocal(func, exceptionalReturn: double.nan);
    Pointer<Pointer<Double>> data = matply__confront(shape[0], shape[1], self.ref.data, other.self.ref.data, _func.nativeFunction);
    final mt = MatrixType.__fromDataPointer(data, shape);
    _func.close();
    return mt;
  }

  Future<MatrixType> confront_async(double Function(double, double) func, {required MatrixType other}) async {
    if (!hasSameShape(other)){
      throw different_shape;
    }
    var [row, column] = shape;
    async_model_showm(row * column, 'confront');
    final data1 = this.self.ref.data;
    final data2 = other.self.ref.data;
    final data = matply__allocateButNoNumbers(row, column);
    await Future.wait(List.generate(row, (r) async {
      for (int c = 0 ;c < column;c++){
        data[r][c] = func(data1[r][c], data2[r][c]);
      }
      return;
    }));
    return MatrixType.__fromDataPointer(data, shape);
  }
}
