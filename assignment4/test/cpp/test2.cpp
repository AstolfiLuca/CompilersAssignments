int foo(int a, int b, int c){
    int i=0; 
    while(i<c){
        a += i;
        i++;
    }
    int z = 0;
    do{
        b += z;
        z++;
    }while(z < c);
    return a+b*z;

}