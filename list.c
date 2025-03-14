#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;
} LinkedList;

int CreateList(LinkedList *list);
void InsertFirst(LinkedList *list, int value);
void InsertLast(LinkedList *list, int value);
void InsertBefore(LinkedList *list, int value, int key);
void InsertAfter(LinkedList *list, int value, int key);
void DeleteFirst(LinkedList *list);
void DeleteLast(LinkedList *list);
void DeleteByValue(LinkedList *list, int value);
void ModifyValue(LinkedList *list, int value, int key);
int SearchValue(LinkedList *list, int value);
int CountNode(LinkedList *list);
int GetFirst(LinkedList *list);
int GetLast(LinkedList *list);
void InsertBetween(LinkedList *list, int value, int key1, int key2);
void PrintForward(LinkedList *list);
void PrintBackward(LinkedList *list);
void ClearList(LinkedList *list);

#endif
