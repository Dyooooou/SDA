/* mahasiswa_list.h */
#ifndef MAHASISWA_LIST_H
#define MAHASISWA_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Definisi InfoType */
typedef struct {
    char nama[50];     // Nama mahasiswa
    int nilaiUTS;      // Nilai UTS SDA
} InfoType;

/* Definisi Node */
typedef struct tElmtList *address;
typedef struct tElmtList {
    InfoType info; // Data Mahasiswa
    address next; // Pointer
} ElmtList;

/* Definisi List */
typedef struct {
    address first; // Pointer ke first element
} List;


/* 1. Creator/Constructor */
void CreateEmpty(List *L); // Membuat list kosong

/* 2. Destructor */
void DestroyList(List *L); // Menghapus semua elemen

/* 3. Validator */
bool IsEmpty(List L); // Cek isi list
bool IsExist(List L, char *nama); // Cek apakah nama ada di list

/* 4. Getter/Setter */
InfoType GetInfo(address P); // Ambil info dari node
void SetInfo(address P, InfoType info); // Set info ke Node
address GetNext(address P); // Ambil pointer next dari node
void SetNext(address P, address Next); // Set pointer next dari node
address First(List L); // Ambil pointer first dari list

/* 5. PrintObject */
void PrintList(List L);

address Allocation(InfoType mhsw); 
void Deallocation(address P); 
void InsertSorted(List *L, InfoType mhsw); 
void PrintListSortedByScore(List L);
int CountElements(List L); 
void CopyElementsGreaterThan(List L1, List *L2, int KKM); // 
void RemoveDuplicatesByName(List *L); 

#endif