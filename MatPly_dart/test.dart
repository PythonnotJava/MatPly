bool ccc(dynamic nu){
  if (nu is num)
    return true;
  return false;
}

main(){
  var a = [1, 3];
  var b = [1, 3];
  print(ccc('nu'));
  print(ccc('1'));
  print(ccc(2));
  print(ccc(.0));
  print((1, 3).runtimeType);
}
