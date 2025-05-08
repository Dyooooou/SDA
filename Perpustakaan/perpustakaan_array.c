#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perpustakaan_array.h"

/* Inisialisasi perpustakaan Array */
void inisialisasiPerpustakaanArray(PerpustakaanArray* perpus) {
    perpus->jumlah = 0;
    for (int i = 0; i < MAX_BOOKS; i++) {
        perpus->buku[i].antrianHead = NULL;
    }
}

/* Tambah buku ke perpustakaan Array */
void tambahBukuArray(PerpustakaanArray* perpus, char* judul, int stok) {
    if (perpus->jumlah >= MAX_BOOKS) {
        printf("Perpustakaan sudah penuh, tidak dapat menambahkan buku baru\n");
        return;
    }
    
    // Periksa apakah buku sudah ada
    for (int i = 0; i < perpus->jumlah; i++) {
        if (strcmp(perpus->buku[i].judul, judul) == 0) {
            printf("Buku '%s' sudah ada di perpustakaan Array\n", judul);
            return;
        }
    }
    
    // Tambahkan buku baru
    strcpy(perpus->buku[perpus->jumlah].judul, judul);
    perpus->buku[perpus->jumlah].stok = stok;
    perpus->buku[perpus->jumlah].antrianHead = NULL;
    
    printf("Buku '%s' dengan stok %d telah ditambahkan ke perpustakaan Array pada indeks %d\n", 
           judul, stok, perpus->jumlah);
    
    perpus->jumlah++;
}

/* Cari buku di perpustakaan Array, mengembalikan indeks */
int cariBukuArray(PerpustakaanArray* perpus, char* judul) {
    for (int i = 0; i < perpus->jumlah; i++) {
        if (strcmp(perpus->buku[i].judul, judul) == 0) {
            return i;
        }
    }
    return -1; // Buku tidak ditemukan
}

/* Tambah permintaan peminjaman ke perpustakaan Array */
void tambahPeminjamanArray(PerpustakaanArray* perpus, char* judul, char* nama, int level, Stack* stackAktivitas) {
    int indeksBuku = cariBukuArray(perpus, judul);
    if (indeksBuku == -1) {
        printf("Buku '%s' tidak ditemukan di perpustakaan Array\n", judul);
        return;
    }
    
    BukuArray* buku = &perpus->buku[indeksBuku];
    
    // Periksa apakah stok tersedia
    if (buku->stok <= 0) {
        printf("Buku '%s' tidak tersedia (stok habis), permintaan tidak dapat diproses\n", judul);
        return;
    }
    
    // Buat objek anggota
    Anggota anggota;
    strcpy(anggota.nama, nama);
    anggota.level = level;
    
    // Buat node peminjaman baru
    PeminjamanArray* peminjamanBaru = (PeminjamanArray*)malloc(sizeof(PeminjamanArray));
    peminjamanBaru->anggota = anggota;
    peminjamanBaru->next = NULL;
    peminjamanBaru->prev = NULL;
    
    // Masukkan ke dalam antrian berdasarkan prioritas
    if (buku->antrianHead == NULL || buku->antrianHead->anggota.level < level) {
        peminjamanBaru->next = buku->antrianHead;
        
        if (buku->antrianHead != NULL) {
            buku->antrianHead->prev = peminjamanBaru;
        }
        
        buku->antrianHead = peminjamanBaru;
    } else {
        PeminjamanArray* current = buku->antrianHead;
        
        while (current->next != NULL && current->next->anggota.level >= level) {
            current = current->next;
        }
        
        peminjamanBaru->next = current->next;
        peminjamanBaru->prev = current;
        
        if (current->next != NULL) {
            current->next->prev = peminjamanBaru;
        }
        
        current->next = peminjamanBaru;
    }
    
    // Catat aktivitas untuk undo
    Aktivitas* aktivitas = (Aktivitas*)malloc(sizeof(Aktivitas));
    strcpy(aktivitas->nama, nama);
    strcpy(aktivitas->judulBuku, judul);
    aktivitas->tipeAksi = PEMINJAMAN;
    aktivitas->tipeImplementasi = 3; // Array
    
    Push(stackAktivitas, (int)aktivitas);
    
    printf("Permintaan peminjaman untuk buku '%s' oleh '%s' dengan prioritas %d telah ditambahkan ke perpustakaan Array\n", 
           judul, nama, level);
}

/* Proses peminjaman buku di perpustakaan Array */
void prosesPeminjamanArray(PerpustakaanArray* perpus, char* judul) {
    int indeksBuku = cariBukuArray(perpus, judul);
    if (indeksBuku == -1) {
        printf("Buku '%s' tidak ditemukan di perpustakaan Array\n", judul);
        return;
    }
    
    BukuArray* buku = &perpus->buku[indeksBuku];
    
    if (buku->stok <= 0) {
        printf("Tidak dapat memproses peminjaman: Buku tidak tersedia (stok habis)\n");
        return;
    }
    
    if (buku->antrianHead == NULL) {
        printf("Tidak ada permintaan peminjaman dalam antrian untuk buku '%s'\n", judul);
        return;
    }
    
    // Ambil permintaan dengan prioritas tertinggi
    PeminjamanArray* peminjaman = buku->antrianHead;
    buku->antrianHead = peminjaman->next;
    
    if (buku->antrianHead != NULL) {
        buku->antrianHead->prev = NULL;
    }
    
    // Kurangi stok
    buku->stok--;
    
    printf("Buku '%s' dipinjam oleh '%s' (prioritas %d) di perpustakaan Array\n", 
           buku->judul, peminjaman->anggota.nama, peminjaman->anggota.level);
    
    free(peminjaman);
    
    // Jika stok habis, hapus semua antrian yang tersisa
    if (buku->stok <= 0 && buku->antrianHead != NULL) {
        printf("Stok buku '%s' habis, semua permintaan peminjaman yang tersisa dibatalkan\n", buku->judul);
        
        PeminjamanArray* temp;
        while (buku->antrianHead != NULL) {
            temp = buku->antrianHead;
            buku->antrianHead = buku->antrianHead->next;
            if (buku->antrianHead != NULL) {
                buku->antrianHead->prev = NULL;
            }
            free(temp);
        }
    }
}

/* Proses pengembalian buku di perpustakaan Array */
void pengembalianBukuArray(PerpustakaanArray* perpus, char* judul, char* nama) {
    int indeksBuku = cariBukuArray(perpus, judul);
    if (indeksBuku == -1) {
        printf("Buku '%s' tidak ditemukan di perpustakaan Array\n", judul);
        return;
    }
    
    BukuArray* buku = &perpus->buku[indeksBuku];
    
    // Tambah stok
    buku->stok++;
    
    printf("Buku '%s' dikembalikan oleh '%s'. Stok baru: %d di perpustakaan Array\n", 
           buku->judul, nama, buku->stok);
    
    // Tampilkan antrean berikutnya jika ada
    if (buku->antrianHead != NULL) {
        printf("Peminjam berikutnya dalam antrean: '%s' dengan prioritas %d\n",
               buku->antrianHead->anggota.nama, buku->antrianHead->anggota.level);
    }
}

/* Batalkan aktivitas di perpustakaan Array */
void batalkanAktivitasArray(PerpustakaanArray* perpus, Aktivitas* aktivitas) {
    if (aktivitas->tipeAksi == PEMINJAMAN) {
        printf("Membatalkan permintaan peminjaman buku '%s' oleh '%s' di perpustakaan Array\n", 
               aktivitas->judulBuku, aktivitas->nama);
        
        int indeksBuku = cariBukuArray(perpus, aktivitas->judulBuku);
        if (indeksBuku == -1) {
            printf("Buku tidak ditemukan\n");
            return;
        }
        
        BukuArray* buku = &perpus->buku[indeksBuku];
        
        // Cari dan hapus permintaan
        PeminjamanArray* curr = buku->antrianHead;
        while (curr != NULL) {
            if (strcmp(curr->anggota.nama, aktivitas->nama) == 0) {
                if (curr->prev != NULL) {
                    curr->prev->next = curr->next;
                } else {
                    buku->antrianHead = curr->next;
                }
                
                if (curr->next != NULL) {
                    curr->next->prev = curr->prev;
                }
                
                free(curr);
                break;
            }
            curr = curr->next;
        }
    }
}

/* Tampilkan status perpustakaan Array */
void tampilkanStatusArray(PerpustakaanArray* perpus) {
    printf("\n===== Status Perpustakaan Array =====\n");
    
    if (perpus->jumlah == 0) {
        printf("Perpustakaan kosong\n");
        return;
    }
    
    for (int i = 0; i < perpus->jumlah; i++) {
        printf("Buku[%d]: %s (Stok: %d)\n", i, perpus->buku[i].judul, perpus->buku[i].stok);
        
        // Tampilkan permintaan untuk buku ini
        PeminjamanArray* nodePeminjaman = perpus->buku[i].antrianHead;
        if (nodePeminjaman != NULL) {
            printf("  Permintaan Peminjaman:\n");
            while (nodePeminjaman != NULL) {
                printf("  - %s (Prioritas: %d)\n", nodePeminjaman->anggota.nama, nodePeminjaman->anggota.level);
                nodePeminjaman = nodePeminjaman->next;
            }
        } else {
            printf("  Tidak ada permintaan peminjaman\n");
        }
    }
    printf("=====================================\n\n");
}

/* Jalankan skenario pengujian Array */
void jalankanSkenarioArray(PerpustakaanArray* perpus, Stack* stack) {
    printf("\n=== Menjalankan Skenario Pengujian Array ===\n");
    
    // Reset perpustakaan dan stack
    inisialisasiPerpustakaanArray(perpus);
    ClearStack(stack);
    
    // a) 2 X insert elemen "Buku1" dan "Buku2" di list Buku dimana stok buku masing masing 1
    printf("\na) Menambahkan buku 'Buku1' dan 'Buku2' dengan stok 1\n");
    tambahBukuArray(perpus, "Buku1", 1);
    tambahBukuArray(perpus, "Buku2", 1);
    tampilkanStatusArray(perpus);
    
    // b) 1 X insert elemen "Anggota1" sebagai mahasiswa di list peminjaman "Buku1"
    printf("\nb) Menambahkan permintaan peminjaman oleh 'Anggota1' (mahasiswa) untuk 'Buku1'\n");
    tambahPeminjamanArray(perpus, "Buku1", "Anggota1", MAHASISWA, stack);
    tampilkanStatusArray(perpus);
    
    // c) 1 X insert elemen "Dosen1" sebagai dosen di list peminjaman "Buku1"
    printf("\nc) Menambahkan permintaan peminjaman oleh 'Dosen1' (dosen) untuk 'Buku1'\n");
    tambahPeminjamanArray(perpus, "Buku1", "Dosen1", DOSEN, stack);
    tampilkanStatusArray(perpus);
    
    // d) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku1"
    printf("\nd) Menambahkan permintaan peminjaman oleh 'Umum1' (masyarakat umum) untuk 'Buku1'\n");
    tambahPeminjamanArray(perpus, "Buku1", "Umum1", MASYARAKAT, stack);
    tampilkanStatusArray(perpus);
    
    // e) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku2"
    printf("\ne) Menambahkan permintaan peminjaman oleh 'Umum1' (masyarakat umum) untuk 'Buku2'\n");
    tambahPeminjamanArray(perpus, "Buku2", "Umum1", MASYARAKAT, stack);
    tampilkanStatusArray(perpus);
    
    // f) Proses peminjaman "Buku1". Pastikan "Dosen1" yang mendapatkan proses peminjaman.
    printf("\nf) Memproses peminjaman 'Buku1'. Dosen1 seharusnya mendapatkan buku karena memiliki prioritas tertinggi\n");
    prosesPeminjamanArray(perpus, "Buku1");
    tampilkanStatusArray(perpus);
    
    // g) Proses pengembalian "Buku1" oleh "Dosen1". Pastikan potensi selanjutnya adalah "Anggota1".
    printf("\ng) Mengembalikan 'Buku1' oleh 'Dosen1'. Sekarang 'Anggota1' seharusnya berada di antrian teratas\n");
    pengembalianBukuArray(perpus, "Buku1", "Dosen1");
    tampilkanStatusArray(perpus);
    
    // h) Elemen "Umum1" melakukan pembatalan aktivitas peminjaman buku (untuk "Buku2").
    printf("\nh) Membatalkan permintaan peminjaman terakhir (Umum1 untuk Buku2)\n");
    batalkanAktivitasTerakhir(NULL, NULL, perpus, stack);
    tampilkanStatusArray(perpus);
    
    printf("\n=== Skenario Pengujian Array Selesai ===\n");
}