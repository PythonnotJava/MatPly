part of '../core.dart';

String __login_platform_cpp(){
  if (Platform.isWindows) {
    return 'cpp_extension.dll';
  } else if (Platform.isLinux || Platform.isAndroid) {
    return 'cpp_extension.so';
  } else
    throw UnsupportedError('This platform is not supported');
}

late final String platform_cpp = __login_platform_cpp();

/// C++ Extension for C
class MatrixCppApi {
  // 发布时
  static MatrixCppApi get instance => MatrixCppApi(DynamicLibrary.open(
      path.join(pubCacheDir, 'lib/src/Cpp', platform_cpp)));
  // 开发时
  // static MatrixCppApi get instance => MatrixCppApi(DynamicLibrary.open(
  //     path.join(pubCacheDir, '../', 'cpp_extension.dll')));
  /// Holds the symbol lookup function.
  final Pointer<T> Function<T extends NativeType>(String symbolName)
  _lookup;

  /// The symbols are looked up in [dynamicLibrary].
  MatrixCppApi(DynamicLibrary dynamicLibrary)
      : _lookup = dynamicLibrary.lookup;

  /// The symbols are looked up with [lookup].
  MatrixCppApi.fromLookup(
      Pointer<T> Function<T extends NativeType>(String symbolName)
      lookup)
      : _lookup = lookup;

  /// 获取中位数
  Pointer<Double> mode(
      int row,
      int column,
      Pointer<Pointer<Double>> data,
      int dim,
      ) {
    return _mode(
      row,
      column,
      data,
      dim,
    );
  }

  late final _modePtr = _lookup<
      NativeFunction<
          Pointer<Double> Function(Int, Int,
              Pointer<Pointer<Double>>, Int)>>('mode');
  late final _mode = _modePtr.asFunction<
      Pointer<Double> Function(
          int, int, Pointer<Pointer<Double>>, int)>();

  void registerObject(
      Pointer<Void> obj,
      int id,
      ) {
    return _registerObject(
      obj,
      id,
    );
  }

  late final _registerObjectPtr = _lookup<
      NativeFunction<
          Void Function(Pointer<Void>, Int)>>('registerObject');
  late final _registerObject = _registerObjectPtr
      .asFunction<void Function(Pointer<Void>, int)>();

  void unregisterObject(
      Pointer<Void> obj,
      ) {
    return _unregisterObject(
      obj,
    );
  }

  late final _unregisterObjectPtr =
  _lookup<NativeFunction<Void Function(Pointer<Void>)>>(
      'unregisterObject');
  late final _unregisterObject =
  _unregisterObjectPtr.asFunction<void Function(Pointer<Void>)>();

  void freeHashMap() {
    return _freeHashMap();
  }

  late final _freeHashMapPtr =
  _lookup<NativeFunction<Void Function()>>('freeHashMap');
  late final _freeHashMap = _freeHashMapPtr.asFunction<void Function()>();

  Pointer<NativeFunction<Double Function(Double)>> poly(
      Pointer<Double> coefs,
      Pointer<Double> powers,
      int len,
      ) {
    return _poly(
      coefs,
      powers,
      len,
    );
  }

  late final _polyPtr = _lookup<
      NativeFunction<
          Pointer<NativeFunction<Double Function(Double)>> Function(
              Pointer<Double>,
              Pointer<Double>,
              Int)>>('poly');
  late final _poly = _polyPtr.asFunction<
      Pointer<NativeFunction<Double Function(Double)>> Function(
          Pointer<Double>, Pointer<Double>, int)>();

  void freepoly(
      Pointer<PolyElement> polyElement,
      ) {
    return _freepoly(
      polyElement,
    );
  }

  late final _freepolyPtr =
  _lookup<NativeFunction<Void Function(Pointer<PolyElement>)>>(
      'freepoly');
  late final _freepoly =
  _freepolyPtr.asFunction<void Function(Pointer<PolyElement>)>();
}

/// 多项式函数的创建与释放
/// id = 0
final class PolyElement extends Struct {
  external Pointer<Double> coefs;

  external Pointer<Double> powers;

  @Int()
  external int len;
}