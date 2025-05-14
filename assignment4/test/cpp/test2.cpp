// Due loop guarded
int foo(int a, int b, int c, int z){
    int n=z;
    int i = 0;
    if (n > 0) {
        do {
          i += 1;
        } while (i < n);
    }
    if (n > 0){
        do{
            b += z;
        } while(i < n);
    }

    return a+b*c;
}