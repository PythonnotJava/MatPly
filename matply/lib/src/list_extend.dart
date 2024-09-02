part of 'core.dart';

/// extension for List.Test from V1.0.2
/// Established extension from V1.0.8

/// Extension for List operations, supporting both int and double types
extension ListExtensions<T extends num> on List<T> {
  /// Convert the list to a list of doubles
  List<double> get toDoubleList => this.map((i) => i.toDouble()).toList();

  /// Get a pointer to the data in the list
  Pointer<Double> getOnePointer({bool methed_is_malloc = true}) {
    Pointer<Double> op = methed_is_malloc
        ? malloc<Double>(length * sizeOf<Double>())
        : calloc<Double>(length * sizeOf<Double>());
    for (int i = 0; i < length; i++) {
      op[i] = this[i].toDouble();
    }
    return op;
  }

  /// Reshape the list into a matrix
  MatrixType reshape({required int row, required int column}) {
    assert(row > 0 && column > 0);
    if (length == column * row) {
      var op = getOnePointer();
      MatrixType mt = MatrixType.__fromDataPointer(
          matply__oneTotwoArray(op, row, column), [row, column]);
      malloc.free(op);
      return mt;
    } else {
      throw different_shape;
    }
  }
}

/// Extension for 2D List operations, supporting both int and double types
extension TwoDimListExtensions<T extends num> on List<List<T>> {
  int get row => this.length;
  int get column => this[0].length;
  List<int> get shape => [row, column];

  /// Convert the 2D list to a 2D list of doubles
  List<List<double>> get toDoubleList =>
      List.generate(row, (i) => this[i].toDoubleList);

  /// Get a pointer to the data in the 2D list
  Pointer<Pointer<Double>> getTwoPointer() {
    var tp = malloc<Pointer<Double>>(row * sizeOf<Pointer<Double>>());
    for (int r = 0; r < row; r++) {
      tp[r] = malloc<Double>(column * sizeOf<Double>());
      for (int j = 0; j < column; j++) {
        tp[r][j] = this[r][j].toDouble();
      }
    }
    return tp;
  }

  /// Convert the 2D list to a MatrixType by pointer
  MatrixType toMatrixTypeByPointer() => MatrixType.__fromDataPointer(getTwoPointer(), this.shape);
  /// Convert the 2D list to a MatrixType by list
  MatrixType toMatrixTypeByList() => MatrixType(toDoubleList);
}
