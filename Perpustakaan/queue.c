#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void CreateQueue(Queue *q) {
    CreateList(q);
}

int IsQueueEmpty(Queue q) {
    return (q.head == NULL);
}

void Enqueue(Queue *q, int value) {
    InsertLast(q, value);
}

int Dequeue(Queue *q) {
    int value = -1;
    if (!IsQueueEmpty(*q)) {
        value = GetFirst(q);
        DeleteFirst(q);
    }
    return value;
}

int QueueSize(Queue q) {
    return CountNode(&q);
}

void PrintQueue(Queue q) {
    if (IsQueueEmpty(q)) {
        printf("Queue kosong\n");
    } else {
        PrintForward(&q);
    }
}

