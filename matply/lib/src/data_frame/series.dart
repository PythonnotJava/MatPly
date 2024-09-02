import 'dart:ffi';

final class Series<T>{
  late final bool horizontal;
  late final Pointer<Double> data;
  late final int row;
  late final int column;
  late String? whatthis;
  late final T series;
  late final List<T> labels;
  Series(
    this.data, {
    required this.horizontal,
    required List<T> labels,
    required this.series,
    String? whatthis
  }){
    int len = labels.length;
    this.labels = labels;
    if (horizontal){
      row = 1;
      column = len;
    }else{
      row = len;
      column = 1;
    }
    this.whatthis = whatthis != null ? whatthis : 'Unknow';
  }

  List<int> get shape => [row, column];

  @override
  String toString() {
    final buffer = StringBuffer();
    buffer.write('Series description : $whatthis\n');
    for (int i = 0; i < labels.length; i++)
      buffer.writeln("${labels[i]}\t${data[i]}");
    buffer.write("series : $series\n");
    buffer.write('shape : $shape');
    return buffer.toString();
  }

  Map<T, double> toMap(){
    final Map<T, double> map = {};
    for (int i = 0; i < labels.length; i++) {
      map[labels[i]] = data[i];
    }
    return map;
  }
}

