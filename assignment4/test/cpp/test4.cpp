int fun(int a, int b, int n){
    for(int j=0; j < b; j++){
        a += b;
    }
    for(int i = 0; i < b; i++){
        a += b;
    }
    for(int k=0; k < n; k++){
        a += b;
    }
    return a + b;
}
int main(){
    return fun(1,2,3);
}