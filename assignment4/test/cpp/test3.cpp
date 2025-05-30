// Due loop non guarded -> cannot compute trip count
int foo(int a, int b, int c, int z){
    int n=z;
    int i = 0;
    do {
        i += 1;
    } while (i < n);
    do{
        b += z; // i non viene aggiornata
    } while(i < n);

    return a+b*c;
}

int main(){
    return foo(1,2,3,4);
}