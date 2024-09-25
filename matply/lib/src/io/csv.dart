import 'dart:convert' show Encoding, utf8;
import 'dart:io' show File;
import '../core.dart' show MatrixType;

class CSVReader{
  late final String path;
  List<String>? rowLabels;
  List<String>? colLabels;
  List<int>? shape;
  List<List<String>>? content;
  List<List<double>>? data;

  CSVReader(this.path) : assert(File(path).existsSync());

  Future<void> read_csv_async({
    bool first_col_is_labels = true,
    String loss_column_label = "Unnamed",
    Encoding encoding = utf8
  }) async {
    final file = File(path);
    final csvString = await file.readAsString(encoding: encoding);
    final List<List<String>> result = [];
    final lines = csvString.split('\n');
    List<String> _cols = [];
    var [row, col] = [0, 0];
    col = first_col_is_labels ? lines[0].split(',').length - 1: lines[0].split(',').length;
    if (!first_col_is_labels) {
      int _counter = -1;
      for (var line in lines) {
        final fields = line.split(',').map((field) => field.trim()).toList();
        var len = fields.length;
        if (len != col) {
          int require = col - len;
          fields.forEach((i) => i.trim().isEmpty? null.toString(): i);
          fields.addAll(List.generate(require, (_) => null.toString()));
        }
        result.add(fields);
        _cols.add('${loss_column_label}${_counter++}');
        row++;
      }
    } else{
      for (var line in lines) {
        final fields = line.split(',').map((field) => field.trim()).toList();
        var r = fields.removeAt(0);
        var len = fields.length;
        if (len != col) {
          int require = col - len;
          fields.forEach((i) => i.trim().isEmpty? null.toString(): i);
          fields.addAll(List.generate(require, (_) => null.toString()));
        }
        result.add(fields);
        _cols.add(r);
        row++;
      }
    }
    _cols.removeAt(0);
    this.shape = [row - 1, col];
    this.rowLabels = result[0];
    this.colLabels = _cols;
    this.content = result;
  }

  Future<List<List<double>>> convertToNumberAsync({double replace = double.nan}) async{
    if (content == null) throw Exception("CSV content is null");
    var [row, column] = this.shape!;
    List<List<double>> numericContent = List<List<double>>.generate(row, (i) => List.generate(
      column, (j){
        String cell = content![i][j];
        return double.tryParse(cell) ?? replace;
      }
    ));
    this.data = numericContent;
    return this.data!;
  }

  void read_csv_sync({
    bool first_col_is_labels = true,
    String loss_column_label = "Unnamed",
    Encoding encoding = utf8
  }) {
    final file = File(path);
    final csvString = file.readAsStringSync(encoding: encoding);
    final List<List<String>> result = [];
    final lines = csvString.split('\n');
    List<String> _cols = [];
    var [row, col] = [0, 0];
    col = first_col_is_labels ? lines[0].split(',').length - 1: lines[0].split(',').length;
    if (!first_col_is_labels) {
      int _counter = -1;
      for (var line in lines) {
        final fields = line.split(',').map((field) => field.trim()).toList();
        var len = fields.length;
        if (len != col) {
          int require = col - len;
          fields.forEach((i) => i.trim().isEmpty? null.toString(): i);
          fields.addAll(List.generate(require, (_) => null.toString()));
        }
        result.add(fields);
        _cols.add('${loss_column_label}${_counter++}');
        row++;
      }
    } else{
      for (var line in lines) {
        final fields = line.split(',').map((field) => field.trim()).toList();
        var r = fields.removeAt(0);
        var len = fields.length;
        if (len != col) {
          int require = col - len;
          fields.forEach((i) => i.trim().isEmpty? null.toString(): i);
          fields.addAll(List.generate(require, (_) => null.toString()));
        }
        result.add(fields);
        _cols.add(r);
        row++;
      }
    }
    _cols.removeAt(0);
    this.shape = [row - 1, col];
    this.rowLabels = result[0];
    this.colLabels = _cols;
    this.content = result;
  }

  List<List<double>> convertToNumberSync({double replace = double.nan}) {
    if (content == null) throw Exception("CSV content is null");
    var [row, column] = this.shape!;
    List<List<double>> numericContent = List<List<double>>.generate(row, (i) => List.generate(
        column, (j){
      String cell = content![i][j];
      return double.tryParse(cell) ?? replace;
    }
    ));
    this.data = numericContent;
    return this.data!;
  }
}

extension CSV on MatrixType{
  static Future<MatrixType> read_csv_async(
    String path, {
    bool first_col_is_labels = true,
    String loss_column_label = "Unnamed",
    Encoding encoding = utf8,
    double replace = double.nan
  }) async{
    final csvr = new CSVReader(path);
    await csvr.read_csv_async(
        first_col_is_labels: first_col_is_labels,
        loss_column_label: loss_column_label,
        encoding: encoding
    );
    var [row, column] = csvr.shape!;
    List<List<double>> data = await csvr.convertToNumberAsync(replace: replace);
    return MatrixType(data, row: row, column: column);
  }

  static MatrixType read_csv_sync(
    String path, {
    bool first_col_is_labels = true,
    String loss_column_label = "Unnamed",
    Encoding encoding = utf8,
    double replace = double.nan
  }){
    final csvr = new CSVReader(path);
    csvr.read_csv_sync(
      first_col_is_labels: first_col_is_labels,
      loss_column_label: loss_column_label,
      encoding: encoding
    );
    var [row, column] = csvr.shape!;
    List<List<double>> data = csvr.convertToNumberSync(replace: replace);
    return MatrixType(data, row: row, column: column);
  }
}

// test
// main() async {;
//   var csvr = CSVReader('../AirPassengers.csv');
//   csvr.read_csv_sync(first_col_is_labels: true);
//   var lis = (csvr.convertToNumberSync());
//   print(lis.shape);
//   print(csvr.shape);
//   print(csvr.colLabels);
// }