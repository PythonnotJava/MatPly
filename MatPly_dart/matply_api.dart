import 'dart:ffi';
import 'dart:io' show Directory;
import 'package:ffi/ffi.dart';
import 'package:path/path.dart' as path;

final dylib = DynamicLibrary.open(path.join(Directory.current.path, '../', 'matbox.dll'));

// 定义与SpecialAttributes结构体对应的Dart结构体
final class SpecialAttributes extends Struct {
  @Bool()
  external bool identityMatrix;

  @Bool()
  external bool principalDiagonalMatrix;

  @Bool()
  external bool subdiagonalMatrix;

  @Bool()
  external bool upperTriangularMatrix;

  @Bool()
  external bool lowerTriangularMatrix;

  @Bool()
  external bool singularMatrix;
}

// 定义与Matrix结构体对应的Dart结构体
final class Matrix extends Struct {
  @Int32()
  external int row;

  @Int32()
  external int column;

  external Pointer<SpecialAttributes> spc;

  external Pointer<Pointer<Double>> data;
}

// 定义DLL中的函数
typedef __new__base__ffi = Pointer<Matrix> Function(Int32 row, Int32 column);
typedef __new__base = Pointer<Matrix> Function(int row, int column);

typedef __init__base__ffi = Pointer<Matrix> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Pointer<SpecialAttributes> spc);
typedef __init__base = Pointer<Matrix> Function(int row, int column, Pointer<Pointer<Double>> data, Pointer<SpecialAttributes> spc);

typedef VisibleMatrix__base__ffi = Void Function(Pointer<Matrix> matrix);
typedef VisibleMatrix__base = void Function(Pointer<Matrix> matrix);

typedef __delete__base__ffi = Void Function(Pointer<Matrix> matrix);
typedef __delete__base = void Function(Pointer<Matrix> matrix);

typedef filled__base__ffi = Pointer<Matrix> Function(Int32 row, Int32 column, Double number);
typedef filled__base = Pointer<Matrix> Function(int row, int column, double number);

typedef zeros__base__ffi = Pointer<Matrix> Function(Int32 row, Int32 column);
typedef zeros__base = Pointer<Matrix> Function(int row, int column);

typedef ones__base__ffi = Pointer<Matrix> Function(Int32 row, Int32 column);
typedef ones__base = Pointer<Matrix> Function(int row, int column);

typedef VisibleMatrixSpc__base__ffi = Void Function(Pointer<Matrix> matrix);
typedef VisibleMatrixSpc__base = void Function(Pointer<Matrix> matrix);

typedef row__base__ffi = Pointer<Double> Function(Int32 row, Pointer<Matrix> matrix);
typedef row__base = Pointer<Double> Function(int row, Pointer<Matrix> matrix);

typedef column__base__ffi = Pointer<Double> Function(Int32 column, Pointer<Matrix> matrix);
typedef column__base = Pointer<Double> Function(int column, Pointer<Matrix> matrix);

typedef at__base__ffi = Double Function(Int32 row, Int32 column, Pointer<Matrix> matrix);
typedef at__base = double Function(int row, int column, Pointer<Matrix> matrix);

final __new__base matply__new__ = dylib.lookup<NativeFunction<__new__base__ffi>>('__new__').asFunction<__new__base>();
final __init__base matply__init__ = dylib.lookup<NativeFunction<__init__base__ffi>>('__init__').asFunction<__init__base>();
final VisibleMatrix__base matply__VisibleMatrix = dylib.lookup<NativeFunction<VisibleMatrix__base__ffi>>('VisibleMatrix').asFunction<VisibleMatrix__base>();
final __delete__base matply__delete__ = dylib.lookup<NativeFunction<__delete__base__ffi>>('__delete__').asFunction<__delete__base>();
final filled__base matply__filled = dylib.lookup<NativeFunction<filled__base__ffi>>('filled').asFunction<filled__base>();
final zeros__base matply__zeros = dylib.lookup<NativeFunction<zeros__base__ffi>>('zeros').asFunction<zeros__base>();
final ones__base matply__ones = dylib.lookup<NativeFunction<ones__base__ffi>>('ones').asFunction<ones__base>();
final VisibleMatrixSpc__base matply__VisibleMatrixSpc = dylib.lookup<NativeFunction<VisibleMatrixSpc__base__ffi>>('VisibleMatrixSpc').asFunction<VisibleMatrixSpc__base>();
final row__base matply__row_ = dylib.lookup<NativeFunction<row__base__ffi>>('row_').asFunction<row__base>();
final column__base matply__column_ = dylib.lookup<NativeFunction<column__base__ffi>>('column_').asFunction<column__base>();
final at__base matply__at = dylib.lookup<NativeFunction<at__base__ffi>>('at').asFunction<at__base>();

dynamic debug_matply_api<T>(T Function() func, [String info = 'Error Here']) {
  try {
    return func();
  } catch (e) {
    print('$info: ${e.toString()}');
  }
}

// 将二维数组转为二级指针
Pointer<Pointer<Double>> toMatrixPPointerData(List<List<double>> data, int row, int column){
  final dataPointer = malloc<Pointer<Double>>(row);
  for (int r = 0; r < row; r++) {
    dataPointer[r] = malloc<Double>(column);
    for (int j = 0; j < column; j++) {
      dataPointer[r][j] = data[r][j];
    }
  }
  return dataPointer;
}

