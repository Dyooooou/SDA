#include <stdio.h>
#include <string.h>
#include "list_mahasiswa.h"

int main() {
    List L1, L2;
    InfoType mhs;
    
    // 1: ADT Link-List Mahasiswa sudah dibuat di mahasiswa_list.h dan mahasiswa_list.c
    
    // 2: Buat List L1 dan L2
    
    CreateEmpty(&L1);
    CreateEmpty(&L2);
    
    
    // 3: Isikan sejumlah elemen ke List L1, terurut Ascending menurut Nama
    printf("3: Mengisi List L1 (terurut Ascending berdasarkan Nama)\n");
    
    // Data mahasiswa
    strcpy(mhs.nama, "Adinda Syakila");
    mhs.nilaiUTS = 85;
    InsertSorted(&L1, mhs);
    printf("Menambahkan: %s (Nilai: %d)\n", mhs.nama, mhs.nilaiUTS);
    
    strcpy(mhs.nama, "Sudiono Biregar");
    mhs.nilaiUTS = 75;
    InsertSorted(&L1, mhs);
    printf("Menambahkan: %s (Nilai: %d)\n", mhs.nama, mhs.nilaiUTS);
    
    strcpy(mhs.nama, "Teddy Maiyor");
    mhs.nilaiUTS = 90;
    InsertSorted(&L1, mhs);
    printf("Menambahkan: %s (Nilai: %d)\n", mhs.nama, mhs.nilaiUTS);
    
    strcpy(mhs.nama, "Gita Nurfadila");
    mhs.nilaiUTS = 65;
    InsertSorted(&L1, mhs);
    printf("Menambahkan: %s (Nilai: %d)\n", mhs.nama, mhs.nilaiUTS);
    
    strcpy(mhs.nama, "Eko Prabroro");
    mhs.nilaiUTS = 82;
    InsertSorted(&L1, mhs);
    printf("Menambahkan: %s (Nilai: %d)\n", mhs.nama, mhs.nilaiUTS);
    
    strcpy(mhs.nama, "Joko Mulyono");
    mhs.nilaiUTS = 68;
    InsertSorted(&L1, mhs);
    printf("Menambahkan: %s (Nilai: %d)\n", mhs.nama, mhs.nilaiUTS);
    
    strcpy(mhs.nama, "Fatimah Azzahra");
    mhs.nilaiUTS = 95;
    InsertSorted(&L1, mhs);
    printf("Menambahkan: %s (Nilai: %d)\n\n", mhs.nama, mhs.nilaiUTS);
    
    // 4: Tampilkan isi List L1 terurut ascending berdasarkan nama
    printf("4: Menampilkan List L1 (terurut Ascending berdasarkan Nama)\n");
    PrintList(L1);
    printf("\n");
    
    // 5: Tampilkan isi List L1 terurut descending berdasarkan nilai
    printf("5: Menampilkan List L1 (terurut Descending berdasarkan Nilai)\n");
    PrintListSortedByScore(L1);
    printf("\n");
    
    // 6: Hitung Jumlah elemen
    printf("6: Menghitung Jumlah Mahasiswa ===\n");
    int count = CountElements(L1);
    printf("Jumlah mahasiswa pada List L1: %d\n\n", count);
    
    // 7: Copy elemen pada list L1 yang Nilainya > 70 ke List L2
    printf("7: Menyalin Mahasiswa dengan Nilai > 70 ke List L2 ===\n");
    CopyElementsGreaterThan(L1, &L2, 70);
    printf("Elemen dengan nilai > 70 berhasil disalin ke List L2\n\n");
    
    // 8: Tampilkan Isi elemen List L2
    printf("8: Menampilkan List L2 ===\n");
    PrintList(L2);
    printf("\n");
    
    // Menambahkan data duplikat untuk pengujian langkah 9
    printf("Menambahkan data duplikat untuk pengujian:\n");
    
    strcpy(mhs.nama, "Fatimah Azzahra");
    mhs.nilaiUTS = 78;
    InsertSorted(&L2, mhs);
    printf("Menambahkan: %s (Nilai: %d)\n", mhs.nama, mhs.nilaiUTS);
    
    strcpy(mhs.nama, "Gita Nurfadila");
    mhs.nilaiUTS = 83;
    InsertSorted(&L2, mhs);
    printf("Menambahkan: %s (Nilai: %d)\n\n", mhs.nama, mhs.nilaiUTS);
    
    printf("List L2 setelah penambahan data duplikat:\n");
    PrintList(L2);
    printf("\n");
    
    // 9: Menghapus nama duplikat dari List L2
    printf("9: Menghapus Duplikat Nama dari List L2 \n");
    RemoveDuplicatesByName(&L2);
    printf("Duplikat nama berhasil dihapus dari List L2\n\n");
    
    // 10: Tampilkan elemen List L2 yang baru
    printf("10: Menampilkan List L2 setelah Menghapus Duplikasi\n");
    PrintList(L2);
    printf("\n");
    
    // 11: Hapus List L1 dan List L2
    printf("11: Menghapus List L1 dan L2\n");
    DestroyList(&L1);
    DestroyList(&L2);
    printf("List L1 dan L2 berhasil dihapus\n");
    
    return 0;
}