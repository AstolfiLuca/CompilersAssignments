// Test con 3 loop da fondere
int fun(int a, int b, int n){
    int c = 0;
    int d = 0;
    int j;
    for(j=0; j < b; j++){
        a += b;
    }
    for(int i = 0; i < b; i++){
        c += b;
    }
    for(j=0; j < b; j++){
        n += n;
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