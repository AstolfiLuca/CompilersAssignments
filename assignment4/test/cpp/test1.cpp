int foo(int a, int b){
    for(int i = 0; i<10; i++){
        a += i;
    }
    // b = b + a; // Controllo isAdjacent (ora commentato)
    for(int i=0; i<10; i++){
        b += i; // Contr
        // olla se b = b + a ha usi nel for per capire se ha dipendenze o meno
    }
    return a+b;
}
int main(){
    return foo(1,2);
}