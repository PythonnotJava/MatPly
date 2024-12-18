import 'dart:async';
import 'dart:ffi';
import 'dart:io';
import 'dart:math' as math;
import 'package:ffi/ffi.dart';
import 'package:path/path.dart' as path;

part 'list_extend.dart';
part 'errors.dart';
part 'matply_api.dart';
part 'matply_test.dart';
part 'matrix_type.dart';
part 'matply_type_basement.dart';
part 'matrix_type_linalg.dart';
part 'matrix_type_pure_math.dart';
part 'matrix_type_random.dart';
part 'matrix_type_visualization.dart';
part 'matrix_type_func_condition.dart';

part 'cpp_extension/matply_type_cpp_extension.dart';
part 'cpp_extension/matply_type_cpp_api.dart';

/// Global functions
late final int Function() getInstances = dylib.lookupFunction<Int32 Function(), int Function()>('getInstances');
void initMp({Pointer<Matrix>? matrix}) => __initMp(matrix?? nullptr);
void freeMp({bool visible = false, bool hex = true}) => __freeMp(visible, hex);

void set_visible_round(String format) => matply__set__visible__round(format.toNativeUtf8());
String get_visible_round() => matply__get__visible__round().toDartString();

void set_round(double number) => matply__set__round(number);
double get_round() => matply__get__round();
void set_seed(int seed) => matply__setSeed(seed);

// Deleted from V1.10
// void set_mult_rand(bool multi) {matply__set_mult_rand(multi);}
// bool get_mult_rand() {return matply__get_mult_rand();}

void set_max_thread_support(int n) => matply_set_max_thread_support(n);
int get_max_thread_support() => matply_get_max_thread_support();
int get_max_thread_sys() => matply_get_max_thread_sys();
void set_simple_dvcst_value(int n) => matply_set_simple_dvcst_value(n);
int get_simple_dvcst_value() => matply_get_simple_dvcst_value();
void set_complex_dvcst_value(int n) => matply_set_complex_dvcst_value(n);
int get_complex_dvcst_value() => matply_get_complex_dvcst_value();
double get_time() => matply_get_time();  // 可以使用DateTime代替
void set_multp_shown(bool show) => matply_set_multp_shown(show);
bool get_multp_shown() => matply__get_multp_shown();
void set_simple_dvcst_value_force(int n) => matply_set_simple_dvcst_value_force(n);
void set_complex_dvcst_value_force(int n) => matply_set_complex_dvcst_value_force(n);

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
