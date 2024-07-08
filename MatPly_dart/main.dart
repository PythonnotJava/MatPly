import 'dart:ffi';
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
  MatrixType mt = MatrixType([
    [3, 6, 2],
    [0, 9, 2],
    [1, 1, 6]
  ]);
  mt.visible();
  print(mt.det);
  print(mt.trace);
  mt.cofactor(1, 1).visible();
  mt.inv!.visible();
  mt.adj.visible();
  var d = MatrixType.deepCopy(mt);
  print(d.hashCode);
  print(mt.hashCode);
  d.visible();
}
