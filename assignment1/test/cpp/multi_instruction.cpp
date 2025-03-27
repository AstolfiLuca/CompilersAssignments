int multi_instruction_optimizazion_test(int a, int b, int c, int d){
    // "test" instruction are random instruction needed to prove that d = a, we'll use the number 5 (randomly selected)

    // --- Number at the SECOND operand (2° instruction) ---
    // ADD - SUB // FUNZIONA
    c = a + 1;
    d = c - 1; // d = a + 1 - 1 = a
    b = d + 5; // test:  

    // ADD (commutative) - SUB // FUNZIONA
    c = 1 + a;
    d = c - 1;
    b = d + 5; // test:

    // SUB - ADD // FUNZIONA
    c = a - 1;
    d = c + 1;
    b = d + 5; // test: d = a - 1 + 1 = a

    // SUB - ADD // DA FARE (instruzione uguale)
    c = -1 + a;
    d = c + 1;
    b = d + 5; // test: d = a - 1 + 1 = a

    // Addizione -> istruzione uguale, operando opposto
    // Sottrazione -> istruzione uguale, operando uguale
    
    c = 1 - a;
    d = 1 - c; // test: d = 1 - 1 + a
    b = d + 5;

    // MUL - DIV
    c = a * 3;
    d = c / 3;
    b = d + 5; // test: d = a * 3 / 3 = a

    // MUL (commutative) - DIV // FUNZIONA (istruzione opposta, stesso operando numerico)
    c = 3 * a;
    d = c / 3;
    b = d + 5; // test: d = a * 3 / 3 = a
    
    // --- Number at the FIRST operand (2° instruction)---
    // istruzione è la stessa, primo operando è opposto
    c = 1 + a;
    d = -1 + c;
    b = d + 5; // test: d = -1 + 1 + a = a
    
    // SUB - SUB
    c = -1 - a;
    d = -1 - c; 
    b = d + 5; // test: d = -1 - (-1 - a) = -1 + 1 + a = a

    // SUB - ADD (commutative) 
    c = a - 1;
    d = 1 + c;
    b = d + 5; // test: d = a - 1 + 1 = a

    // Tutte le precedenti devono funzionare
    
    // --- DON'T NEED OPTIMIZATION
    c = 1 + a; 
    d = 1 - c; // sottr. operando sx
    b = d + 5;

    // Non deve funzionare
    c = -1 - a; // sottr. operando sx  (ad es. a - (-1) funzionerebbe)
    d = -1 + c; // add
    d = d + 5;

    return b;
}