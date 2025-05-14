int foo(int a, int b, int c){
    for(int i=0; i<c; i++){
        a += i;
        if(a > 10){
            return a+b;
        }
    }
    int z = 0;
    do{
        b += z;
        z++;
    }while(z < c);
    return a+b*z;

}