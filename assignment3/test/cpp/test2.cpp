int fun(int a, int b, int c){
    int i = 0;
    int d;
    int e;

    int z = 1;

    while(true){
        if(i<5)
            a = b + c; // more reaching definitions
        else{
            e = b + 1;
            break;
        }
        d = a + 1; // a not moved, so d not movable
        i++;
    }

    c = a;
    d = e;

    return c;
    
}

int main(){
    int a = fun(1,2,3);
    return a;
}