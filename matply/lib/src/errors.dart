part of 'core.dart';

// 涉及到row与column不符合的错误
class ShapeRangeError implements Exception {
  final String message;

  const ShapeRangeError(this.message);

  @override
  String toString() {
    return 'ShapeRangeError: $message';
  }
}

const ShapeRangeError matmul_unsupport = ShapeRangeError("Left Matrix's columns must be equal to right Matrix's rows.");
const ShapeRangeError row_outRange = ShapeRangeError('The row is out of range.');
const ShapeRangeError column_outRange = ShapeRangeError('The column is out of range.');
const ShapeRangeError random_outRange = ShapeRangeError('You are out of range.');
const ShapeRangeError different_shape = ShapeRangeError('Shapes must be the same.');
const ShapeRangeError not_a_square = ShapeRangeError('Not a square.');
const ShapeRangeError cannot_be_splitt_more = ShapeRangeError('A row or column with only 1 cannot be split.');
const ShapeRangeError row_or_column_not_same = ShapeRangeError(
  'If you choose horizontal concatenating, '
  'the number of rows must be the same;'
  'if you choose vertical concatenating, the number of columns must be the same.'
);
const ShapeRangeError size_changed = ShapeRangeError('Original size is changed.');