#ifndef PERPUSTAKAAN_DLL_H
#define PERPUSTAKAAN_DLL_H

#include "perpustakaan_common.h"

/* *** Implementasi DLL *** */
typedef struct PeminjamanDLL {
    Anggota anggota;
    struct PeminjamanDLL* next;
    struct PeminjamanDLL* prev;
} PeminjamanDLL;

typedef struct BukuDLL {
    char judul[MAX_NAME];
    int stok;
    PeminjamanDLL* antrianHead;  /* Antrian peminjaman (hanya jika stok > 0) */
    struct BukuDLL* next;
    struct BukuDLL* prev;
} BukuDLL;

typedef struct {
    BukuDLL* head;
    BukuDLL* tail;
} PerpustakaanDLL;

/* --- Fungsi-fungsi DLL --- */
void inisialisasiPerpustakaanDLL(PerpustakaanDLL* perpus);
void tambahBukuDLL(PerpustakaanDLL* perpus, char* judul, int stok);
BukuDLL* cariBukuDLL(PerpustakaanDLL* perpus, char* judul);
void tambahPeminjamanDLL(PerpustakaanDLL* perpus, char* judul, char* nama, int level, Stack* stackAktivitas);
void prosesPeminjamanDLL(PerpustakaanDLL* perpus, char* judul);
void pengembalianBukuDLL(PerpustakaanDLL* perpus, char* judul, char* nama);
void batalkanAktivitasDLL(PerpustakaanDLL* perpus, Aktivitas* aktivitas);
void tampilkanStatusDLL(PerpustakaanDLL* perpus);
void jalankanSkenarioDLL(PerpustakaanDLL* perpus, Stack* stack);

#endif // PERPUSTAKAAN_DLL_H