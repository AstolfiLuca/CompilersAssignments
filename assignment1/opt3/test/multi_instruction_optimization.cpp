int multi_instruction_optimizazion_test(int a, int b, int c, int d, int e, int f){
    // Addizione e Sottrazione
    b = 1 + a;



    c = 1 - b; // c = b - 1 | b = a * 2 
    d = b + 1;

    /*
     c = b - 1
     auto *Op1 = Inst.getOperand(0); // b
     auto *Op2 = Inst.getOperand(1); // 1
     b -> OP? cos'è?
     
    */
    

    

    // Moltiplicazione e Divisione
    e = d * 2;
    f = e / 2; //  Ottimizzazione -> f = d

    return a;
}