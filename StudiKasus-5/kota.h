#ifndef KOTA_H
#define KOTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Konstanta untuk ukuran maksimum
#define MAX_CITY_NAME 50    // Panjang maksimum nama kota
#define MAX_PERSON_NAME 50  // Panjang maksimum nama orang
#define MAX_TOTAL_NAMES 100 // Jumlah maksimum nama yang dapat disimpan

// Struktur Kota dengan linked list
typedef struct {
    char cityName[MAX_CITY_NAME];
    LinkedList list;  // Menggunakan LinkedList dari list.h
} City;

// Fungsi-fungsi utama yang diperlukan
void CreateCity(City *city, char *name);         // Membuat kota baru
void AddPersonToCity(City *city, char *personName); // Menambah orang ke kota
void DeletePersonFromCity(City *city, char *personName); // Menghapus orang dari kota
void DisplayCity(City *city);                   // Menampilkan isi kota
void DeallocateAllCities(City cities[], int size); // Membersihkan memori

int FindPersonInCity(City *city, char *personName); // Mencari orang di kota

#endif 