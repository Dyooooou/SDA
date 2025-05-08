#ifndef PERPUSTAKAAN_ARRAY_H
#define PERPUSTAKAAN_ARRAY_H

#include "perpustakaan_common.h"

/* *** Implementasi Array *** */
typedef struct PeminjamanArray {
    Anggota anggota;
    struct PeminjamanArray* next;
    struct PeminjamanArray* prev;
} PeminjamanArray;

typedef struct {
    char judul[MAX_NAME];
    int stok;
    PeminjamanArray* antrianHead;  /* Antrian peminjaman (hanya jika stok > 0) */
} BukuArray;

typedef struct {
    BukuArray buku[MAX_BOOKS];
    int jumlah;
} PerpustakaanArray;

/* --- Fungsi-fungsi Array --- */
void inisialisasiPerpustakaanArray(PerpustakaanArray* perpus);
void tambahBukuArray(PerpustakaanArray* perpus, char* judul, int stok);
int cariBukuArray(PerpustakaanArray* perpus, char* judul);
void tambahPeminjamanArray(PerpustakaanArray* perpus, char* judul, char* nama, int level, Stack* stackAktivitas);
void prosesPeminjamanArray(PerpustakaanArray* perpus, char* judul);
void pengembalianBukuArray(PerpustakaanArray* perpus, char* judul, char* nama);
void batalkanAktivitasArray(PerpustakaanArray* perpus, Aktivitas* aktivitas);
void tampilkanStatusArray(PerpustakaanArray* perpus);
void jalankanSkenarioArray(PerpustakaanArray* perpus, Stack* stack);

#endif // PERPUSTAKAAN_ARRAY_H