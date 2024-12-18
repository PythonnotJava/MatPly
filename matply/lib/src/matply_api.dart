part of 'core.dart';

String __login_platform(){
 if (Platform.isWindows) {
      return 'matply.dll';
    } else if (Platform.isLinux || Platform.isAndroid) {
      return 'libmatply.so';
    } else
      throw UnsupportedError('This platform is not supported');
}

late final String platform = __login_platform();

const VERSION = '1.1.0';

String pubCacheDir = path.join(
    Platform.environment['LOCALAPPDATA']!,
    'Pub',
    'Cache',
    'hosted',
    'pub.dev',
    'matply-$VERSION',
    'assets'
);  // 会出现依赖找不到的问题，需要查找pub下载cache路径，如果每个人不一样，可以通过设置pubCacheDir即可

late final dylib = DynamicLibrary.open(path.join(pubCacheDir, platform));

late final Pointer<Double> _Pi = dylib.lookup('PI').cast<Double>();
late final Pointer<Double> _e = dylib.lookup('e').cast<Double>();
late final Pointer<Double> _nan = dylib.lookup('_nan').cast<Double>();
late final Pointer<Double> _inf = dylib.lookup('inf').cast<Double>();
late final Pointer<Double> _euler = dylib.lookup('euler').cast<Double>();

/// global functions
typedef set__visible__round__base__ffi = Void Function(Pointer<Utf8> new_round);
typedef set__visible__round__base = void Function(Pointer<Utf8> new_round);
late final set__visible__round__base matply__set__visible__round = dylib.lookupFunction<set__visible__round__base__ffi, set__visible__round__base>('set_visible_round');

typedef set__round__base__ffi = Void Function(Double number);
typedef set__round__base = void Function(double number);
late final set__round__base matply__set__round = dylib.lookupFunction<set__round__base__ffi, set__round__base>('set_round');

typedef get__visible__round__base__ffi = Pointer<Utf8> Function();
typedef get__visible__round__base = Pointer<Utf8> Function();
late final get__visible__round__base matply__get__visible__round = dylib.lookupFunction<get__visible__round__base__ffi, get__visible__round__base>('get_visible_round');

typedef get__round__base__ffi = Double Function();
typedef get__round__base = double Function();
late final get__round__base matply__get__round = dylib.lookupFunction<get__round__base__ffi, get__round__base>('get_round');

// Deleted from V1.10
// typedef set_mult_rand__base__ffi = Void Function(Bool use);
// typedef set_mult_rand__base = void Function(bool use);
// late final set_mult_rand__base matply__set_mult_rand = dylib.lookupFunction<set_mult_rand__base__ffi, set_mult_rand__base>('set_mult_rand');
// Deleted from V1.10
// typedef get_mult_rand__base__ffi = Bool Function();
// typedef get_mult_rand__base = bool Function();
// late final get_mult_rand__base matply__get_mult_rand = dylib.lookupFunction<get_mult_rand__base__ffi, get_mult_rand__base>('get_mult_rand');

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

// 存储多个二维数组的结构体
final class MultiDatas2 extends Struct{
  external Pointer<Pointer<Double>> data1;
  external Pointer<Pointer<Double>> data2;
}

final class MultiDatas3 extends Struct{
  external Pointer<Pointer<Double>> data1;
  external Pointer<Pointer<Double>> data2;
  external Pointer<Pointer<Double>> data3;
}

final class MultiDatas4 extends Struct{
  external Pointer<Pointer<Double>> data1;
  external Pointer<Pointer<Double>> data2;
  external Pointer<Pointer<Double>> data3;
  external Pointer<Pointer<Double>> data4;
}

final class Point2D extends Struct{
  @Double()
  external double x;
  @Double()
  external double y;
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

typedef __delete__data__base__ffi = Void Function(Pointer<Pointer<Double>> data, Int32 row);
typedef __delete__data__base = void Function(Pointer<Pointer<Double>> data, int row);

typedef filled__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double number);
typedef filled__base = Pointer<Pointer<Double>> Function(int row, int column, double number);

typedef zeros__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column);
typedef zeros__base = Pointer<Pointer<Double>>Function(int row, int column);

typedef ones__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column);
typedef ones__base = Pointer<Pointer<Double>> Function(int row, int column);

typedef VisibleMatrixSpc__base__ffi = Void Function(Pointer<Matrix> matrix);
typedef VisibleMatrixSpc__base = void Function(Pointer<Matrix> matrix);

typedef row__base__ffi = Pointer<Double> Function( Int32 row,  Int32 column, Pointer<Pointer<Double>> data);
typedef row__base = Pointer<Double> Function( int row,  int column, Pointer<Pointer<Double>> data);

typedef column__base__ffi = Pointer<Double> Function( Int32 row,  Int32 column, Pointer<Pointer<Double>> data);
typedef column__base = Pointer<Double> Function( int row,  int column, Pointer<Pointer<Double>> data);

typedef at__base__ffi = Double Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data);
typedef at__base = double Function(int row, int column, Pointer<Pointer<Double>> data);

typedef transpose__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data);
typedef transpose__base = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data);

typedef exchangeR__base__ffi = Void Function(Int32 column, Pointer<Pointer<Double>> data, Int32 row1, Int32 row2);
typedef exchangeR__base = void Function(int column, Pointer<Pointer<Double>> data, int row1, int row2);

typedef multiplyR__base__ffi = Void Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Double size);
typedef multiplyR__base = void Function(int row, int column, Pointer<Pointer<Double>> data, double size);

typedef addR__base__ffi = Void Function( Int32 column, Pointer<Pointer<Double>> data, Int32 row1, Int32 row2, Double size);
typedef addR__base = void Function( int column, Pointer<Pointer<Double>> data, int row1, int row2, double size);

typedef exchangeC__base__ffi = Void Function( Int32 row, Pointer<Pointer<Double>> data, Int32 column1,Int32 column2);
typedef exchangeC__base = void Function( int row, Pointer<Pointer<Double>> data, int column1, int column2);

typedef multiplyC__base__ffi = Void Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Double size);
typedef multiplyC__base = void Function( int row, int column, Pointer<Pointer<Double>> data, double size);

typedef addC__base__ffi = Void Function(Int32 row, Pointer<Pointer<Double>> data, Int32 column1, Int32 column2, Double size);
typedef addC__base = void Function( int row, Pointer<Pointer<Double>> data, int column1, int column2, double size);

typedef addNumber__base__ffi = Pointer<Pointer<Double>> Function( Int32 row, Int32 column, Pointer<Pointer<Double>> data, Double number);
typedef addNumber__base = Pointer<Pointer<Double>> Function( int row, int column,  Pointer<Pointer<Double>> data, double number);

typedef addNumberNoReturned__base__ffi = Void Function( Int32 row,  Int32 column, Pointer<Pointer<Double>> data, Double number);
typedef addNumberNoReturned__base = void Function( int row,  int column, Pointer<Pointer<Double>> data, double number);

typedef addMatrix__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data1, Pointer<Pointer<Double>> data2);
typedef addMatrix__base = Pointer<Pointer<Double>> Function( int row, int column, Pointer<Pointer<Double>> data1, Pointer<Pointer<Double>> data2);

typedef addMatrixNoReturned__base__ffi = Void Function( Int32 row,  Int32 column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2);
typedef addMatrixNoReturned__base = void Function( int row,  int column, Pointer<Pointer<Double>> data1, Pointer<Pointer<Double>> data2);

typedef minusMatrix__base__ffi = Pointer<Pointer<Double>> Function( Int32 row, Int32, Pointer<Pointer<Double>> data1, Pointer<Pointer<Double>> data2);
typedef minusMatrix__base = Pointer<Pointer<Double>> Function( int row, int column, Pointer<Pointer<Double>> data1, Pointer<Pointer<Double>> data2);

typedef minusMatrixNoReturned__base__ffi = Void Function( Int32 row,  Int32 column, Pointer<Pointer<Double>> data1, Pointer<Pointer<Double>> data2);
typedef minusMatrixNoReturned__base = void Function( int row,  int column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2);

typedef matmul__base__ffi = Pointer<Pointer<Double>> Function( Int32 row, Int32 column,  Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2, Int32 column2);
typedef matmul__base = Pointer<Pointer<Double>> Function( int row,  int column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2, int column2);

typedef multiplyMatrixNoReturned__base__ffi = Void Function( Int32 row,  Int32 column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2);
typedef multiplyMatrixNoReturned__base = void Function( int row,  int column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2);

typedef multiplyMatrix__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2);
typedef multiplyMatrix__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2);

typedef multiplyNumberNoReturned__base__ffi = Void Function( Int32 row,  Int32 column, Pointer<Pointer<Double>> data,  Double number);
typedef multiplyNumberNoReturned__base = void Function( int row,  int column, Pointer<Pointer<Double>> data,  double number);

typedef multiplyNumber__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>> data,  Double number);
typedef multiplyNumber__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>> data,  double number);

typedef kronecker__base__ffi = Pointer<Pointer<Double>> Function( Int32 row1,  Int32 column1,  Pointer<Pointer<Double>> data1,  Int32 row2,  Int32 column2,  Pointer<Pointer<Double>> data2);
typedef kronecker__base = Pointer<Pointer<Double>> Function( int row1,  int column1,  Pointer<Pointer<Double>> data1,  int row2,  int column2,  Pointer<Pointer<Double>> data2);

typedef divide__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column, Pointer<Pointer<Double>> data,  Double number);
typedef divide__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>> data,  double number);

typedef divideNoReturned__base__ffi = Void Function( Int32 row,  Int32, Pointer<Pointer<Double>> data,  Double number);
typedef divideNoReturned__base = void Function( int row,  int column, Pointer<Pointer<Double>> data,  double number);

typedef arrange__base__ffi = Pointer<Pointer<Double>> Function(Double start, Int32 row, Int32 column);
typedef arrange__base = Pointer<Pointer<Double>> Function(double start, int row, int column);

typedef linspace__base__ffi = Pointer<Pointer<Double>> Function(Double start, Double end, Int32 row, Int32 column, Bool keep);
typedef linspace__base = Pointer<Pointer<Double>> Function(double start, double end, int row, int column, bool keep);

typedef trace__base__ffi = Double Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>> data);
typedef trace__base = double Function( int row,  int column,  Pointer<Pointer<Double>> data);

typedef det__base__ffi = Double Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>> data);
typedef det__base = double Function( int row,  int column,  Pointer<Pointer<Double>> data);

typedef E__base__ffi = Pointer<Pointer<Double>> Function(Int32 n);
typedef E__base = Pointer<Pointer<Double>> Function(int n);

typedef cofactor__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data,  Int32 prow,  Int32 pcolumn);
typedef cofactor__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data,  int prow,  int pcolumn);

typedef inverse__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data, Double det);
typedef inverse__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data, double det);

typedef adjugate__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data);
typedef adjugate__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data);

typedef deepcopy__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data);
typedef deepcopy__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data);

typedef compare__base__ffi = Pointer<Pointer<Bool>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>>  data2,  Int32 mode);
typedef compare__base = Pointer<Pointer<Bool>> Function(int row,  int column,  Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>>  data2,  int mode);

typedef sum__base__ffi = Pointer<Double> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>> data,  Int32 dim);
typedef sum__base = Pointer<Double> Function( int row,  int column,  Pointer<Pointer<Double>> data,  int dim);

typedef mean__base__ffi = Pointer<Double> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>> data,  Int32 dim);
typedef mean__base = Pointer<Double> Function( int row,  int column,  Pointer<Pointer<Double>> data,  int dim);

typedef min__base__ffi = Pointer<Double> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>> data,  Int32 dim);
typedef min__base = Pointer<Double> Function( int row,  int column,  Pointer<Pointer<Double>> data,  int dim);

typedef max__base__ffi = Pointer<Double> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>> data,  Int32 dim);
typedef max__base = Pointer<Double> Function( int row,  int column,  Pointer<Pointer<Double>> data,  int dim);

typedef data_isSame__base__ffi = Bool Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data1,  Pointer<Pointer<Double>>  data2);
typedef data_isSame__base = bool Function( int row,  int column,  Pointer<Pointer<Double>>  data1,  Pointer<Pointer<Double>>  data2);

typedef spc__isSame__base__ffi = Bool Function(Pointer<SpecialAttributes> spc1, Pointer<SpecialAttributes> spc2);
typedef spc__isSame__base = bool Function(Pointer<SpecialAttributes> spc1, Pointer<SpecialAttributes> spc2);

typedef cut__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data,  Int32 prow,  Int32 pcolumn,  Int32 width,  Int32 height);
typedef cut__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data,  int prow,  int pcolumn,  int width,  int height);

typedef cutfree__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data,  Int32 prow,  Int32 pcolumn, Int32 width,  Int32 height,  Double number);
typedef cutfree__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data,  int prow,  int pcolumn,  int width,  int height,  double number);

typedef concatR__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column1,  Int32 column2,  Pointer<Pointer<Double>>  data1,  Pointer<Pointer<Double>>  data2);
typedef concatR__base = Pointer<Pointer<Double>> Function( int row,  int column1,  int column2,  Pointer<Pointer<Double>>  data1,  Pointer<Pointer<Double>>  data2);

typedef concatC__base__ffi = Pointer<Pointer<Double>> Function( Int32 row1,  Int32 row2,  Int32 column,  Pointer<Pointer<Double>>  data1,  Pointer<Pointer<Double>>  data2);
typedef concatC__base = Pointer<Pointer<Double>> Function( int row1,  int row2,  int column,  Pointer<Pointer<Double>>  data1,  Pointer<Pointer<Double>>  data2);

typedef resizeR__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data,  Int32 origin_row,  Int32 origin_column,  Double number);
typedef resizeR__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data,  int origin_row,  int origin_column,  double number);

typedef resizeC__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data,  Int32 origin_row,  Int32 origin_column,  Double number);
typedef resizeC__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data,  int origin_row,  int origin_column,  double number);

typedef reshape__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data,  Int32 origin_column);
typedef reshape__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data,  int origin_column);

typedef setSeed__base__ffi = Void Function(Int32 seed);
typedef setSeed__base = void Function(int seed);

typedef mathBasement1__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data,  Int32 mode);
typedef mathBasement1__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data,  int mode);

typedef mathBasement2__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data,  Int32 mode, Double number);
typedef mathBasement2__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data,  int mode, double number);

typedef mathBasement2reverse__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data,  Int32 mode, Double number);
typedef mathBasement2reverse__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data,  int mode, double number);

typedef allocateButNoNumbers__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column);
typedef allocateButNoNumbers__base = Pointer<Pointer<Double>> Function(int row, int column);

typedef sigmoid__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data);
typedef sigmoid__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data);

typedef softmax__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data,  Int32 dim,  Double mask_nan,  Double mask_inf,  Double mask_neginf);
typedef softmax__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data,  int dim,  double mask_nan,  double mask_inf,  double mask_neginf);

typedef shuffle__base__ffi = Void Function( Int32 row,  Int32 column, Pointer<Pointer<Double>>  data, Int32 seed, Bool use);
typedef shuffle__base = void Function( int row,  int column, Pointer<Pointer<Double>>  data, int seed, bool use);

typedef sortNoReturned__base__ffi = Void Function( Int32 row,  Int32 column, Pointer<Pointer<Double>>  data,  Bool reverse,  Int32 dim,  Double mask_nan);
typedef sortNoReturned__base = void Function( int row,  int column, Pointer<Pointer<Double>>  data,  bool reverse,  int dim,  double mask_nan);

typedef sort__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column, Pointer<Pointer<Double>>  data,  Bool reverse,  Int32 dim,  Double mask_nan);
typedef sort__base = Pointer<Pointer<Double>> Function(int row,  int column, Pointer<Pointer<Double>>  data,  bool reverse,  int dim,  double mask_nan);

typedef uniform__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Double start,  Double end,  Int32 seed,  Bool use);
typedef uniform__base = Pointer<Pointer<Double>> Function( int row,  int column,  double start,  double end,  int seed,  bool use);

typedef normal__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Double mu,  Double sigma,  Int32 seed,  Bool use);
typedef normal__base = Pointer<Pointer<Double>> Function( int row,  int column,  double mu,  double sigma,  int seed,  bool use);

typedef poisson__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Double lambda,  Int32 seed,  Bool use);
typedef poisson__base = Pointer<Pointer<Double>> Function( int row,  int column,  double lambda,  int seed,  bool use);

typedef rref__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data);
typedef rref__base = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data);

typedef set_mask_nan__base__ffi = Void Function( Int32 row,  Int32 column, Pointer<Pointer<Double>>  data,  Double number);
typedef set_mask_nan__base  = void Function( int row,  int column, Pointer<Pointer<Double>>  data,  double number);

typedef set_mask_inf__base__ffi = Void Function( Int32 row,  Int32 column, Pointer<Pointer<Double>>  data,  Double number,  Bool isNegativeInf);
typedef set_mask_inf__base  = void Function( int row,  int column, Pointer<Pointer<Double>>  data,  double number,  bool isNegativeInf);

typedef rank__base__ffi = Int32 Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data);
typedef rank__base  = int Function( int row,  int column,  Pointer<Pointer<Double>>  data);

typedef oneTotwoArray__base__ffi = Pointer<Pointer<Double>> Function(Pointer<Double> array, Int32 row, Int32 column);
typedef oneTotwoArray__base = Pointer<Pointer<Double>> Function(Pointer<Double> array, int row, int column);

typedef __init__point__data__base__ffi = Pointer<Matrix> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Pointer<SpecialAttributes> spc);
typedef __init__point__data__base = Pointer<Matrix> Function(int row, int column, Pointer<Pointer<Double>> data, Pointer<SpecialAttributes> spc);

typedef variance__base__ffi = Pointer<Double> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data, Bool sample, Int32 dim, Bool std);
typedef variance__base  = Pointer<Double> Function( int row,  int column,  Pointer<Pointer<Double>>  data, bool sample, int dim, bool std);

typedef median__base__ffi = Pointer<Double> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data,  Int32 dim);
typedef median__base  = Pointer<Double> Function( int row,  int column,  Pointer<Pointer<Double>>  data, int dim);

typedef norm_negainf__base__ffi = Double Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data);
typedef norm_negainf__base  = double Function( int row,  int column,  Pointer<Pointer<Double>>  data);

typedef norm_inf__base__ffi = Double Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data);
typedef norm_inf__base  = double Function( int row,  int column,  Pointer<Pointer<Double>>  data);

typedef norm_zero__base__ffi = Pointer<Double> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data, Int32 dim);
typedef norm_zero__base  = Pointer<Double> Function( int row,  int column,  Pointer<Pointer<Double>>  data, int dim);

typedef norm_one__base__ffi = Double Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data);
typedef norm_one__base  = double Function( int row,  int column,  Pointer<Pointer<Double>>  data);

typedef norm__base__ffi = Pointer<Double> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data, Int32 n, Int32 dim);
typedef norm__base  = Pointer<Double> Function( int row,  int column,  Pointer<Pointer<Double>>  data, int n, int dim);

typedef argmax__base__ffi = Pointer<Int32> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data, Int32 dim);
typedef argmax__base  = Pointer<Int32> Function( int row,  int column,  Pointer<Pointer<Double>>  data, int dim);

typedef argmin__base__ffi = Pointer<Int32> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data, Int32 dim);
typedef argmin__base  = Pointer<Int32> Function( int row,  int column,  Pointer<Pointer<Double>>  data, int dim);

typedef flatten__base__ffi = Pointer<Double> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data, Int32 mode);
typedef flatten__base  = Pointer<Double> Function( int row,  int column,  Pointer<Pointer<Double>>  data, int mode);

typedef range__base__ffi = Pointer<Pointer<Double>> Function(Double start, Double step, Int32 row,  Int32 column);
typedef range__base  = Pointer<Pointer<Double>> Function(double start, double step, int row,  int column);

typedef replace__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Double number, Pointer<NativeFunction<Bool Function(Double)>> condition);
typedef replace__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, double number, Pointer<NativeFunction<Bool Function(Double)>> condition);

typedef replaceNoReturned__base__ffi = Void Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Double number, Pointer<NativeFunction<Bool Function(Double)>> condition);
typedef replaceNoReturned__base  = void Function(int row, int column, Pointer<Pointer<Double>> data, double number, Pointer<NativeFunction<Bool Function(Double)>> condition);

typedef normalization1__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data, Int32 dim);
typedef normalization1__base  = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data, int dim);

typedef normalization2__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data, Int32 dim);
typedef normalization2__base  = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data, int dim);

typedef normalization3__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column,  Pointer<Pointer<Double>>  data, Int32 dim);
typedef normalization3__base  = Pointer<Pointer<Double>> Function( int row,  int column,  Pointer<Pointer<Double>>  data, int dim);

typedef sliceR__base__ffi = Pointer<Pointer<Double>> Function(Int32 column,  Pointer<Pointer<Double>>  data, Int32 from, Int32 to);
typedef sliceR__base  = Pointer<Pointer<Double>> Function(int column,  Pointer<Pointer<Double>>  data, int from, int to);

typedef sliceC__base__ffi = Pointer<Pointer<Double>> Function( Int32 row, Pointer<Pointer<Double>>  data, Int32 from, Int32 to);
typedef sliceC__base  = Pointer<Pointer<Double>> Function( int row,  Pointer<Pointer<Double>>  data, int from, int to);

typedef clip__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Double lb, Double ub);
typedef clip__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, double lb, double ub);

typedef clipNoReturned__base__ffi = Void Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Double lb, Double ub);
typedef clipNoReturned__base  = void Function(int row, int column, Pointer<Pointer<Double>> data, double lb, double ub);

typedef all__base__ffi = Bool Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Pointer<NativeFunction<Bool Function(Double)>> condition);
typedef all__base  = bool Function(int row, int column, Pointer<Pointer<Double>> data, Pointer<NativeFunction<Bool Function(Double)>> condition);

typedef any__base__ffi = Bool Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Pointer<NativeFunction<Bool Function(Double)>> condition);
typedef any__base  = bool Function(int row, int column, Pointer<Pointer<Double>> data, Pointer<NativeFunction<Bool Function(Double)>> condition);

typedef counter__base__ffi = Pointer<Int32> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Int32 dim, Pointer<NativeFunction<Bool Function(Double)>> condition);
typedef counter__base  = Pointer<Int32> Function(int row, int column, Pointer<Pointer<Double>> data, int dim, Pointer<NativeFunction<Bool Function(Double)>> condition);

typedef reduce__base__ffi = Pointer<Double> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Int32 dim, Pointer<NativeFunction<Double Function(Double, Double)>> condition, Double init);
typedef reduce__base = Pointer<Double> Function(int row, int column, Pointer<Pointer<Double>> data, int dim, Pointer<NativeFunction<Double Function(Double, Double)>> condition, double init);

typedef qr__base__ffi = MultiDatas2 Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data);
typedef qr__base = MultiDatas2 Function(int row, int column, Pointer<Pointer<Double>> data);

typedef E_like__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column);
typedef E_like__base = Pointer<Pointer<Double>> Function(int row, int column);

typedef divrev__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column,  Pointer<Pointer<Double>> data, Double number);
typedef divrev__base = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, double number);

typedef clip_reverse__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Double lb, Double ub, Pointer<NativeFunction<Double Function(Double)>> condition);
typedef clip_reverse__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, double lb, double ub, Pointer<NativeFunction<Double Function(Double)>> condition);

typedef clip_reverseNoReturned__base__ffi = Void Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Double lb, Double ub, Pointer<NativeFunction<Double Function(Double)>> condition);
typedef clip_reverseNoReturned__base  = void Function(int row, int column, Pointer<Pointer<Double>> data, double lb, double ub, Pointer<NativeFunction<Double Function(Double)>> condition);

typedef customize__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Pointer<NativeFunction<Double Function(Double)>> condition);
typedef customize__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, Pointer<NativeFunction<Double Function(Double)>> condition);

typedef findIndexs__base__ffi = Pointer<Pointer<Int32>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Pointer<NativeFunction<Bool Function(Double)>> condition, Int32 prediction);
typedef findIndexs__base  = Pointer<Pointer<Int32>> Function(int row, int column, Pointer<Pointer<Double>> data, Pointer<NativeFunction<Bool Function(Double)>> condition, int prediction);

typedef freeppvoid__base__ffi = Void Function(Pointer<Pointer<Void>> data, Int32 row);
typedef freeppvoid__base  = void Function(Pointer<Pointer<Void>> data, int row);

typedef rotate__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Int32 mode);
typedef rotate__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, int mode);

typedef mirror__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Int32 mode);
typedef mirror__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, int mode);

typedef decentralizate__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Int32 dim);
typedef decentralizate__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, int dim);

typedef covariance__base__ffi = Pointer<Double> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data1, Pointer<Pointer<Double>> data2, Bool sample, Int32 dim);
typedef covariance__base  = Pointer<Double> Function(int row, int column, Pointer<Pointer<Double>> data1, Pointer<Pointer<Double>> data2, bool sample, int dim);

typedef cov1__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Bool sample);
typedef cov1__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, bool sample);

typedef cov2__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2, Bool sample);
typedef cov2__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2, bool sample);

typedef pearsonCoef__base__ffi = Pointer<Double> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2, Bool sample, Int32 dim);
typedef pearsonCoef__base  = Pointer<Double> Function(int row, int column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2, bool sample, int dim);

typedef MSE__base__ffi = Pointer<Double> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2, Int32 dim, Bool rmse);
typedef MSE__base  = Pointer<Double> Function(int row, int column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2, int dim, bool rmse);

typedef MAE__base__ffi = Pointer<Double> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> pre,  Pointer<Pointer<Double>> rea, Int32 dim);
typedef MAE__base  = Pointer<Double> Function(int row, int column, Pointer<Pointer<Double>> pre,  Pointer<Pointer<Double>> rea, int dim);

typedef MAPE__base__ffi = Pointer<Double> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> pre,  Pointer<Pointer<Double>> rea, Int32 dim);
typedef MAPE__base  = Pointer<Double> Function(int row, int column, Pointer<Pointer<Double>> pre,  Pointer<Pointer<Double>> rea, int dim);

typedef R2__base__ffi = Pointer<Double> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> pre,  Pointer<Pointer<Double>> rea, Int32 dim);
typedef R2__base  = Pointer<Double> Function(int row, int column, Pointer<Pointer<Double>> pre,  Pointer<Pointer<Double>> rea, int dim);

typedef SMAPE__base__ffi = Pointer<Double> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2, Int32 dim);
typedef SMAPE__base  = Pointer<Double> Function(int row, int column, Pointer<Pointer<Double>> data1,  Pointer<Pointer<Double>> data2, int dim);

typedef diagonal__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double start, Double end, Bool sub, Int32 seed, Bool use);
typedef diagonal__base  = Pointer<Pointer<Double>> Function(int row, int column, double start, double end, bool sub, int seed, bool use);

typedef fill_diagonal__base__ffi = Void Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Double number);
typedef fill_diagonal__base  = void Function(int row, int column, Pointer<Pointer<Double>> data, double number);

typedef choice1__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Pointer<Pointer<Double>> p, Int32 times, Bool back, Int32 method);
typedef choice1__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, Pointer<Pointer<Double>> p, int times, bool back, int method);

typedef choice2__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Pointer<Double> p, Int32 times, Bool back, Int32 method);
typedef choice2__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, Pointer<Double> p, int times, bool back, int method);

typedef choice3__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Int32 times, Bool back);
typedef choice3__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, int times, bool back);

typedef concatsR__base__ffi = Pointer<Pointer<Double>> Function( Int32 row,  Int32 column1, Int32 column2, Int32 column3, Int32 column4, Pointer<Pointer<Double>> data1, Pointer<Pointer<Double>> data2, Pointer<Pointer<Double>> data3, Pointer<Pointer<Double>> data4);
typedef concatsR__base = Pointer<Pointer<Double>> Function( int row,  int column1,  int column2,  int column3, int column4, Pointer<Pointer<Double>>  data1,  Pointer<Pointer<Double>>  data2, Pointer<Pointer<Double>> data3, Pointer<Pointer<Double>> data4);

typedef concatsC__base__ffi = Pointer<Pointer<Double>> Function( Int32 row1,  Int32 row2,  Int32 row3, Int32 row4, Int32 column,  Pointer<Pointer<Double>>  data1,  Pointer<Pointer<Double>>  data2, Pointer<Pointer<Double>> data3, Pointer<Pointer<Double>> data4);
typedef concatsC__base = Pointer<Pointer<Double>> Function( int row1,  int row2,  int row3, int row4, int column,  Pointer<Pointer<Double>>  data1,  Pointer<Pointer<Double>>  data2, Pointer<Pointer<Double>> data3, Pointer<Pointer<Double>> data4);

typedef split__base__ffi = Pointer<Pointer<Pointer<Double>>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Int32 len, Pointer<Int32> slices, Bool mode);
typedef split__base  = Pointer<Pointer<Pointer<Double>>> Function(int row, int column, Pointer<Pointer<Double>> data, int len, Pointer<Int32> slices, bool mode);

typedef cover__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data1, Int32 row1, Int32 column1, Pointer<Pointer<Double>> data2, Int32 rowx, Int32 rowy);
typedef cover__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, int row1, int column1, Pointer<Pointer<Double>> data2, int rowx, int rowy);

typedef stretch__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Int32 len, Bool hor, Double number, Int32 method);
typedef stretch__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, int len, bool hor, double number, int method);

typedef diffC__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Pointer<NativeFunction<Double Function(Double)>> func);
typedef diffC__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, Pointer<NativeFunction<Double Function(Double)>> func);

typedef get_range__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Int32 dim);
typedef get_range__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, int dim);

typedef cumsum__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Int32 dim, Bool flatten);
typedef cumsum__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data, int dim, bool flatten);

typedef sgn__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data);
typedef sgn__base  = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>> data);

typedef exponential__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double scale, Int32 seed, Bool use);
typedef exponential__base  = Pointer<Pointer<Double>> Function(int row, int column, double scale, int seed, bool use);

typedef gamma__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double shape, Double scale, Int32 seed, Bool use);
typedef gamma__base  = Pointer<Pointer<Double>> Function(int row, int column, double shape, double scale, int seed, bool use);

typedef binomial__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Int32 n, Double p, Int32 seed, Bool use);
typedef binomial__base  = Pointer<Pointer<Double>> Function(int row, int column, int n, double p, int seed, bool use);

typedef chisquare__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Int32 k, Int32 seed, Bool use);
typedef chisquare__base  = Pointer<Pointer<Double>> Function(int row, int column, int k, int seed, bool use);

typedef tdis__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Int32 k, Int32 seed, Bool use);
typedef tdis__base  = Pointer<Pointer<Double>> Function(int row, int column, int k, int seed, bool use);

typedef fdis__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Int32 k1, Int32 k2, Int32 seed, Bool use);
typedef fdis__base  = Pointer<Pointer<Double>> Function(int row, int column, int k1, int k2, int seed, bool use);

typedef geometric__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double p, Int32 seed, Bool use);
typedef geometric__base  = Pointer<Pointer<Double>> Function(int row, int column, double p, int seed, bool use);

typedef nbinomial__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Int32 n, Double p, Int32 seed, Bool use);
typedef nbinomial__base  = Pointer<Pointer<Double>> Function(int row, int column, int n, double p, int seed, bool use);

typedef lognormal__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double mu, Double sigma, Int32 seed, Bool use);
typedef lognormal__base  = Pointer<Pointer<Double>> Function(int row, int column, double mu, double sigma, int seed, bool use);

typedef cauchydis__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double base, Double gamma, Int32 seed, Bool use);
typedef cauchydis__base  = Pointer<Pointer<Double>> Function(int row, int column, double base, double gamma, int seed, bool use);

typedef multinomial__base__ffi = Pointer<Pointer<Double>> Function(Pointer<Double> p, Int32 len, Int32 n, Int32 size, Int32 seed, Bool use);
typedef multinomial__base  = Pointer<Pointer<Double>> Function(Pointer<Double> p, int len, int n, int size, int seed, bool use);

typedef beta__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double a, Double b, Int32 seed, Bool use);
typedef beta__base  = Pointer<Pointer<Double>> Function(int row, int column, double a, double b, int seed, bool use);

typedef wiener_process__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double t, Int32 seed, Bool use);
typedef wiener_process__base  = Pointer<Pointer<Double>> Function(int row, int column, double t, int seed, bool use);

typedef wiener_process_stage__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double t1, Double t2, Double base, Int32 seed, Bool use);
typedef wiener_process_stage__base  = Pointer<Pointer<Double>> Function(int row, int column, double t1, double t2, double base, int seed, bool use);

typedef dirichlet__base__ffi = Pointer<Pointer<Double>> Function(Pointer<Double> alpha, Int32 len, Int32 size, Int32 seed, Bool use);
typedef dirichlet__base  = Pointer<Pointer<Double>> Function(Pointer<Double> alpha, int len, int size, int seed, bool use);

typedef laplacedis__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double mu, Double b, Int32 seed, Bool use);
typedef laplacedis__base  = Pointer<Pointer<Double>> Function(int row, int column, double mu, double b, int seed, bool use);

typedef gumbel__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double mu, Double beta, Bool left, Int32 seed, Bool use);
typedef gumbel__base  = Pointer<Pointer<Double>> Function(int row, int column, double mu, double beta, bool left, int seed, bool use);

typedef hypergeometric__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Int32 expected, Int32 unexpected, Int32 n, Int32 seed, Bool use);
typedef hypergeometric__base  = Pointer<Pointer<Double>> Function(int row, int column, int expected, int unexpected, int n, int seed, bool use);

typedef logseries__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double p, Int32 seed, Bool use);
typedef logseries__base  = Pointer<Pointer<Double>> Function(int row, int column, double p, int seed, bool use);

typedef weibull__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double lambda, Double k, Int32 seed, Bool use);
typedef weibull__base  = Pointer<Pointer<Double>> Function(int row, int column, double lambda, double k, int seed, bool use);

typedef triangular__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double left, Double middle, Double right, Int32 seed, Bool use);
typedef triangular__base  = Pointer<Pointer<Double>> Function(int row, int column, double left, double middle, double right, int seed, bool use);

typedef power_law__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double xmin, Double alpha, Int32 seed, Bool use);
typedef power_law__base  = Pointer<Pointer<Double>> Function(int row, int column, double xmin, double alpha, int seed, bool use);

typedef rayleigh__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double sigma, Int32 seed, Bool use);
typedef rayleigh__base  = Pointer<Pointer<Double>> Function(int row, int column, double sigma, int seed, bool use);

typedef stabledis__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double alpha, Double beta, Double gamma, Double delta, Int32 seed, Bool use);
typedef stabledis__base  = Pointer<Pointer<Double>> Function(int row, int column, double alpha, double beta, double gamma, double delta, int seed, bool use);

typedef pareto__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double xmin, Double alpha, Int32 seed, Bool use);
typedef pareto__base  = Pointer<Pointer<Double>> Function(int row, int column, double xmin, double alpha, int seed, bool use);

typedef rice__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double v, Double sigma, Int32 seed, Bool use);
typedef rice__base  = Pointer<Pointer<Double>> Function(int row, int column, double v, double sigma, int seed, bool use);

typedef wald__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Double mu, Double sigma, Int32 seed, Bool use);
typedef wald__base  = Pointer<Pointer<Double>> Function(int row, int column, double mu, double sigma, int seed, bool use);

typedef ellipse_edge__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Double a, Double b, Int32 seed, Bool use, Double bias);
typedef ellipse_edge__base  = Pointer<Pointer<Double>> Function(int size, double a, double b, int seed, bool use, double bias);

typedef ellipse_area__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Double a, Double b, Int32 seed, Bool use, Double bias);
typedef ellipse_area__base  = Pointer<Pointer<Double>> Function(int size, double a, double b, int seed, bool use, double bias);

typedef freeOp__base__ffi = Void Function(Pointer<Void> data);
typedef freeOp__base = void Function(Pointer<Void> data);

typedef circle_edge__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Double r, Int32 seed, Bool use, Double bias);
typedef circle_edge__base  = Pointer<Pointer<Double>> Function(int size, double r, int seed, bool use, double bias);

typedef circle_area__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Double r, Int32 seed, Bool use, Double bias);
typedef circle_area__base  = Pointer<Pointer<Double>> Function(int size, double r, int seed, bool use, double bias);

typedef line__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Point2D start, Point2D end, Int32 seed, Bool use, Double bias);
typedef line__base  = Pointer<Pointer<Double>> Function(int size, Point2D start, Point2D end, int seed, bool use, double bias);

typedef triangle_edge__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Point2D a, Point2D b, Point2D c, Int32 seed, Bool use, Double bias);
typedef triangle_edge__base  = Pointer<Pointer<Double>> Function(int size, Point2D a, Point2D b, Point2D c, int seed, bool use, double bias);

typedef triangle_area__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Point2D a, Point2D b, Point2D c, Int32 seed, Bool use, Double bias);
typedef triangle_area__base  = Pointer<Pointer<Double>> Function(int size, Point2D a, Point2D b, Point2D c, int seed, bool use, double bias);

typedef quadrilateral_edge__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Point2D a, Point2D b, Point2D c, Point2D d, Int32 seed, Bool use, Double bias);
typedef quadrilateral_edge__base = Pointer<Pointer<Double>> Function(int size, Point2D a, Point2D b, Point2D c, Point2D d, int seed, bool use, double bias);

typedef quadrilateral_area__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Point2D a, Point2D b, Point2D c, Point2D d, Int32 seed, Bool use, Double bias);
typedef quadrilateral_area__base = Pointer<Pointer<Double>> Function(int size, Point2D a, Point2D b, Point2D c, Point2D d, int seed, bool use, double bias);

typedef heart_edge__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Double x, Int32 seed, Bool use, Double bias);
typedef heart_edge__base = Pointer<Pointer<Double>> Function(int size, double x, int seed, bool use, double bias);

typedef heart_area__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Double x, Int32 seed, Bool use, Double bias);
typedef heart_area__base = Pointer<Pointer<Double>> Function(int size, double x, int seed, bool use, double bias);

typedef curve__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Double x1, Double x2, Pointer<NativeFunction<Double Function(Double)>> func, Int32 seed, Bool use, Double bias);
typedef curve__base = Pointer<Pointer<Double>> Function(int size, double x1, double x2, Pointer<NativeFunction<Double Function(Double)>> func, int seed, bool use, double bias);

typedef bezier__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, Point2D start, Point2D end, Point2D ctrl, Int32 seed, Bool use, Double bias);
typedef bezier__base = Pointer<Pointer<Double>> Function(int size, Point2D start, Point2D end, Point2D ctrl, int seed, bool use, double bias);

typedef xytoPoint2D__base__ffi = Point2D Function(Double x, Double y);
typedef xytoPoint2D__base = Point2D Function(double x, double y);

typedef shake__base__ffi = Void Function(Int32 row, Int32 column, Pointer<Pointer<Double>> data, Int32 seed, Bool use, Double bias);
typedef shake__base = void Function(int row, int column, Pointer<Pointer<Double>> data, int seed, bool use, double bias);

typedef coord_func = Pointer<NativeFunction<Double Function(Double, Pointer<Void>)>>;
typedef custom_curve__base__ffi = Pointer<Pointer<Double>> Function(Int32 size, coord_func x_func, coord_func y_func, Pointer<Void> params, Double theta_start, Double theta_step, Int32 seed, Bool use, Double bias);
typedef custom_curve__base = Pointer<Pointer<Double>> Function(int size, coord_func x_func, coord_func y_func, Pointer<Void> params, double theta_start, double theta_step, int seed, bool use, double bias);

typedef testArray__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column);
typedef testArray__base = Pointer<Pointer<Double>> Function(int row, int column);

typedef testOmp__base__ffi = Void Function();
typedef testOmp__base = void Function();

typedef genTestdatas__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<NativeFunction<Double Function(Double, Double)>> func);
typedef genTestdatas__base = Pointer<Pointer<Double>> Function(int row, int column, Pointer<NativeFunction<Double Function(Double, Double)>> func);

typedef testSingleT__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<NativeFunction<Double Function(Int32, Int32)>> func);
typedef testSingleT__base = Pointer<Pointer<Double>> Function(int row, int column, Pointer<NativeFunction<Double Function(Int32, Int32)>> func);

typedef get_multp_shown__base__ffi = Bool Function();
typedef get_multp_shown__base = bool Function();

typedef confront__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column, Pointer<Pointer<Double>>, Pointer<Pointer<Double>>, Pointer<NativeFunction<Double Function(Double, Double)>> func);
typedef confront__base = Pointer<Pointer<Double>> Function(int row, int column, Pointer<Pointer<Double>>, Pointer<Pointer<Double>>, Pointer<NativeFunction<Double Function(Double, Double)>> func);

typedef testOmpCanRun__base__ffi = Void Function(
    Int32 row,
    Int32 column,
    Pointer<Pointer<Double>> data,
    Pointer<NativeFunction<Void Function(Int32, Int32, Pointer<Pointer<Double>> data)>> func
);
typedef testOmpCanRun__base = void Function(
    int row,
    int column,
    Pointer<Pointer<Double>> data,
    Pointer<NativeFunction<Void Function(Int32, Int32, Pointer<Pointer<Double>> data)>> func
);

typedef testOmpUniform__base__ffi = Pointer<Pointer<Double>> Function(Int32 row, Int32 column);
typedef testOmpUniform__base = Pointer<Pointer<Double>> Function(int row, int column);

typedef allocateOp__base__ffi = Pointer<Void> Function(Int32 len, Int32 mode);
typedef allocateOp__base = Pointer<Void> Function(int len, int mode);

late final __new__base matply__new__ = dylib.lookupFunction<__new__base__ffi, __new__base>('__new__');
late final __init__base matply__init__ = dylib.lookupFunction<__init__base__ffi, __init__base>('__init__');
late final VisibleMatrix__base matply__VisibleMatrix = dylib.lookupFunction<VisibleMatrix__base__ffi, VisibleMatrix__base>('VisibleMatrix');
late final __delete__base matply__delete__ = dylib.lookupFunction<__delete__base__ffi, __delete__base>('__delete__');
late final __delete__data__base matply__delete__data__ = dylib.lookupFunction<__delete__data__base__ffi, __delete__data__base>('__delete__data__');
late final filled__base matply__filled = dylib.lookupFunction<filled__base__ffi, filled__base>('filled');
late final zeros__base matply__zeros = dylib.lookupFunction<zeros__base__ffi, zeros__base>('zeros');
late final ones__base matply__ones = dylib.lookupFunction<ones__base__ffi, ones__base>('ones');
late final VisibleMatrixSpc__base matply__VisibleMatrixSpc = dylib.lookupFunction<VisibleMatrixSpc__base__ffi, VisibleMatrixSpc__base>('VisibleMatrixSpc');
late final row__base matply__row_ = dylib.lookupFunction<row__base__ffi, row__base>('row_');
late final column__base matply__column_ = dylib.lookupFunction<column__base__ffi, column__base>('column_');
late final at__base matply__at = dylib.lookupFunction<at__base__ffi, at__base>('at');
late final transpose__base matply__transpose = dylib.lookupFunction<transpose__base__ffi, transpose__base>('transpose');
late final exchangeR__base matply__exchangeR = dylib.lookupFunction<exchangeR__base__ffi, exchangeR__base>('exchangeR');
late final multiplyR__base matply__multiplyR = dylib.lookupFunction<multiplyR__base__ffi, multiplyR__base>('multiplyR');
late final addR__base matply__addR = dylib.lookupFunction<addR__base__ffi, addR__base>('addR');
late final addC__base matply__addC = dylib.lookupFunction<addC__base__ffi, addC__base>('addC');
late final exchangeC__base matply__exchangeC = dylib.lookupFunction<exchangeC__base__ffi, exchangeC__base>('exchangeC');
late final multiplyC__base matply__multiplyC = dylib.lookupFunction<multiplyC__base__ffi, multiplyC__base>('multiplyC');
late final addNumber__base matply__addNumber = dylib.lookupFunction<addNumber__base__ffi, addNumber__base>('addNumber');
late final addNumberNoReturned__base matply__addNumberNoReturned = dylib.lookupFunction<addNumberNoReturned__base__ffi, addNumberNoReturned__base>('addNumberNoReturned');
late final addMatrix__base matply__addMatrix = dylib.lookupFunction<addMatrix__base__ffi, addMatrix__base>('addMatrix');
late final addMatrixNoReturned__base matply__addMatrixNoReturned = dylib.lookupFunction<addMatrixNoReturned__base__ffi, addMatrixNoReturned__base>('addMatrixNoReturned');
late final minusMatrix__base matply__minusMatrix = dylib.lookupFunction<minusMatrix__base__ffi, minusMatrix__base>('minusMatrix');
late final minusMatrixNoReturned__base matply__minusMatrixNoReturned = dylib.lookupFunction<minusMatrixNoReturned__base__ffi, minusMatrixNoReturned__base>('minusMatrixNoReturned');
late final matmul__base matply__matmul = dylib.lookupFunction<matmul__base__ffi, matmul__base>('matmul');
late final multiplyMatrixNoReturned__base matply__multiplyMatrixNoReturned = dylib.lookupFunction<multiplyMatrixNoReturned__base__ffi, multiplyMatrixNoReturned__base>('multiplyMatrixNoReturned');
late final multiplyMatrix__base matply__multiplyMatrix = dylib.lookupFunction<multiplyMatrix__base__ffi, multiplyMatrix__base>('multiplyMatrix');
late final multiplyNumberNoReturned__base matply__multiplyNumberNoReturned = dylib.lookupFunction<multiplyNumberNoReturned__base__ffi, multiplyNumberNoReturned__base>('multiplyNumberNoReturned');
late final multiplyNumber__base matply__multiplyNumber = dylib.lookupFunction<multiplyNumber__base__ffi, multiplyNumber__base>('multiplyNumber');
late final kronecker__base matply__kronecker = dylib.lookupFunction<kronecker__base__ffi, kronecker__base>('kronecker');
late final divide__base matply__divide = dylib.lookupFunction<divide__base__ffi, divide__base>('divide');
late final divideNoReturned__base matply__divideNoReturned = dylib.lookupFunction<divideNoReturned__base__ffi, divideNoReturned__base>('divideNoReturned');
late final arrange__base matply__arrange = dylib.lookupFunction<arrange__base__ffi, arrange__base>('arrange');
late final linspace__base matply__linspace = dylib.lookupFunction<linspace__base__ffi, linspace__base>('linspace');
late final trace__base matply__trace = dylib.lookupFunction<trace__base__ffi, trace__base>('trace');
late final det__base matply__det = dylib.lookupFunction<det__base__ffi, det__base>('det');
late final E__base matply__E = dylib.lookupFunction<E__base__ffi, E__base>('E');
late final cofactor__base matply__cofacto = dylib.lookupFunction<cofactor__base__ffi, cofactor__base>('cofactor');
late final inverse__base matply__inverse = dylib.lookupFunction<inverse__base__ffi, inverse__base>('inverse');
late final adjugate__base matply__adjugate = dylib.lookupFunction<adjugate__base__ffi, adjugate__base>('adjugate');
late final deepcopy__base matply__deepcopy = dylib.lookupFunction<deepcopy__base__ffi, deepcopy__base>('deepcopy');
late final compare__base matply__compare = dylib.lookupFunction<compare__base__ffi, compare__base>('compare');
late final sum__base matply__sum = dylib.lookupFunction<sum__base__ffi, sum__base>('sum');
late final mean__base matply__mean = dylib.lookupFunction<mean__base__ffi, mean__base>('mean');
late final max__base matply__max = dylib.lookupFunction<max__base__ffi, max__base>('max');
late final min__base matply__min = dylib.lookupFunction<min__base__ffi, min__base>('min');
late final data_isSame__base matply__data__isSame = dylib.lookupFunction<data_isSame__base__ffi, data_isSame__base>('data_isSame');
late final spc__isSame__base matply__spc__isSame = dylib.lookupFunction<spc__isSame__base__ffi, spc__isSame__base>('spc_isSame');
late final cut__base matply__cut = dylib.lookupFunction<cut__base__ffi, cut__base>('cut');
late final cutfree__base matply__cutfree = dylib.lookupFunction<cutfree__base__ffi, cutfree__base>('cutfree');
late final concatR__base matply__concatR = dylib.lookupFunction<concatR__base__ffi, concatR__base>('concatR');
late final concatC__base matply__concatC = dylib.lookupFunction<concatC__base__ffi, concatC__base>('concatC');
late final resizeR__base matply__resizeR = dylib.lookupFunction<resizeR__base__ffi, resizeR__base>('resizeR');
late final resizeC__base matply__resizeC = dylib.lookupFunction<resizeC__base__ffi, resizeC__base>('resizeC');
late final reshape__base matply__reshape = dylib.lookupFunction<reshape__base__ffi, reshape__base>('reshape');
late final setSeed__base matply__setSeed = dylib.lookupFunction<setSeed__base__ffi, setSeed__base>('setSeed');
late final mathBasement1__base matply_mathBasement1 = dylib.lookupFunction<mathBasement1__base__ffi, mathBasement1__base>('mathBasement1');
late final mathBasement2__base matply_mathBasement2 = dylib.lookupFunction<mathBasement2__base__ffi, mathBasement2__base>('mathBasement2');
late final mathBasement2reverse__base matply_mathBasement2reverse = dylib.lookupFunction<mathBasement2reverse__base__ffi, mathBasement2reverse__base>('mathBasement2reverse');
late final allocateButNoNumbers__base matply__allocateButNoNumbers = dylib.lookupFunction<allocateButNoNumbers__base__ffi, allocateButNoNumbers__base>('allocateButNoNumbers');
late final sigmoid__base matply__sigmoid = dylib.lookupFunction<sigmoid__base__ffi, sigmoid__base>('sigmoid');
late final softmax__base matply__softmax = dylib.lookupFunction<softmax__base__ffi, softmax__base>('softmax');
late final shuffle__base matply__shuffle = dylib.lookupFunction<shuffle__base__ffi, shuffle__base>('shuffle');
late final sortNoReturned__base matply__sortNoReturned = dylib.lookupFunction<sortNoReturned__base__ffi, sortNoReturned__base>('sortNoReturned');
late final sort__base matply__sort = dylib.lookupFunction<sort__base__ffi, sort__base>('sort');
late final uniform__base matply__uniform = dylib.lookupFunction<uniform__base__ffi, uniform__base>('uniform');
late final normal__base matply__normal = dylib.lookupFunction<normal__base__ffi, normal__base>('normal');
late final poisson__base matply__poisson = dylib.lookupFunction<poisson__base__ffi, poisson__base>('poisson');
late final rref__base matply__rref = dylib.lookupFunction<rref__base__ffi, rref__base>('rref');
late final set_mask_nan__base matply__set_mask_nan = dylib.lookupFunction<set_mask_nan__base__ffi, set_mask_nan__base>('set_mask_nan');
late final set_mask_inf__base matply__set_mask_inf = dylib.lookupFunction<set_mask_inf__base__ffi, set_mask_inf__base>('set_mask_inf');
late final __init__point__data__base matply__init__point__data__ = dylib.lookupFunction<__init__point__data__base__ffi, __init__point__data__base>('__init__point__data__');
late final rank__base matply__rank = dylib.lookupFunction<rank__base__ffi, rank__base>('rank');
late final oneTotwoArray__base matply__oneTotwoArray = dylib.lookupFunction<oneTotwoArray__base__ffi, oneTotwoArray__base>('oneTotwoArray');
late final variance__base matply__variance = dylib.lookupFunction<variance__base__ffi, variance__base>('variance');
late final median__base matply__median = dylib.lookupFunction<median__base__ffi, median__base>('median');
late final norm_negainf__base matply__norm_negainf = dylib.lookupFunction<norm_negainf__base__ffi, norm_negainf__base>('norm_negainf');
late final norm_inf__base matply__norm_inf = dylib.lookupFunction<norm_inf__base__ffi, norm_inf__base>('norm_inf');
late final norm_zero__base matply__norm_zero = dylib.lookupFunction<norm_zero__base__ffi, norm_zero__base>('norm_zero');
late final norm_one__base matply__norm_one = dylib.lookupFunction<norm_one__base__ffi, norm_one__base>('norm_one');
late final norm__base matply__norm = dylib.lookupFunction<norm__base__ffi, norm__base>('norm');
late final argmax__base matply__argmax = dylib.lookupFunction<argmax__base__ffi, argmax__base>('argmax');
late final argmin__base matply__argmin = dylib.lookupFunction<argmin__base__ffi, argmin__base>('argmin');
late final flatten__base matply__flatten = dylib.lookupFunction<flatten__base__ffi, flatten__base>('flatten');
late final range__base matply__range = dylib.lookupFunction<range__base__ffi, range__base>('range');
late final replace__base matply__replace = dylib.lookupFunction<replace__base__ffi, replace__base>('replace');
late final replaceNoReturned__base matply__replaceNoReturned = dylib.lookupFunction<replaceNoReturned__base__ffi, replaceNoReturned__base>('replaceNoReturned');
late final normalization1__base matply__normalization1 = dylib.lookupFunction<normalization1__base__ffi, normalization1__base>('normalization1');
late final normalization2__base matply__normalization2 = dylib.lookupFunction<normalization2__base__ffi, normalization2__base>('normalization2');
late final normalization3__base matply__normalization3 = dylib.lookupFunction<normalization3__base__ffi, normalization3__base>('normalization3');
late final sliceR__base matply__sliceR = dylib.lookupFunction<sliceR__base__ffi, sliceR__base>('sliceR');
late final sliceC__base matply__sliceC = dylib.lookupFunction<sliceC__base__ffi, sliceC__base>('sliceC');
late final clip__base matply__clip = dylib.lookupFunction<clip__base__ffi, clip__base>('clip');
late final clipNoReturned__base matply__clipNoReturned = dylib.lookupFunction<clipNoReturned__base__ffi, clipNoReturned__base>('clipNoReturned');
late final all__base matply__all = dylib.lookupFunction<all__base__ffi, all__base>('all');
late final any__base matply__any = dylib.lookupFunction<any__base__ffi, any__base>('any');
late final counter__base matply__counter = dylib.lookupFunction<counter__base__ffi, counter__base>('counter');
late final reduce__base matply__reduce = dylib.lookupFunction<reduce__base__ffi, reduce__base>('reduce');
late final qr__base matply__qr = dylib.lookupFunction<qr__base__ffi, qr__base>('qr');
late final E_like__base matply__E_like = dylib.lookupFunction<E_like__base__ffi, E_like__base>('E_like');
late final divrev__base matply__divrev= dylib.lookupFunction<divrev__base__ffi, divrev__base>('divrev');
late final clip_reverse__base matply__clip_reverse = dylib.lookupFunction<clip_reverse__base__ffi, clip_reverse__base>('clip_reverse');
late final clip_reverseNoReturned__base matply__clip_reverseNoReturned = dylib.lookupFunction<clip_reverseNoReturned__base__ffi, clip_reverseNoReturned__base>('clip_reverseNoReturned');
late final customize__base matply__customize = dylib.lookupFunction<customize__base__ffi, customize__base>('customize');
late final findIndexs__base matply__findIndexs = dylib.lookupFunction<findIndexs__base__ffi, findIndexs__base>('findIndexs');
late final freeppvoid__base matply__freeppvoid = dylib.lookupFunction<freeppvoid__base__ffi, freeppvoid__base>('freeppvoid');
late final mirror__base matply__mirror = dylib.lookupFunction<mirror__base__ffi, mirror__base>('mirror');
late final rotate__base matply__rotate = dylib.lookupFunction<rotate__base__ffi, rotate__base>('rotate');
late final decentralizate__base matply__decentralizate = dylib.lookupFunction<decentralizate__base__ffi, decentralizate__base>('decentralizate');
late final covariance__base matply__covariance = dylib.lookupFunction<covariance__base__ffi, covariance__base>('covariance');
late final cov1__base matply__cov1 = dylib.lookupFunction<cov1__base__ffi, cov1__base>('cov1');
late final cov2__base matply__cov2 = dylib.lookupFunction<cov2__base__ffi, cov2__base>('cov2');
late final pearsonCoef__base matply__pearsonCoef = dylib.lookupFunction<pearsonCoef__base__ffi, pearsonCoef__base>('pearsonCoef');
late final MSE__base matply__MSE = dylib.lookupFunction<MSE__base__ffi, MSE__base>('MSE');
late final MAE__base matply__MAE = dylib.lookupFunction<MAE__base__ffi, MAE__base>('MAE');
late final MAPE__base matply__MAPE = dylib.lookupFunction<MAPE__base__ffi, MAPE__base>('MAPE');
late final R2__base matply__R2 = dylib.lookupFunction<R2__base__ffi, R2__base>('R2');
late final SMAPE__base matply__SMAPE = dylib.lookupFunction<SMAPE__base__ffi, SMAPE__base>('SMAPE');
late final diagonal__base matply__diagonal = dylib.lookupFunction<diagonal__base__ffi, diagonal__base>('diagonal');
late final fill_diagonal__base matply__fill_diagonal = dylib.lookupFunction<fill_diagonal__base__ffi, fill_diagonal__base>('fill_diagonal');
late final choice1__base matply__choice1 = dylib.lookupFunction<choice1__base__ffi, choice1__base>('choice1');
late final choice2__base matply__choice2 = dylib.lookupFunction<choice2__base__ffi, choice2__base>('choice2');
late final choice3__base matply__choice3 = dylib.lookupFunction<choice3__base__ffi, choice3__base>('choice3');
late final concatsR__base matply__concatsR = dylib.lookupFunction<concatsR__base__ffi, concatsR__base>('concatsR');
late final concatsC__base matply__concatsC = dylib.lookupFunction<concatsC__base__ffi, concatsC__base>('concatsC');
late final split__base matply__split = dylib.lookupFunction<split__base__ffi, split__base>('split');
late final cover__base matply__cover = dylib.lookupFunction<cover__base__ffi, cover__base>('cover');
late final stretch__base matply__stretch = dylib.lookupFunction<stretch__base__ffi, stretch__base>('stretch');
late final diffC__base matply__diffC = dylib.lookupFunction<diffC__base__ffi, diffC__base>('diffC');
late final get_range__base matply__get_range = dylib.lookupFunction<get_range__base__ffi, get_range__base>('get_range');
late final cumsum__base matply__cumsum = dylib.lookupFunction<cumsum__base__ffi, cumsum__base>('cumsum');
late final sgn__base matply__sgn = dylib.lookupFunction<sgn__base__ffi, sgn__base>('sgn');
late final exponential__base matply__exponential = dylib.lookupFunction<exponential__base__ffi, exponential__base>('exponential');
late final gamma__base matply__gamma_ = dylib.lookupFunction<gamma__base__ffi, gamma__base>('gamma_');
late final binomial__base matply__binomial = dylib.lookupFunction<binomial__base__ffi, binomial__base>('binomial');
late final chisquare__base matply__chisquare = dylib.lookupFunction<chisquare__base__ffi, chisquare__base>('chisquare');
late final tdis__base matply__tdis = dylib.lookupFunction<tdis__base__ffi, tdis__base>('tdis');
late final fdis__base matply__fdis = dylib.lookupFunction<fdis__base__ffi, fdis__base>('fdis');
late final geometric__base matply__geometric = dylib.lookupFunction<geometric__base__ffi, geometric__base>('geometric');
late final nbinomial__base matply__nbinomial = dylib.lookupFunction<nbinomial__base__ffi, nbinomial__base>('nbinomial');
late final lognormal__base matply__lognormal = dylib.lookupFunction<lognormal__base__ffi, lognormal__base>('lognormal');
late final cauchydis__base matply__cauchydis = dylib.lookupFunction<cauchydis__base__ffi, cauchydis__base>('cauchydis');
late final multinomial__base matply__multinomial = dylib.lookupFunction<multinomial__base__ffi, multinomial__base>('multinomial');
late final beta__base matply__beta = dylib.lookupFunction<beta__base__ffi, beta__base>('beta');
late final wiener_process__base matply__wiener_process = dylib.lookupFunction<wiener_process__base__ffi, wiener_process__base>('wiener_process');
late final wiener_process_stage__base matply__wiener_process_stage = dylib.lookupFunction<wiener_process_stage__base__ffi, wiener_process_stage__base>('wiener_process_stage');
late final dirichlet__base matply__dirichlet = dylib.lookupFunction<dirichlet__base__ffi, dirichlet__base>('dirichlet');
late final laplacedis__base matply__laplacedis = dylib.lookupFunction<laplacedis__base__ffi, laplacedis__base>('laplacedis');
late final gumbel__base matply__gumbel = dylib.lookupFunction<gumbel__base__ffi, gumbel__base>('gumbel');
late final hypergeometric__base matply__hypergeometric = dylib.lookupFunction<hypergeometric__base__ffi, hypergeometric__base>('hypergeometric');
late final logseries__base matply__logseries = dylib.lookupFunction<logseries__base__ffi, logseries__base>('logseries');
late final weibull__base matply__weibull = dylib.lookupFunction<weibull__base__ffi, weibull__base>('weibull');
late final triangular__base matply__triangular = dylib.lookupFunction<triangular__base__ffi, triangular__base>('triangular');
late final power_law__base matply__power_law = dylib.lookupFunction<power_law__base__ffi, power_law__base>('power_law');
late final rayleigh__base matply__rayleigh = dylib.lookupFunction<rayleigh__base__ffi, rayleigh__base>('rayleigh');
late final stabledis__base matply__stabledis = dylib.lookupFunction<stabledis__base__ffi, stabledis__base>('stabledis');
late final pareto__base matply__pareto= dylib.lookupFunction<pareto__base__ffi, pareto__base>('pareto');
late final rice__base matply__rice = dylib.lookupFunction<rice__base__ffi, rice__base>('rice');
late final wald__base matply__wald = dylib.lookupFunction<wald__base__ffi, wald__base>('wald');
late final ellipse_edge__base matply__ellipse_edge = dylib.lookupFunction<ellipse_edge__base__ffi, ellipse_edge__base>('ellipse_edge');
late final ellipse_area__base matply__ellipse_area = dylib.lookupFunction<ellipse_area__base__ffi, ellipse_area__base>('ellipse_area');
late final freeOp__base matply__freeOp = dylib.lookupFunction<freeOp__base__ffi, freeOp__base>('freeOp');
late final circle_edge__base matply__circle_edge = dylib.lookupFunction<circle_edge__base__ffi, circle_edge__base>('circle_edge');
late final circle_area__base matply__circle_area = dylib.lookupFunction<circle_area__base__ffi, circle_area__base>('circle_area');
late final line__base matply__line = dylib.lookupFunction<line__base__ffi, line__base>('line');
late final triangle_edge__base matply__triangle_edge = dylib.lookupFunction<triangle_edge__base__ffi, triangle_edge__base>('triangle_edge');
late final triangle_area__base matply__triangle_area = dylib.lookupFunction<triangle_area__base__ffi, triangle_area__base>('triangle_area');
late final quadrilateral_edge__base matply__quadrilateral_edge = dylib.lookupFunction<quadrilateral_edge__base__ffi, quadrilateral_edge__base>('quadrilateral_edge');
late final quadrilateral_area__base matply__quadrilateral_area = dylib.lookupFunction<quadrilateral_area__base__ffi, quadrilateral_area__base>('quadrilateral_area');
late final heart_edge__base matply__heart_edge = dylib.lookupFunction<heart_edge__base__ffi, heart_edge__base>('heart_edge');
late final heart_area__base matply__heart_area = dylib.lookupFunction<heart_area__base__ffi, heart_area__base>('heart_area');
late final curve__base matply__curve = dylib.lookupFunction<curve__base__ffi, curve__base>('curve');
late final bezier__base matply__bezier = dylib.lookupFunction<bezier__base__ffi, bezier__base>('bezier');
late final xytoPoint2D__base matply__xytoPoint2D = dylib.lookupFunction<xytoPoint2D__base__ffi, xytoPoint2D__base>('xytoPoint2D');
late final shake__base matply__shake = dylib.lookupFunction<shake__base__ffi, shake__base>('shake');
late final custom_curve__base matply__custom_curve = dylib.lookupFunction<custom_curve__base__ffi, custom_curve__base>('custom_curve');
late final testArray__base matply__testArray = dylib.lookupFunction<testArray__base__ffi, testArray__base>('testArray');
late final testOmp__base matply__testOmp = dylib.lookupFunction<testOmp__base__ffi, testOmp__base>('testOmp');
late final genTestdatas__base matply__genTestdatas = dylib.lookupFunction<genTestdatas__base__ffi, genTestdatas__base>('genTestdatas');
late final testSingleT__base matply__testSingleT = dylib.lookupFunction<testSingleT__base__ffi, testSingleT__base>('testSingleT');
late final testOmpCanRun__base matply__testOmpCanRun = dylib.lookupFunction<testOmpCanRun__base__ffi, testOmpCanRun__base>('testOmpCanRun');
late final testOmpUniform__base matply__testOmpUniform = dylib.lookupFunction<testOmpUniform__base__ffi, testOmpUniform__base>('testOmpUniform');
late final double Function() matply__testOut = dylib.lookupFunction<Double Function(), double Function()>('testOut');
late final allocateOp__base matply__allocateOp = dylib.lookupFunction<allocateOp__base__ffi, allocateOp__base>('allocateOp');
late final get_multp_shown__base matply__get_multp_shown = dylib.lookupFunction<get_multp_shown__base__ffi, get_multp_shown__base>('get_multp_shown');
late final confront__base matply__confront = dylib.lookupFunction<confront__base__ffi, confront__base>('confront');

late final double Pi = _Pi.value;
late final double e = _e.value;
late final double inf = _inf.value;  // 正无穷大，和Dart的内置相通，下同
late final double negativeinf = -inf;  // 负无穷大
late final double nan = _nan.value;  // 非法数据
late final double euler = _euler.value;  // 欧拉常数

/// 全局的内存管理单例
/// 该内存单例允许：凡是创建一个新Matrix实例，都会主动被检测并添加到内存池中，在程序执行完毕后，可以一键释放。
late final void Function(Pointer<Matrix> matrix) __initMp = dylib.lookupFunction<Void Function(Pointer<Matrix> matrix), void Function(Pointer<Matrix> matrix)>('initMp');
late final void Function(Pointer<Matrix> matrix) Signal = dylib.lookupFunction<Void Function(Pointer<Matrix> matrix), void Function(Pointer<Matrix> matrix)>('addToMp');
late final void Function(bool, bool) __freeMp = dylib.lookupFunction<Void Function(Bool, Bool), void Function(bool, bool)>('freeMp');

/// 简易的随机数拓展
typedef initialize_random_seed__base__ffi = Void Function();
typedef initialize_random_seed__base = void Function();
late final initialize_random_seed__base matply_initialize_random_seed = dylib.lookupFunction<initialize_random_seed__base__ffi, initialize_random_seed__base>('initialize_random_seed');

typedef random__base__ffi = Double Function();
typedef random__base = double Function();
late final random__base matply_random = dylib.lookupFunction<random__base__ffi, random__base>('random1');

typedef randint__base__ffi = Int32 Function(Double lb, Double ub);
typedef randint__base = int Function(double lb, double ub);
late final randint__base matply_randint = dylib.lookupFunction<randint__base__ffi, randint__base>('randint');

typedef randdouble__base__ffi = Double Function(Double lb, Double ub);
typedef randdouble__base = double Function(double lb, double ub);
late final randdouble__base matply_randdouble = dylib.lookupFunction<randdouble__base__ffi, randdouble__base>('randdouble');

typedef random_choice__base__ffi = Double Function(Pointer<Double> arr, Int32 len);
typedef random_choice__base = double Function(Pointer<Double> arr, int len);
late final random_choice__base matply_random_choice = dylib.lookupFunction<random_choice__base__ffi, random_choice__base>('random_choice');

typedef random_choices__base__ffi = Pointer<Double> Function(Pointer<Double> arr, Int32 len, Int32 times, Bool back);
typedef random_choices__base = Pointer<Double> Function(Pointer<Double> arr, int len, int times, bool back);
late final random_choices__base matply_random_choices = dylib.lookupFunction<random_choices__base__ffi, random_choices__base>('random_choices');

typedef perfect_choices__base__ffi = Pointer<Double> Function(Pointer<Double> arr, Pointer<Double> p, Int32 len, Int32 times, Bool back, Int32 method);
typedef perfect_choices__base = Pointer<Double> Function(Pointer<Double> arr, Pointer<Double> p, int len, int times, bool back, int method);
late final perfect_choices__base matply_perfect_choices = dylib.lookupFunction<perfect_choices__base__ffi, perfect_choices__base>('perfect_choices');

/// omp底层优化
typedef set_max_thread_support__base__ffi = Void Function(Int32 n);
typedef set_max_thread_support__base = void Function(int n);
late final set_max_thread_support__base matply_set_max_thread_support = dylib.lookupFunction<set_max_thread_support__base__ffi, set_max_thread_support__base>('set_max_thread_support');

typedef get_max_thread_support__base__ffi = Int32 Function();
typedef get_max_thread_support__base = int Function();
late final get_max_thread_support__base matply_get_max_thread_support = dylib.lookupFunction<get_max_thread_support__base__ffi, get_max_thread_support__base>('get_max_thread_support');

typedef get_max_thread_sys__base__ffi = Int32 Function();
typedef get_max_thread_sys__base = int Function();
late final get_max_thread_sys__base matply_get_max_thread_sys = dylib.lookupFunction<get_max_thread_sys__base__ffi, get_max_thread_sys__base>('get_max_thread_sys');

typedef set_simple_dvcst_value__base__ffi = Void Function(Int64 n);
typedef set_simple_dvcst_value__base = void Function(int n);
late final set_simple_dvcst_value__base matply_set_simple_dvcst_value = dylib.lookupFunction<set_simple_dvcst_value__base__ffi, set_simple_dvcst_value__base>('set_simple_dvcst_value');

typedef get_simple_dvcst_value__base__ffi = Int64 Function();
typedef get_simple_dvcst_value__base = int Function();
late final get_simple_dvcst_value__base matply_get_simple_dvcst_value = dylib.lookupFunction<get_simple_dvcst_value__base__ffi, get_simple_dvcst_value__base>('get_simple_dvcst_value');

typedef set_complex_dvcst_value__base__ffi = Void Function(Int64 n);
typedef set_complex_dvcst_value__base = void Function(int n);
late final set_complex_dvcst_value__base matply_set_complex_dvcst_value = dylib.lookupFunction<set_complex_dvcst_value__base__ffi, set_complex_dvcst_value__base>('set_complex_dvcst_value');

typedef get_complex_dvcst_value__base__ffi = Int64 Function();
typedef get_complex_dvcst_value__base = int Function();
late final get_complex_dvcst_value__base matply_get_complex_dvcst_value = dylib.lookupFunction<get_complex_dvcst_value__base__ffi, get_complex_dvcst_value__base>('get_complex_dvcst_value');

typedef get_time__base__ffi = Double Function();
typedef get_time__base = double Function();
late final get_time__base matply_get_time = dylib.lookupFunction<get_time__base__ffi, get_time__base>('get_time');

typedef set_multp_shown__base__ffi = Void Function(Bool _isShowMultp);
typedef set_multp_shown__base = void Function(bool _isShowMultp);
late final set_multp_shown__base matply_set_multp_shown = dylib.lookupFunction<set_multp_shown__base__ffi, set_multp_shown__base>('set_multp_shown');

typedef multp_msg__base__ffi = Void Function(Int64 dataCounts, Bool multThreads, Bool complex, Pointer<Utf8> name);
typedef multp_msg__base = void Function(int dataCounts, bool multThreads, bool complex, Pointer<Utf8> name);
late final multp_msg__base matply_multp_msg = dylib.lookupFunction<multp_msg__base__ffi, multp_msg__base>('multp_msg');

typedef mixin_multp_msg__base__ffi = Void Function(Int64 dataCounts, Bool multThreads, Bool complex, Pointer<Utf8> name);
typedef mixin_multp_msg__base = void Function(int dataCounts, bool multThreads, bool complex, Pointer<Utf8> name);
late final mixin_multp_msg__base matply_mixin_multp_msg = dylib.lookupFunction<mixin_multp_msg__base__ffi, mixin_multp_msg__base>('mixin_multp_msg');

typedef no_multp_msg__base__ffi = Void Function(Int64 dataCounts, Bool complex, Pointer<Utf8> name);
typedef no_multp_msg__base = void Function(int dataCounts, bool complex, Pointer<Utf8> name);
late final no_multp_msg__base matply_no_multp_msg = dylib.lookupFunction<no_multp_msg__base__ffi, no_multp_msg__base>('no_multp_msg');

typedef set_simple_dvcst_value_force__base__ffi = Void Function(Int64 n);
typedef set_simple_dvcst_value_force__base = void Function(int n);
late final set_simple_dvcst_value__base matply_set_simple_dvcst_value_force = dylib.lookupFunction<set_simple_dvcst_value_force__base__ffi, set_simple_dvcst_value_force__base>('set_simple_dvcst_value_force');

typedef set_complex_dvcst_value_force__base__ffi = Void Function(Int64 n);
typedef set_complex_dvcst_value_force__base = void Function(int n);
late final set_complex_dvcst_value_force__base matply_set_complex_dvcst_value_force = dylib.lookupFunction<set_complex_dvcst_value_force__base__ffi, set_complex_dvcst_value_force__base>('set_complex_dvcst_value_force');

