int algebraic_identity_test(){
    int x = 1; 
    int a, b, c, d;

    x = x + 0;
    a = x + 1;

    x = 0 + x;
    b = x + 2;

    x = x * 1;
    c = x + 3;

    x = 1 * x;
    d = x + 4;

    return x;
}