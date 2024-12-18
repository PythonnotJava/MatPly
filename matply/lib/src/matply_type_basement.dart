/// 矩阵相关的基础操作

part of "core.dart";

extension BasementMethods on MatrixType {
  void visible() => matply__VisibleMatrix(this.self);

  void visible_spc() => matply__VisibleMatrixSpc(this.self);

  @Alert('Returning a Pointer? or a List? depends on the type you give in.'
      'However in Dart, Using the Pointer type is not a good choice;'
      'The data you will get are all copies.')
  Object row_<T>(int row) {
    if (row < 0 || row >= shape[0]) {
      throw row_outRange;
    } else {
      if (T == Pointer) {
        return matply__row_(row, shape[1], self.ref.data);
      } else if (T == List || T == dynamic) {
        Pointer<Double> op = matply__row_(row, shape[1], self.ref.data);
        List<double> list = op.asTypedList(shape[1]).toList();
        matply__freeOp(op.cast<Void>());
        return list;
      } else {
        throw UnsupportedError('T must be Pointer or List');
      }
    }
  }

  @Alert('Returning a Pointer? or a List? depends on the type you give in.'
      'However in Dart, Using the Pointer type is not a good choice;'
      'The data you will get are all copies.')
  Object column_<T>(int column) {
    if (column < 0 || column >= shape[1]) {
      throw column_outRange;
    } else {
      if (T == Pointer) {
        return matply__column_(shape[0], column, self.ref.data);
      } else if (T == List || T == dynamic) {
        final op = matply__column_(shape[0], column, self.ref.data);
        final list = op..asTypedList(shape[1]).toList();
        matply__freeOp(op.cast<Void>());
        return list;
      } else {
        throw UnsupportedError('T must be Pointer or List');
      }
    }
  }

  double at(int row, int column) {
    if (column < 0 || column >= shape[1] || row < 0 || row >= shape[0])
      throw random_outRange;
    else {
      return matply__at(row, column, self.ref.data);
    }
  }

  bool hasSameShape(MatrixType other) {
    return other.shape[0] == shape[0] && shape[1] == other.shape[1];
  }

  List<List<bool>> compare(MatrixType other, {int mode = 0}) {
    if (hasSameShape(other)) {
      Pointer<Pointer<Bool>> results = matply__compare(
          shape[0], shape[1], self.ref.data, other.self.ref.data, mode);
      final ls = List.generate(shape[0], (e) {
        Pointer<Bool> rowPointer = (results + e).value;
        return List.generate(shape[1], (j) => (rowPointer + j).value);
      });
      matply__freeppvoid(results.cast<Pointer<Void>>(), shape[0]);
      return ls;
    } else
      throw different_shape;
  }

  MatrixType cut(
      {required int row,
      required int column,
      required int width,
      required int height}) {
    assert(width > 0 && height > 0);
    if (row < 0 ||
        row >= shape[0] ||
        column < 0 ||
        column >= shape[1] ||
        column + width > shape[1] ||
        row + height > shape[0])
      throw random_outRange;
    else
      return MatrixType.__fromDataPointer(
          matply__cut(
              shape[0], shape[1], self.ref.data, row, column, width, height),
          shape);
  }

  MatrixType cutfree(
      {required int row,
      required int column,
      required int width,
      required int height,
      double number = .0}) {
    assert(width > 0 && height > 0);
    if (row < 0 || row >= shape[0] || column < 0 || column >= shape[1])
      throw random_outRange;
    else
      return MatrixType.__fromDataPointer(
          matply__cutfree(shape[0], shape[1], self.ref.data, row, column, width,
              height, number),
          shape);
  }

  MatrixType concat({required MatrixType other, required bool horizontal}) {
    if (horizontal ? other.shape[0] == shape[0] : other.shape[1] == shape[1]) {
      return horizontal
          ? MatrixType.__fromDataPointer(
              matply__concatR(shape[0], shape[1], other.shape[1], self.ref.data,
                  other.self.ref.data),
              [shape[0], shape[1] + other.shape[1]])
          : MatrixType.__fromDataPointer(
              matply__concatC(shape[0], other.shape[0], shape[1], self.ref.data,
                  other.self.ref.data),
              [shape[0] + other.shape[0], shape[1]]);
    } else
      throw row_or_column_not_same;
  }

  MatrixType reshape({required int row, required int column}) {
    if (row * column != size)
      throw size_changed;
    else {
      if (row == shape[0]) {
        return MatrixType.deepCopy(this);
      }
      assert(row > 0 && column > 0);
      return MatrixType.__fromDataPointer(
          matply__reshape(row, column, self.ref.data, shape[1]), [row, column]);
    }
  }

  MatrixType resize(
      {required int row,
      required int column,
      double number = .0,
      bool horizontal = true}) {
    assert(row > 0 && column > 0);
    return horizontal
        ? MatrixType.__fromDataPointer(
            matply__resizeR(
                row, column, self.ref.data, shape[0], shape[1], number),
            [row, column])
        : MatrixType.__fromDataPointer(
            matply__resizeC(
                row, column, self.ref.data, shape[0], shape[1], number),
            [row, column]);
  }

  void resize_no_returned(
      {required int row,
      required int column,
      double number = .0,
      bool horizontal = true}) {
    assert(row > 0 && column > 0);
    Pointer<Pointer<Double>> data = horizontal
        ? matply__resizeR(
            row, column, self.ref.data, shape[0], shape[1], number)
        : matply__resizeC(
            row, column, self.ref.data, shape[0], shape[1], number);
    matply__delete__data__(self.ref.data, shape[0]);
    self.ref.data = data;
    self.ref.column = column;
    self.ref.row = row;
  }

  void reshape_no_returned({required int row, required int column}) {
    if (row * column != size)
      throw size_changed;
    else {
      if (row == shape[0]) return;
      assert(row > 0 && column > 0);
      Pointer<Pointer<Double>> data =
          matply__reshape(row, column, self.ref.data, shape[1]);
      matply__delete__data__(self.ref.data, shape[0]);
      self.ref.data = data;
      self.ref.column = column;
      self.ref.row = row;
    }
  }

  void sort_no_returned(
          {bool reverse = false, double mask_nan = 0.0, int dim = -1}) =>
      matply__sortNoReturned(
          shape[0], shape[1], self.ref.data, reverse, dim, mask_nan);

  MatrixType sort(
          {bool reverse = false, double mask_nan = 0.0, int dim = -1}) =>
      MatrixType.__fromDataPointer(
          matply__sort(
              shape[0], shape[1], self.ref.data, reverse, dim, mask_nan),
          shape);

  void setMask(
      {double? mask_nan,
      double? mask_inf,
      bool isNegativeInf = true,
      bool both = false}) {
    // both表示正负无穷大都取值
    if (mask_nan == null && mask_inf == null) {
      throw UnsupportedError(
          'At least one of mask_nan or mask_inf cannot be empty.');
    }
    if (mask_nan != null) {
      matply__set_mask_nan(shape[0], shape[1], self.ref.data, mask_nan);
    }
    if (mask_inf != null) {
      matply__set_mask_inf(
          shape[0], shape[1], self.ref.data, mask_inf, isNegativeInf);
      if (both) {
        matply__set_mask_inf(
            shape[0], shape[1], self.ref.data, mask_inf, !isNegativeInf);
      }
    }
  }

  List<List<T>> toList<T>() {
    if (T == double) {
      return List.generate(shape[0], (i) => (this[i] as List).map<double>((e) => e).toList()) as List<List<T>>;
    } else if (T == int) {
      return List.generate(shape[0],
          (i) => (this[i] as List).map<int>((e) => e.toInt()).toList()) as List<List<T>>;
    } else if (T == String) {
      return List.generate(shape[0],
          (i) => (this[i] as List).map<String>((e) => e.toString()).toList()) as List<List<T>>;
    } else if (T == bool) {
      return List.generate(shape[0],
          (i) => (this[i] as List).map<bool>((e) => (e != 0)).toList()) as List<List<T>>;
    } else {
      throw UnsupportedError('Unsupported type.');
    }
  }

  MatrixType flatten({int mode = 0}) => MatrixType.__fromDataPointer(
      matply__oneTotwoArray(
          matply__flatten(shape[0], shape[1], self.ref.data, mode),
          1,
          shape[0] * shape[1]),
      [1, shape[0] * shape[1]]);

  @Deprecated('Use toDoubleVector instead')
  List<double> flatten_list({int mode = 0}) {
    var [row, column] = shape;
    final op = matply__flatten(row, column, self.ref.data, mode);
    var list = op.asTypedList(size).toList();
    matply__freeOp(op.cast<Void>());
    return list;
  }

  MatrixType slice({required int from, int? to, bool horizontal = true}) {
    var [row, column] = shape;
    if (to != null) {
      assert(from <= to);
      if (horizontal) {
        if (from >= 0 && to < row)
          return MatrixType.__fromDataPointer(
              matply__sliceR(shape[1], self.ref.data, from, to),
              [to - from + 1, column]);
        else
          throw row_outRange;
      } else {
        if (from >= 0 && to < column)
          return MatrixType.__fromDataPointer(
              matply__sliceC(shape[0], self.ref.data, from, to),
              [row, to - from + 1]);
        else
          throw column_outRange;
      }
    } else {
      if (horizontal) {
        if (from >= 0 && from < row)
          return MatrixType.__fromDataPointer(
              matply__sliceR(shape[1], self.ref.data, from, row - 1),
              [row - from, column]);
        else
          throw row_outRange;
      } else {
        if (from >= 0 && from < column)
          return MatrixType.__fromDataPointer(
              matply__sliceC(shape[0], self.ref.data, from, column - 1),
              [row, column - from]);
        else
          throw column_outRange;
      }
    }
  }

  MatrixType clip({required double lb, required double ub}) {
    assert(lb <= ub);
    return MatrixType.__fromDataPointer(
        matply__clip(shape[0], shape[1], self.ref.data, lb, ub), shape);
  }

  void clip_no_returned({required double lb, required double ub}) {
    assert(lb <= ub);
    matply__clipNoReturned(shape[0], shape[1], self.ref.data, lb, ub);
  }

  MatrixType rotate({required int angle}) {
    // 正数代表顺时针，负数逆时针
    if (angle % 90 != 0)
      throw UnsupportedError('The angle must be an integer multiple of 90.');
    else {
      int mode = angle ~/ 90 % 4;

      /// The value of [mode] just in [-3, -2, -1, 0, 1, 2, 3]
      List<int> _shape = mode % 2 == 0 ? shape : [shape[1], shape[0]];
      return MatrixType.__fromDataPointer(
          matply__rotate(shape[0], shape[1], self.ref.data, mode), _shape);
    }
  }

  MatrixType mirror({int mode = 0}) => MatrixType.__fromDataPointer(
      matply__mirror(shape[0], shape[1], self.ref.data, mode), shape);

  void fill_diagonal({double number = 0.0}) =>
      matply__fill_diagonal(shape[0], shape[1], self.ref.data, number);

  MatrixType __concatsR3(MatrixType other1, MatrixType other2) {
    int row = shape[0],
        column = shape[1],
        column1 = other1.shape[1],
        column2 = other2.shape[1];
    if (column == column1 && column == column2)
      return MatrixType.__fromDataPointer(
          matply__concatsR(row, column, column1, column2, 0, self.ref.data,
              other1.self.ref.data, other2.self.ref.data, nullptr),
          [row, column + column1 + column2]);
    else
      throw row_or_column_not_same;
  }

  MatrixType __concatsR4(
      MatrixType other1, MatrixType other2, MatrixType other3) {
    int row = shape[0],
        column = shape[1],
        column1 = other1.shape[1],
        column2 = other2.shape[1],
        column3 = other3.shape[1];
    if (column == column1 && column == column2 && column == column3)
      return MatrixType.__fromDataPointer(
          matply__concatsR(
              row,
              column,
              column1,
              column2,
              column3,
              self.ref.data,
              other1.self.ref.data,
              other2.self.ref.data,
              other3.self.ref.data),
          [row, column + column1 + column2 + column3]);
    else
      throw row_or_column_not_same;
  }

  MatrixType __concatsC3(MatrixType other1, MatrixType other2) {
    int row = shape[0],
        column = shape[1],
        row1 = other1.shape[0],
        row2 = other2.shape[0];
    if (row == row1 && row == row2)
      return MatrixType.__fromDataPointer(
          matply__concatsC(row, row1, row2, 0, column, self.ref.data,
              other1.self.ref.data, other2.self.ref.data, nullptr),
          [row + row1 + row2, column]);
    else
      throw row_or_column_not_same;
  }

  MatrixType __concatsC4(
      MatrixType other1, MatrixType other2, MatrixType other3) {
    int row = shape[0],
        column = shape[1],
        row1 = other1.shape[0],
        row2 = other2.shape[0],
        row3 = other3.shape[0];
    if (row == row1 && row == row2 && row == row3)
      return MatrixType.__fromDataPointer(
          matply__concatsC(row, row1, row2, row3, column, self.ref.data,
              other1.self.ref.data, other2.self.ref.data, other3.self.ref.data),
          [row + row1 + row2 + row3, column]);
    else
      throw row_or_column_not_same;
  }

  MatrixType concats(
      {required MatrixType other1,
      MatrixType? other2,
      MatrixType? other3,
      bool horizontal = true}) {
    if (other3 == null && other2 == null)
      return concat(other: other1, horizontal: horizontal);
    else if (other2 != null && other3 == null) {
      if (horizontal)
        return __concatsR3(other1, other2);
      else
        return __concatsC3(other1, other2);
    } else if (other2 == null && other3 != null) {
      if (horizontal)
        return __concatsR3(other1, other3);
      else
        return __concatsC3(other1, other3);
    } else {
      if (horizontal)
        return __concatsR4(other1, other2!, other3!);
      else
        return __concatsC4(other1, other2!, other3!);
    }
  }

  List<MatrixType> split({required List<int> slices, bool horizontal = true}) {
    // 检测是不是严格递增的且在范围内的正整数数列
    if (slices[0] > 0 && horizontal
        ? slices.last < shape[1]
        : slices.last < shape[0]) {
      bool stop = false;
      int len = slices.length, row = shape[0], column = shape[1];
      List<List<int>> shapes = [
        horizontal ? [row, slices.first] : [slices.first, column]
      ];
      for (int i = 1; i < len; i++) {
        if (slices[i] <= slices[i - 1]) {
          stop = true;
          break;
        }
        shapes.add(horizontal
            ? [row, slices[i] - slices[i - 1]]
            : [slices[i] - slices[i - 1], column]);
      }
      shapes.add(horizontal
          ? [row, column - slices.last]
          : [row - slices.last, column]);
      if (stop)
        throw "Please pass in a strictly increasing positive integer slice index that is within the range.";
      else {
        Pointer<Int32> op = oneListToArrayInt32(slices);
        Pointer<Pointer<Pointer<Double>>> mtops = matply__split(
            shape[0], shape[1], self.ref.data, len, op, horizontal);
        freeOp(op);
        return List.generate(
            len + 1,
            (index) =>
                MatrixType.__fromDataPointer(mtops[index], shapes[index]),
            growable: true);
      }
    } else
      throw random_outRange;
  }

  Object split_equal({required int step, bool horizontal = true}) {
    assert(step > 0);
    var [row, column] = shape;
    if (horizontal ? step < column : step < row)
      return split(
          slices: horizontal
              ? List<int>.generate(
                  (column / step).ceil() - 1, (i) => (i + 1) * step)
              : List<int>.generate(
                  (row / step).ceil() - 1, (i) => (i + 1) * step),
          horizontal: horizontal);
    else if (horizontal ? step == column : step == row)
      return MatrixType.deepCopy(this);
    else
      throw random_outRange;
  }

  MatrixType cover(MatrixType mt, {required int row, required int column}) {
    if (row >= 0 && row < shape[0] && column >= 0 && column < shape[1]) {
      return MatrixType.__fromDataPointer(
          matply__cover(shape[0], shape[1], self.ref.data, mt.shape[0],
              mt.shape[1], mt.self.ref.data, row, column),
          shape);
    } else
      throw random_outRange;
  }

  MatrixType stretch(
      {required int len,
      bool horizontal = true,
      double? number,
      int method = 0}) {
    assert(len > 0);
    if (method == 1) assert(number != null);
    var [row, column] = shape;
    return MatrixType.__fromDataPointer(
        matply__stretch(
            row, column, self.ref.data, len, horizontal, number ?? 0, method),
        horizontal ? [row, column + len] : [row + len, column]);
  }

  List<double> toDoubleVector({int mode = 0}) {
    var [row, column] = shape;
    final Pointer<Double> op =
        matply__flatten(row, column, self.ref.data, mode);
    final vec = op.asTypedList(row * column).toList();
    matply__freeOp(op.cast<Void>());
    return vec;
  }

  List<int> toIntVector({int mode = 0}) {
    var [row, column] = shape;
    final Pointer<Double> op =
        matply__flatten(row, column, self.ref.data, mode);
    final vec = op.asTypedList(row * column).toList();
    matply__freeOp(op.cast<Void>());
    return vec.map((e) => e.toInt()).toList();
  }

  List<bool> toBoolVector({int mode = 0}) {
    var [row, column] = shape;
    final Pointer<Double> op =
        matply__flatten(row, column, self.ref.data, mode);
    final vec = op.asTypedList(row * column).toList();
    matply__freeOp(op.cast<Void>());
    return vec.map((e) => e != 0).toList();
  }
}
