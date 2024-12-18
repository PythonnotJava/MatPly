part of '../core.dart';

late final _MtCppApi = MatrixCppApi.instance;

extension MatplyTypeCppExtension on MatrixType{
  /// Random Module
  Object getMode({int dim = -1}){
    Pointer<Double> op;
    Object target;
    switch(dim){
      case 0:
        op = _MtCppApi.mode(shape[0], shape[1], self.ref.data, 0);
        target = op.asTypedList(shape[0]).toList();
        break;
      case 1:
        op = _MtCppApi.mode(shape[0], shape[1], self.ref.data, 1);
        target = op.asTypedList(shape[1]).toList();
        break;
      default:
        op = _MtCppApi.mode(shape[0], shape[1], self.ref.data, -1);
        target = op.value;
        break;
    }
    freeOp(op);
    return target;
  }
}