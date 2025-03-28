int strength_reduction_test(int x){
    int a = x * 15; // Ottimizzato
    int b = a * 9; // Ottimizzato
    int c = b * 6; // Non ottimizzato
    int d = c * (-15); // Non ottimizzato
    int e = d / d; // Non ottimizzato
    int f = e / 16; // Ottimizzato 
    return f;
}

int main(){
    return strength_reduction_test(3);
}