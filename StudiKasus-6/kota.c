#include "kota.h"
#include <string.h>


char namesArray[MAX_TOTAL_NAMES][MAX_PERSON_NAME];
int nameCount = 0;


void CreateCity(City *city, char *name) {
    strcpy(city->cityName, name);
    // Menggunakan fungsi dari list.c untuk membuat list kosong
    CreateList(&(city->list));
}

// Menambahkan orang ke dalam kota
void AddPersonToCity(City *city, char *personName) {
    // Cari indeks nama atau tambahkan ke array nama
    int nameIndex = -1;
    
    // Periksa apakah nama sudah ada di array
    for (int i = 0; i < nameCount; i++) {
        if (strcmp(namesArray[i], personName) == 0) {
            nameIndex = i;
            break;
        }
    }
    
    // Tambahkan nama jika belum ada
    if (nameIndex == -1) {
        if (nameCount < MAX_TOTAL_NAMES) {
            strcpy(namesArray[nameCount], personName);
            nameIndex = nameCount;
            nameCount++;
        } else {
            printf("Error: Jumlah nama maksimum tercapai.\n");
            return;
        }
    }
    
    // Periksa apakah orang sudah ada di kota ini
    Node *current = city->list.head;
    while (current != NULL) {
        if (current->value == nameIndex) {
            printf("Orang dengan nama %s sudah ada di kota %s.\n", personName, city->cityName);
            return;
        }
        current = current->next;
    }
    
    // Tambahkan ke linked list kota (menggunakan fungsi dari list.c)
    InsertLast(&(city->list), nameIndex);
}

// Menghapus orang dari kota
void DeletePersonFromCity(City *city, char *personName) {
    // Cari indeks nama
    int nameIndex = -1;
    for (int i = 0; i < nameCount; i++) {
        if (strcmp(namesArray[i], personName) == 0) {
            nameIndex = i;
            break;
        }
    }
    
    if (nameIndex == -1) {
        printf("Orang dengan nama %s tidak ditemukan.\n", personName);
        return;
    }
    
    // Hapus dari linked list kota (menggunakan fungsi dari list.c)
    Node *current = city->list.head;
    while (current != NULL) {
        if (current->value == nameIndex) {
            DeleteByValue(&(city->list), nameIndex);
            printf("Orang dengan nama %s dihapus dari kota %s.\n", personName, city->cityName);
            return;
        }
        current = current->next;
    }
    
    printf("Orang dengan nama %s tidak ditemukan di kota %s.\n", personName, city->cityName);
}

// Menampilkan semua orang di kota
void DisplayCity(City *city) {
    printf("Kota: %s\n", city->cityName);
    
    if (city->list.head == NULL) {
        printf("  (Tidak ada penduduk)\n");
        return;
    }
    
    // Perhatikan kita menggunakan struktur list dari list.c
    Node *current = city->list.head;
    while (current != NULL) {
        printf("  Nama: %s\n", namesArray[current->value]);
        current = current->next;
    }
}

// Mencari orang di kota
int FindPersonInCity(City *city, char *personName) {
    // Cari indeks nama
    int nameIndex = -1;
    for (int i = 0; i < nameCount; i++) {
        if (strcmp(namesArray[i], personName) == 0) {
            nameIndex = i;
            break;
        }
    }
    
    if (nameIndex == -1) {
        return 0;  // Nama tidak ada di array
    }
    
    // Periksa apakah nama ada di kota (bisa menggunakan SearchValue)
    return SearchValue(&(city->list), nameIndex);
}

// Membersihkan memori untuk semua kota
void DeallocateAllCities(City cities[], int size) {
    for (int i = 0; i < size; i++) {
        ClearList(&(cities[i].list));
    }
}