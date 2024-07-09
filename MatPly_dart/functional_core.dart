// 函数式构造法
import 'package:ffi/ffi.dart';

import 'matply_api.dart';

void set_round(String format) => matply__set__round(format.toNativeUtf8());