int strength_reduction_test(){
    int a = 1;
    int b = 60; // 60 / (3 * 4 * 5) = 1
    int c = 1;
    int d = 1320; // 1320 / (10 * 11 * 12) = 1 


    // Moltiplicazione
    a = a * 3;
    a = a * 4;
    a = a * 5;


    // Divisione
    b = b / 3;
    b = b / 4; // Probabilmente l'unica che funziona
    b = b / 5;

    // No ottimizzazione
    // Non va fatta perchè si moltiplica/divide per un numero diverso da 2^n +- 1 e quindi i cicli sono più o uguali a quelli utilizzati dalla moltiplicazione 
    // I numeri non sono casuali, sono i primi numeri naturali diversi da 2^n +- 1 

    // Moltiplicazione
    c = c * 10;
    c = c * 11;
    c = c * 12;

    // Divisione
    d = d / 10;
    d = d / 11;
    d = d / 12;


    return a;
}