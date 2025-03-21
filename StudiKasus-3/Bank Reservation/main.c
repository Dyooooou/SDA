#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void PickQueue(Queue q[], int QueueCount);
void QueueProcess(Queue q[], int QueueCount);
void PrintAllQueue(Queue q[], int QueueCount);
void ExitApp(Queue q[], int QueueCount);
void PrintMenu();
Queue *pickWhichQueue(Queue q[], int QueueCount);
void ClearTerminal();

// this is Arkan's

int main() {
    bool isRunning = true;
    void (*tab[])(Queue q[], int QueueCount) = {PickQueue, QueueProcess, PrintAllQueue, ExitApp};
    int QueueCount;
    printf("Banyak Antrian: ");
    scanf("%d", &QueueCount);
    Queue q[QueueCount];
    for (int i = 0; i < QueueCount; i++) {
        CreateQueue(&q[i]);
    }
    while (isRunning) {
        int a;
        PrintMenu();
        scanf("%d", &a);
        if (a >= 1 && a <= 4) {
            tab[a - 1](q, QueueCount);
        } else {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
    return 0;
}

Queue *PickWhichQueue(Queue q[], int QueueCount) {
    int a;
    do {
        printf("Pilih antrian ke berapa? (1-%d): ", QueueCount);
        scanf("%d", &a);
        if (a < 1 || a > QueueCount) {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (a < 1 || a > QueueCount);
    return &q[a - 1];
}

void PickQueue(Queue q[], int QueueCount) {
    ClearTerminal();
    for (int i = 0; i < QueueCount; i++) {
        printf("Jumlah antrian ke-%d: %d\n", i + 1, QueueSize(q[i]));
    }
    
    Queue *selected = PickWhichQueue(q, QueueCount);
    int NextNumber = 1;
    
    if (!IsQueueEmpty(*selected)) {
        NextNumber = GetLast(selected) + 1;
    }
    
    Enqueue(selected, NextNumber);
    printf("Nomor antrian %d telah ditambahkan ke antrian %d\n", NextNumber, (int)(selected - q) + 1);
    PrintAllQueue(q, QueueCount);
}

void QueueProcess(Queue q[], int QueueCount) {
    ClearTerminal();
    Queue *selected = PickWhichQueue(q, QueueCount);
    bool processed = false;
    int processedNumber = -1;
    
    if (!IsQueueEmpty(*selected)) {
        processedNumber = Dequeue(selected);
        processed = true;
    }
    
    bool isRunning = true;
    while (isRunning) {
        ClearTerminal();
        if (processed) {
            printf("Diproses: %d\n", processedNumber);
            if (!IsQueueEmpty(*selected)) {
                printf("Up next: %d\n", GetFirst(selected));
            } else {
                printf("Tidak ada antrian berikutnya\n");
            }
        } else {
            printf("Tidak ada antrian..\n");
        }
        char a;
        printf("Input q untuk keluar... \n");
        getchar(); // Clear buffer
        scanf("%c", &a);
        if (a == 'q') {
            isRunning = false;
        }
        PrintAllQueue(q, QueueCount);
    }
}

void PrintAllQueue(Queue q[], int QueueCount) {
    bool isRunning = true;
    while (isRunning) {
        ClearTerminal();
        for (int i = 0; i < QueueCount; i++) {
            printf("Queue %d: ", i+1);
            PrintQueue(q[i]);
        }
        char a;
        printf("Input q untuk keluar... \n");
        getchar(); // Clear buffer
        scanf("%c", &a);
        if (a == 'q') {
            isRunning = false;
        }
    }
}

void ClearTerminal() {
        system("cls");
}

void ExitApp(Queue q[], int queueCount) {
    ClearTerminal();
    for (int i = 0; i < queueCount; i++) {
        ClearList(&q[i]);
    }
    printf("Terima kasih telah menggunakan aplikasi ini!\n");
    exit(0);
}

void PrintMenu() {
    ClearTerminal();
    printf("[Reservasi Antrian Konsultasi Bank]\n");
    printf("1. Ambil Nomer Antrian\n");
    printf("2. Proses Antrian\n");
    printf("3. Cetak Antrian\n");
    printf("4. Exit Aplikasi\n");
    printf("Pilihan Anda: ");
}