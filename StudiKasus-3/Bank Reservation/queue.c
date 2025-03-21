
#include <stdio.h>
#include "queue.h"

int CreateQueue(Queue *q) {
    return CreateList(q);
}

void Enqueue(Queue *q, int value) {
    InsertLast(q, value);
}

int Dequeue(Queue *q, int *value) {
    if (IsQueueEmpty(q)) {
        return 0;  
    }
    *value = GetFirst(q);
    
    DeleteFirst(q);
    
    return 1; 
}

int IsQueueEmpty(Queue *q) {
    return (q->head == NULL);
}

int QueueCount(Queue *q) {
    return CountNode(q);
}

int QueueFront(Queue *q) {
    if (IsQueueEmpty(q)) {
        return -1;  
    }
    return GetFirst(q);
}

int QueueRear(Queue *q) {
    if (IsQueueEmpty(q)) {
        return -1; 
    }
    return GetLast(q);
}

void DisplayQueue(Queue *q) {
    if (IsQueueEmpty(q)) {
        printf("Antrian kosong\n");
        return;
    }
    
    printf("Antrian: ");
    PrintForward(q);
}

void ClearQueue(Queue *q) {
    ClearList(q);
}
