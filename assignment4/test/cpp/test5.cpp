int foo(int a, int b, int N, int f){
    int A[10];
    int B[10];

    for(int i=0; i<10; i++){
        A[i] = a + b;
    }
    for(int j=0; j<10; j++){
        B[j] = A[j+1] + b;
    }
    return a + f;
}