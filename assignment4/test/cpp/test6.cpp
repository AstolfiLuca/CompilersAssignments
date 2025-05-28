int foo(int a) {
  int b;
  for (int i = 0; i < 10; i++) {
    int tmp = i + 2;
    b = tmp;
  }
  for (int j = 0; j < 10; j++) {
    a = b + 1;
  }
  return a;
}