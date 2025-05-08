#ifndef STACK_H
#define STACK_H

#include "list.h"


typedef struct {
    LinkedList list;  
} Stack;

int IsEmpty(Stack *stack);             // Memeriksa apakah stack kosong
int CreateStack(Stack *stack);         // Inisialisasi stack baru
void Push(Stack *stack, int value);    // Menambahkan elemen ke stack
int Pop(Stack *stack);                 // Menghapus dan mengembalikan elemen dari stack
int Peek(Stack *stack);                // Melihat elemen teratas tanpa menghapus
void ClearStack(Stack *stack);         // Mengosongkan stack


#endif 