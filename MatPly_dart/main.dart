import 'dart:ffi';
import 'matply.dart';

main(){
  MatrixType matrixType = MatrixType(
      [[1, 2, 3], [4, 4, 4], [7, 0, 9]]
  );
  matrixType.visible();
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
}
