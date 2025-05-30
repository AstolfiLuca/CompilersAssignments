// Test con 3 loop da fondere
int fun(int a, int b, int n){
    int c = 0;
    int d = 0;
    for(int j=0; j < b; j++){
        a += b;
    }
    for(int i = 0; i < b; i++){
        c += b;
    }
    for(int j=0; j < n; j++){
        a += c + d;
    }
    for(int j=0; j < b; j++){
       d += b;
    }
    for(int j=0; j < b; j++){
       a += b;
    }
    return a + b + c + d;
}

int main(){
    return fun(1,2,3);
}