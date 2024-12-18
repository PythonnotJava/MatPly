/// matply底层的快速测试工具，由底层各个模块提供，同时也包括一些实用基础工具集
/// 部分函数建议开发使用
/// 构造一个NativeCallable.isolateLocal，必须从创建它的同一线程调用
/// 而NativeCallable.listener构造一个可以从任何线程调用的NativeCallable
part of 'core.dart';

// 测试matply-api
dynamic debugmatply_api<T>(T Function() func, [String info = 'Error Here']) {
  try {
    return func();
  } catch (e) {
    print('$info: ${e.toString()}');
  }
}

// 测试一个一维数组指针
void TestOneArrayPointer(int len, Pointer<Double> data){
  for (int r = 0;r < len;r++) {
    print(data[r]);
  }
}

// 测试一个二维数组指针
void TestArrayPointer(int row, int column, Pointer<Pointer<Double>> data){
  for (int r = 0;r < row;r++){
    for (int c = 0;c < column;c ++){
      print(data[r][c]);
    }
  }
}

// 申请一维泛型指针，0 == Double，1 == Int32，其他 == Bool
Pointer<Void> allocateOp(int len, int mode) => matply__allocateOp(len, mode);
// 释放一维泛型指针
void freeOp(Pointer op) => matply__freeOp(op.cast<Void>());
// 释放二维泛型指针
void freeTp(Pointer<Pointer> op, int row) => matply__freeppvoid(op.cast<Pointer<Void>>(), row);

// 一维列表转一维数组
Pointer<Double> oneListToArray(List<double> data){
  int len = data.length;
  Pointer<Double> op = allocateOp(len, 0).cast<Double>();
  for (int r = 0;r < len;r++) {
    op[r] = data[r];
  }
  return op;
}
Pointer<Int32> oneListToArrayInt32(List<int> data){
  int len = data.length;
  Pointer<Int32> op = allocateOp(len, 1).cast<Int32>();
  for (int r = 0;r < len;r++) {
    op[r] = data[r];
  }
  return op;
}

// 测试omp是否对Dart有效
void justTestOmp() => matply__testOmp();

// 更新测试
MatrixType justTestArray({required int row, required int column}) {
  assert(row > 0 && column > 0);
  return MatrixType.__fromDataPointer(matply__testArray(row, column), [row, column]);
}

// 可视化线程信息
void multp_msg(int dataCounts, bool multThreads, bool complex, String name) =>
    matply_multp_msg(dataCounts, multThreads, complex, name.toNativeUtf8());
// 多种循环混合可视化线程信息
void mixin_multp_msg(int dataCounts, bool multThreads, bool complex, String name) =>
    matply_mixin_multp_msg(dataCounts, multThreads, complex, name.toNativeUtf8());
// 未优化函数记录
void no_multp_msg(int dataCounts, bool complex, String name) => matply_no_multp_msg(dataCounts, complex, name.toNativeUtf8());

// 快速测试
double testOut() => matply__testOut();

// 可视化异步信息
void async_model_showm(int dataCounts, String name){
  if(get_multp_shown()) {
    print("Function named < $name > infos :");
    print("\t- This is a native asynchronous function.");
    print("\t- Amount of data processed : $dataCounts.");
  }
}

// 根据行列索引快速测试数据
MatrixType genTestdatas({
  required int row,
  required int column,
  required double Function(double r, double c) func
}) {
  assert(row > 0 && column > 0);
  NativeCallable<Double Function(Double, Double)> _func =
      NativeCallable<Double Function(Double, Double)>.isolateLocal(func,
          exceptionalReturn: double.nan);
  var shape = [row, column];
  MatrixType mt = MatrixType.__fromDataPointer(matply__genTestdatas(row, column, _func.nativeFunction), shape);
  _func.close();
  return mt;
}

// 仅分配内存的模式
Pointer<Pointer<Double>> justAllocateButNoNumbers(
    {required int row, required int column}) {
  assert(row > 0 && column > 0);
  return matply__allocateButNoNumbers(row, column);
}

// 空矩阵
@Alert("Maybe dangerous")
MatrixType justEmptyMatrix({required int row, required int column}) {
  assert(row > 0 && column > 0);
  return MatrixType.__fromDataPointer(
      matply__allocateButNoNumbers(row, column), [row, column]);
}

// 单线程回调函数测试
MatrixType justTestSingleT({
  required int row,
  required int column,
  required double Function(int r, int c) func
}) {
  assert(row > 0 && column > 0);
  NativeCallable<Double Function(Int32, Int32)> _func =
      NativeCallable<Double Function(Int32, Int32)>.isolateLocal(func,
          exceptionalReturn: double.nan);
  var shape = [row, column];
  MatrixType mt = MatrixType.__fromDataPointer(
      matply__testSingleT(row, column, _func.nativeFunction), shape);
  _func.close();
  return mt;
}

// 对底层openmp多线程函数回调
// 多线程必须NativeCallable<T>.listener
// 但是多次测试表明，Dart原生处理却比C+openmp更快
// 怀疑点：是不是每次函数都被包装了一次，而不是一次创建永久使用
// Question solved by: https://github.com/dart-lang/sdk/issues/59680#issuecomment-2526570241
typedef CallBackUp = Void Function(Int32, Int32, Pointer<Pointer<Double>>);
Future<MatrixType> justTestOmpCanRun({
  required int row,
  required int column,
  required double Function(int, int) func,
}) async {
  assert(row > 0 && column > 0);
  Pointer<Pointer<Double>> data = matply__allocateButNoNumbers(row, column);  // Just allocate memory
  if (row * column <= 100000){
    final NativeCallable<CallBackUp> callback = NativeCallable<CallBackUp>.listener((int r, int c, Pointer<Pointer<Double>> data) {
      data[r][c] = func(r, c);  // Wrap it as a void function according to the documentation
    });
    matply__testOmpCanRun(row, column, data, callback.nativeFunction);
    // Add a delay to allow OpenMP computation to complete before closing the callback
    await Future.delayed(const Duration(milliseconds: 100), () {
      callback.close();
    });
  }else{
    List<Future<void>> futures = [];
    for (int r = 0; r < row; r++) {
      futures.add(Future(() {
        for (int c = 0; c < column; c ++) {
          data[r][c] = func(r, c);
        }
      }));
    }
    await Future.wait(futures);
  }
  return MatrixType.__fromDataPointer(data, [row, column]);
}

// 测试多线程下的均匀分布
MatrixType testOmpUniform({required int row, required int column}){
  assert(row > 0 && column > 0);
  return MatrixType.__fromDataPointer(matply__testOmpUniform(row, column), [row, column]);
}

// 判断两个数据一样，为什么要这样？
// Matply底层才用double而不是long，当涉及到大量数据计算时，会出现精度问题
// 这个问题暂不解决
bool equal(double v1, double v2){
  return v1 < v2 ? v2 - v1 <= get_round() : v1 - v2 <= get_round();
}
