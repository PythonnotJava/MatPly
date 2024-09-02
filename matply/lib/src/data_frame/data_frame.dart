import 'dart:ffi';
import '../core.dart';
import 'series.dart';

class Dataframe<T> extends MatrixType{
  late final List<T> rowLabels;
  late final List<T> colLabels;
  late final String? whatthis;
  Dataframe(super.data, {required this.rowLabels, required this.colLabels, String? whatthis}){
    assert(shape[0] == rowLabels.length && shape[1] == colLabels.length);
    this.whatthis = whatthis == null? 'Unknow' : whatthis;
  }

  /// 包装一个MatrixType实例成为Dataframe实例
  Dataframe.fromMatrixType(MatrixType mt, {required this.rowLabels, required this.colLabels, String? whatthis}):
  super.fromPointer(mt.self){
    var [row, column] = mt.shape;
    assert (row == rowLabels.length && column == colLabels.length);
    this.whatthis = whatthis == null? 'DataFrame' : whatthis;
  }

  @override
  String toString() {
    print('DataFrame description : $whatthis');
    return super.toString();
  }

  @override
  Series<T> operator [](Object indice) {
    if (indice is int)
      return Series(
          super.row_<Pointer>(indice) as Pointer<Double>,
          horizontal: true,
          labels: colLabels,
          series: rowLabels[indice]
      );
    int index = rowLabels.indexOf(indice as T);
    if (index != -1)
      return Series(
          super.row_<Pointer>(index) as Pointer<Double>,
          horizontal: true,
          labels: colLabels,
          series: rowLabels[index]
      );
    else
      throw "Cannot find the label that matches your input!";
  }

  Series<T> loc(T indice, {bool horizontal = true}){
    int index = (horizontal? rowLabels : colLabels).indexOf(indice);
    if (index != -1)
      return Series(
          horizontal? super.row_<Pointer>(index) as Pointer<Double>
              :super.column_<Pointer>(index) as Pointer<Double>,
          horizontal: horizontal,
          labels: horizontal? colLabels: rowLabels,
          series: indice
      );
    else
      throw "Cannot find the label that matches your input!";
  }

  List<Series<T>> locs(Object indice, {bool horizontal = true}){
    if (indice is List)
      return List.generate(indice.length, (i) => loc(indice[i], horizontal: horizontal));
    else if (indice is (T, T)){
      List<T> temp = horizontal? rowLabels : colLabels;
      int from = temp.indexOf(indice.$1);
      int to = temp.indexOf(indice.$2);
      assert (from < to);
      if (from != -1 && to != -1)
        return List.generate(from - to, (i) => loc(temp[from + i], horizontal: horizontal));
      else
        throw "Cannot find the label that matches your input!";
    }else
      throw UnsupportedError('Unsupported indexing method.');
  }

  Series<T> iloc(int indice, {bool horizontal = true}){
    return Series(
        horizontal?super.row_<Pointer>(indice) as Pointer<Double>
            :super.column_<Pointer>(indice) as Pointer<Double>,
        horizontal: horizontal,
        labels: horizontal?colLabels : rowLabels,
        series: horizontal?rowLabels[indice] : colLabels[indice]
    );
  }

  List<Series<T>> ilocs(Object indice, {bool horizontal = true}){
    if (indice is List)
      return List.generate(indice.length, (i) => iloc(i, horizontal: horizontal));
    else if (indice is (int, int)) {
      assert(indice.$1 < indice.$2);
      return List.generate(indice.$2 - indice.$1, (i) => iloc(i + indice.$1, horizontal: horizontal));
    }else
      throw UnsupportedError('Unsupported indexing method.');
  }
}

main(){
  Dataframe dataframe = Dataframe(
      [[2.0, 4, 2], [2, 5, 1]],
      rowLabels: ['A', 'B'],
      colLabels: ['T1', 'T2', 'T3'],
      whatthis: 'DES'
  );
  var s1 = dataframe[1];
  print(s1);
  dataframe.self.ref.data[1] = ([3, 2, 1]).getOnePointer();
  print(s1);

}