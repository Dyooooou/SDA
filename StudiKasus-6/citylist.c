#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "citylist.h"

// Inisialisasi linked list kota
void CreateCityList(CityList *cityList) {
    cityList->head = NULL;
    cityList->tail = NULL;
    cityList->count = 0;
}

// Menambahkan kota baru ke dalam linked list
void AddCity(CityList *cityList, char *cityName) {
    // Periksa apakah kota sudah ada
    if (FindCity(cityList, cityName) != NULL) {
        printf("Kota dengan nama %s sudah ada!\n", cityName);
        return;
    }
    
    // Membuat node baru
    CityNode *newNode = (CityNode*)malloc(sizeof(CityNode));
    if (newNode == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk kota baru.\n");
        return;
    }
    
    // Inisialisasi kota
    CreateCity(&(newNode->city), cityName);
    newNode->next = NULL;
    newNode->prev = cityList->tail;
    
    // Menambahkan node ke linked list
    if (cityList->tail != NULL) {
        cityList->tail->next = newNode;
    } else {
        cityList->head = newNode;
    }
    
    cityList->tail = newNode;
    cityList->count++;
    
    printf("Kota %s berhasil ditambahkan.\n", cityName);
}

// Menghapus kota dari linked list
void RemoveCity(CityList *cityList, char *cityName) {
    CityNode *current = cityList->head;
    
    // Mencari kota yang akan dihapus
    while (current != NULL) {
        if (strcmp(current->city.cityName, cityName) == 0) {
            // Menyesuaikan pointer jika node adalah head
            if (current->prev == NULL) {
                cityList->head = current->next;
            } else {
                current->prev->next = current->next;
            }
            
            // Menyesuaikan pointer jika node adalah tail
            if (current->next == NULL) {
                cityList->tail = current->prev;
            } else {
                current->next->prev = current->prev;
            }
            
            // Membersihkan linked list dalam kota
            ClearList(&(current->city.list));
            
            // Membebaskan memori
            free(current);
            cityList->count--;
            
            printf("Kota %s berhasil dihapus.\n", cityName);
            return;
        }
        current = current->next;
    }
    
    printf("Kota dengan nama %s tidak ditemukan.\n", cityName);
}

// Mencari kota berdasarkan nama
City* FindCity(CityList *cityList, char *cityName) {
    CityNode *current = cityList->head;
    
    while (current != NULL) {
        if (strcmp(current->city.cityName, cityName) == 0) {
            return &(current->city);
        }
        current = current->next;
    }
    
    return NULL;
}

// Menampilkan semua kota
void DisplayAllCities(CityList *cityList) {
    if (cityList->head == NULL) {
        printf("Tidak ada kota yang tersedia.\n");
        return;
    }
    
    printf("=== DAFTAR SEMUA KOTA ===\n");
    CityNode *current = cityList->head;
    int count = 1;
    
    while (current != NULL) {
        printf("Kota #%d:\n", count++);
        DisplayCity(&(current->city));
        printf("\n");
        current = current->next;
    }
}

// Membersihkan semua kota dari linked list
void ClearCityList(CityList *cityList) {
    CityNode *current = cityList->head;
    CityNode *next;
    
    while (current != NULL) {
        next = current->next;
        
        // Membersihkan linked list dalam kota
        ClearList(&(current->city.list));
        
        // Membebaskan node
        free(current);
        
        current = next;
    }
    
    cityList->head = NULL;
    cityList->tail = NULL;
    cityList->count = 0;
}