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
    
    /*
    Prendiamo la variabile di induzione canonica di L1
    Facciamo lo stesso per L2
    Sostituiamo gli usi della variabile ind. di L2 con quella di L1
    Con la guardia, abbiamo i++ alla fine dell'header 
    (non alla fine, ma dov'è posizionato)
    Dovremmo avere:
      a + = i;
      b += i;
      i++;
    ma per farlo dovremmo prendere tutte le istruzioni
    nell'header di L2 (perchè i loop con guardia hanno una struttura diversa)
    prima dell'aggiornamento di j++ (che diventa i++),
    poi spostarle prima del primo uso di i nell'header di L1.
    
    */
    if(n>0){
        int j=0;
        do{
            b += j;
            j++;
        }while(j < n);
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