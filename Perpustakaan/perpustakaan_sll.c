#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perpustakaan_sll.h"

/* Inisialisasi perpustakaan SLL */
void inisialisasiPerpustakaanSLL(PerpustakaanSLL* perpus) {
    perpus->head = NULL;
}

/* Tambah buku ke perpustakaan SLL */
void tambahBukuSLL(PerpustakaanSLL* perpus, char* judul, int stok) {
    BukuSLL* bukuBaru = (BukuSLL*)malloc(sizeof(BukuSLL));
    strcpy(bukuBaru->judul, judul);
    bukuBaru->stok = stok;
    bukuBaru->antrianHead = NULL;
    
    // Masukkan di awal linked list
    bukuBaru->next = perpus->head;
    perpus->head = bukuBaru;
    
    printf("Buku '%s' dengan stok %d telah ditambahkan ke perpustakaan SLL\n", judul, stok);
}

/* Cari buku di perpustakaan SLL */
BukuSLL* cariBukuSLL(PerpustakaanSLL* perpus, char* judul) {
    BukuSLL* current = perpus->head;
    while (current != NULL) {
        if (strcmp(current->judul, judul) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/* Tambah permintaan peminjaman ke perpustakaan SLL */
void tambahPeminjamanSLL(PerpustakaanSLL* perpus, char* judul, char* nama, int level, Stack* stackAktivitas) {
    BukuSLL* buku = cariBukuSLL(perpus, judul);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan di perpustakaan SLL\n", judul);
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
    PeminjamanSLL* peminjamanBaru = (PeminjamanSLL*)malloc(sizeof(PeminjamanSLL));
    peminjamanBaru->anggota = anggota;
    peminjamanBaru->next = NULL;
    
    // Masukkan ke dalam antrian berdasarkan prioritas
    if (buku->antrianHead == NULL || buku->antrianHead->anggota.level < level) {
        peminjamanBaru->next = buku->antrianHead;
        buku->antrianHead = peminjamanBaru;
    } else {
        PeminjamanSLL* current = buku->antrianHead;
        while (current->next != NULL && current->next->anggota.level >= level) {
            current = current->next;
        }
        peminjamanBaru->next = current->next;
        current->next = peminjamanBaru;
    }
    
    // Catat aktivitas untuk undo
    Aktivitas* aktivitas = (Aktivitas*)malloc(sizeof(Aktivitas));
    strcpy(aktivitas->nama, nama);
    strcpy(aktivitas->judulBuku, judul);
    aktivitas->tipeAksi = PEMINJAMAN;
    aktivitas->tipeImplementasi = 1; // SLL
    
    Push(stackAktivitas, (int)aktivitas);
    
    printf("Permintaan peminjaman untuk buku '%s' oleh '%s' dengan prioritas %d telah ditambahkan ke perpustakaan SLL\n", 
           judul, nama, level);
}

/* Proses peminjaman buku di perpustakaan SLL */
void prosesPeminjamanSLL(PerpustakaanSLL* perpus, char* judul) {
    BukuSLL* buku = cariBukuSLL(perpus, judul);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan di perpustakaan SLL\n", judul);
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
    PeminjamanSLL* peminjaman = buku->antrianHead;
    buku->antrianHead = peminjaman->next;
    
    // Kurangi stok
    buku->stok--;
    
    printf("Buku '%s' dipinjam oleh '%s' (prioritas %d) di perpustakaan SLL\n", 
           buku->judul, peminjaman->anggota.nama, peminjaman->anggota.level);
    
    free(peminjaman);
    
    // Jika stok habis, hapus semua antrian yang tersisa
    if (buku->stok <= 0 && buku->antrianHead != NULL) {
        printf("Stok buku '%s' habis, semua permintaan peminjaman yang tersisa dibatalkan\n", buku->judul);
        
        PeminjamanSLL* temp;
        while (buku->antrianHead != NULL) {
            temp = buku->antrianHead;
            buku->antrianHead = buku->antrianHead->next;
            free(temp);
        }
    }
}

/* Proses pengembalian buku di perpustakaan SLL */
void pengembalianBukuSLL(PerpustakaanSLL* perpus, char* judul, char* nama) {
    BukuSLL* buku = cariBukuSLL(perpus, judul);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan di perpustakaan SLL\n", judul);
        return;
    }
    
    // Tambah stok
    buku->stok++;
    
    printf("Buku '%s' dikembalikan oleh '%s'. Stok baru: %d di perpustakaan SLL\n", 
           buku->judul, nama, buku->stok);
    
    // Tampilkan antrean berikutnya jika ada
    if (buku->antrianHead != NULL) {
        printf("Peminjam berikutnya dalam antrean: '%s' dengan prioritas %d\n",
               buku->antrianHead->anggota.nama, buku->antrianHead->anggota.level);
    }
}

/* Batalkan aktivitas di perpustakaan SLL */
void batalkanAktivitasSLL(PerpustakaanSLL* perpus, Aktivitas* aktivitas) {
    if (aktivitas->tipeAksi == PEMINJAMAN) {
        printf("Membatalkan permintaan peminjaman buku '%s' oleh '%s' di perpustakaan SLL\n", 
               aktivitas->judulBuku, aktivitas->nama);
        
        BukuSLL* buku = cariBukuSLL(perpus, aktivitas->judulBuku);
        if (buku == NULL) {
            printf("Buku tidak ditemukan\n");
            return;
        }
        
        // Cari dan hapus permintaan dari antrian
        if (buku->antrianHead != NULL) {
            if (strcmp(buku->antrianHead->anggota.nama, aktivitas->nama) == 0) {
                PeminjamanSLL* temp = buku->antrianHead;
                buku->antrianHead = temp->next;
                free(temp);
            } else {
                PeminjamanSLL* prev = buku->antrianHead;
                PeminjamanSLL* curr = prev->next;
                
                while (curr != NULL) {
                    if (strcmp(curr->anggota.nama, aktivitas->nama) == 0) {
                        prev->next = curr->next;
                        free(curr);
                        break;
                    }
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }
}

/* Tampilkan status perpustakaan SLL */
void tampilkanStatusSLL(PerpustakaanSLL* perpus) {
    printf("\n===== Status Perpustakaan SLL =====\n");
    
    BukuSLL* nodeBuku = perpus->head;
    if (nodeBuku == NULL) {
        printf("Perpustakaan kosong\n");
        return;
    }
    
    while (nodeBuku != NULL) {
        printf("Buku: %s (Stok: %d)\n", nodeBuku->judul, nodeBuku->stok);
        
        // Tampilkan permintaan untuk buku ini
        PeminjamanSLL* nodePeminjaman = nodeBuku->antrianHead;
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

/* Jalankan skenario pengujian SLL */
void jalankanSkenarioSLL(PerpustakaanSLL* perpus, Stack* stack) {
    printf("\n=== Menjalankan Skenario Pengujian SLL ===\n");
    
    // Reset perpustakaan dan stack
    inisialisasiPerpustakaanSLL(perpus);
    ClearStack(stack);
    
    // a) 2 X insert elemen "Buku1" dan "Buku2" di list Buku dimana stok buku masing masing 1
    printf("\na) Menambahkan buku 'Buku1' dan 'Buku2' dengan stok 1\n");
    tambahBukuSLL(perpus, "Buku1", 1);
    tambahBukuSLL(perpus, "Buku2", 1);
    tampilkanStatusSLL(perpus);
    
    // b) 1 X insert elemen "Anggota1" sebagai mahasiswa di list peminjaman "Buku1"
    printf("\nb) Menambahkan permintaan peminjaman oleh 'Anggota1' (mahasiswa) untuk 'Buku1'\n");
    tambahPeminjamanSLL(perpus, "Buku1", "Anggota1", MAHASISWA, stack);
    tampilkanStatusSLL(perpus);
    
    // c) 1 X insert elemen "Dosen1" sebagai dosen di list peminjaman "Buku1"
    printf("\nc) Menambahkan permintaan peminjaman oleh 'Dosen1' (dosen) untuk 'Buku1'\n");
    tambahPeminjamanSLL(perpus, "Buku1", "Dosen1", DOSEN, stack);
    tampilkanStatusSLL(perpus);
    
    // d) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku1"
    printf("\nd) Menambahkan permintaan peminjaman oleh 'Umum1' (masyarakat umum) untuk 'Buku1'\n");
    tambahPeminjamanSLL(perpus, "Buku1", "Umum1", MASYARAKAT, stack);
    tampilkanStatusSLL(perpus);
    
    // e) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku2"
    printf("\ne) Menambahkan permintaan peminjaman oleh 'Umum1' (masyarakat umum) untuk 'Buku2'\n");
    tambahPeminjamanSLL(perpus, "Buku2", "Umum1", MASYARAKAT, stack);
    tampilkanStatusSLL(perpus);
    
    // f) Proses peminjaman "Buku1". Pastikan "Dosen1" yang mendapatkan proses peminjaman.
    printf("\nf) Memproses peminjaman 'Buku1'. Dosen1 seharusnya mendapatkan buku karena memiliki prioritas tertinggi\n");
    prosesPeminjamanSLL(perpus, "Buku1");
    tampilkanStatusSLL(perpus);
    
    // g) Proses pengembalian "Buku1" oleh "Dosen1". Pastikan potensi selanjutnya adalah "Anggota1".
    printf("\ng) Mengembalikan 'Buku1' oleh 'Dosen1'. Sekarang 'Anggota1' seharusnya berada di antrian teratas\n");
    pengembalianBukuSLL(perpus, "Buku1", "Dosen1");
    tampilkanStatusSLL(perpus);
    
    // h) Elemen "Umum1" melakukan pembatalan aktivitas peminjaman buku (untuk "Buku2").
    printf("\nh) Membatalkan permintaan peminjaman terakhir (Umum1 untuk Buku2)\n");
    batalkanAktivitasTerakhir(perpus, NULL, NULL, stack);
    tampilkanStatusSLL(perpus);
    
    printf("\n=== Skenario Pengujian SLL Selesai ===\n");
}