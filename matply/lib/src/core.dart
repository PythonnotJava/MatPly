import 'dart:ffi';
import 'dart:math';
import 'package:ffi/ffi.dart';
import 'dart:io' show Directory;
import 'package:path/path.dart' as path;

part 'matply_api.dart';
part 'matrix_type.dart';
part 'list_extend.dart';
part 'errors.dart';

/// Global functions
void set_visible_round(String format) => matply__set__visible__round(format.toNativeUtf8());
String get_visible_round() => matply__get__visible__round().toDartString();

void set_round(double number) => matply__set__round(number);
double get_round() => matply__get__round();

void set_seed(int seed) => matply__setSeed(seed);

final class Alert{
  final String info;
  const Alert(this.info);
}

/// Auxiliary functions
void _setSpecialAttributes(MatrixType matrixType,
{
  bool identityMatrix = false,
  bool principalDiagonalMatrix = false,
  bool subDiagonalMatrix = false,
  bool upperTriangularMatrix = false,
  bool lowerTriangularMatrix = false,
  bool singularMatrix = false
}) {
  matrixType
    ..identityMatrix = identityMatrix
    ..upperTriangularMatrix = upperTriangularMatrix
    ..lowerTriangularMatrix = lowerTriangularMatrix
    ..singularMatrix = singularMatrix
    ..subDiagonalMatrix = subDiagonalMatrix
    ..principalDiagonalMatrix = principalDiagonalMatrix;
}

typedef void DefaultSpc(MatrixType matrixType, {
  bool identityMatrix, bool principalDiagonalMatrix, bool subDiagonalMatrix,
  bool upperTriangularMatrix, bool lowerTriangularMatrix, bool singularMatrix}
);

final DefaultSpc defaultSpc = _setSpecialAttributes;
