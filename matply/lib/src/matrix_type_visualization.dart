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

}