import 'dart:ffi';
import 'package:ffi/ffi.dart';
import 'package:path/path.dart';

import 'matply.dart';

main(){
  // MatrixType matrixType = MatrixType(
  //     [[1, 2, 3], [4, 4, 4], [7, 0, 9], [3, 7, 0]],
  //   singularMatrix: true
  // );
  // matrixType.visible();
  // print(matrixType.shape);
  // print(matrixType.self.ref.spc);
  // matrixType.visible_spc();
  // var m = MatrixType.filled(number:   4.1 ,row: 4, column: 3, upperTriangularMatrix: true);
  // print(m.runtimeType);
  // m.visible_spc();
  // m.visible();
  // MatrixType.ones(row: 3, column: 4).visible();
  // print(matrixType.row_<Pointer>(2));
  // print(matrixType.row_<List>(2));
  // print(matrixType.column_<List>(2));
  // print(matrixType.at(2, 2));
  // print((matrixType[0] as List)[2]);
  // print(matrixType[0]![2]);
  // print(identityHashCode(matrixType));
  // print(identityHashCode(MatrixType.deepCopy(matrixType)));
  // MatrixType fill5 = MatrixType.filled(number: 5, row: 3, column: 5);
  // fill5.visible();
  // fill5.visible_spc();
  // var t = matrixType.T_;
  // t.visible();
  // // t.visible_spc();
  // t.exchange_row(2, 1);
  // t.visible();
  // t.exchange_column(1, 3);
  // t.visible();
  // matrixType.minus(number: 4).visible();
  // matrixType.visible();
  // matrixType.minus_no_returned(number: 2);
  // matrixType.visible();
  // MatrixType matrixType = MatrixType.arrange(start: .0, row: 4, column: 3);
  // matrixType.visible();
  // MatrixType matrixType1 = MatrixType.linspace(start: 0, end: 5, row: 3, column: 4, keep: false);
  // matrixType1.visible();
  // matrixType.matmul(matrixType1).visible();
  // (matrixType / 2).visible();
  // (matrixType * 2).visible();
  // matrixType.kronecker(matrixType1).visible();
  // MatrixType.E(n: 5)..visible()..visible_spc();
  set_round('%.8f');
  MatrixType mt = MatrixType([
    [3, 6, 2],
    [0, 9, 2],
    [1, 1, 6]
  ]);
  // mt.visible();
  // print(mt.det);
  // print(mt.trace);
  // mt.cofactor(1, 1).visible();
  // mt.inv!.visible();
  // mt.adj.visible();
  // var d = MatrixType.deepCopy(mt);
  // print(d.hashCode);
  // print(mt.hashCode);
  // d.visible();
  // print(mt.max());
  // print(mt.max(dim: 0));
  // print(mt.max(dim: 1));
  // MatrixType mt2 = MatrixType([
  //   [13, 6, 2],
  //   [0, 9, -2],
  //   [3, 13, -6]
  // ]);
  // mt2.visible();
  // print(mt == mt2);
  // print(mt < mt2);
  // print(mt <= mt2);
  // print(mt.compare(mt2));
  // print(matply__set__round.runtimeType);
  MatrixType mt4 = MatrixType([
    [3, 6, 2, 10, -34, 2],
    [0, 9, 2, 4, 6, 0],
    [1, 1, 6, 4, 6, 2]
  ]);
  // MatrixType e2 = MatrixType.E(n: 3);
  // MatrixType e3 = MatrixType.E(n: 6);
  // mt4.cut(row: 1, column: 2, width: 3, height: 2).visible();
  // mt4.cutfree(row: 2, column: 5, width: 6, height: 6, number: 5).visible();
  // e2.concat(other: mt4, horizontal: true).visible();
  // e3.concat(other: mt4, horizontal: false).visible();
  // MatrixType mt5 = MatrixType.deepCopy(mt4);
  // mt5 << [2, 9];
  // mt5.visible();
  // MatrixType mt6 = mt4.reshape(row: 6, column: 3);
  // mt6.visible();
  mt4.resize(row: 2, column: 2, horizontal: true).visible();
  // mt4.resize(row: 2, column: 2, horizontal: false).visible();

}
