#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kota.h"
#include "citylist.h"

#define MAX_PERSON_NAME 50
#define MAX_CITY_NAME 50

// Fungsi untuk membersihkan buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fungsi-fungsi menu
void displayMenu();
void handleAddCity(CityList *cityList);
void handleAddPerson(CityList *cityList);
void handleRemovePerson(CityList *cityList);
void handleRemoveCity(CityList *cityList);
void handleSearchPerson(CityList *cityList);
void handleDisplayCities(CityList *cityList);

int main() {
    CityList cityList;
    int choice;
    
    // Inisialisasi linked list kota
    CreateCityList(&cityList);
    
    printf("=== PROGRAM MANAJEMEN KOTA (KASUS 6) ===\n");
    printf("Menggunakan linked list untuk menyimpan kota\n\n");
    
    do {
        displayMenu();
        printf("Pilihan Anda: ");
        scanf("%d", &choice);
        clearBuffer(); // Membersihkan buffer input
        
        switch (choice) {
            case 1:
                handleAddCity(&cityList);
                break;
            case 2:
                handleAddPerson(&cityList);
                break;
            case 3:
                handleRemovePerson(&cityList);
                break;
            case 4:
                handleRemoveCity(&cityList);
                break;
            case 5:
                handleDisplayCities(&cityList);
                break;
            case 6:
                handleSearchPerson(&cityList);
                break;
            case 0:
                printf("Terima kasih telah menggunakan program ini!\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
        
        printf("\n");
    } while (choice != 0);
    
    // Membersihkan linked list kota sebelum keluar
    ClearCityList(&cityList);
    
    return 0;
}

void displayMenu() {
    printf("\nMENU:\n");
    printf("1. Tambah Kota\n");
    printf("2. Tambah Orang ke Kota\n");
    printf("3. Hapus Orang dari Kota\n");
    printf("4. Hapus Kota\n");
    printf("5. Tampilkan Semua Kota\n");
    printf("6. Cari Orang\n");
    printf("0. Keluar\n");
}

void handleAddCity(CityList *cityList) {
    char cityName[MAX_CITY_NAME];
    
    printf("Masukkan nama kota: ");
    fgets(cityName, MAX_CITY_NAME, stdin);
    cityName[strcspn(cityName, "\n")] = '\0'; // Menghapus newline
    
    AddCity(cityList, cityName);
}

void handleAddPerson(CityList *cityList) {
    if (cityList->count == 0) {
        printf("Belum ada kota yang ditambahkan!\n");
        return;
    }
    
    char cityName[MAX_CITY_NAME];
    char personName[MAX_PERSON_NAME];
    
    // Menampilkan daftar kota
    printf("Daftar kota yang tersedia:\n");
    CityNode *current = cityList->head;
    while (current != NULL) {
        printf("- %s\n", current->city.cityName);
        current = current->next;
    }
    
    // Meminta input nama kota
    printf("Masukkan nama kota: ");
    fgets(cityName, MAX_CITY_NAME, stdin);
    cityName[strcspn(cityName, "\n")] = '\0'; // Menghapus newline
    
    // Mencari kota
    City *city = FindCity(cityList, cityName);
    if (city == NULL) {
        printf("Kota dengan nama %s tidak ditemukan.\n", cityName);
        return;
    }
    
    // Meminta input nama orang
    printf("Masukkan nama orang: ");
    fgets(personName, MAX_PERSON_NAME, stdin);
    personName[strcspn(personName, "\n")] = '\0'; // Menghapus newline
    
    // Menambahkan orang ke kota
    AddPersonToCity(city, personName);
}

void handleRemovePerson(CityList *cityList) {
    if (cityList->count == 0) {
        printf("Belum ada kota yang ditambahkan!\n");
        return;
    }
    
    char cityName[MAX_CITY_NAME];
    char personName[MAX_PERSON_NAME];
    
    // Menampilkan daftar kota
    printf("Daftar kota yang tersedia:\n");
    CityNode *current = cityList->head;
    while (current != NULL) {
        printf("- %s\n", current->city.cityName);
        current = current->next;
    }
    
    // Meminta input nama kota
    printf("Masukkan nama kota: ");
    fgets(cityName, MAX_CITY_NAME, stdin);
    cityName[strcspn(cityName, "\n")] = '\0'; // Menghapus newline
    
    // Mencari kota
    City *city = FindCity(cityList, cityName);
    if (city == NULL) {
        printf("Kota dengan nama %s tidak ditemukan.\n", cityName);
        return;
    }
    
    // Meminta input nama orang
    printf("Masukkan nama orang yang akan dihapus: ");
    fgets(personName, MAX_PERSON_NAME, stdin);
    personName[strcspn(personName, "\n")] = '\0'; // Menghapus newline
    
    // Menghapus orang dari kota
    DeletePersonFromCity(city, personName);
}

void handleRemoveCity(CityList *cityList) {
    if (cityList->count == 0) {
        printf("Belum ada kota yang ditambahkan!\n");
        return;
    }
    
    char cityName[MAX_CITY_NAME];
    
    // Menampilkan daftar kota
    printf("Daftar kota yang tersedia:\n");
    CityNode *current = cityList->head;
    while (current != NULL) {
        printf("- %s\n", current->city.cityName);
        current = current->next;
    }
    
    // Meminta input nama kota
    printf("Masukkan nama kota yang akan dihapus: ");
    fgets(cityName, MAX_CITY_NAME, stdin);
    cityName[strcspn(cityName, "\n")] = '\0'; // Menghapus newline
    
    // Menghapus kota
    RemoveCity(cityList, cityName);
}

void handleSearchPerson(CityList *cityList) {
    if (cityList->count == 0) {
        printf("Belum ada kota yang ditambahkan!\n");
        return;
    }
    
    char personName[MAX_PERSON_NAME];
    
    // Meminta input nama orang
    printf("Masukkan nama orang yang akan dicari: ");
    fgets(personName, MAX_PERSON_NAME, stdin);
    personName[strcspn(personName, "\n")] = '\0'; // Menghapus newline
    
    printf("Mencari '%s' di semua kota...\n", personName);
    int found = 0;
    
    // Mencari orang di semua kota
    CityNode *current = cityList->head;
    while (current != NULL) {
        if (FindPersonInCity(&(current->city), personName)) {
            printf("- Ditemukan di kota: %s\n", current->city.cityName);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("'%s' tidak ditemukan di kota manapun.\n", personName);
    }
}

void handleDisplayCities(CityList *cityList) {
    DisplayAllCities(cityList);
}