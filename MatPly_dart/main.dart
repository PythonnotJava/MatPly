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
  set_visible_round('%.8f');
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
  // mt4.cutfree(row: 2, column:  5, width: 2, height: 3).visible();
  // mt4.visible();
  // mt4.resize(row: 2, column: 2, horizontal: true).visible();
  // mt4.resize(row: 2, column: 2, horizontal: false).visible();
  // mt4..resize_no_returned(row: 3, column: 4)..visible()..resize_no_returned(row: 5, column: 3, number: 100)..visible();
  // mt4
  //   ..resize_no_returned(row: 3, column: 2, horizontal: false)
  //   ..visible()
  //   ..resize_no_returned(row: 4, column: 3, horizontal: false ,number: 111)
  //   ..visible();
  // print(nan.isNaN);
  // print(inf);
  // matply__setSeed(1);
  // print(e);
  // print(Pi);
  // print(nan);
  // print(inf);
  // print(negativeinf);
  // print(inf + negativeinf);
  // print(negativeinf.isInfinite);
  // print(nan.isNaN);
  // MatrixType mt8 = MatrixType([
  //   [3, 6, 2, 10, -0.1, -inf],
  //   [0, 9, 2, 4, 6, 0],
  //   [1, 1, nan, 4, 6, inf]
  // ]);
  // mt8.visible();
  // mt8.exp.visible();
  // mt8.ceil.visible();
  // mt8.cos.visible();
  // mt8.power(number: 3, reverse: true).visible();
  // mt8.power(number: 3, reverse: false).visible();
  // print(mt8.toString());
  // mt8.softmax(dim: -1).visible();
  // mt8.softmax(dim: 0).visible();
  // mt8.softmax(dim: 1).visible();
  // mt8.sigmoid().visible();
  // set_seed(412);
  // mt8..shuffle()..visible();
  // set_seed(12);
  // mt8..shuffle()..visible();
  // mt8.sort(dim: -1, mask_nan: -100).visible();
  // mt8.sort(dim: 0, mask_nan: 100).visible();
  // mt8.sort(dim: 1, mask_nan: e).visible();
  // mt8..sort_no_returned(dim: 1, mask_nan: e)..visible();
  set_visible_round('%.3f,');
  // MatrixType.uniform(row: 10, column: 100, start: 1, end: 2, seed: 42).visible();
  // MatrixType.normal(row: 10, column: 100, mu: 2, sigma: 1.5).visible();
  // MatrixType.poisson(lambda: 5, row: 1, column: 1000).visible();
  // MatrixType mt8 = MatrixType([
  //   [3, 6, 2, 10, -0.1, -inf],
  //   [0, 9, 2, 4, 6, 0],
  //   [1, 1, nan, 4, 6, inf]
  // ]);
  // mt8.visible();
  // print(mt8.rank);
  // mt8..setMask(mask_nan: 2, mask_inf: 1, isNegativeInf: true, both: true)..visible();
  // mt8.rref().visible();
  MatrixType mt10 = MatrixType( [
      [1.0, 2.0, 3.0, 4.0, 5.0],
      [6.0, 7.0, 8.0, 9.0, 10.0],
      [11.0, 12.0, 13.0, 14.0, 15.0]
  ]);
  mt10.visible();
  mt10.rref().visible();
  print(mt10.rank);
}
