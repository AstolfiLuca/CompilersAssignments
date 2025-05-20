int fun(int a, int b, int n){
    for(int j=0; j<10; j++){
        a += b;
    }
    for(int i = 0; i < n; i++){
        a += b;
    }
    return a + b;
}