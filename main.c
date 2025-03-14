
/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

// Gunakan pseudocode ADT Linked List anda menjadi program dengan mengikuti
// spesifikasi pembuatan deret bilangan ganjil dengan langkah berikut:
// 1) masukan bilangan 7 sebagai elemen pertama {insert first}
// > F.S. : elemen List = {7}
// 2) masukan bilangan 11 sebagai elemen kedua {insert last}
// > F.S. : elemen List = {7, 11}
// 3) masukan bilangan 9 diantara bilangan 7 dan 11 {insert after}
// > F.S. : elemen List = {7, 9, 11}
// 4) masukan bilangan 5 di awal list {insert first}
// > F.S. : elemen List = {5, 7, 9, 11}
// 5) masukan bilangan 13 di akhir list {insert last}
// > F.S. : elemen List = {5, 7, 9, 11, 13}
// 6) hapus elemen terakhir (bilangan 13) pada list {delete last}
// > F.S. : elemen List = {5, 7, 9, 11}
// 7) hapus bilangan 7 pada list
// > F.S. : elemen List = {5, 9, 11}
// 8) hapus elemen pertama (bilangan 5) pada list {delete first}
// > F.S. : elemen List = {9, 11}
// 9) hapus semua elemen list deret bilangan ganjil
// > F.S. : elemen List = {}

// Note: agar perubahan operasi pada elemen list terlihat dan dinyatakan berhasil maka:
// a. Tampilkan elemen datanya pada setiap instruksi dengan menambahkan sintaks
// print pada program setelah melakukan operasi.
// b. Setiap kali akan melakukan penghapusan elemen pastikan terlebih dahulu bahwa info
// elemen yang akan dihapus tersedia pada list. Tolak penghapusan jika kondisi linked list
// dalam underflow, yaitu operasi DELETION tidak mungkin dilakukan lagi, karena list
// sudah kosong.
// c. Setiap kali memasukan elemen ke dalam linked list pastikan bahwa hasil alokasi saat
// create node elemen list tidak null, artinya pengalokasian ke dalam memori berhasil.
// Namun, ketika overflow terjadi / hasil alokasi tidak berhasil mendapatkan alamat di
// dalam memori, maka proses insertion harus di tolak. 

#include <stdio.h>
#include <stdlib.h>
#include "LIST.H"


int main() {
    LinkedList list;
    CreateList(&list);

    // 1) Insert 7 diawal
    InsertFirst(&list, 7);
    PrintForward(&list);

    // 2) Insert 11 diakhir
    InsertLast(&list, 11);
    PrintForward(&list);

    // 3) Insert 9 diantara 7 dan 11
    InsertAfter(&list, 9, 7);
    PrintForward(&list);

    // 4) Insert 5 diawal
    InsertFirst(&list, 5);
    PrintForward(&list);

    // 5) Insert 13 diakhir
    InsertLast(&list, 13);
    PrintForward(&list);

    // 6) Delete last element (13)
    DeleteLast(&list);
    PrintForward(&list);

    // 7) Delete element dgn value 7
    DeleteByValue(&list, 7);
    PrintForward(&list);

    // 8) Delete Element pertama
    DeleteFirst(&list);
    PrintForward(&list);

    // 9) Clear list
    ClearList(&list);
    PrintForward(&list);

    return 0;
}

