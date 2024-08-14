part of '../core.dart';

late final _MtCppApi = MatrixCppApi.instance;

extension MatplyTypeCppExtension on MatrixType{
  /// Random Module
  Object getMode({int dim = -1}){
    switch(dim){
      case 0:
        return _MtCppApi.mode(shape[0], shape[1], self.ref.data, 0).asTypedList(shape[0]).toList();
      case 1:
        return _MtCppApi.mode(shape[0], shape[1], self.ref.data, 1).asTypedList(shape[1]).toList();
      default:
        return _MtCppApi.mode(shape[0], shape[1], self.ref.data, -1).value;
    }
  }
}