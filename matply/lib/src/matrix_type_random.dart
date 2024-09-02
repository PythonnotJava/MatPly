/// 矩阵相关的统计学分支
part of 'core.dart';

/// simple-random
extension RandomExtension on math.Random{
  void setSeed(int seed) => seed > 0 ? matply__setSeed(seed) : matply_initialize_random_seed();

  double random() => matply_random();

  int randint(double lb, double ub){
    assert(lb < ub);
    return matply_randint(lb, ub);
  }

  double randn(double lb, double ub){
    assert(lb < ub);
    return matply_randdouble(lb, ub);
  }

  void shuffle<T>(List<T> list) => list.shuffle();

  Object choice({required List<double> arr, List<double>? p, int? times, bool? back, int? method}){
    int len = arr.length;
    if (p == null && times == null && back == null && method == null){
      Pointer<Double> op = oneListToArray(arr);
      double value = matply_random_choice(op, len);
      malloc.free(op);
      return value;
    }else if(p == null && times != null && back != null){
      assert(times >= 0);
      times = times != 0? times : len;
      Pointer<Double> op1 = oneListToArray(arr);
      Pointer<Double> op2 = matply_random_choices(op1, len, times, back);
      List<double> value = op2.asTypedList(len).toList();
      malloc.free(op1);
      malloc.free(op2);
      return value;
    }else if(p != null && times != null && back != null && method != null){
      assert(times >= 0 && p.length == len);
      times = times != 0? times : len;
      Pointer<Double> op1 = oneListToArray(arr);
      Pointer<Double> op2 = oneListToArray(p);
      Pointer<Double> op3 = matply_perfect_choices(op1, op2, len, times, back, method);
      List<double> value = op3.asTypedList(len).toList();
      malloc.free(op1);
      malloc.free(op2);
      malloc.free(op3);
      return value;
    }else
      throw UnsupportedError('Confusing parameter matching');
  }
}

extension ProbStat on MatrixType{
  void shuffle() => matply__shuffle(shape[0], shape[1], self.ref.data);

  Object __variance_std({bool sample = false, required bool std, int dim = -1}){
    switch(dim){
      case 0:
        return matply__variance(shape[0], shape[1], self.ref.data, sample, 0, std).asTypedList(shape[0]).toList();
      case 1:
        return matply__variance(shape[0], shape[1], self.ref.data, sample, 1, std).asTypedList(shape[1]).toList();
      default:
        return matply__variance(shape[0], shape[1], self.ref.data, sample, -1, std).value;
    }
  }

  Object std({bool sample = false, int dim = -1}) => __variance_std(dim: dim, sample: sample, std: true);
  Object variance({bool sample = false, int dim = -1}) => __variance_std(dim: dim, sample: sample, std: false);

  Object median({int dim = -1}){
    switch (dim){
      case 0:
        return matply__median(shape[0], shape[1], self.ref.data, 0).asTypedList(shape[0]).toList();
      case 1:
        return matply__median(shape[0], shape[1], self.ref.data, 1).asTypedList(shape[1]).toList();
      default:
        return matply__median(shape[0], shape[1], self.ref.data, -1).value;
    }
  }

  Object mode({int dim  = -1}){
    Pointer<Pointer<Double>> data = self.ref.data;

    double value;
    switch(dim){
      case 0:
        List<double> list = [];
        for (int r = 0;r < shape[0];r ++){
          Map<double, int> hist = {};
          for(int c=0;c < shape[1];c ++){
            value = data[r][c];
            if (!hist.containsKey(value))
              hist[value] = 1;
            else
              hist[value] = hist[value]! + 1;
          }
          int maxCount = 0;
          double _k = 0.0;
          hist.forEach((k, v){
            if (v > maxCount) {
              maxCount = v;
              _k = k;
            }
          });
          list.add(_k);
        }
        return list;
      case 1:
        List<double> list = [];
        for (int c = 0;c < shape[1];c ++){
          Map<double, int> hist = {};
          for(int r =0;r < shape[0];r++){
            value = data[r][c];
            if (!hist.containsKey(value))
              hist[value] = 1;
            else
              hist[value] = hist[value]! + 1;
          }
          int maxCount = 0;
          double _k = 0.0;
          hist.forEach((k, v){
            if (v > maxCount) {
              maxCount = v;
              _k = k;
            }
          });
          list.add(_k);
        }
        return list;
      default:
        Map<double, int> hist = {};
        for (int r= 0;r < shape[0];r++){
          for (int c = 0;c < shape[1];c ++){
            value = data[r][c];
            if (hist.containsKey(value))
              hist[value] = hist[value]! + 1;
            else
              hist[value] = 1;
          }
        }
        int maxCount = 0;
        double _k = 0.0;
        hist.forEach((k, v){
          if(maxCount < v){
            _k = k;
            maxCount = v;
          }
        });
        return _k;
    }
  }

  MatrixType decentralizate({int dim = -1}) => MatrixType.__fromDataPointer(
      matply__decentralizate(shape[0], shape[1], self.ref.data, dim), shape
  );

  Object covariance({required MatrixType other, bool sample = false, int dim = -1}){
    if (hasSameShape(other)){
      switch(dim){
        case 0:
           return matply__covariance(
               shape[0], shape[1], self.ref.data, other.self.ref.data, sample, 0).asTypedList(shape[0]).toList();
        case 1:
          return matply__covariance(
              shape[0], shape[1], self.ref.data, other.self.ref.data, sample, 1).asTypedList(shape[1]).toList();
        default:
          return matply__covariance(shape[0], shape[1], self.ref.data, other.self.ref.data, sample, -1).value;
      }
    }else
      throw different_shape;
  }

  MatrixType cov({MatrixType? other, bool sample = false}){
    int row = shape[0], column = shape[1];
    if (other == null)
      return MatrixType.__fromDataPointer(matply__cov1(row, column, self.ref.data, sample), [row, row]);
    else{
      if (hasSameShape(other))
        return MatrixType.__fromDataPointer(
            matply__cov2(row, column, self.ref.data, other.self.ref.data, sample),
            [2 * row, 2 * row]
        );
      else
        throw different_shape;
    }
  }

  Object pearsonCoef({required MatrixType other, bool sample = false, int dim = -1}){
    if (hasSameShape(other)){
      switch(dim){
        case 0:
          return matply__pearsonCoef(
              shape[0], shape[1], self.ref.data, other.self.ref.data, sample, 0).asTypedList(shape[0]).toList();
        case 1:
          return matply__pearsonCoef(
              shape[0], shape[1], self.ref.data, other.self.ref.data, sample, 1).asTypedList(shape[1]).toList();
        default:
          return matply__pearsonCoef(
              shape[0], shape[1], self.ref.data, other.self.ref.data, sample, -1).value;
      }
    }else
      throw different_shape;
  }

  /// 在几个评分标准中，传入的矩阵参数表示真实数据，而本身表示预测数据
  Object __MSE({required MatrixType rea, bool rmse = false, int dim = -1}){
    if (!hasSameShape(rea))
      throw different_shape;
    switch(dim){
      case 0:
        return matply__MSE(shape[0], shape[1], self.ref.data, rea.self.ref.data, 0, rmse).asTypedList(shape[0]).toList();
      case 1:
        return matply__MSE(shape[0], shape[1], self.ref.data, rea.self.ref.data, 1, rmse).asTypedList(shape[1]).toList();
      default:
        return matply__MSE(shape[0], shape[1], self.ref.data, rea.self.ref.data, -1, rmse).value;
    }
  }

  Object MSE({required MatrixType rea, int dim = -1}) => __MSE(rea: rea, rmse: false, dim: dim);
  Object RMSE({required MatrixType rea, int dim = -1}) => __MSE(rea: rea, rmse: true, dim: dim);

  Object MAE({required MatrixType rea, int dim = -1}){
    if (hasSameShape(rea)){
      switch(dim){
        case 0:
          return matply__MAE(shape[0], shape[1], self.ref.data, rea.self.ref.data, 0).asTypedList(shape[0]).toList();
        case 1:
          return matply__MAE(shape[0], shape[1], self.ref.data, rea.self.ref.data, 1).asTypedList(shape[1]).toList();
        default:
          return matply__MAE(shape[0], shape[1], self.ref.data, rea.self.ref.data, -1).value;
      }
    }else
      throw different_shape;
  }

  Object MAPE({required MatrixType rea, int dim = -1}){
    if (hasSameShape(rea)){
      switch(dim) {
        case 0:
          return matply__MAPE(shape[0], shape[1], self.ref.data, rea.self.ref.data, 0).asTypedList(shape[0]).toList();
        case 1:
          return matply__MAPE(shape[0], shape[1], self.ref.data, rea.self.ref.data, 1).asTypedList(shape[1]).toList();
        default:
          return matply__MAPE(shape[0], shape[1], self.ref.data, rea.self.ref.data, -1).value;
      }
    }else
      throw different_shape;
  }

  Object R2({required MatrixType rea, int dim = -1}){
    if (hasSameShape(rea)){
      switch(dim) {
        case 0:
          return matply__R2(shape[0], shape[1], self.ref.data, rea.self.ref.data, 0).asTypedList(shape[0]).toList();
        case 1:
          return matply__R2(shape[0], shape[1], self.ref.data, rea.self.ref.data, 1).asTypedList(shape[1]).toList();
        default:
          return matply__R2(shape[0], shape[1], self.ref.data, rea.self.ref.data, -1).value;
      }
    }else
      throw different_shape;
  }

  Object SMAPE({required MatrixType rea, int dim = -1}){
    if (hasSameShape(rea)){
      switch(dim) {
        case 0:
          return matply__SMAPE(shape[0], shape[1], self.ref.data, rea.self.ref.data, 0).asTypedList(shape[0]).toList();
        case 1:
          return matply__SMAPE(shape[0], shape[1], self.ref.data, rea.self.ref.data, 1).asTypedList(shape[1]).toList();
        default:
          return matply__SMAPE(shape[0], shape[1], self.ref.data, rea.self.ref.data, -1).value;
      }
    }else
      throw different_shape;
  }

  MatrixType choice({List<double>? commonp, MatrixType? seriesp, int times = 1, bool back = true, int method = 0}){
    assert(times >= 0);
    int row = shape[0], column = shape[1];
    List<int> newShape = [row, times];
    times = times != 0? times : column;
    if (commonp == null && seriesp == null){
      if (back == false && times <= column)
        return MatrixType.__fromDataPointer(matply__choice3(row, column, self.ref.data, times, false), newShape);
      else if (back)
        return MatrixType.__fromDataPointer(matply__choice3(row, column, self.ref.data, times, true), newShape);
      else
        throw "The number of times must be no more than column when setting not back";
    }
    else if (commonp != null){
     if (commonp.length == column){
        if (back == false && times <= column){
          Pointer<Double> op = oneListToArray(commonp);
          var mt = MatrixType.__fromDataPointer(matply__choice2(row, column, self.ref.data, op, times, false, method), newShape);
          malloc.free(op);
          return mt;
        }else if(back == true){
          Pointer<Double> op = oneListToArray(commonp);
          var mt = MatrixType.__fromDataPointer(matply__choice2(row, column, self.ref.data, op, times, true, method), newShape);
          malloc.free(op);
          return mt;
        }else{
          throw "The number of times must be no more than column when setting not back";
        }
     }else
       throw "commonp.length must be equal to column";
    }else{
      seriesp as MatrixType;
      if (!hasSameShape(seriesp)){
        throw different_shape;
      }else{
        if (back)
          return MatrixType.__fromDataPointer(matply__choice1(row, column, self.ref.data, seriesp.self.ref.data, times, true, method), newShape);
        else{
          if (times <= column){
            return MatrixType.__fromDataPointer(matply__choice1(row, column, self.ref.data, seriesp.self.ref.data, times, false, method), newShape);
          }else
            throw "The number of times must be no more than column when setting not back";
        }
      }
    }
  }
}

