#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Untuk fungsi sleep (Linux/Mac)
#include "list.h"
#include "stack.h"
#include "queue.h"

// Fungsi untuk membersihkan layar (cross-platform)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi untuk delay (animasi)
void delay(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif
}

// Fungsi untuk menampilkan judul program
void tampilkanJudul() {
    printf("\n");
    printf("+-------------------------------------------------------------+\n");
    printf("|                                                             |\n");
    printf("|              DATA STRUCTURE SIMULATOR 2025                  |\n");
    printf("|           List | Stack | Queue Integration                  |\n");
    printf("|                                                             |\n");
    printf("+-------------------------------------------------------------+\n");
}

// Visualisasi stack (tampilan grafis untuk stack)
void visualisasiStack(Stack *stack) {
    printf("\n");
    printf("+-------------------------------------------------------------+\n");
    printf("|                     VISUALISASI STACK                       |\n");
    printf("+-------------------------------------------------------------+\n");
    
    if (IsEmpty(stack)) {
        printf("|                       [KOSONG]                             |\n");
    } else {
        Node *curr = stack->list.head;
        while (curr != NULL) {
            printf("|                        [%3d]                              |\n", curr->value);
            curr = curr->next;
        }
    }
    
    printf("+-------------------------------------------------------------+\n");
}

// Visualisasi queue (tampilan grafis untuk queue)
void visualisasiQueue(Queue *queue) {
    printf("\n");
    printf("+-------------------------------------------------------------+\n");
    printf("|                     VISUALISASI QUEUE                       |\n");
    printf("+-------------------------------------------------------------+\n");
    
    if (IsQueueEmpty(*queue)) {
        printf("|                       [KOSONG]                             |\n");
    } else {
        printf("|  HEAD ");
        Node *curr = queue->head;
        int count = 0;
        while (curr != NULL && count < 8) {
            printf("-> [%d] ", curr->value);
            curr = curr->next;
            count++;
        }
        
        if (curr != NULL) {
            printf("-> ... ");
        }
        
        printf("-> TAIL  |\n");
    }
    
    printf("+-------------------------------------------------------------+\n");
}

// Visualisasi linked list (tampilan grafis untuk linked list)
void visualisasiList(LinkedList *list) {
    printf("\n");
    printf("+-------------------------------------------------------------+\n");
    printf("|                  VISUALISASI LINKED LIST                    |\n");
    printf("+-------------------------------------------------------------+\n");
    
    if (list->head == NULL) {
        printf("|                       [KOSONG]                             |\n");
    } else {
        printf("|  HEAD ");
        Node *curr = list->head;
        int count = 0;
        while (curr != NULL && count < 8) {
            printf("-> [%d] ", curr->value);
            curr = curr->next;
            count++;
        }
        
        if (curr != NULL) {
            printf("-> ... ");
        }
        
        printf("-> TAIL  |\n");
    }
    
    printf("+-------------------------------------------------------------+\n");
}

// Fungsi untuk operasi list
void operasiList() {
    LinkedList list;
    CreateList(&list);
    int pilihan, nilai, kunci;
    int running = 1;
    
    while (running) {
        clearScreen();
        visualisasiList(&list);
        
        printf("\n");
        printf("+-------------------------------------------------------------+\n");
        printf("|                   OPERASI LINKED LIST                       |\n");
        printf("+-------------------------------------------------------------+\n");
        printf("|  1. Tambah Node di Awal                                     |\n");
        printf("|  2. Tambah Node di Akhir                                    |\n");
        printf("|  3. Tambah Node Sebelum Nilai Tertentu                      |\n");
        printf("|  4. Tambah Node Setelah Nilai Tertentu                      |\n");
        printf("|  5. Hapus Node Pertama                                      |\n");
        printf("|  6. Hapus Node Terakhir                                     |\n");
        printf("|  7. Hapus Node dengan Nilai Tertentu                        |\n");
        printf("|  8. Tampilkan List (Maju)                                   |\n");
        printf("|  9. Tampilkan List (Mundur)                                 |\n");
        printf("| 10. Kembali ke Menu Utama                                   |\n");
        printf("+-------------------------------------------------------------+\n");
        
        printf("Jumlah Node: %d\n\n", CountNode(&list));
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                printf("Masukkan nilai: ");
                scanf("%d", &nilai);
                InsertFirst(&list, nilai);
                break;
            case 2:
                printf("Masukkan nilai: ");
                scanf("%d", &nilai);
                InsertLast(&list, nilai);
                break;
            case 3:
                printf("Masukkan nilai: ");
                scanf("%d", &nilai);
                printf("Masukkan nilai kunci: ");
                scanf("%d", &kunci);
                InsertBefore(&list, nilai, kunci);
                break;
            case 4:
                printf("Masukkan nilai: ");
                scanf("%d", &nilai);
                printf("Masukkan nilai kunci: ");
                scanf("%d", &kunci);
                InsertAfter(&list, nilai, kunci);
                break;
            case 5:
                DeleteFirst(&list);
                printf("Node pertama dihapus.\n");
                break;
            case 6:
                DeleteLast(&list);
                printf("Node terakhir dihapus.\n");
                break;
            case 7:
                printf("Masukkan nilai yang akan dihapus: ");
                scanf("%d", &nilai);
                DeleteByValue(&list, nilai);
                break;
            case 8:
                printf("List (Maju): ");
                PrintForward(&list);
                printf("\nTekan Enter untuk melanjutkan...");
                getchar(); getchar(); // Membaca enter
                break;
            case 9:
                printf("List (Mundur): ");
                PrintBackward(&list);
                printf("\nTekan Enter untuk melanjutkan...");
                getchar(); getchar(); // Membaca enter
                break;
            case 10:
                running = 0;
                break;
            default:
                printf("Pilihan tidak valid.\n");
                printf("Tekan Enter untuk melanjutkan...");
                getchar(); getchar(); // Membaca enter
        }
        
        // Jeda sebentar untuk melihat pesan
        if (pilihan != 8 && pilihan != 9 && pilihan != 10) {
            printf("Tekan Enter untuk melanjutkan...");
            getchar(); getchar(); // Membaca enter
        }
    }
}

// Fungsi untuk operasi stack
void operasiStack() {
    Stack stack;
    CreateStack(&stack);
    int pilihan, nilai;
    int running = 1;
    
    while (running) {
        clearScreen();
        visualisasiStack(&stack);
        
        printf("\n");
        printf("+-------------------------------------------------------------+\n");
        printf("|                      OPERASI STACK                          |\n");
        printf("+-------------------------------------------------------------+\n");
        printf("|  1. Push (Tambah Elemen)                                    |\n");
        printf("|  2. Pop (Ambil Elemen Teratas)                              |\n");
        printf("|  3. Peek (Lihat Elemen Teratas)                             |\n");
        printf("|  4. Kosongkan Stack                                         |\n");
        printf("|  5. Kembali ke Menu Utama                                   |\n");
        printf("+-------------------------------------------------------------+\n");
        
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                printf("Masukkan nilai: ");
                scanf("%d", &nilai);
                Push(&stack, nilai);
                printf("Nilai %d telah di-push ke stack.\n", nilai);
                break;
            case 2:
                if (!IsEmpty(&stack)) {
                    nilai = Pop(&stack);
                    printf("Nilai yang di-pop: %d\n", nilai);
                } else {
                    printf("Stack kosong!\n");
                }
                break;
            case 3:
                if (!IsEmpty(&stack)) {
                    nilai = Peek(&stack);
                    printf("Nilai teratas: %d\n", nilai);
                } else {
                    printf("Stack kosong!\n");
                }
                break;
            case 4:
                ClearStack(&stack);
                printf("Stack telah dikosongkan.\n");
                break;
            case 5:
                running = 0;
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
        
        if (pilihan != 5) {
            printf("Tekan Enter untuk melanjutkan...");
            getchar(); getchar(); // Membaca enter
        }
    }
}

// Fungsi untuk operasi queue
void operasiQueue() {
    Queue queue;
    CreateQueue(&queue);
    int pilihan, nilai;
    int running = 1;
    
    while (running) {
        clearScreen();
        visualisasiQueue(&queue);
        
        printf("\n");
        printf("+-------------------------------------------------------------+\n");
        printf("|                      OPERASI QUEUE                          |\n");
        printf("+-------------------------------------------------------------+\n");
        printf("|  1. Enqueue (Tambah Elemen)                                 |\n");
        printf("|  2. Dequeue (Ambil Elemen Terdepan)                         |\n");
        printf("|  3. Lihat Ukuran Queue                                      |\n");
        printf("|  4. Kembali ke Menu Utama                                   |\n");
        printf("+-------------------------------------------------------------+\n");
        
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                printf("Masukkan nilai: ");
                scanf("%d", &nilai);
                Enqueue(&queue, nilai);
                printf("Nilai %d telah di-enqueue.\n", nilai);
                break;
            case 2:
                if (!IsQueueEmpty(queue)) {
                    nilai = Dequeue(&queue);
                    printf("Nilai yang di-dequeue: %d\n", nilai);
                } else {
                    printf("Queue kosong!\n");
                }
                break;
            case 3:
                printf("Ukuran queue: %d\n", QueueSize(queue));
                break;
            case 4:
                running = 0;
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
        
        if (pilihan != 4) {
            printf("Tekan Enter untuk melanjutkan...");
            getchar(); getchar(); // Membaca enter
        }
    }
}

// Fungsi simulasi semua struktur data bekerja bersama
void simulasiKombinasi() {
    LinkedList daftarData;
    Stack stackProses;
    Queue antrianProses;
    
    CreateList(&daftarData);
    CreateStack(&stackProses);
    CreateQueue(&antrianProses);
    
    clearScreen();
    printf("\n");
    printf("+-------------------------------------------------------------+\n");
    printf("|             KOMBINASI LIST, STACK, DAN QUEUE                |\n");
    printf("+-------------------------------------------------------------+\n");
    printf("|  Simulasi Data Processing Pipeline:                         |\n");
    printf("|  1. Data masuk ke list (penyimpanan awal)                   |\n");
    printf("|  2. Data pindah ke queue (antrean proses)                   |\n");
    printf("|  3. Data diproses satu per satu                             |\n");
    printf("|  4. Hasil proses disimpan di stack (riwayat)                |\n");
    printf("+-------------------------------------------------------------+\n\n");
    
    printf("Tekan Enter untuk memulai simulasi...");
    getchar(); getchar();
    
    // Langkah 1: Mengisi data ke dalam list
    clearScreen();
    printf("\nLangkah 1: Mengisi data ke linked list (database)...\n\n");
    for (int i = 1; i <= 5; i++) {
        printf("Menambahkan data %d ke list... ", i * 10);
        InsertLast(&daftarData, i * 10);
        delay(500);
        printf("Selesai\n");
    }
    
    printf("\nIsi linked list sekarang: ");
    PrintForward(&daftarData);
    
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
    
    // Langkah 2: Memindahkan data dari list ke queue
    clearScreen();
    printf("\nLangkah 2: Memindahkan data dari list ke queue (antrean proses)...\n\n");
    
    while (daftarData.head != NULL) {
        int nilai = GetFirst(&daftarData);
        printf("Memindahkan data %d dari list ke queue... ", nilai);
        Enqueue(&antrianProses, nilai);
        DeleteFirst(&daftarData);
        delay(500);
        printf("Selesai\n");
    }
    
    printf("\nIsi queue sekarang: ");
    PrintQueue(antrianProses);
    
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
    
    // Langkah 3 & 4: Memproses data dari queue dan menyimpan hasil ke stack
    clearScreen();
    printf("\nLangkah 3 & 4: Memproses data dari queue dan menyimpan hasil ke stack...\n\n");
    
    while (!IsQueueEmpty(antrianProses)) {
        int nilai = Dequeue(&antrianProses);
        int hasil = nilai * 2; // Contoh proses: nilai dikali 2
        
        printf("Mengambil data %d dari queue, memproses (x 2) = %d, menyimpan ke stack... ", 
               nilai, hasil);
        Push(&stackProses, hasil);
        delay(500);
        printf("Selesai\n");
    }
    
    printf("\nIsi stack sekarang (hasil proses, terurut dari atas): \n");
    visualisasiStack(&stackProses);
    
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
    
    // Langkah 5: Mengambil hasil dari stack
    clearScreen();
    printf("\nLangkah 5: Mengambil hasil dari stack (berurutan dari yang terbaru)...\n\n");
    
    while (!IsEmpty(&stackProses)) {
        int hasil = Pop(&stackProses);
        printf("Mengambil hasil: %d dari stack...\n", hasil);
        delay(500);
    }
    
    printf("\nSemua data telah diproses!\n");
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
}

// Fungsi utama
int main() {
    int pilihan;
    int running = 1;
    
    // Inisialisasi random seed
    srand(time(NULL));
    
    while (running) {
        clearScreen();
        tampilkanJudul();
        
        printf("\n");
        printf("+-------------------------------------------------------------+\n");
        printf("|                        MENU UTAMA                           |\n");
        printf("+-------------------------------------------------------------+\n");
        printf("|  1. Operasi Linked List                                     |\n");
        printf("|  2. Operasi Stack                                           |\n");
        printf("|  3. Operasi Queue                                           |\n");
        printf("|  4. Simulasi Kombinasi List + Stack + Queue                 |\n");
        printf("|  5. Keluar                                                  |\n");
        printf("+-------------------------------------------------------------+\n");
        
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                operasiList();
                break;
            case 2:
                operasiStack();
                break;
            case 3:
                operasiQueue();
                break;
            case 4:
                simulasiKombinasi();
                break;
            case 5:
                running = 0;
                break;
            default:
                printf("Pilihan tidak valid.\n");
                printf("Tekan Enter untuk melanjutkan...");
                getchar(); getchar(); // Membaca enter
        }
    }
    
    clearScreen();
    printf("\n");
    printf("+-------------------------------------------------------------+\n");
    printf("|                  TERIMA KASIH TELAH MENCOBA                 |\n");
    printf("|                DATA STRUCTURE SIMULATOR 2025                |\n");
    printf("+-------------------------------------------------------------+\n");
    
    return 0;
}
