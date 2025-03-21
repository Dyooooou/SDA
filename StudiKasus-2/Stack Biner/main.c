#include <stdio.h>
#include "DecToBin.h"


int main() {
    int decimal;
    
    printf("Masukkan bilangan desimal: ");
    scanf("%d", &decimal);
    
    printf("Hasil konversi biner: ");
    DecimalToBinary(decimal);
    
    return 0;
}