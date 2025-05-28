int foo(int a, int b, int N, int f){
    int A[12];
    int B[12];

    for(int i=0; i<11; i++){
        A[i] = a + b;
    }
    for(int j=0; j<11; j++){
        B[j] = A[j+1];
    }
    return a + f;
}