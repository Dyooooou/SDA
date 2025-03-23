#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef LinkedList Queue;

// Create a new empty queue
void CreateQueue(Queue *q);

// Check if queue is empty
int IsQueueEmpty(Queue q);

// Add a new element to the queue (enqueue)
void Enqueue(Queue *q, int value);

// Remove an element from the queue (dequeue)
int Dequeue(Queue *q);

// Get the number of elements in the queue
int QueueSize(Queue q);

// Display the queue
void PrintQueue(Queue q);

#endif // QUEUE_H