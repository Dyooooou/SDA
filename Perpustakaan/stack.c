
#include <stdio.h>
#include "stack.h"


// Validator stack kosong/tidak
int IsEmpty(Stack *stack){
    return stack->list.head == NULL;
}

// Init stack baru
int CreateStack(Stack *stack){
    return CreateList(&stack->list);
}

// Insert elemen ke stack 
void Push(Stack *stack, int value){
    InsertFirst(&stack->list, value);
}

// Menghapus + Mengembalikan elemen dari stack
int Pop(Stack *stack){
    if (IsEmpty(stack)){
        printf("Stack Underflow\n"); //Stack underflow happens when we try to pop (remove) an item from the stack, 
                                     //when nothing is actually there to remove. 
                                        // This will raise an alarm of sorts in the computer because we told it to do something that cannot be done.
    }
    int value = GetFirst(&stack->list);
    DeleteFirst(&stack->list);
    return value;
}

// Melihat elemen teratas tanpa dihapus ()
int Peek(Stack *stack){
    if (IsEmpty(stack)){
        printf("Stack kosong\n");

    }
    return GetFirst(&stack->list);
}

// Kosongin stack
void ClearStack(Stack *stack){
    ClearList(&stack->list);
}
