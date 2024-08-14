import 'dart:ffi';
import 'dart:math';
import 'package:ffi/ffi.dart';
import 'dart:io' show Platform, Directory;
import 'package:path/path.dart' as path;

part 'matply_api.dart';
part 'matrix_type.dart';
part 'list_extend.dart';
part 'errors.dart';
part 'matrix_type_linalg.dart';
part 'matrix_type_pure_math.dart';
part 'matrix_type_random.dart';
part 'matrix_type_visualization.dart';
part 'matrix_type_func_condition.dart';
part 'cpp_extension/matply_type_cpp_extension.dart';
part 'cpp_extension/matply_type_cpp_api.dart';

/// Global functions
void set_visible_round(String format) => matply__set__visible__round(format.toNativeUtf8());
String get_visible_round() => matply__get__visible__round().toDartString();

void set_round(double number) => matply__set__round(number);
double get_round() => matply__get__round();

/// simple-random
void set_seed(int seed) => matply__setSeed(seed);
extension RandomExtension on Random{
  void setSeed(int seed) => seed > 0 ? matply__setSeed(seed) : matply_initialize_random_seed();

  double random() => matply_random();

  int randint(double lb, double ub){
    assert(lb < ub);
    return matply_randint(lb, ub);
  }

  double randn(double lb, double ub){
    assert(lb < ub);
    return matply_randdouble(lb, ub);
  }

  void shuffle<T>(List<T> list) => list.shuffle();

  Object choice({required List<double> arr, List<double>? p, int? times, bool? back, int? method}){
    int len = arr.length;
    if (p == null && times == null && back == null && method == null){
      Pointer<Double> op = oneListToArray(arr);
      double value = matply_random_choice(op, len);
      malloc.free(op);
      return value;
    }else if(p == null && times != null && back != null){
      assert(times >= 0);
      times = times != 0? times : len;
      Pointer<Double> op1 = oneListToArray(arr);
      Pointer<Double> op2 = matply_random_choices(op1, len, times, back);
      List<double> value = op2.asTypedList(len).toList();
      malloc.free(op1);
      malloc.free(op2);
      return value;
    }else if(p != null && times != null && back != null && method != null){
      assert(times >= 0 && p.length == len);
      times = times != 0? times : len;
      Pointer<Double> op1 = oneListToArray(arr);
      Pointer<Double> op2 = oneListToArray(p);
      Pointer<Double> op3 = matply_perfect_choices(op1, op2, len, times, back, method);
      List<double> value = op3.asTypedList(len).toList();
      malloc.free(op1);
      malloc.free(op2);
      malloc.free(op3);
      return value;
    }else
      throw UnsupportedError('Confusing parameter matching');
  }
}

/// 对误会以及不建议内容的警告
final class Alert{
  final String info;
  const Alert(this.info);
}

/// 做出特大更新的标志
final class Since {
  final String info;
  const Since(this.info);
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

