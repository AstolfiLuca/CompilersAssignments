int foo(int a, int c, int d, int e, int i, int f){
    int b = 5 + f;
    while(i < 5){
        a = b + c;

        if (i<3) { 
            e = b + 3;
            break;
        }
        else 
            e = a + 4;
        
        d = a + 1;
        f = e + 2;

        i++;
    }

    return c;
}