// Cicli con array -> FUSIONE
int foo(int a, int b, int N, int f){
    int A[10];
    int B[10];

    for(int i=0; i<10; i++){
        A[i] = a + b;
    }
    for(int j=0; j<10; j++){
        B[j] = A[j];
    }

    int g = N + f;
    /*
    // Controllo dipendenze OK, ma niente merge perchè non è canonica
    // Canonica: parte da 0 e si ferma ad un certo punto
    for(int i=9; i>=0; i--){
        A[i] = a + b;
    }
    for(int j=9; j>=0; j--){
        B[j] = A[j];
    }
    */
    return A[0] + B[0] + g;
}

int main(){
    int result = foo(1, 2, 3, 4);
    return result;
}