int fun(int a, int b, int c){
    int d;
    int e;
    int f;
    int z;

    while(true){
        d = a + b; // code motion
        if(c > 5){
            e = d + 1; // non considerato (exit block)
            break;
        }
        else
            e = d - 1;  // code motion 
    }

    while(true){
        f = b + 1; // code motion
         
        if(e > 5){
            c++;  // non considerato (exit block)
            break;
        }
        else
            e++; // no loop invariant (usa un PHINode)
        
        z = e + 5; // no loop invariant (usa un PHINode)
    }
    
    return e;
}