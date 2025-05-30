// FUSIONE
int foo(int a, int c) {
  int b;
  int z;
  for (int i = 0; i < 10; i++) {
    z = a+b;
    if(z>0){
      b=10;
    }else{
      b=20;
    }
    a = 5;
  }
  int x = 10 + c;
  for (int j = 0; j < 10; j++) {
    c = j + 1;
  }
  return a;
}

int main() {
  return foo(1, 2);
}