#include <stdio.h>
#include "list.h"
#include <stdlib.h>


int CreateList(LinkedList *list){
    list->head = NULL;
    list->tail = NULL;
    return 1;
    return 0;
}

void InsertFirst(LinkedList *list, int value){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;  // Set the value
    newNode->next = list->head;
    newNode->prev = NULL;
    if (list->head != NULL){
        list->head->prev = newNode;
    }else{
        list->tail = newNode;
    }
    list->head = newNode;
}

void InsertLast(LinkedList *list, int value){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->prev = list->tail;
    if (list->tail != NULL){

        list->tail->next = newNode;
    }else{
        list->head = newNode;
    }
    list->tail = newNode;
}

void InsertBefore(LinkedList *list, int value, int key){
    Node *curr = list->head;
    while (curr != NULL && curr->value != key){
        curr = curr->next;
    }
    if (curr != NULL){
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->value = value;
        newNode->next = curr;
        newNode->prev = curr->prev;
        if (curr->prev != NULL){
            curr->prev->next = newNode;
        }else{
            list->head = newNode;
        }
        curr->prev = newNode;
    }
}


void InsertAfter(LinkedList *list, int value, int key){
    Node *curr = list->head;
    while (curr != NULL && curr->value != key){
        curr = curr->next;
    }
    if (curr != NULL){
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->value = value;
        newNode->next = curr->next;
        newNode->prev = curr;
        if (curr->next != NULL){
            curr->next->prev = newNode;
        }else{
            list->tail = newNode;
        }
        curr->next = newNode;
    }
}
void DeleteFirst(LinkedList *list){
    if (list->head != NULL){
        Node *temp = list->head;
        list->head = list->head->next;
        if (list->head != NULL){
            list->head->prev = NULL;
        }else{
            list->tail = NULL;
        }
        free(temp);
    }
}

void DeleteLast(LinkedList *list){
    if (list->tail != NULL){
        Node *temp = list->tail;
        list->tail = list->tail->prev;
        if (list->tail != NULL){
            list->tail->next = NULL;
        }else{
            list->head = NULL;
        }
        free(temp);
    }
}


void DeleteByValue(LinkedList *list, int value){
    Node *curr = list->head;
    while (curr != NULL && curr->value != value){
        curr = curr->next;
    }
    if (curr != NULL){
        if (curr->prev != NULL){
            curr->prev->next = curr->next;
        }else{
            list->head = curr->next;
        }
        if (curr->next != NULL){
            curr->next->prev = curr->prev;
        }else{
            list->tail = curr->prev;
        }
        free(curr);
    }
}

void ModifyValue(LinkedList *list, int value, int key){
    Node *curr = list->head;
    while (curr != NULL && curr->value != key){
        curr = curr->next;
    }
    if (curr != NULL){
        curr->value = value;
    }
}
int SearchValue(LinkedList *list, int value){
    Node *curr = list->head;
    while (curr != NULL){
        if (curr->value == value){
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}
            
int CountNode(LinkedList *list){
    int count = 0;
    Node *curr = list->head;
    while (curr != NULL){
        count++;
        curr = curr->next;
    }
    return count;
}
 

int GetFirst(LinkedList *list){
    if (list->head != NULL){
        return list->head->value;
    }else{
        return -1;
    }
}

int GetLast(LinkedList *list){
    if (list->tail != NULL){
        return list->tail->value;
    }else{
        return -1;
    }
}

void InsertBetween(LinkedList *list, int value, int key1, int key2){
    Node *curr = list->head;
    while (curr != NULL && (curr->value != key1 && curr->value != key2)){
        curr = curr->next;
    }
    if (curr != NULL && curr->next != NULL){
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->value = value;
        newNode->next = curr->next;
        newNode->prev = curr;
        curr->next->prev = newNode;
        curr->next = newNode;
    }
}

void PrintForward(LinkedList *list){
    Node *curr = list->head;
    while (curr != NULL){
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
}

void PrintBackward(LinkedList *list){
    Node *curr = list->tail;
    while (curr != NULL){
        printf("%d ", curr->value);
        curr = curr->prev;
    }
    printf("\n");
}

void ClearList(LinkedList *list){
    while (list->head != NULL){
        DeleteFirst(list);
    }
}
