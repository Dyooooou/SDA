#ifndef PERPUSTAKAAN_COMMON_H
#define PERPUSTAKAAN_COMMON_H

#include "list.h"
#include "queue.h"
#include "stack.h"

#define MAX_BOOKS 100
#define MAX_NAME 50

/* Definisi level prioritas */
#define MASYARAKAT 1
#define MAHASISWA 2
#define DOSEN 3

/* Definisi tipe aksi */
#define PEMINJAMAN 1
#define PEMBATALAN 2

/* *** Tipe Anggota *** */
typedef struct {
    char nama[MAX_NAME];
    int level;  /* Level prioritas: 1=Masyarakat, 2=Mahasiswa, 3=Dosen */
} Anggota;

/* Struktur untuk aktivitas (untuk fitur undo) */
typedef struct {
    char nama[MAX_NAME];
    char judulBuku[MAX_NAME];
    int tipeAksi;
    int tipeImplementasi;  /* 1=SLL, 2=DLL, 3=Array */
} Aktivitas;

// Deklarasi forward untuk fungsi undo
void batalkanAktivitasTerakhir(void* perpusSLL, void* perpusDLL, void* perpusArray, Stack* stackAktivitas);

#endif