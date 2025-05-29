// Due loop guarded
int foo(int a, int b, int c, int z){
    int n=z;
    int i = 0;
    if (n > 0) {
        do {
          z = i+1;
          i += 1;
        } while (i < n);
    }
    i=0;
    if (n > 0){
        do{
            b += z;
            i += 1;
        } while(i < n);
    }

    return a+b*c;
}