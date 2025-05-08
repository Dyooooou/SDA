
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perpustakaan_common.h"
#include "perpustakaan_sll.h"
#include "perpustakaan_dll.h"
#include "perpustakaan_array.h"

void tampilkanMenu() {
    printf("\n=============== SISTEM PERPUSTAKAAN ===============\n");
    printf("1. Pilih Implementasi (SLL, DLL, Array)\n");
    printf("2. Tambah Buku\n");
    printf("3. Tambah Permintaan Peminjaman\n");
    printf("4. Proses Peminjaman\n");
    printf("5. Proses Pengembalian\n");
    printf("6. Batalkan Aktivitas Terakhir (Undo)\n");
    printf("7. Tampilkan Status Perpustakaan\n");
    printf("8. Jalankan Skenario Pengujian\n"); // Soal di ETS
    printf("9. Kosongkan Perpustakaan\n");
    printf("0. Keluar\n");
    printf("Pilihan: ");
}

// Fungsi untuk mendapatkan nama level prioritas sebagai string
const char* getLevelName(int level) {
    switch (level) {
        case MASYARAKAT: return "Masyarakat";
        case MAHASISWA: return "Mahasiswa";
        case DOSEN: return "Dosen";
        default: return "Tidak dikenal";
    }
}

int main() {
    PerpustakaanSLL perpusSLL;
    PerpustakaanDLL perpusDLL;
    PerpustakaanArray perpusArray;
    Stack stackAktivitas;
    
    int pilihan = -1;
    int implementasiYangDipilih = 0; // 0=Belum dipilih, 1=SLL, 2=DLL, 3=Array
    
    // Inisialisasi stack aktivitas
    CreateStack(&stackAktivitas);
    
    // Pre-inisialisasi semua implementasi
    inisialisasiPerpustakaanSLL(&perpusSLL);
    inisialisasiPerpustakaanDLL(&perpusDLL);
    inisialisasiPerpustakaanArray(&perpusArray);
    
    while (pilihan != 0) {
        tampilkanMenu();
        scanf("%d", &pilihan);
        
        // Buffer untuk membaca input
        char judul[MAX_NAME];
        char nama[MAX_NAME];
        int level, stok;
        
        switch (pilihan) {
            case 1: 
                printf("Pilih implementasi:\n");
                printf("1. Single Linked List (SLL)\n");
                printf("2. Double Linked List (DLL)\n");
                printf("3. Array\n");
                printf("Pilihan: ");
                scanf("%d", &implementasiYangDipilih);
                
                if (implementasiYangDipilih == 1) {
                    printf("Implementasi SLL dipilih\n");
                } else if (implementasiYangDipilih == 2) {
                    printf("Implementasi DLL dipilih\n");
                } else if (implementasiYangDipilih == 3) {
                    printf("Implementasi Array dipilih\n");
                } else {
                    printf("Pilihan tidak valid\n");
                    implementasiYangDipilih = 0;
                }
                break;
                
            case 2: // Tambah Buku
                if (implementasiYangDipilih == 0) {
                    printf("Pilih implementasi terlebih dahulu\n");
                    break;
                }
                
                printf("Masukkan judul buku: ");
                scanf("%s", judul);
                
                printf("Masukkan stok buku: ");
                scanf("%d", &stok);
                
                if (stok < 0) {
                    printf("Stok tidak boleh negatif\n");
                    break;
                }
                
                if (implementasiYangDipilih == 1) {
                    tambahBukuSLL(&perpusSLL, judul, stok);
                } else if (implementasiYangDipilih == 2) {
                    tambahBukuDLL(&perpusDLL, judul, stok);
                } else {
                    tambahBukuArray(&perpusArray, judul, stok);
                }
                break;
                
            case 3: // Tambah Permintaan Peminjaman
                if (implementasiYangDipilih == 0) {
                    printf("Pilih implementasi terlebih dahulu\n");
                    break;
                }
                
                printf("Masukkan judul buku: ");
                scanf("%s", judul);
                
                printf("Masukkan nama peminjam: ");
                scanf("%s", nama);
                
                printf("Pilih level prioritas:\n");
                printf("1. Masyarakat Umum\n");
                printf("2. Mahasiswa\n");
                printf("3. Dosen\n");
                printf("Pilihan: ");
                scanf("%d", &level);
                
                if (level < 1 || level > 3) {
                    printf("Level prioritas tidak valid\n");
                    break;
                }
                
                if (implementasiYangDipilih == 1) {
                    tambahPeminjamanSLL(&perpusSLL, judul, nama, level, &stackAktivitas);
                } else if (implementasiYangDipilih == 2) {
                    tambahPeminjamanDLL(&perpusDLL, judul, nama, level, &stackAktivitas);
                } else {
                    tambahPeminjamanArray(&perpusArray, judul, nama, level, &stackAktivitas);
                }
                break;
                
            case 4: // Proses Peminjaman
                if (implementasiYangDipilih == 0) {
                    printf("Pilih implementasi terlebih dahulu\n");
                    break;
                }
                
                printf("Masukkan judul buku: ");
                scanf("%s", judul);
                
                if (implementasiYangDipilih == 1) {
                    prosesPeminjamanSLL(&perpusSLL, judul);
                } else if (implementasiYangDipilih == 2) {
                    prosesPeminjamanDLL(&perpusDLL, judul);
                } else {
                    prosesPeminjamanArray(&perpusArray, judul);
                }
                break;
                
            case 5: // Proses Pengembalian
                if (implementasiYangDipilih == 0) {
                    printf("Pilih implementasi terlebih dahulu\n");
                    break;
                }
                
                printf("Masukkan judul buku: ");
                scanf("%s", judul);
                
                printf("Masukkan nama peminjam: ");
                scanf("%s", nama);
                
                if (implementasiYangDipilih == 1) {
                    pengembalianBukuSLL(&perpusSLL, judul, nama);
                } else if (implementasiYangDipilih == 2) {
                    pengembalianBukuDLL(&perpusDLL, judul, nama);
                } else {
                    pengembalianBukuArray(&perpusArray, judul, nama);
                }
                break;
                
            case 6: // Batalkan Aktivitas Terakhir (Undo)
                if (implementasiYangDipilih == 0) {
                    printf("Pilih implementasi terlebih dahulu\n");
                    break;
                }
                
                if (implementasiYangDipilih == 1) {
                    batalkanAktivitasTerakhir(&perpusSLL, NULL, NULL, &stackAktivitas);
                } else if (implementasiYangDipilih == 2) {
                    batalkanAktivitasTerakhir(NULL, &perpusDLL, NULL, &stackAktivitas);
                } else {
                    batalkanAktivitasTerakhir(NULL, NULL, &perpusArray, &stackAktivitas);
                }
                break;
                
            case 7: // Tampilkan Status Perpustakaan
                if (implementasiYangDipilih == 0) {
                    printf("Pilih implementasi terlebih dahulu\n");
                    break;
                }
                
                if (implementasiYangDipilih == 1) {
                    tampilkanStatusSLL(&perpusSLL);
                } else if (implementasiYangDipilih == 2) {
                    tampilkanStatusDLL(&perpusDLL);
                } else {
                    tampilkanStatusArray(&perpusArray);
                }
                break;
                
            case 8: // Jalankan Skenario Pengujian
                if (implementasiYangDipilih == 0) {
                    printf("Pilih implementasi terlebih dahulu\n");
                    break;
                }
                
                if (implementasiYangDipilih == 1) {
                    jalankanSkenarioSLL(&perpusSLL, &stackAktivitas);
                } else if (implementasiYangDipilih == 2) {
                    jalankanSkenarioDLL(&perpusDLL, &stackAktivitas);
                } else {
                    jalankanSkenarioArray(&perpusArray, &stackAktivitas);
                }
                break;
                
            case 9: // Kosongkan Perpustakaan
                if (implementasiYangDipilih == 0) {
                    printf("Pilih implementasi terlebih dahulu\n");
                    break;
                }
                
                printf("Mengosongkan perpustakaan... ");
                
                if (implementasiYangDipilih == 1) {
                    inisialisasiPerpustakaanSLL(&perpusSLL);
                } else if (implementasiYangDipilih == 2) {
                    inisialisasiPerpustakaanDLL(&perpusDLL);
                } else {
                    inisialisasiPerpustakaanArray(&perpusArray);
                }
                
                // Reset stack aktivitas juga
                ClearStack(&stackAktivitas);
                
                printf("Perpustakaan telah dikosongkan\n");
                break;
                
            case 0: // Keluar
                printf("Terima kasih telah menggunakan Sistem Perpustakaan!\n");
                break;
                
            default:
                printf("Pilihan tidak valid\n");
                break;
        }
    }
    
    return 0;
}