int foo(int a, int b){
    for(int i=0; i<10; i++){
        a += i;
    }
    for(int i=0; i<10; i++){
        b += i;
    }
    return a+b;
}
int main(){
    return foo(1,2);
    
}