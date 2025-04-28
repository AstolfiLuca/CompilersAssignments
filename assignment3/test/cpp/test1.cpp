int foo(int a, int c, int d, int e, int i, int f){
    int b = 5 + f;
    while(i < 5){
        a = b + c;

        if (i<3) 
            e = 2;
        else 
            e = 3;
        
        d = a + 1;
        f = e + 2;

        i++;
    }

    return c;
}