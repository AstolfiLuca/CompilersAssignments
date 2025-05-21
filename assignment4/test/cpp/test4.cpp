int fun(int a, int b, int n){
    for(int j=0; j < n; j++){
        a += b;
    }
    for(int i = 0; i < b; i++){
        a += b;
    }
    for(int k=0; k < 10 ; k++){
        a += b;
    }
    return a + b;
}