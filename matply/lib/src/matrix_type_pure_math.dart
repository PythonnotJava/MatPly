/// 矩阵相关的纯粹数学操作分支
part of 'core.dart';

/// 关于二维点的操作拓展
extension Point2DOperator<T extends num> on math.Point<T> {
  // 二次线性变换
  math.Point<T> transform(Object mt) {
    if (mt is MatrixType) {
      assert(mt.shape[0] == 2 && mt.shape[1] == 2);
      var x = mt.at(0, 0) * this.x.toDouble() + mt.at(0, 1) * this.y.toDouble();
      var y = mt.at(1, 0) * this.x.toDouble() + mt.at(1, 1) * this.y.toDouble();
      return math.Point(x as T, y as T);
    } else if (mt is List<List<num>>) {
      assert(mt.length == 2 && mt[0].length == 2);
      var x = mt[0][0] * this.x.toDouble() + mt[0][1] * this.y.toDouble();
      var y = mt[1][0] * this.x.toDouble() + mt[1][1] * this.y.toDouble();
      return math.Point(x as T, y as T);
    } else
      throw UnsupportedError('Unsupported Type!');
  }

  // 旋转变换
  math.Point<T> rotate(num angle) => transform([
        [math.cos(angle), -math.sin(angle)],
        [math.sin(angle), math.cos(angle)]
      ]);
  // 缩放变换
  math.Point<T> scale(num sx, num sy) => transform([
        [sx, 0.0],
        [0.0, sy]
      ]);
  // 判断不是同一个点
  bool isSame(math.Point<T> p) {
    return p.x == x && p.y == y;
  }
  // 转Point2D
  get toPoint2d => matply__xytoPoint2D(x.toDouble(), y.toDouble());
}

// 生成笛卡尔积
Iterable<math.Point<num>> getCartesianProduct(
    List<num> list1, List<num> list2) sync* {
  assert(list1.isNotEmpty && list2.isNotEmpty);
  for (num value1 in list1) {
    for (num value2 in list2) {
      yield math.Point<num>(value1, value2);
    }
  }
}

extension PureMath on MatrixType {
  /// setter && getter
  MatrixType get acos => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 0), shape);
  MatrixType get asin => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 1), shape);
  MatrixType get atan => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 2), shape);
  MatrixType get cos => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 3), shape);
  MatrixType get sin => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 4), shape);
  MatrixType get tan => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 5), shape);
  MatrixType get cosh => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 6), shape);
  MatrixType get sinh => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 7), shape);
  MatrixType get tanh => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 8), shape);
  MatrixType get exp => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 9), shape);
  MatrixType get log => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 10), shape);
  MatrixType get log10 => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 11), shape);
  MatrixType get sqrt => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 12), shape);
  MatrixType get ceil => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 13), shape);
  MatrixType get floor => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 14), shape);
  MatrixType get fabs => MatrixType.__fromDataPointer(
      matply_mathBasement1(shape[0], shape[1], self.ref.data, 15), shape);

  /// method
  Object sum({int dim = -1}) {
    switch (dim) {
      case 0:
        return matply__sum(shape[0], shape[1], self.ref.data, 0)
            .asTypedList(shape[0])
            .toList();
      case 1:
        return matply__sum(shape[0], shape[1], self.ref.data, 1)
            .asTypedList(shape[1])
            .toList();
      default:
        return matply__sum(shape[0], shape[1], self.ref.data, -1).value;
    }
  }

  Object mean({int dim = -1}) {
    switch (dim) {
      case 0:
        return matply__mean(shape[0], shape[1], self.ref.data, 0)
            .asTypedList(shape[0])
            .toList();
      case 1:
        return matply__mean(shape[0], shape[1], self.ref.data, 1)
            .asTypedList(shape[1])
            .toList();
      default:
        return matply__mean(shape[0], shape[1], self.ref.data, -1).value;
    }
  }

  Object min({int dim = -1}) {
    switch (dim) {
      case 0:
        return matply__min(shape[0], shape[1], self.ref.data, 0)
            .asTypedList(shape[0])
            .toList();
      case 1:
        return matply__min(shape[0], shape[1], self.ref.data, 1)
            .asTypedList(shape[1])
            .toList();
      default:
        return matply__min(shape[0], shape[1], self.ref.data, -1).value;
    }
  }

  Object max({int dim = -1}) {
    switch (dim) {
      case 0:
        return matply__max(shape[0], shape[1], self.ref.data, 0)
            .asTypedList(shape[0])
            .toList();
      case 1:
        return matply__max(shape[0], shape[1], self.ref.data, 1)
            .asTypedList(shape[1])
            .toList();
      default:
        return matply__max(shape[0], shape[1], self.ref.data, -1).value;
    }
  }

  MatrixType power({required double number, bool reverse = false}) => reverse
      ? MatrixType.__fromDataPointer(
          matply_mathBasement2reverse(
              shape[0], shape[1], self.ref.data, 0, number),
          shape)
      : MatrixType.__fromDataPointer(
          matply_mathBasement2(shape[0], shape[1], self.ref.data, 0, number),
          shape);

  MatrixType atan2({required double number, bool reverse = true}) => reverse
      ? MatrixType.__fromDataPointer(
          matply_mathBasement2reverse(
              shape[0], shape[1], self.ref.data, 1, number),
          shape)
      : MatrixType.__fromDataPointer(
          matply_mathBasement2(shape[0], shape[1], self.ref.data, 1, number),
          shape);

  MatrixType sigmoid() => MatrixType.__fromDataPointer(
      matply__sigmoid(shape[0], shape[1], self.ref.data), shape);

  MatrixType softmax(
          {double mask_nan = 0.0,
          double mask_inf = 0.0,
          double mask_neginf = 0.0,
          int dim = -1}) =>
      MatrixType.__fromDataPointer(
          matply__softmax(shape[0], shape[1], self.ref.data, dim, mask_nan,
              mask_nan, mask_neginf),
          shape);

  Object argmax({int dim = -1}) {
    switch (dim) {
      case 0:
        return matply__argmax(shape[0], shape[1], self.ref.data, 0)
            .asTypedList(shape[0])
            .toList();
      case 1:
        return matply__argmax(shape[0], shape[1], self.ref.data, 1)
            .asTypedList(shape[1])
            .toList();
      default:
        return matply__argmax(shape[0], shape[1], self.ref.data, -1).value;
    }
  }

  Object argmin({int dim = -1}) {
    switch (dim) {
      case 0:
        return matply__argmin(shape[0], shape[1], self.ref.data, 0)
            .asTypedList(shape[0])
            .toList();
      case 1:
        return matply__argmin(shape[0], shape[1], self.ref.data, 1)
            .asTypedList(shape[1])
            .toList();
      default:
        return matply__argmin(shape[0], shape[1], self.ref.data, -1).value;
    }
  }

  MatrixType diff_center(double Function(double) condition) {
    NativeCallable<Double Function(Double)> func =
        NativeCallable<Double Function(Double)>.isolateLocal(condition,
            exceptionalReturn: 0.0);
    var mt =
        matply__diffC(shape[0], shape[1], self.ref.data, func.nativeFunction);
    func.close();
    return MatrixType.__fromDataPointer(mt, shape);
  }

  List get_range({int dim = -1}) {
    late final List list;
    var [row, column] = shape;
    Pointer<Pointer<Double>> dataOp =
        matply__get_range(row, column, self.ref.data, dim);
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

  MatrixType cumsum({bool? flatten, int dim = -1}) {
    var [row, column] = shape;
    switch (dim) {
      case 0:
        return MatrixType.__fromDataPointer(
            matply__cumsum(row, column, self.ref.data, 0, true), shape);
      case 1:
        return MatrixType.__fromDataPointer(
            matply__cumsum(row, column, self.ref.data, 1, true), shape);
      default:
        if (flatten != null)
          return MatrixType.__fromDataPointer(
              matply__cumsum(row, column, self.ref.data, -1, flatten),
              flatten ? [1, size] : shape);
        else
          throw "When dim is not equal to 0 or 1, the parameter flatten must be set.";
    }
  }

  MatrixType sgn() => MatrixType.__fromDataPointer(
      matply__sgn(shape[0], shape[1], self.ref.data), shape);

  void shake({double bias = 1.0, int? seed}){
    if (bias != 0)
      matply__shake(shape[0], shape[1], self.ref.data, seed?? 0, seed != null, bias);
  }
}

/// 模拟生成符合几何数据，具有随机性
extension GeometryGenerator on MatrixType {
  // 椭圆轮廓
  static MatrixType ellipse_edge({
    int size = 50,
    required double a,
    required double b,
    int? seed,
    double bias = 0.0
  }) {
    assert(size >= 50 && a > 0 && b > 0);
    return MatrixType.__fromDataPointer(
        matply__ellipse_edge(size, a, b, seed ?? 0, seed != null, bias), [size, 2]);
  }

  // 椭圆区域
  static MatrixType ellipse_area({
    int size = 50,
    required double a,
    required double b,
    int? seed,
    double bias = 0.0
  }) {
    assert(size >= 50 && a > 0 && b > 0);
    return MatrixType.__fromDataPointer(
        matply__ellipse_area(size, a, b, seed ?? 0, seed != null, bias), [size, 2]);
  }

  // 圆轮廓
  static MatrixType circle_edge({
    int size = 50,
    required double r,
    int? seed,
    double bias = 0.0
  }) {
    assert(size >= 50 && r > 0);
    return MatrixType.__fromDataPointer(
        matply__circle_edge(size, r, seed ?? 0, seed != null, bias), [size, 2]);
  }

  // 圆区域
  static MatrixType circle_area({
    int size = 50,
    required double r,
    int? seed,
    double bias = 0.0
  }) {
    assert(size >= 50 && r > 0);
    return MatrixType.__fromDataPointer(
        matply__circle_area(size, r, seed ?? 0, seed != null, bias), [size, 2]);
  }

  // 线性散点
  static MatrixType line({
    int size = 50,
    required math.Point<double> start,
    required math.Point<double> end,
    int? seed,
    double bias = 0.0
  }) {
    assert(size >= 50 && !start.isSame(end));
    return MatrixType.__fromDataPointer(
        matply__line(size, start.toPoint2d, end.toPoint2d, seed ?? 0, seed != null, bias),
        [size, 2]);
  }

  // 三角形轮廓
  static MatrixType triangle_edge({
    int size = 50,
    required math.Point<double> a,
    required math.Point<double> b,
    required math.Point<double> c,
    int? seed,
    double bias = 0.0
  }) {
    assert(size >= 50);
    return MatrixType.__fromDataPointer(
        matply__triangle_edge(
          size, a.toPoint2d, b.toPoint2d, c.toPoint2d, seed ?? 0, seed != null, bias),
          [size, 2]
    );
  }

  // 三角形区域
  static MatrixType triangle_area({
    int size = 50,
    required math.Point<double> a,
    required math.Point<double> b,
    required math.Point<double> c,
    int? seed,
    double bias = 0.0
  }) {
    assert(size >= 50);
    return MatrixType.__fromDataPointer(
        matply__triangle_area(
            size,
            a.toPoint2d, b.toPoint2d, c.toPoint2d, seed ?? 0, seed != null, bias),
        [size, 2]);
  }

  // 四边形轮廓
  static MatrixType quadrilateral_edge(
      {int size = 50,
      required math.Point<double> a,
      required math.Point<double> b,
      required math.Point<double> c,
      required math.Point<double> d,
      int? seed,
      double bias = 0.0
    }) {
    assert(size >= 50);
    return MatrixType.__fromDataPointer(
        matply__quadrilateral_edge(
            size,
            a.toPoint2d, b.toPoint2d, c.toPoint2d, d.toPoint2d, seed ?? 0, seed != null, bias),
        [size, 2]);
  }

  // 四边形区域
  static MatrixType quadrilateral_area(
      {int size = 50,
      required math.Point<double> a,
      required math.Point<double> b,
      required math.Point<double> c,
      required math.Point<double> d,
      int? seed,
      double bias = 0.0}) {
    assert(size >= 50);
    return MatrixType.__fromDataPointer(
        matply__quadrilateral_area(
            size, a.toPoint2d, b.toPoint2d, c.toPoint2d, d.toPoint2d,
            seed ?? 0,
            seed != null, bias),
        [size, 2]);
  }

  // 心形线轮廓
  static MatrixType heart_edge({
    int size = 50,
    double x_center = 0.0,
    int? seed,
    double bias = 0.0
  }) {
    assert(size >= 50);
    return MatrixType.__fromDataPointer(
        matply__heart_edge(size, x_center, seed ?? 0, seed != null, bias), [size, 2]);
  }

  // 心形线区域
  static MatrixType heart_area({
    int size = 50,
    double x_center = 0.0,
    int? seed,
    double bias = 0.0
  }){
      assert(size >= 50);
      return MatrixType.__fromDataPointer(
          matply__heart_area(size, x_center, seed ?? 0, seed != null, bias), [size, 2]);
  }

  // 任意曲线拟合
  static MatrixType curve(
    double Function(double) func, {
    int size = 50,
    required double x1,
    required double x2,
    int? seed,
    double bias = 0.0
  }){
    assert(size >= 50);
    NativeCallable<Double Function(Double)> _func = NativeCallable<
        Double Function(Double)>
        .isolateLocal(func, exceptionalReturn: 0.0);
    MatrixType mt = MatrixType.__fromDataPointer(
      matply__curve(size, x1, x2, _func.nativeFunction, seed ?? 0, seed != null, bias),
      [size, 2]
    );
    _func.close();
    return mt;
  }

  // 贝塞尔曲线拟合
  static MatrixType bezier({
    int size = 50,
    required math.Point<double> start,
    required math.Point<double> end,
    required math.Point<double> ctrl,
    int? seed,
    double bias = 0.0
  }){
      assert(size >= 50);
      return MatrixType.__fromDataPointer(
          matply__bezier(size,
              start.toPoint2d, end.toPoint2d, ctrl.toPoint2d,
              seed ?? 0,
              seed != null,
              bias
          ),
          [size, 2]
      );
  }

  // 矩形边缘模拟
  static MatrixType rectangle_edge({
    int size = 50,
    required math.Point<double> top_left,
    required double width,
    required double height,
    int? seed,
    double bias = 0.0
  }){
    assert(size >= 50);
    final b = matply__xytoPoint2D(top_left.x + width, top_left.y);
    final c = matply__xytoPoint2D(b.x, top_left.y - height);
    final d = matply__xytoPoint2D(top_left.x, c.y);
    return MatrixType.__fromDataPointer(
        matply__quadrilateral_edge(
            size,
            top_left.toPoint2d, b, c, d,
            seed ?? 0,
            seed != null,
            bias
        ), [size, 2]
    );
  }

  // 矩形区域模拟
  static MatrixType rectangle_area({
    int size = 50,
    required math.Point<double> top_left,
    required double width,
    required double height,
    int? seed,
    double bias = 0.0
  }){
    assert(size >= 50);
    final b = matply__xytoPoint2D(top_left.x + width, top_left.y);
    final c = matply__xytoPoint2D(b.x, top_left.y - height);
    final d = matply__xytoPoint2D(top_left.x, c.y);
    return MatrixType.__fromDataPointer(
        matply__quadrilateral_area(
            size,
            top_left.toPoint2d, b, c, d,
            seed ?? 0,
            seed != null,
            bias
        ), [size, 2]
    );
  }

  // 任意曲线模拟
  static MatrixType custom_curve({
    int size = 50,
    required double Function(double, Pointer<Void>) x_func,
    required double Function(double, Pointer<Void>) y_func,
    required List<num> params,
    required double theta_start,
    required double theta_step,
    int? seed,
    double bias = 0.0
  }){
    assert(size >= 0);
    var op = params.getOnePointer().cast<Void>();
    NativeCallable<Double Function(Double, Pointer<Void>)> _funcX = NativeCallable<
        Double Function(Double, Pointer<Void>)>
        .isolateLocal(x_func, exceptionalReturn: 0.0);
    NativeCallable<Double Function(Double, Pointer<Void>)> _funcY = NativeCallable<
        Double Function(Double, Pointer<Void>)>
        .isolateLocal(y_func, exceptionalReturn: 0.0);
    MatrixType mt = MatrixType.__fromDataPointer(
      matply__custom_curve(size, _funcX.nativeFunction, _funcY.nativeFunction, op, theta_start, theta_step, seed ?? 0, seed != null, bias),
      [size, 2]
    );
    malloc.free(op);
    _funcY.close();
    _funcX.close();
    return mt;
  }

  // 按照一元线性系数模拟直线
  static MatrixType linewb({
    int size = 50,
    required double start,
    required double end,
    required double w,
    required double b,
    int? seed,
    double bias = 0.0
  }){
      assert(size >= 50);
      return MatrixType.__fromDataPointer(
        matply__line(size, matply__xytoPoint2D(start, w * start + b), matply__xytoPoint2D(end, end * w + b), seed ?? 0, seed != null, bias),
        [size, 2]
      );
  }
}
