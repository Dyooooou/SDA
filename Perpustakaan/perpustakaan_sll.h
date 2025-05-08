#ifndef PERPUSTAKAAN_SLL_H
#define PERPUSTAKAAN_SLL_H

#include "perpustakaan_common.h"

/* *** Implementasi SLL *** */
typedef struct PeminjamanSLL {
    Anggota anggota;
    struct PeminjamanSLL* next;
} PeminjamanSLL;

typedef struct BukuSLL {
    char judul[MAX_NAME];
    int stok;
    PeminjamanSLL* antrianHead;  /* Antrian peminjaman (hanya jika stok > 0) */
    struct BukuSLL* next;
} BukuSLL;

typedef struct {
    BukuSLL* head;
} PerpustakaanSLL;

/* --- Fungsi-fungsi SLL --- */
void inisialisasiPerpustakaanSLL(PerpustakaanSLL* perpus);
void tambahBukuSLL(PerpustakaanSLL* perpus, char* judul, int stok);
BukuSLL* cariBukuSLL(PerpustakaanSLL* perpus, char* judul);
void tambahPeminjamanSLL(PerpustakaanSLL* perpus, char* judul, char* nama, int level, Stack* stackAktivitas);
void prosesPeminjamanSLL(PerpustakaanSLL* perpus, char* judul);
void pengembalianBukuSLL(PerpustakaanSLL* perpus, char* judul, char* nama);
void batalkanAktivitasSLL(PerpustakaanSLL* perpus, Aktivitas* aktivitas);
void tampilkanStatusSLL(PerpustakaanSLL* perpus);
void jalankanSkenarioSLL(PerpustakaanSLL* perpus, Stack* stack);

#endif // PERPUSTAKAAN_SLL_H