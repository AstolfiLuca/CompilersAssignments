// Due loop guarded
int foo(int a, int b, int c, int z){
    int n=z;
    int i = 0;
    if (n > 0) {
        int z = n+c;
        do {
          z = i+1;
          i += 1;
        } while (i < n);
    }
    int e = i + 1;
    i=0;
    if (n > 0){
        do{
            b += e;
            e += 1;
            i += 1;
        } while(i < n);
    }

    return a+b+z+e;
}

int main(){
    return foo(1,2,3,4);
}

/* DA FARE:
La stessa cosa che facevamo per il preheader lo dobbiamo fare per la guardia.
Dobbiamo poi cambiare i vari successorPHIUses e branch.
L1_ExitBlock -> L2_FirstBlock
Prediamo GuardiaL2, PreHeaderL2, HeaderL2, LatchL2, ExitL2
(ricordiiamo che svuotiamo anche l'header L2 spostandolo in L1) 
Ma spostiamo tutte le istruzioni prima del branch della guardia di L2 nella guardia di L1.
Infine, la prima guardia punterà alla fine della seconda.


*/