int foo(int a, int b, int c){
    int n=5;
    int i = 0;
    if (n > 0) {
        do {
          // Loop body
          i += 1;
        } while (i < n);
    }
    do{
        b += z;
        z++;
    } while(z < c);

    return a+b*c;
}