# CSV读取器

## properties
```text
late final String path;  文件路径
List<String>? rowLabels;  行标签
List<String>? colLabels;  列标签
List<int>? shape;  形状（包含行标签）
List<List<String>>? content;  初始读取的字符串数据
List<List<double>>? data;  转换字符串数据到数字型数据
```

## methods
```text
CSVReader(this.path)
在构造时传入文件路径且必须保证文件路径存在
```

```text
Future<void> read_csv_async({
    bool first_col_is_labels = true,
    String loss_column_label = "Unnamed",
    Encoding encoding = utf8
}) 
  
void read_csv_sync({
    bool first_col_is_labels = true,
    String loss_column_label = "Unnamed",
    Encoding encoding = utf8
}) 
异/同步读取方法。三个参数分别是第一列是否是列标签、在第一列不是标签的情况下替换方案、读取时编码格式。  
只有调用了read_csv_async或者read_csv_sync才能写入到rowLabels、colLabels、shape以及content
```

```text
Future<List<List<double>>> convertToNumberAsync({double replace = double.nan})

List<List<double>> convertToNumberSync({double replace = double.nan})
将content属性转换生成data数据的方法，当数据不是数字型数据，可以使用replace替换
```

# MatrixType拓展
```text
static Future<MatrixType> read_csv_async(
    String path, {
    bool first_col_is_labels = true,
    String loss_column_label = "Unnamed",
    Encoding encoding = utf8,
    double replace = double.nan
})
static MatrixType read_csv_sync(
    String path, {
    bool first_col_is_labels = true,
    String loss_column_label = "Unnamed",
    Encoding encoding = utf8,
    double replace = double.nan
})
注意：生成的MatrixType保留了第一行是行标签的替换（一般是NaN、NaN……）。
```




