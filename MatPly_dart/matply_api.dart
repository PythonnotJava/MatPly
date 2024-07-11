import 'dart:ffi';
import 'dart:io' show Directory;
import 'package:ffi/ffi.dart';
import 'package:path/path.dart' as path;

final dylib = DynamicLibrary.open(path.join(Directory.current.path, '../', 'matply.dll'));

Pointer<Double> _Pi = dylib.lookup('PI').cast<Double>();
Pointer<Double> _e = dylib.lookup('e').cast<Double>();
Pointer<Double> _nan = dylib.lookup('_nan').cast<Double>();
Pointer<Double> _inf = dylib.lookup('inf').cast<Double>();

typedef set__round__base__ffi = Void Function(Pointer<Utf8> new_round);
typedef set__round__base = void Function(Pointer<Utf8> new_round);

final set__round__base matply__set__round = dylib.lookupFunction<set__round__base__ffi, set__round__base>('set_round');

// 定义与SpecialAttributes结构体对应的Dart结构体
final class SpecialAttributes extends Struct {
  @Bool()
  external bool identityMatrix;

  @Bool()
  external bool principalDiagonalMatrix;

  @Bool()
  external bool subDiagonalMatrix;

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

typedef transpose__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix);
typedef transpose__base = Pointer<Matrix> Function(Pointer<Matrix> matrix);

typedef exchangeR__base__ffi = Void Function(Int32 row1, Int32 row2, Pointer<Matrix> matrix);
typedef exchangeR__base = void Function(int row1, int row2, Pointer<Matrix> matrix);

typedef multiplyR__base__ffi = Void Function(Int32 row, Double size, Pointer<Matrix> matrix);
typedef multiplyR__base = void Function(int row, double size, Pointer<Matrix> matrix);

typedef addR__base__ffi = Void Function(Int32 row1, Int32 row2, Double size, Pointer<Matrix> matrix);
typedef addR__base = void Function(int row1, int row2, double size, Pointer<Matrix> matrix);

typedef exchangeC__base__ffi = Void Function(Int32 column1, Int32 column2, Pointer<Matrix> matrix);
typedef exchangeC__base = void Function(int column1, int column2, Pointer<Matrix> matrix);

typedef multiplyC__base__ffi = Void Function(Int32 column, Double size, Pointer<Matrix> matrix);
typedef multiplyC__base = void Function(int column, double size, Pointer<Matrix> matrix);

typedef addC__base__ffi = Void Function(Int32 column1, Int32 column2, Double size, Pointer<Matrix> matrix);
typedef addC__base = void Function(int column1, int column2, double size, Pointer<Matrix> matrix);

typedef addNumber__base__ffi = Pointer<Matrix> Function(Double number, Pointer<Matrix> matrix);
typedef addNumber__base = Pointer<Matrix> Function(double number, Pointer<Matrix> matrix);

typedef addNumberNoReturned__base__ffi = Void Function(Double number, Pointer<Matrix> matrix);
typedef addNumberNoReturned__base = void Function(double number, Pointer<Matrix> matrix);

typedef addMatrix__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);
typedef addMatrix__base = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);

typedef addMatrixNoReturned__base__ffi = Void Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);
typedef addMatrixNoReturned__base = void Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);

typedef minusMatrix__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);
typedef minusMatrix__base = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);

typedef minusMatrixNoReturned__base__ffi = Void Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);
typedef minusMatrixNoReturned__base = void Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);

typedef matmul__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);
typedef matmul__base = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);

typedef multiplyMatrixNoReturned__base__ffi = Void Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);
typedef multiplyMatrixNoReturned__base = void Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);

typedef multiplyMatrix__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);
typedef multiplyMatrix__base = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);

typedef multiplyNumberNoReturned__base__ffi = Void Function(Double number, Pointer<Matrix> matrix);
typedef multiplyNumberNoReturned__base = void Function(double number, Pointer<Matrix> matrix);

typedef multiplyNumber__base__ffi = Pointer<Matrix> Function(Double number, Pointer<Matrix> matrix);
typedef multiplyNumber__base = Pointer<Matrix> Function(double number, Pointer<Matrix> matrix);

typedef kronecker__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);
typedef kronecker__base = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);

typedef divide__base__ffi = Pointer<Matrix> Function(Double number, Pointer<Matrix> matrix);
typedef divide__base = Pointer<Matrix> Function(double number, Pointer<Matrix> matrix);

typedef divideNoReturned__base__ffi = Void Function(Double number, Pointer<Matrix> matrix);
typedef divideNoReturned__base = void Function(double number, Pointer<Matrix> matrix);

typedef arrange__base__ffi = Pointer<Matrix> Function(Double start, Int32 row, Int32 column);
typedef arrange__base = Pointer<Matrix> Function(double start, int row, int column);

typedef linspace__base__ffi = Pointer<Matrix> Function(Double start, Double end, Int32 row, Int32 column, Bool keep);
typedef linspace__base = Pointer<Matrix> Function(double start, double end, int row, int column, bool keep);

typedef trace__base__ffi = Double Function(Pointer<Matrix> matrix);
typedef trace__base = double Function(Pointer<Matrix> matrix);

typedef det__base__ffi = Double Function(Pointer<Matrix> matrix);
typedef det__base = double Function(Pointer<Matrix> matrix);

typedef E__base__ffi = Pointer<Matrix> Function(Int32 n);
typedef E__base = Pointer<Matrix> Function(int n);

typedef cofactor__base__ffi = Pointer<Matrix> Function(Int32 row, Int32 column, Pointer<Matrix> matrix);
typedef cofactor__base = Pointer<Matrix> Function(int row, int column, Pointer<Matrix> matrix);

typedef inverse__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix, Double det);
typedef inverse__base = Pointer<Matrix> Function(Pointer<Matrix> matrix, double det);

typedef adjugate__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix);
typedef adjugate__base = Pointer<Matrix> Function(Pointer<Matrix> matrix);

typedef deepcopy__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix);
typedef deepcopy__base = Pointer<Matrix> Function(Pointer<Matrix> matrix);

typedef compare__base__ffi = Pointer<Pointer<Bool>> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2, Int32 mode);
typedef compare__base = Pointer<Pointer<Bool>> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2, int mode);

typedef sum__base__ffi = Pointer<Double> Function(Pointer<Matrix> matrix, Int32 dim);
typedef sum__base = Pointer<Double> Function(Pointer<Matrix> matrix, int dim);

typedef mean__base__ffi = Pointer<Double> Function(Pointer<Matrix> matrix, Int32 dim);
typedef mean__base = Pointer<Double> Function(Pointer<Matrix> matrix, int dim);

typedef min__base__ffi = Pointer<Double> Function(Pointer<Matrix> matrix, Int32 dim);
typedef min__base = Pointer<Double> Function(Pointer<Matrix> matrix, int dim);

typedef max__base__ffi = Pointer<Double> Function(Pointer<Matrix> matrix, Int32 dim);
typedef max__base = Pointer<Double> Function(Pointer<Matrix> matrix, int dim);

typedef data_isSame__base__ffi = Bool Function(Pointer<Pointer<Double>> data1, Pointer<Pointer<Double>> data2, Int32 row, Int32 column);
typedef data_isSame__base = bool Function(Pointer<Pointer<Double>> data1, Pointer<Pointer<Double>> data2, int row, int column);

typedef spc__isSame__base__ffi = Bool Function(Pointer<SpecialAttributes> spc1, Pointer<SpecialAttributes> spc2);
typedef spc__isSame__base = bool Function(Pointer<SpecialAttributes> spc1, Pointer<SpecialAttributes> spc2);

typedef cut__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix, Int32 row, Int32 column, Int32 width, Int32 height);
typedef cut__base = Pointer<Matrix> Function(Pointer<Matrix> matrix, int row, int column, int width, int height);

typedef cutfree__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix, Int32 row, Int32 column, Int32 width, Int32 height, Double number);
typedef cutfree__base = Pointer<Matrix> Function(Pointer<Matrix> matrix, int row, int column, int width, int height, double number);

typedef concatR__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);
typedef concatR__base = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);

typedef concatC__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);
typedef concatC__base = Pointer<Matrix> Function(Pointer<Matrix> matrix1, Pointer<Matrix> matrix2);

typedef resizeR__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix, Int32 row, Int32 column, Double number);
typedef resizeR__base = Pointer<Matrix> Function(Pointer<Matrix> matrix, int row, int column, double number);

typedef resizeC__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix, Int32 row, Int32 column, Double number);
typedef resizeC__base = Pointer<Matrix> Function(Pointer<Matrix> matrix, int row, int column, double number);

typedef reshape__base__ffi = Pointer<Matrix> Function(Pointer<Matrix> matrix, Int32 row, Int32 column);
typedef reshape__base = Pointer<Matrix> Function(Pointer<Matrix> matrix, int row, int column);

typedef resizeRNoReturned__base__ffi = Void Function(Pointer<Matrix> matrix, Int32 row, Int32 column, Double number);
typedef resizeRNoReturned__base = void Function(Pointer<Matrix> matrix, int row, int column, double number);

typedef resizeCNoReturned__base__ffi = Void Function(Pointer<Matrix> matrix, Int32 row, Int32 column, Double number);
typedef resizeCNoReturned__base = void Function(Pointer<Matrix> matrix, int row, int column, double number);

typedef reshapeNoReturned__base__ffi = Void Function(Pointer<Matrix> matrix, Int32 row, Int32 column);
typedef reshapeNoReturned__base = void Function(Pointer<Matrix> matrix, int row, int column);

typedef setSeed__base__ffi = Void Function(Int32 seed);
typedef setSeed__base = void Function(int seed);

typedef mathBasement1__base__ffi = Pointer<Void> Function(Pointer<Pointer<Double>>, Int32 mode, Int32 row, Int32 column, Bool returnArray);
typedef mathBasement1__base = Pointer<void> Function(Pointer<Pointer<Double>>, int mode, int row, int column, bool returnArray);

typedef mathBasement2__base__ffi = Pointer<Void> Function(Pointer<Pointer<Double>>, Int32 mode, Double number, Int32 row, Int32 column, Bool returnArray);
typedef mathBasement2__base = Pointer<void> Function(Pointer<Pointer<Double>>, int mode, double number, int row, int column, bool returnArray);

typedef mathBasement2reverse__base__ffi = Pointer<Void> Function(Pointer<Pointer<Double>>, Int32 mode, Double number, Int32 row, Int32 column, Bool returnArray);
typedef mathBasement2reverse__base = Pointer<void> Function(Pointer<Pointer<Double>>, int mode, double number, int row, int column, bool returnArray);

typedef allocateButNoNumbers__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column);
typedef allocateButNoNumbers__base = Pointer<Pointer<Double>> Function(int row, int column);

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
final transpose__base matply__transpose = dylib.lookup<NativeFunction<transpose__base__ffi>>('transpose').asFunction<transpose__base>();
final exchangeR__base matply__exchangeR = dylib.lookup<NativeFunction<exchangeR__base__ffi>>('exchangeR').asFunction<exchangeR__base>();
final multiplyR__base matply__multiplyR = dylib.lookup<NativeFunction<multiplyR__base__ffi>>('multiplyR').asFunction<multiplyR__base>();
final addR__base matply__addR = dylib.lookup<NativeFunction<addR__base__ffi>>('addR').asFunction<addR__base>();
final addC__base matply__addC = dylib.lookup<NativeFunction<addC__base__ffi>>('addC').asFunction<addC__base>();
final exchangeC__base matply__exchangeC = dylib.lookup<NativeFunction<exchangeC__base__ffi>>('exchangeC').asFunction<exchangeC__base>();
final multiplyC__base matply__multiplyC = dylib.lookup<NativeFunction<multiplyC__base__ffi>>('multiplyC').asFunction<multiplyC__base>();
final addNumber__base matply__addNumber = dylib.lookup<NativeFunction<addNumber__base__ffi>>('addNumber').asFunction<addNumber__base>();
final addNumberNoReturned__base matply__addNumberNoReturned = dylib.lookup<NativeFunction<addNumberNoReturned__base__ffi>>('addNumberNoReturned').asFunction<addNumberNoReturned__base>();
final addMatrix__base matply__addMatrix = dylib.lookup<NativeFunction<addMatrix__base__ffi>>('addMatrix').asFunction<addMatrix__base>();
final addMatrixNoReturned__base matply__addMatrixNoReturned = dylib.lookup<NativeFunction<addMatrixNoReturned__base__ffi>>('addMatrixNoReturned').asFunction<addMatrixNoReturned__base>();
final minusMatrix__base matply__minusMatrix = dylib.lookup<NativeFunction<minusMatrix__base__ffi>>('minusMatrix').asFunction<minusMatrix__base>();
final minusMatrixNoReturned__base matply__minusMatrixNoReturned = dylib.lookup<NativeFunction<minusMatrixNoReturned__base__ffi>>('minusMatrixNoReturned').asFunction<minusMatrixNoReturned__base>();
final matmul__base matply__matmul = dylib.lookup<NativeFunction<matmul__base__ffi>>('matmul').asFunction<matmul__base>();
final multiplyMatrixNoReturned__base matply__multiplyMatrixNoReturned = dylib.lookup<NativeFunction<multiplyMatrixNoReturned__base__ffi>>('multiplyMatrixNoReturned').asFunction<multiplyMatrixNoReturned__base>();
final multiplyMatrix__base matply__multiplyMatrix = dylib.lookup<NativeFunction<multiplyMatrix__base__ffi>>('multiplyMatrix').asFunction<multiplyMatrix__base>();
final multiplyNumberNoReturned__base matply__multiplyNumberNoReturned = dylib.lookup<NativeFunction<multiplyNumberNoReturned__base__ffi>>('multiplyNumberNoReturned').asFunction<multiplyNumberNoReturned__base>();
final multiplyNumber__base matply__multiplyNumber = dylib.lookup<NativeFunction<multiplyNumber__base__ffi>>('multiplyNumber').asFunction<multiplyNumber__base>();
final kronecker__base matply__kronecker = dylib.lookup<NativeFunction<kronecker__base__ffi>>('kronecker').asFunction<kronecker__base>();
final divide__base matply__divide = dylib.lookup<NativeFunction<divide__base__ffi>>('divide').asFunction<divide__base>();
final divideNoReturned__base matply__divideNoReturned = dylib.lookup<NativeFunction<divideNoReturned__base__ffi>>('divideNoReturned').asFunction<divideNoReturned__base>();
final arrange__base matply__arrange = dylib.lookup<NativeFunction<arrange__base__ffi>>('arrange').asFunction<arrange__base>();
final linspace__base matply__linspace = dylib.lookup<NativeFunction<linspace__base__ffi>>('linspace').asFunction<linspace__base>();
final trace__base matply__trace = dylib.lookup<NativeFunction<trace__base__ffi>>('trace').asFunction<trace__base>();
final det__base matply__det = dylib.lookup<NativeFunction<det__base__ffi>>('det').asFunction<det__base>();
final E__base matply__E = dylib.lookup<NativeFunction<E__base__ffi>>('E').asFunction<E__base>();
final cofactor__base matply__cofacto = dylib.lookup<NativeFunction<cofactor__base__ffi>>('cofactor').asFunction<cofactor__base>();
final inverse__base matply__inverse = dylib.lookup<NativeFunction<inverse__base__ffi>>('inverse').asFunction<inverse__base>();
final adjugate__base matply__adjugate = dylib.lookup<NativeFunction<adjugate__base__ffi>>('adjugate').asFunction<adjugate__base>();
final deepcopy__base matply__deepcopy = dylib.lookup<NativeFunction<deepcopy__base__ffi>>('deepcopy').asFunction<deepcopy__base>();
final compare__base matply__compare = dylib.lookup<NativeFunction<compare__base__ffi>>('compare').asFunction<compare__base>();
final sum__base matply__sum = dylib.lookup<NativeFunction<sum__base__ffi>>('sum').asFunction<sum__base>();
final mean__base matply__mean = dylib.lookup<NativeFunction<mean__base__ffi>>('mean').asFunction<mean__base>();
final max__base matply__max = dylib.lookup<NativeFunction<max__base__ffi>>('max').asFunction<max__base>();
final min__base matply__min = dylib.lookup<NativeFunction<min__base__ffi>>('min').asFunction<min__base>();
final data_isSame__base matply__data__isSame = dylib.lookup<NativeFunction<data_isSame__base__ffi>>('data_isSame').asFunction<data_isSame__base>();
final spc__isSame__base matply__spc__isSame = dylib.lookup<NativeFunction<spc__isSame__base__ffi>>('spc__isSame').asFunction<spc__isSame__base>();
final cut__base matply__cut = dylib.lookup<NativeFunction<cut__base__ffi>>('cut').asFunction<cut__base>();
final cutfree__base matply__cutfree = dylib.lookup<NativeFunction<cutfree__base__ffi>>('cutfree').asFunction<cutfree__base>();
final concatR__base matply__concatR = dylib.lookup<NativeFunction<concatR__base__ffi>>('concatR').asFunction<concatR__base>();
final concatC__base matply__concatC = dylib.lookup<NativeFunction<concatC__base__ffi>>('concatC').asFunction<concatC__base>();
final resizeR__base matply__resizeR = dylib.lookup<NativeFunction<resizeR__base__ffi>>('resizeR').asFunction<resizeR__base>();
final resizeC__base matply__resizeC = dylib.lookup<NativeFunction<resizeC__base__ffi>>('resizeC').asFunction<resizeC__base>();
final reshape__base matply__reshape = dylib.lookup<NativeFunction<reshape__base__ffi>>('reshape').asFunction<reshape__base>();
final resizeRNoReturned__base matply__resizeRNoReturned = dylib.lookup<NativeFunction<resizeRNoReturned__base__ffi>>('resizeRNoReturned').asFunction<resizeRNoReturned__base>();
final resizeCNoReturned__base matply__resizeCNoReturned = dylib.lookup<NativeFunction<resizeCNoReturned__base__ffi>>('resizeCNoReturned').asFunction<resizeCNoReturned__base>();
final reshapeNoReturned__base matply__reshapeNoReturned = dylib.lookup<NativeFunction<reshapeNoReturned__base__ffi>>('reshapeNoReturned').asFunction<reshapeNoReturned__base>();
final setSeed__base matply__setSeed = dylib.lookup<NativeFunction<setSeed__base__ffi>>('setSeed').asFunction<setSeed__base>();
final mathBasement1__base matply__mathBasement1 = dylib.lookup<NativeFunction<mathBasement1__base__ffi>>('mathBasement1').asFunction<mathBasement1__base>();
final mathBasement2__base matply__mathBasement2 = dylib.lookup<NativeFunction<mathBasement2__base__ffi>>('mathBasement2').asFunction<mathBasement2__base>();
final mathBasement2reverse__base matply__mathBasement2reverse = dylib.lookup<NativeFunction<mathBasement2reverse__base__ffi>>('mathBasement2reverse').asFunction<mathBasement2reverse__base>();
final allocateButNoNumbers__base matply__allocateButNoNumbers = dylib.lookup<NativeFunction<allocateButNoNumbers__base__ffi>>('allocateButNoNumbers').asFunction<allocateButNoNumbers__base>();

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

final double Pi = _Pi.value;
final double e = _e.value;
final double inf = _inf.value;  // 正无穷大，和Dart的内置相通，下同
final double negativeinf = -inf;  // 负无穷大
final double nan = _nan.value;  // 非法数据