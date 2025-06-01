// Due loop non guarded 
int foo(int a, int b, int c, int z){
    int n=z;
    int i = 0;
    do {
        i++;
        a += i;
    } while (i < n);
    i=0;
    do{
        i++;
        b += 1; 
        if (b>0){
            b -=i;
        } else{
            b += i;
        }
        //i++;
    } while(i < z);

    return a+b*c;
}

int main(){
    return foo(1,2,3,4);
}