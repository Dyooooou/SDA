#include <stdio.h>      // Include standard input-output library
#include "DecToBin.h"  // Inlclude dectobin header file
#include "stack.h"      // Include stack header file


// Fungsi untuk mengkonversi bilangan desimal ke biner menggunakan stack
void DecimalToBinary(int decimal) {
    // Buat stack baru
    Stack stack;
    CreateStack(&stack);
    
    // Kasus khusus: jika bilangan adalah 0
    if (decimal == 0) {
        printf("0\n");
        return;
    }
    
    // Proses bilangan desimal sampai menjadi 0
    while (decimal > 0) {
        Push(&stack, decimal % 2);  // Push sisa pembagian (0 atau 1) ke stack
        decimal = decimal / 2;      // Bagi desimal dengan 2
    }
    
    // Cetak representasi biner dengan pop dari stack
    while (!IsEmpty(&stack)) {
        printf("%d", Pop(&stack));  // Pop dan cetak setiap digit
    }
    printf("\n");
    
    // Bersihkan stack
    ClearStack(&stack);
}
