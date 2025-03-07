int multi_instruction_optimizazion_test(){
    
    // Addizione e Sottrazione
    int a = 1;
    int b, c;

    b = a + 1;
    c = b - 1; // Ottimizzazione -> c = a

    // Moltiplicazione e Divisione
    int d;
    int e, f;

    e = d * 2;
    f = e / 2; //  Ottimizzazione -> f = d

    return a;
}