int strength_reduction_test(int a, int b){
    a = a * 15; // Ottimizzato
    a = a * 9; // Ottimizzato
    a = a * 6; // Non ottimizzato
    a = a * (-15); // Non ottimizzato
    int c = b / 15; // Non ottimizzato
    b = b / 16; // Ottimizzato
    // int g = a * 0; 
    return b; // 2
}

int main(){
    return strength_reduction_test(3, 44);
}