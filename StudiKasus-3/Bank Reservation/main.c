#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "queue.h"

// Function prototypes
void clearScreen();
void printMenu();
void displayQueueStatus(Queue q[], int queueCount);
void pickQueue(Queue q[], int queueCount);
void processQueue(Queue q[], int queueCount);
void printAllQueues(Queue q[], int queueCount);
void exitApp(Queue q[], int queueCount);
int selectQueue(Queue q[], int queueCount, Queue **selected);
void waitForEnter();

int main() {
    int queueCount;
    int choice;
    int running = 1;
    
    printf("===============================\n");
    printf("    SISTEM ANTRIAN BANK\n");
    printf("===============================\n\n");
    printf("Masukkan jumlah antrian: ");
    
    // Input validasi for queue count
    while (scanf("%d", &queueCount) != 1 || queueCount <= 0) {
        // Clear input buffer
        while (getchar() != '\n');
        printf("Input tidak valid. Masukkan angka positif: ");
    }
    
    // Create array of queues
    Queue *queues = (Queue*)malloc(queueCount * sizeof(Queue));

    if (queues == NULL) {
        printf("Error: Tidak cukup memori.\n");
        return 1;
    }
    
    // Initialize setiap queue
    for (int i = 0; i < queueCount; i++) {
        if (!CreateQueue(&queues[i])) {
            printf("Error: Gagal membuat antrian #%d.\n", i + 1);
            // Clean up previously created queues
            for (int j = 0; j < i; j++) {
                ClearQueue(&queues[j]);
            }
            free(queues);
            return 1;
        }
    }
    
    printf("\nBerhasil membuat %d antrian!\n", queueCount);
    waitForEnter();
    
    // Main program
    while (running) {
        printMenu();
        printf("Pilihan Anda: ");
        
        // Input validation for menu choice
        if (scanf("%d", &choice) != 1) {
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                pickQueue(queues, queueCount);
                break;
            case 2:
                processQueue(queues, queueCount);
                break;
            case 3:
                printAllQueues(queues, queueCount);
                break;
            case 4:
                exitApp(queues, queueCount);
                running = 0;
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                waitForEnter();
                break;
        }
    }
    
    // Free memory for queues array
    free(queues);
    
    return 0;
}

void printMenu() {
    clearScreen();
    printf("\n===============================\n");
    printf("      APLIKASI TELLER BANK\n");
    printf("===============================\n\n");
    printf("1. Ambil Nomor Antrian\n");
    printf("2. Proses Antrian\n");
    printf("3. Cetak Antrian\n");
    printf("4. Exit Aplikasi\n");
    printf("-------------------------------\n");
}

void displayQueueStatus(Queue q[], int queueCount) {
    printf("Status Antrian:\n");
    printf("-------------------------------\n");
    for (int i = 0; i < queueCount; i++) {
        printf("Antrian #%d: %d orang\n", i + 1, QueueCount(&q[i]));
    }
    printf("-------------------------------\n");
}

int selectQueue(Queue q[], int queueCount, Queue **selected) {
    int queueNumber;
    
    printf("Pilih antrian (1-%d): ", queueCount);
    
    // Input validasi
    if (scanf("%d", &queueNumber) != 1) {
        // Clear input buffer
        while (getchar() != '\n');
        printf("Input tidak valid. Harus berupa angka.\n");
        return 0;
    }
    
    // Validasi
    if (queueNumber < 1 || queueNumber > queueCount) {
        printf("Nomor antrian tidak valid. Pilih antara 1-%d.\n", queueCount);
        return 0;
    }
    
    // Index 0
    *selected = &q[queueNumber - 1];
    return 1;
}

void waitForEnter() {
    printf("\nTekan Enter untuk melanjutkan...");
    
    // Clear the input buffer
    while (getchar() != '\n');
    getchar(); // Wait for Enter key
}

void pickQueue(Queue q[], int queueCount) {
    clearScreen();
    Queue *selected = NULL;
    int nextNumber = 1;  // Default 
    
    // Print queu
    displayQueueStatus(q, queueCount);
    
    // Select queue yang ingin di isi
    if (!selectQueue(q, queueCount, &selected)) {
        waitForEnter();
        return;
    }
    
    // If there are elements in the queue, get the last one and add 1
    if (!IsQueueEmpty(selected)) {
        // Use the QueueRear function to get the last element's value
        nextNumber = QueueRear(selected) + 1;
    }
    
    // Add the new customer to the queue
    Enqueue(selected, nextNumber);
    
    printf("\nNomor antrian %d telah ditambahkan!\n", nextNumber);
    printf("\nStatus antrian sekarang: ");
    DisplayQueue(selected);
    
    waitForEnter();
}

void processQueue(Queue q[], int queueCount) {
    clearScreen();
    Queue *selected = NULL;
    int customerNumber;
    
    // Show current queue counts
    displayQueueStatus(q, queueCount);
    
    // Select which queue to process
    if (!selectQueue(q, queueCount, &selected)) {
        waitForEnter();
        return;
    }
    
    // Check if the queue is empty
    if (IsQueueEmpty(selected)) {
        printf("Antrian kosong. Tidak ada yang dapat diproses.\n");
    } else {
        // Process the front of the queue
        Dequeue(selected, &customerNumber);
        printf("\n*** Memproses pelanggan dengan nomor antrian: %d ***\n", customerNumber);
        
        // Display the next customer in line
        if (!IsQueueEmpty(selected)) {
            printf("Pelanggan berikutnya: %d\n", QueueFront(selected));
        } else {
            printf("Tidak ada pelanggan lagi dalam antrian ini.\n");
        }
        
        // Display current queue state
        printf("\nStatus antrian sekarang: ");
        DisplayQueue(selected);
    }
    
    waitForEnter();
}

void printAllQueues(Queue q[], int queueCount) {
    clearScreen();
    printf("===============================\n");
    printf("     STATUS SEMUA ANTRIAN\n");
    printf("===============================\n\n");
    
    for (int i = 0; i < queueCount; i++) {
        printf("Antrian #%d: ", i + 1);
        DisplayQueue(&q[i]);
        printf("\n");
    }
    
    waitForEnter();
}

void exitApp(Queue q[], int queueCount) {
    clearScreen();
    char confirmation;
    
    printf("Apakah Anda yakin ingin keluar? (y/n): ");
    // Clear input buffer
    while (getchar() != '\n');
    scanf("%c", &confirmation);
    
    if (confirmation == 'y' || confirmation == 'Y') {
        printf("\nMenutup aplikasi dan membersihkan semua antrian...\n");
        
        // Clear all queues
        for (int i = 0; i < queueCount; i++) {
            ClearQueue(&q[i]);
        }
        
        printf("\nTerima kasih telah menggunakan Aplikasi Teller Bank!\n");
    } else {
        // User decided not to exit
        return;
    }
    
    waitForEnter();
}

void clearScreen() {
    system("cls");
}
