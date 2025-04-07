#ifndef CITYLIST_H
#define CITYLIST_H

#include "kota.h"

// Struktur node untuk linked list kota
typedef struct CityNode {
    City city;                  // Data kota
    struct CityNode *next;      // Pointer ke node berikutnya
    struct CityNode *prev;      // Pointer ke node sebelumnya
} CityNode;

// Struktur linked list kota
typedef struct {
    CityNode *head;             // Pointer ke node pertama
    CityNode *tail;             // Pointer ke node terakhir
    int count;                  // Jumlah kota dalam list
} CityList;

// Fungsi-fungsi untuk mengelola CityList
void CreateCityList(CityList *cityList);
void AddCity(CityList *cityList, char *cityName);
void RemoveCity(CityList *cityList, char *cityName);
City* FindCity(CityList *cityList, char *cityName);
void DisplayAllCities(CityList *cityList);
void ClearCityList(CityList *cityList);

#endif