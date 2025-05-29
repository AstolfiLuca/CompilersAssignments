int algebraic_identity_test(int a, int b, int c, int d){
    a = a * 1;
    b = a + 0;
    a = b / b;
    
    // ADD - SUB 
    c = a + 1;
    d = c - 1; // d = (a + 1) - 1 = a + 1 - 1 = a
    b = d + 5; // test 

    // ADD (commutative) - SUB 
    c = 1 + a;
    d = c - 1; // d = (1 + a) - 1 = 1 + a - 1 = a 
    b = d * 5; // test
    
    return a;
}