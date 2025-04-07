#include <stdio.h>
#include <stdlib.h>
#include "kota.h"

int main() {
    // Membuat array kota dengan 5 elemen (sesuai persyaratan minimal)
    City cities[5]; 
    
    // Membuat kota-kota
    CreateCity(&cities[0], "Bandung");
    CreateCity(&cities[1], "Jakarta");
    CreateCity(&cities[2], "Surabaya");
    CreateCity(&cities[3], "Yogyakarta");
    CreateCity(&cities[4], "Medan");
    
    // Menambahkan orang-orang ke kota Bandung
    AddPersonToCity(&cities[0], "Yahya");
    AddPersonToCity(&cities[0], "Wahab");
    AddPersonToCity(&cities[0], "Amir");
    
    // Menambahkan orang-orang ke kota Jakarta
    AddPersonToCity(&cities[1], "Hasan");
    AddPersonToCity(&cities[1], "Badu");
    
    // Menambahkan orang-orang ke kota Surabaya
    AddPersonToCity(&cities[2], "Rini");
    AddPersonToCity(&cities[2], "Tono");
    
    // Menambahkan orang-orang ke kota Yogyakarta
    AddPersonToCity(&cities[3], "Siti");
    
    // Menambahkan orang-orang ke kota Medan
    AddPersonToCity(&cities[4], "Budi");
    AddPersonToCity(&cities[4], "Dewi");
    
    // Menampilkan isi semua kota
    printf("=== Isi kota: ===\n");
    for (int i = 0; i < 5; i++) {
        DisplayCity(&cities[i]);
        printf("\n");
    }
    
    // Menghapus beberapa orang dari kota
    printf("=== Menghapus beberapa orang... ===\n");
    DeletePersonFromCity(&cities[0], "Wahab");  // Hapus Wahab dari Bandung
    DeletePersonFromCity(&cities[1], "Hasan");  // Hapus Hasan dari Jakarta
    DeletePersonFromCity(&cities[2], "Tono");   // Hapus Tono dari Surabaya
    
    // Menampilkan isi kota setelah penghapusan orang
    printf("\n=== Isi kota (setelah penghapusan orang): ===\n");
    for (int i = 0; i < 5; i++) {
        DisplayCity(&cities[i]);
        printf("\n");
    }
    
    // Menghapus sebuah kota 
    printf("=== Menghapus kota Bandung... ===\n");
    // Membersihkan list dan mengosongkan nama untuk menghapus kota
    ClearList(&(cities[0].list));
    cities[0].cityName[0] = '\0';
    
    // Menampilkan isi kota setelah penghapusan kota (melewati kota yang dihapus)
    printf("\n=== Isi kota (setelah penghapusan kota): ===\n");
    for (int i = 0; i < 5; i++) {
        if (cities[i].cityName[0] != '\0') {
            DisplayCity(&cities[i]);
            printf("\n");
        }
    }
    
    // Mencari orang di semua kota
    printf("=== Mencari 'Budi' di semua kota: ===\n");
    for (int i = 0; i < 5; i++) {
        if (cities[i].cityName[0] != '\0' && FindPersonInCity(&cities[i], "Budi")) {
            printf("Budi ditemukan di kota %s\n", cities[i].cityName);
        }
    }
    
    // Membersihkan memori untuk semua kota
    DeallocateAllCities(cities, 5);
    printf("\nProgram selesai.\n");
    
    return 0;
}
