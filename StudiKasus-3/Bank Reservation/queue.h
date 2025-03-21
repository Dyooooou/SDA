#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef LinkedList Queue;

int CreateQueue(Queue *q);
void Enqueue(Queue *q, int value);
int Dequeue(Queue *q, int *value);
int IsQueueEmpty(Queue *q);
int QueueCount(Queue *q);
int QueueFront(Queue *q); // Function untuk dapatkan first Elmt
int QueueRear(Queue *q);  // Function untuk dapatkan last Elmt
void DisplayQueue(Queue *q);
void ClearQueue(Queue *q);

#endif
