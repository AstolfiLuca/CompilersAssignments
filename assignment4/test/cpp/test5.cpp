int foo(int a, int b, int N, int f){
    int A[10];
    int B[10];

    for(int i=0; i<10; i++){
        B[i] = A[i];
    }
    for(int j=0; j<10; j++){
        A[j+1] = B[j+1];
    }

    int g = N + f;

    for(int i = 11; i>=0; i--){
        a = A[i];
    }
    for (int i = 11; i>=0; i--){
        A[i-1] = b;
    }

    // A[a,a,a,,a....]
    // A[a,b,b,b,...]

    // A[0] = a
    // A[1] = b
    // A[1] = a


    return a + f;
}