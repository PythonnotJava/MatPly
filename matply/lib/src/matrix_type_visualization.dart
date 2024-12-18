/// 矩阵相关的数据可视化过程与可视化分支

part of 'core.dart';

extension Visualization on MatrixType{
  Object Hist({int dim = -1}){
    double key;
    switch(dim){
      case 0:
        Map<double, int> hs;
        List<Map<double, int>> hist = [];
        for (int r = 0;r < shape[0];r++){
          hs = {};
          for(int c = 0;c < shape[1];c ++){
            key = self.ref.data[r][c];
            if (hist.contains(key))
              hs[key] = hs[key]! + 1;
            else
              hs[key] = 1;
          }
          hist.add(hs);
        }
        return hist;
      case 1:
        Map<double, int> hs;
        List<Map<double, int>> hist = [];
        for (int c = 0;c < shape[1];c ++){
          hs = {};
          for(int r = 0;r < shape[0];r ++){
            key = self.ref.data[r][c];
            if (hist.contains(key))
              hs[key] = hs[key]! + 1;
            else
              hs[key] = 1;
          }
          hist.add(hs);
        }
        return hist;
      default:
        Map<double, int> hist = {};
        for (int r =0;r < shape[0];r++){
          for(int c = 0;c < shape[1];c ++){
            key = self.ref.data[r][c];
            if (hist.containsKey(key))
              hist[key] = hist[key]! + 1;
            else
              hist[key] = 1;
          }
        }
        return hist;
    }
  }

  Object Bar(
    dynamic Function(double) condition, {
    dynamic Function(dynamic condition_result)? reflect,
    int dim = -1
  }){
    dynamic key;
    double data;
    switch(dim){
      case 0:
        List<Map<dynamic, int>> hist = [];
        if (reflect == null) {
          for (int r = 0; r < shape[0]; r++) {
            Map<Object, int> hs = {};
            for (int c = 0; c < shape[1]; c++) {
              data = self.ref.data[r][c];
              key = condition(data);
              if (hs.containsKey(key))
                hs[key] = hs[key]! + 1;
              else
                hs[key] = 1;
            }
            hist.add(hs);
          }
        } else{
          for (int r = 0; r < shape[0]; r++) {
            Map<Object, int> hs = {};
            for (int c = 0; c < shape[1]; c++) {
              data = self.ref.data[r][c];
              key = reflect(condition(data));
              if (hs.containsKey(key))
                hs[key] = hs[key]! + 1;
              else
                hs[key] = 1;
            }
            hist.add(hs);
          }
        }
        return hist;
      case 1:
        List<Map<dynamic, int>> hist = [];
        if (reflect == null){
          for (int c = 0;c < shape[1];c ++){
            Map<Object, int> hs = {};
            for(int r = 0;r < shape[0];r++){
              data = self.ref.data[r][c];
              key = condition(data);
              if (hs.containsKey(key))
                hs[key] = hs[key]! + 1;
              else
                hs[key] = 1;
            }
            hist.add(hs);
          }
        }else{
          for (int c = 0;c < shape[1];c ++){
            Map<Object, int> hs = {};
            for(int r = 0;r < shape[0];r++){
              data = self.ref.data[r][c];
              key = reflect(condition(data));
              if (hs.containsKey(key))
                hs[key] = hs[key]! + 1;
              else
                hs[key] = 1;
            }
            hist.add(hs);
          }
        }
        return hist;
      default:
        Map<dynamic, int> hist = {};
        if (reflect == null){
          for (int r =0;r < shape[0];r++){
            for(int c = 0;c < shape[1];c ++){
              data = self.ref.data[r][c];
              key = condition(data);
              if (hist.containsKey(key))
                hist[key] = hist[key]! + 1;
              else
                hist[key] = 1;
            }
          }
        }else{
          for (int r =0;r < shape[0];r++){
            for(int c = 0;c < shape[1];c ++){
              data = self.ref.data[r][c];
              key = reflect(condition(data));
              if (hist.containsKey(key))
                hist[key] = hist[key]! + 1;
              else
                hist[key] = 1;
            }
          }
        }
        return hist;
    }
  }
  
  String toMarkdownTable<T>({
    List<Object>? rls,
    List<Object>? cls,
    String rowLack = 'row',
    String colLack = 'col',
    int? format
  }) {

    var [row, column] = this.shape;
    // 使用提供的标签或默认标签，并补充缺失的标签
    rls = rls ?? List.generate(row, (index) => index, growable: true);
    cls = cls ?? List.generate(column, (index) => index, growable: true);

    // 如果行标签长度不足，补充缺失的标签
    if (rls.length < row) {
      rls = List<Object>.from(rls)..addAll(List.generate(row - rls.length, (index) => '$rowLack$index'));
    }

    // 如果列标签长度不足，补充缺失的标签
    if (cls.length < column) {
      cls = List<Object>.from(cls)..addAll(List.generate(column - cls.length, (index) => '$colLack$index'));
    }

    // 构建表头
    StringBuffer buffer = StringBuffer();
    buffer.write('|   |');
    for (var label in cls) {
      buffer.write(' $label |');
    }
    buffer.writeln();

    // 构建分隔行
    buffer.write('|---|');
    for (int i = 0; i < column; i++) {
      buffer.write('---|');
    }
    buffer.writeln();

    // 构建数据行
    if (format == null) {
      for (int r = 0; r < row; r++) {
        buffer.write('| ${rls[r]} |');
        for (int c = 0; c < column; c++) {
          buffer.write(' ${this.at(r, c)} |');
        }
        buffer.writeln();
      }
    }else{
      assert (format >=0);
      for (int r = 0; r < row; r++) {
        buffer.write('| ${rls[r]} |');
        for (int c = 0; c < column; c++) {
          buffer.write(' ${this.at(r, c).toStringAsFixed(format)} |');
        }
        buffer.writeln();
      }
    }
    return buffer.toString();
  }
}