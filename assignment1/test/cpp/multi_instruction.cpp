int multi_instruction_optimizazion_test(int a, int b, int c, int d){
    // "test" instruction are random instruction needed to prove that d = a, we'll use the number 5 (randomly selected)
    
    // ----- DO NEED OPTIMIZATION -----

    // --- Number at the SECOND operand (2° instruction) ---

    // ADD - SUB 
    c = a + 1;
    d = c - 1; // d = (a + 1) - 1 = a + 1 - 1 = a
    b = d + 5; // test 

    // ADD (commutative) - SUB 
    c = 1 + a;
    d = c - 1; // d = (1 + a) - 1 = 1 + a - 1 = a 
    b = d + 5; // test

    // SUB - ADD 
    c = a - 1;
    d = c + 1; // d = (a - 1) + 1 = a - 1 + 1 = a
    b = d + 5; // test

    // SUB - ADD // DA FARE (istruzione uguale)
    c = -1 + a;
    d = c + 1; // d = a - 1 + 1 = a
    b = d + 5; // test

    // Addizione -> istruzione uguale, operando opposto
    // Sottrazione -> istruzione uguale, operando uguale
    c = 1 - a;
    d = 1 - c; // d = 1 - 1 + a
    b = d + 5; // test

    // MUL - DIV
    c = a * 3;
    d = c / 3; // d = a * 3 / 3 = a
    b = d + 5; // test: 

    // MUL (commutative) - DIV  (istruzione opposta, stesso operando numerico)
    c = 3 * a;
    d = c / 3; // d = a * 3 / 3 = a
    b = d + 5; // test
    
    // ----- Number at the FIRST operand (2° instruction)-----
    c = 1 + a;
    d = -1 + c; // d = -1 + 1 + a = a
    b = d + 5;  // test 
    
    // SUB - SUB
    c = -1 - a;
    d = -1 - c; // d = -1 - (-1 - a) = -1 + 1 + a = a
    b = d + 5;  // test 

    // SUB - ADD (commutative) 
    c = a - 1;
    d = 1 + c; // d = a - 1 + 1 = a
    b = d + 5; // test 

    // --- DON'T NEED OPTIMIZATION ---

    //
    c = 1 + a; 
    d = 1 - c; 
    b = d + 5;

    // 
    c = -1 - a; 
    d = -1 + c; 
    d = d + 5;

    // 
    c = 1 - a; 
    d = 1 + c; 
    d = d + 5;


    
    
    return b;
}