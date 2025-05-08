#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perpustakaan_dll.h"

/* Inisialisasi perpustakaan DLL */
void inisialisasiPerpustakaanDLL(PerpustakaanDLL* perpus) {
    perpus->head = NULL;
    perpus->tail = NULL;
}

/* Tambah buku ke perpustakaan DLL */
void tambahBukuDLL(PerpustakaanDLL* perpus, char* judul, int stok) {
    BukuDLL* bukuBaru = (BukuDLL*)malloc(sizeof(BukuDLL));
    strcpy(bukuBaru->judul, judul);
    bukuBaru->stok = stok;
    bukuBaru->antrianHead = NULL;
    
    // Masukkan di awal doubly linked list
    bukuBaru->next = perpus->head;
    bukuBaru->prev = NULL;
    
    if (perpus->head != NULL) {
        perpus->head->prev = bukuBaru;
    } else {
        perpus->tail = bukuBaru;
    }
    
    perpus->head = bukuBaru;
    printf("Buku '%s' dengan stok %d telah ditambahkan ke perpustakaan DLL\n", judul, stok);
}

/* Cari buku di perpustakaan DLL */
BukuDLL* cariBukuDLL(PerpustakaanDLL* perpus, char* judul) {
    BukuDLL* current = perpus->head;
    while (current != NULL) {
        if (strcmp(current->judul, judul) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/* Tambah permintaan peminjaman ke perpustakaan DLL */
void tambahPeminjamanDLL(PerpustakaanDLL* perpus, char* judul, char* nama, int level, Stack* stackAktivitas) {
    BukuDLL* buku = cariBukuDLL(perpus, judul);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan di perpustakaan DLL\n", judul);
        return;
    }
    
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
    PeminjamanDLL* peminjamanBaru = (PeminjamanDLL*)malloc(sizeof(PeminjamanDLL));
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
        PeminjamanDLL* current = buku->antrianHead;
        
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
    aktivitas->tipeImplementasi = 2; // DLL
    
    Push(stackAktivitas, (int)aktivitas);
    
    printf("Permintaan peminjaman untuk buku '%s' oleh '%s' dengan prioritas %d telah ditambahkan ke perpustakaan DLL\n", 
           judul, nama, level);
}

/* Proses peminjaman buku di perpustakaan DLL */
void prosesPeminjamanDLL(PerpustakaanDLL* perpus, char* judul) {
    BukuDLL* buku = cariBukuDLL(perpus, judul);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan di perpustakaan DLL\n", judul);
        return;
    }
    
    if (buku->stok <= 0) {
        printf("Tidak dapat memproses peminjaman: Buku tidak tersedia (stok habis)\n");
        return;
    }
    
    if (buku->antrianHead == NULL) {
        printf("Tidak ada permintaan peminjaman dalam antrian untuk buku '%s'\n", judul);
        return;
    }
    
    // Ambil permintaan dengan prioritas tertinggi
    PeminjamanDLL* peminjaman = buku->antrianHead;
    buku->antrianHead = peminjaman->next;
    
    if (buku->antrianHead != NULL) {
        buku->antrianHead->prev = NULL;
    }
    
    // Kurangi stok
    buku->stok--;
    
    printf("Buku '%s' dipinjam oleh '%s' (prioritas %d) di perpustakaan DLL\n", 
           buku->judul, peminjaman->anggota.nama, peminjaman->anggota.level);
    
    free(peminjaman);
    
    // Jika stok habis, hapus semua antrian yang tersisa
    if (buku->stok <= 0 && buku->antrianHead != NULL) {
        printf("Stok buku '%s' habis, semua permintaan peminjaman yang tersisa dibatalkan\n", buku->judul);
        
        PeminjamanDLL* temp;
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

/* Proses pengembalian buku di perpustakaan DLL */
void pengembalianBukuDLL(PerpustakaanDLL* perpus, char* judul, char* nama) {
    BukuDLL* buku = cariBukuDLL(perpus, judul);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan di perpustakaan DLL\n", judul);
        return;
    }
    
    // Tambah stok
    buku->stok++;
    
    printf("Buku '%s' dikembalikan oleh '%s'. Stok baru: %d di perpustakaan DLL\n", 
           buku->judul, nama, buku->stok);
    
    // Tampilkan antrean berikutnya jika ada
    if (buku->antrianHead != NULL) {
        printf("Peminjam berikutnya dalam antrean: '%s' dengan prioritas %d\n",
               buku->antrianHead->anggota.nama, buku->antrianHead->anggota.level);
    }
}

/* Batalkan aktivitas di perpustakaan DLL */
void batalkanAktivitasDLL(PerpustakaanDLL* perpus, Aktivitas* aktivitas) {
    if (aktivitas->tipeAksi == PEMINJAMAN) {
        printf("Membatalkan permintaan peminjaman buku '%s' oleh '%s' di perpustakaan DLL\n", 
               aktivitas->judulBuku, aktivitas->nama);
        
        BukuDLL* buku = cariBukuDLL(perpus, aktivitas->judulBuku);
        if (buku == NULL) {
            printf("Buku tidak ditemukan\n");
            return;
        }
        
        // Cari dan hapus permintaan
        PeminjamanDLL* curr = buku->antrianHead;
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

/* Tampilkan status perpustakaan DLL */
void tampilkanStatusDLL(PerpustakaanDLL* perpus) {
    printf("\n===== Status Perpustakaan DLL =====\n");
    
    BukuDLL* nodeBuku = perpus->head;
    if (nodeBuku == NULL) {
        printf("Perpustakaan kosong\n");
        return;
    }
    
    while (nodeBuku != NULL) {
        printf("Buku: %s (Stok: %d)\n", nodeBuku->judul, nodeBuku->stok);
        
        // Tampilkan permintaan untuk buku ini
        PeminjamanDLL* nodePeminjaman = nodeBuku->antrianHead;
        if (nodePeminjaman != NULL) {
            printf("  Permintaan Peminjaman:\n");
            while (nodePeminjaman != NULL) {
                printf("  - %s (Prioritas: %d)\n", nodePeminjaman->anggota.nama, nodePeminjaman->anggota.level);
                nodePeminjaman = nodePeminjaman->next;
            }
        } else {
            printf("  Tidak ada permintaan peminjaman\n");
        }
        
        nodeBuku = nodeBuku->next;
    }
    printf("===================================\n\n");
}

/* Jalankan skenario pengujian DLL */
void jalankanSkenarioDLL(PerpustakaanDLL* perpus, Stack* stack) {
    printf("\n=== Menjalankan Skenario Pengujian DLL ===\n");
    
    // Reset perpustakaan dan stack
    inisialisasiPerpustakaanDLL(perpus);
    ClearStack(stack);
    
    // a) 2 X insert elemen "Buku1" dan "Buku2" di list Buku dimana stok buku masing masing 1
    printf("\na) Menambahkan buku 'Buku1' dan 'Buku2' dengan stok 1\n");
    tambahBukuDLL(perpus, "Buku1", 1);
    tambahBukuDLL(perpus, "Buku2", 1);
    tampilkanStatusDLL(perpus);
    
    // b) 1 X insert elemen "Anggota1" sebagai mahasiswa di list peminjaman "Buku1"
    printf("\nb) Menambahkan permintaan peminjaman oleh 'Anggota1' (mahasiswa) untuk 'Buku1'\n");
    tambahPeminjamanDLL(perpus, "Buku1", "Anggota1", MAHASISWA, stack);
    tampilkanStatusDLL(perpus);
    
    // c) 1 X insert elemen "Dosen1" sebagai dosen di list peminjaman "Buku1"
    printf("\nc) Menambahkan permintaan peminjaman oleh 'Dosen1' (dosen) untuk 'Buku1'\n");
    tambahPeminjamanDLL(perpus, "Buku1", "Dosen1", DOSEN, stack);
    tampilkanStatusDLL(perpus);
    
    // d) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku1"
    printf("\nd) Menambahkan permintaan peminjaman oleh 'Umum1' (masyarakat umum) untuk 'Buku1'\n");
    tambahPeminjamanDLL(perpus, "Buku1", "Umum1", MASYARAKAT, stack);
    tampilkanStatusDLL(perpus);
    
    // e) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku2"
    printf("\ne) Menambahkan permintaan peminjaman oleh 'Umum1' (masyarakat umum) untuk 'Buku2'\n");
    tambahPeminjamanDLL(perpus, "Buku2", "Umum1", MASYARAKAT, stack);
    tampilkanStatusDLL(perpus);
    
    // f) Proses peminjaman "Buku1". Pastikan "Dosen1" yang mendapatkan proses peminjaman.
    printf("\nf) Memproses peminjaman 'Buku1'. Dosen1 seharusnya mendapatkan buku karena memiliki prioritas tertinggi\n");
    prosesPeminjamanDLL(perpus, "Buku1");
    tampilkanStatusDLL(perpus);
    
    // g) Proses pengembalian "Buku1" oleh "Dosen1". Pastikan potensi selanjutnya adalah "Anggota1".
    printf("\ng) Mengembalikan 'Buku1' oleh 'Dosen1'. Sekarang 'Anggota1' seharusnya berada di antrian teratas\n");
    pengembalianBukuDLL(perpus, "Buku1", "Dosen1");
    tampilkanStatusDLL(perpus);
    
    // h) Elemen "Umum1" melakukan pembatalan aktivitas peminjaman buku (untuk "Buku2").
    printf("\nh) Membatalkan permintaan peminjaman terakhir (Umum1 untuk Buku2)\n");
    batalkanAktivitasTerakhir(NULL, perpus, NULL, stack);
    tampilkanStatusDLL(perpus);
    
    printf("\n=== Skenario Pengujian DLL Selesai ===\n");
}