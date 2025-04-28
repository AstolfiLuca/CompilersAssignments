int fun(int a, int b, int c){
    int d;
    int e;
    int f;
    int z;

    while(true){
        d = a + b; // loop invariant (si code motion)
        if(c > 5){
            e = d + 1; // loop invariant (si code motion)
            break;
        }
        else
            e = d - 1;  // loop invariant (no code motion)  
        
    }

    while(true){
        f = b + 1; // loop invariant (si code motion)
         
        if(e > 5){
            c++;  // no loop invariant
            break;
        }
        else
            e++; // no loop invariant
        
        z = e + 5;
        
    }
    
    return e;
}