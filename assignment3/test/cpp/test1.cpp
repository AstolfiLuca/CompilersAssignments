int foo(int a, int c, int d, int e, int i, int f){
    int b = 5 + f;
    while(i < 5){
        a = b + c; // code motion

        if (i<3) { 
            e = b + 3; // non considerato (exit block)
            break;
        }
        else 
            e = a + 4;
        
        d = a + 1; // code motion
        f = e + 2; // code motion

        i++; // no loop invariant (usa un PHINode)
    }

    return c;
}