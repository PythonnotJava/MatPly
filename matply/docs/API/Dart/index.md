# 如何构建Dart版本的API？

> MatPly for Dart使用Dart FFI提供的C语言接口，将原生C语言代码编译为各个平台的链接库（这里是Windows下的dll文件），具体流程可参考[https://dart.dev/interop/c-interop](https://dart.dev/interop/c-interop)

## C原生函数与常量
> 对矩阵的一系列操作，完全使用C语言实现，而在Dart中，只需要在封装功能时做好错误检查即可。
> 
> 常量系列，完全采用C原生Math库中的常量，而且解析到Dart中，是完全支持Dart的语法分析的，如下案例

```dart
import 'lib/matply.dart';

/// Constant tests
main(){
  print(e);
  print(Pi);
  print(nan.isNaN);
  print(inf.isInfinite);
  print(negativeinf.isNegative);
  print(e * inf);
}

/* outputs : 
2.718281828459045
3.141592653589793
true
true
true
Infinity
* */
```

