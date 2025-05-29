int foo(int a, int b, int N, int f){
    int A[10];
    int B[10];

    for(int i=1; i<10; i*=2){
        A[i] = a + b;
    }
    for(int j=1; j<10; j*=2){
        B[j] = A[j+2];
    }

    int g = N + f;

    for(int i=9; i>=0; i--){
        A[i] = a + b;
    }
    for(int j=9; j>=0; j--){
        B[j] = A[j];
    }
    return A[0] + B[0] + g;
}

int main(){
    int result = foo(1, 2, 3, 4);
    return result;
}