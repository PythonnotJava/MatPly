/// 矩阵相关的统计学分支

part of 'core.dart';

extension Random on MatrixType{
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
}