int foo(int a, int b){
    for(int i=0; i<10; i++){
        a += i;
    }
    for(int i=0; i<10; i++){
        b += i;
    }
    int c = 0;
    if(a > b){
        c = a;
    }
    
    for(int i=0; i<10; i++){
        c += i;
    }
    return a+b;
}