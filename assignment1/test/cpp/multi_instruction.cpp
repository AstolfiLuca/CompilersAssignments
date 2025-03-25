int multi_instruction_optimizazion_test(int a, int b){
    // d = a -> funziona
    int c = a + 1;
    int d = c - 1;
    b = d + 1;
    //
    c = 5 + a;
    d = 5 - c; // d != a --> d = -a (non dovrebbe essere ottimizzato)
    b = d + 2;

    return b;
}