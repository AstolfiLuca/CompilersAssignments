// Due loop guarded
int foo(int n){
    int i = 0;
    int a = 0;
    int b = 0;
    if(n>0){
        do{
            a += i;
            i++;
        }while(i < n);
    }
    i=0;
    if(n>0){
        do{
            b += i;
            i++;
        }while(i < n);
    }
    return a + b;
}

int main(){
    return foo(4);
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