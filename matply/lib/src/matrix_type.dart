part of 'core.dart';

class MatrixType {
  /// Attributes
  late Pointer<Matrix> self;

  /// Constructors
  // 一般构造
  MatrixType(
      List<List<double>> data, {
      int? row,
      int? column,
      bool identityMatrix = false,
      bool principalDiagonalMatrix = false,
      bool subDiagonalMatrix = false,
      bool upperTriangularMatrix = false,
      bool lowerTriangularMatrix = false,
      bool singularMatrix = false
}) {
    row = row ?? data.length;
    column = column ?? data[0].length;
    this.self = matply__new__(row, column); // 未对data和spc分配了内存，对spc初始化了
    Pointer<Pointer<Double>> dataOp = matply__allocateButNoNumbers(row, column);
    for (int r = 0; r < row; r++) {
      for (int c = 0; c < column; c++) {
        dataOp[r][c] = data[r][c];
      }
    }
    this.self.ref.data = dataOp;
    defaultSpc(this);
  }

  @override
  String toString() {
    print("MatrixType:");
    visible();
    return 'shape : [${shape[0]}, ${shape[1]}]';
  }

  // 全number的矩阵
  MatrixType.filled(
      {required double number, required int row, required int column})
      : assert(row > 0 && column > 0) {
    this.self = matply__init__point__data__(
        row, column, matply__filled(row, column, number), nullptr);
  }

  // 全1矩阵
  MatrixType.ones({required int row, required int column})
      : assert(row > 0 && column > 0) {
    this.self = matply__init__point__data__(
        row, column, matply__ones(row, column), nullptr);
  }

  // 全0矩阵
  MatrixType.zeros({required int row, required int column})
      : assert(row > 0 && column > 0) {
    this.self = matply__init__point__data__(
        row, column, matply__zeros(row, column), nullptr);
  }

  // 连续创建
  MatrixType.arrange(
      {required double? start, required int row, required int column})
      : assert(row > 0 && column > 0) {
    start = start ?? 0.0;
    this.self = matply__init__point__data__(
        row, column, matply__arrange(start, row, column), nullptr);
  }

  // 等差创建
  MatrixType.linspace(
      {required double start,
      required double end,
      required int row,
      required int column,
      bool keep = true})
      : assert(start < end && row > 0 && column > 0) {
    this.self = matply__init__point__data__(
        row, column, matply__linspace(start, end, row, column, keep), nullptr);
  }

  // n阶单位矩阵
  MatrixType.E({required int n}) : assert(n > 0) {
    self = matply__init__point__data__(n, n, matply__E(n), nullptr);
    this.identityMatrix = true;
  }

  // 均匀分布
  MatrixType.uniform(
      {double start = .0,
      double end = 1.0,
      required int row,
      required int column,
      int? seed})
      : assert(start < end && row > 0 && column > 0) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__uniform(row, column, start, end, seed ?? 0, seed != 0),
        nullptr);
  }

  // 正态分布
  MatrixType.normal(
      {double mu = 0.0,
      double sigma = 1.0,
      required int row,
      required int column,
      int? seed})
      : assert(sigma >= 0 && row > 0 && column > 0 && row > 0 && column > 0) {
    this.self = matply__init__point__data__(row, column,
        matply__normal(row, column, mu, sigma, seed ?? 0, seed != 0), nullptr);
  }

  // 泊松分布
  MatrixType.poisson(
      {required double lambda,
      required int row,
      required int column,
      int? seed})
      : assert(lambda >= 0 && row > 0 && column > 0) {
    this.self = matply__init__point__data__(row, column,
        matply__poisson(row, column, lambda, seed ?? 0, seed != null), nullptr);
  }

  // 根据已经建立好的Matrix指针初始化
  // 原__fromPointer方法
  @Since('1.0.8')
  MatrixType.fromPointer(this.self);
  // 根据已经设置完毕的数据指针引用并且初始化
  MatrixType.__fromDataPointer(Pointer<Pointer<Double>> data, List<int> shape)
      : this.self =
            matply__init__point__data__(shape[0], shape[1], data, nullptr);

  // 深拷贝矩阵
  factory MatrixType.deepCopy(MatrixType other) {
    Pointer<Pointer<Double>> data =
        matply__deepcopy(other.shape[0], other.shape[1], other.self.ref.data);
    return MatrixType.__fromDataPointer(data, other.shape);
  }

  // 根据步长建立[new from 1.0.5]
  MatrixType.range(
      {required double start,
      double step = 1.0,
      required int row,
      required int column})
      : assert(row > 0 && column > 0) {
    this.self = matply__init__point__data__(
        row, column, matply__range(start, step, row, column), nullptr);
  }

  MatrixType.E_like({required int row, required int column})
      : assert(row > 0 && column > 0) {
    this.self = matply__init__point__data__(
        row, column, matply__E_like(row, column), nullptr);
  }

  // 生成对角矩阵
  MatrixType.Diag(
      {required int n,
      required double start,
      required double end,
      bool sub = false,
      int? seed})
      : assert(n > 0 && start < end) {
    this.self = matply__init__point__data__(
        n,
        n,
        matply__diagonal(n, n, start, end, sub, seed ?? 0, seed != null),
        nullptr);
  }

  // 指数分布
  MatrixType.exponential(
      {required int row, required int column, required double scale, int? seed})
      : assert(row > 0 && column > 0 && scale > 0) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__exponential(row, column, scale, seed ?? 0, seed != null),
        nullptr);
  }

  // 伽马分布
  MatrixType.gamma(
      {required int row,
      required int column,
      required double shape,
      required double scale,
      int? seed})
      : assert(row > 0 && column > 0 && shape > 0 && scale > 0) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__gamma_(row, column, shape, scale, seed ?? 0, seed != null),
        nullptr);
  }

  // 二项分布
  MatrixType.binomial(
      {required int row,
      required int column,
      required int n,
      required double p,
      int? seed})
      : assert(row > 0 && column > 0 && n > 0 && 0 <= p && p <= 1) {
    this.self = matply__init__point__data__(row, column,
        matply__binomial(row, column, n, p, seed ?? 0, seed != null), nullptr);
  }

  // 卡方分布
  MatrixType.chisquare(
      {required int row, required int column, required int k, int? seed})
      : assert(row > 0 && column > 0 && k > 0) {
    this.self = matply__init__point__data__(row, column,
        matply__chisquare(row, column, k, seed ?? 0, seed != null), nullptr);
  }

  // t分布
  MatrixType.tdis(
      {required int row, required int column, required int k, int? seed})
      : assert(row > 0 && column > 0 && k > 0) {
    this.self = matply__init__point__data__(row, column,
        matply__tdis(row, column, k, seed ?? 0, seed != null), nullptr);
  }

  // F分布
  MatrixType.fdis(
      {required int row,
      required int column,
      required int k1,
      required int k2,
      int? seed})
      : assert(row > 0 && column > 0 && k1 > 0 && k2 > 0) {
    this.self = matply__init__point__data__(row, column,
        matply__fdis(row, column, k1, k2, seed ?? 0, seed != null), nullptr);
  }

  // 几何分布
  MatrixType.geometric(
      {required int row, required int column, required double p, int? seed})
      : assert(row > 0 && column > 0 && p > 0 && p <= 1) {
    this.self = matply__init__point__data__(row, column,
        matply__geometric(row, column, p, seed ?? 0, seed != null), nullptr);
  }

  // 负二项分布
  MatrixType.nbinomial(
      {required int row,
      required int column,
      required int n,
      required double p,
      int? seed})
      : assert(row > 0 && column > 0 && n > 0 && p > 0 && p < 1) {
    this.self = matply__init__point__data__(row, column,
        matply__nbinomial(row, column, n, p, seed ?? 0, seed != null), nullptr);
  }

  // 对数正态分布
  MatrixType.lognormal(
      {required int row,
      required int column,
      required double mu,
      required double sigma,
      int? seed})
      : assert(row > 0 && column > 0 && sigma >= 0) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__lognormal(row, column, mu, sigma, seed ?? 0, seed != null),
        nullptr);
  }

  // 柯西分布
  MatrixType.cauchydis(
      {required int row,
      required int column,
      required double base,
      required double gamma,
      int? seed})
      : assert(row > 0 && column > 0 && gamma > 0) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__cauchydis(row, column, base, gamma, seed ?? 0, seed != null),
        nullptr);
  }

  // 多项式分布
  MatrixType.multinomial(
      {required List<double> p, required int n, required int size, int? seed})
      : assert(p.reduce((a, b) => a + b) == 1.0 && n > 0 && size > 0) {
    int row = size, column = p.length;
    final op = p.getOnePointer();
    this.self = matply__init__point__data__(
        row,
        column,
        matply__multinomial(op, column, n, size, seed ?? 0, seed != null),
        nullptr);
    malloc.free(op);
  }

  // 贝塔分布
  MatrixType.beta(
      {required int row,
      required int column,
      required double a,
      required double b,
      int? seed})
      : assert(row > 0 && column > 0 && a > 0 && b > 0) {
    this.self = matply__init__point__data__(row, column,
        matply__beta(row, column, a, b, seed ?? 0, seed != null), nullptr);
  }

  // 维纳过程
  MatrixType.wiener_process(
      {required int row, required int column, required double t, int? seed})
      : assert(row > 0 && column > 0 && t > 0) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__wiener_process(row, column, t, seed ?? 0, seed != null),
        nullptr);
  }

  // 维纳过程，某时间戳
  MatrixType.wiener_process_stage(
      {required int row,
      required int column,
      required double t1,
      required double t2,
      required double base,
      int? seed})
      : assert(row > 0 && column > 0 && t1 > 0 && t1 < t2) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__wiener_process_stage(
            row, column, t1, t2, base, seed ?? 0, seed != null),
        nullptr);
  }

  // 狄利克雷分布
  MatrixType.dirichlet({required List<num> alpha, required int size, int? seed})
      : assert(size > 0) {
    int column = 0;
    for (var e in alpha) {
      if (e > 0) {
        column++;
      } else
        throw "The alpha array must be all positive real numbers.";
    }
    final op = alpha.getOnePointer();
    this.self = matply__init__point__data__(size, column,
        matply__dirichlet(op, column, size, seed ?? 0, seed != null), nullptr);
    malloc.free(op);
  }

  // 拉普拉斯分布
  MatrixType.laplacedis(
      {required int row,
      required int column,
      required double mu,
      required double b,
      int? seed})
      : assert(row > 0 && column > 0 && b > 0) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__laplacedis(row, column, mu, b, seed ?? 0, seed != null),
        nullptr);
  }

  // 耿贝尔分布
  MatrixType.gumbel(
      {required int row,
      required int column,
      required double mu,
      required double beta,
      bool left = true,
      int? seed})
      : assert(row > 0 && column > 0 && beta > 0) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__gumbel(row, column, mu, beta, left, seed ?? 0, seed != null),
        nullptr);
  }

  // 超几何分布
  MatrixType.hypergeometric(
      {required int row,
      required int column,
      required int expected,
      required int unexpected,
      required int n,
      int? seed})
      : assert(row > 0 &&
            column > 0 &&
            expected >= 0 &&
            unexpected >= 0 &&
            n > 0 &&
            expected + unexpected >= n) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__hypergeometric(
            row, column, expected, unexpected, n, seed ?? 0, seed != null),
        nullptr);
  }

  // 对数分布
  MatrixType.logseries(
      {required int row, required int column, required double p, int? seed})
      : assert(row > 0 && column > 0 && 0 <= p && p < 1) {
    this.self = matply__init__point__data__(row, column,
        matply__logseries(row, column, p, seed ?? 0, seed != null), nullptr);
  }

  // 韦伯分布
  MatrixType.weibull(
      {required int row,
      required int column,
      required double lambda,
      required double k,
      int? seed})
      : assert(row > 0 && column > 0 && lambda > 0 && k > 0) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__weibull(row, column, lambda, k, seed ?? 0, seed != null),
        nullptr);
  }

  // 三角分布
  MatrixType.triangular(
      {required int row,
      required int column,
      required double left,
      required double middle,
      required double right,
      int? seed})
      : assert(row > 0 && column > 0 && left <= middle && middle <= right) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__triangular(
            row, column, left, middle, right, seed ?? 0, seed != null),
        nullptr);
  }

  // 幂定律分布
  MatrixType.power_law(
      {required int row,
      required int column,
      required double xmin,
      required double alpha,
      int? seed})
      : assert(row > 0 && column > 0 && xmin > 0 && alpha > 1) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__power_law(row, column, xmin, alpha, seed ?? 0, seed != null),
        nullptr);
  }

  // 瑞利分布
  MatrixType.rayleigh(
      {required int row, required int column, required double sigma, int? seed})
      : assert(row > 0 && column > 0 && sigma > 0) {
    this.self = matply__init__point__data__(row, column,
        matply__rayleigh(row, column, sigma, seed ?? 0, seed != null), nullptr);
  }

  // 稳定分布
  MatrixType.stabledis(
      {required int row,
      required int column,
      required double alpha,
      required double beta,
      required double gamma,
      required double delta,
      int? seed})
      : assert(row > 0 &&
            column > 0 &&
            alpha > 0 &&
            alpha <= 2 &&
            beta.abs() <= 1 &&
            gamma >= 0) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__stabledis(
            row, column, alpha, beta, gamma, delta, seed ?? 0, seed != null),
        nullptr);
  }

  // 帕累托分布
  MatrixType.pareto(
      {required int row,
      required int column,
      required double xmin,
      required double alpha,
      int? seed})
      : assert(row > 0 && column > 0 && xmin > 0 && alpha > 0) {
    this.self = matply__init__point__data__(
        row,
        column,
        matply__pareto(row, column, xmin, alpha, seed ?? 0, seed != null),
        nullptr);
  }

  // 莱斯分布
  MatrixType.rice(
      {required int row,
      required int column,
      required double v,
      required double sigma,
      int? seed})
      : assert(row > 0 && column > 0 && v >= 0 && sigma >= 0) {
    this.self = matply__init__point__data__(row, column,
        matply__rice(row, column, v, sigma, seed ?? 0, seed != null), nullptr);
  }

  // 逆高斯分布（沃德分布）
  MatrixType.wald(
      {required int row,
      required int column,
      required double mu,
      required double sigma,
      int? seed})
      : assert(row > 0 && column > 0 && mu >= 0 && sigma >= 0) {
    this.self = matply__init__point__data__(row, column,
        matply__wald(row, column, mu, sigma, seed ?? 0, seed != null), nullptr);
  }

  /// setter && getter
  bool get identityMatrix => this.self.ref.spc.ref.identityMatrix;
  set identityMatrix(bool value) =>
      this.self.ref.spc.ref.identityMatrix = value;

  bool get principalDiagonalMatrix =>
      this.self.ref.spc.ref.principalDiagonalMatrix;
  set principalDiagonalMatrix(bool value) =>
      this.self.ref.spc.ref.principalDiagonalMatrix = value;

  bool get upperTriangularMatrix => this.self.ref.spc.ref.upperTriangularMatrix;
  set upperTriangularMatrix(bool value) =>
      this.self.ref.spc.ref.upperTriangularMatrix = value;

  bool get subDiagonalMatrix => this.self.ref.spc.ref.subDiagonalMatrix;
  set subDiagonalMatrix(bool value) =>
      this.self.ref.spc.ref.subDiagonalMatrix = value;

  bool get lowerTriangularMatrix => this.self.ref.spc.ref.lowerTriangularMatrix;
  set lowerTriangularMatrix(bool value) =>
      this.self.ref.spc.ref.lowerTriangularMatrix = value;

  bool get singularMatrix => this.self.ref.spc.ref.singularMatrix;
  set singularMatrix(bool value) =>
      this.self.ref.spc.ref.singularMatrix = value;

  List<int> get shape => [this.self.ref.row, this.self.ref.column];
  int get size => shape[0] * shape[1];
  bool get isSquare => shape[0] == shape[1];
  MatrixType get deepcopy => MatrixType.__fromDataPointer(
      matply__deepcopy(shape[0], shape[1], self.ref.data), shape);
      
  set At((int row, int column, double value) setter){
    int row = setter.$1;
    int column = setter.$2;
    double value = setter.$3;
    this.self.ref.data[row][column] = value;
  }

  /// Overloading Operators
  Object operator [](Object indice) {
    if (indice is int) {
      if (indice >= 0 && indice < shape[0]) {
        Pointer<Double> op = matply__row_(indice, shape[1], self.ref.data);
        List<double> list = op.asTypedList(shape[1]).toList();
        matply__freeOp(op.cast<Void>());
        return list;
      } else
        throw row_outRange;
    } else if (indice is (int,)) {
      return slice(from: indice.$1, to: null);
    } else if (indice is (int, int?)) {
      return slice(from: indice.$1, to: indice.$2);
    } else if (indice is List && indice.length == 2) {
      return at(indice[0], indice[1]);
    } else
      throw UnsupportedError('Unsupported indexing method.');
  }

  MatrixType operator +(Object other) {
    if (other is num) {
      return this.add(number: other.toDouble());
    } else if (other is MatrixType) {
      return this.add(other: other);
    } else {
      throw UnsupportedError(
          'Unsupported operand type for +: ${other.runtimeType}');
    }
  }

  MatrixType operator -(Object other) {
    if (other is num) {
      return this.minus(number: other.toDouble());
    } else if (other is MatrixType) {
      return this.minus(other: other);
    } else {
      throw UnsupportedError(
          'Unsupported operand type for -: ${other.runtimeType}');
    }
  }

  MatrixType operator -() => this * -1;

  MatrixType operator /(num number) => divide(number.toDouble());

  MatrixType operator *(Object other) {
    if (other is num) {
      return this.multiply(number: other.toDouble());
    } else if (other is MatrixType) {
      return this.multiply(other: other);
    } else {
      throw UnsupportedError(
          'Unsupported operand type for *: ${other.runtimeType}');
    }
  }

  MatrixType operator >>(List<int> shape) =>
      reshape(row: shape[0], column: shape[1]);
  void operator <<(List<int> shape) =>
      reshape_no_returned(row: shape[0], column: shape[1]);

  @Alert(
      'The == operator is only used to determine whether the properties of the objects are the same. '
      'If you only want to compare data, use the compare method and set mode to 0.'
  )
  @override
  bool operator ==(Object other) {
    if (identical(this, other)) return true;
    if (other is! MatrixType) return false;
    final MatrixType otherMatrix = other;
    return hasSameShape(otherMatrix) &&
        matply__data__isSame(
            shape[0], shape[1], self.ref.data, otherMatrix.self.ref.data) &&
        matply__spc__isSame(self.ref.spc, otherMatrix.self.ref.spc);
  }

  List<List<bool>> operator >(MatrixType other) => compare(other, mode: 1);
  List<List<bool>> operator <(MatrixType other) => compare(other, mode: 2);
  List<List<bool>> operator <=(MatrixType other) => compare(other, mode: 3);
  List<List<bool>> operator >=(MatrixType other) => compare(other, mode: 4);
}
