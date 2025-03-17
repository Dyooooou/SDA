#include "list_mahasiswa.h"


/* 1. Creator/Constructor */
void CreateEmpty(List *L) {
    (*L).first = NULL;
}

/* 2. Destructor */
void DestroyList(List *L) {
    address P, temp;
    P = (*L).first;
    while (P != NULL) {
        temp = P;
        P = P->next;
        Deallocation(temp);
    }
    (*L).first = NULL;
}

/* 3. Validator */
bool IsEmpty(List L) {
    return (L.first == NULL);
}

bool IsExist(List L, char *nama) {
    address P = L.first;
    while (P != NULL) {
        if (strcmp(P->info.nama, nama) == 0) {
            return true;
        }
        P = P->next;
    }
    return false;
}

/* 4. Getter/Setter */
InfoType GetInfo(address P) {
    return P->info;
}

void SetInfo(address P, InfoType info) {
    P->info = info;
}

address GetNext(address P) {
    return P->next;
}

void SetNext(address P, address Next) {
    P->next = Next;
}

address First(List L) {
    return L.first;
}

/* 5. PrintObject */
void PrintList(List L) {
    address P = L.first;
    printf("%-30s %-10s\n", "Nama", "Nilai UTS SDA");
    
    if (IsEmpty(L)) {
        printf("List Kosong\n");
    } else {
        while (P != NULL) {
            printf("%-30s %-10d\n", P->info.nama, P->info.nilaiUTS);
            P = P->next;
        }
    }
    printf("----------------------------------------\n");
}


address Allocation(InfoType mhsw) {
    address P = (address)malloc(sizeof(ElmtList));
    if (P != NULL) {
        P->info = mhsw;
        P->next = NULL;
    }
    return P;
}

void Deallocation(address P) {
    free(P);
}

void InsertSorted(List *L, InfoType mhsw) {
    address P = Allocation(mhsw);
    
    if (P == NULL) {
        // Alokasi gagal
        printf("Alokasi memori gagal\n");
        return;
    }
    
    if (IsEmpty(*L) || strcmp(mhsw.nama, (*L).first->info.nama) < 0) {
        // Insert diawal
        P->next = (*L).first;
        (*L).first = P;
    } else {
        // Insert di tengah atau akhir
        address current = (*L).first;
        while (current->next != NULL && strcmp(mhsw.nama, current->next->info.nama) > 0) {
            current = current->next;
        }
        P->next = current->next;
        current->next = P;
    }
}

void PrintListSortedByScore(List L) {
    if (IsEmpty(L)) {
        printf("List Kosong\n");
        return;
    }
    
    // Hitung jumlah elemen
    int count = CountElements(L);
    
    // Buat array 
    InfoType *arr = (InfoType*)malloc(count * sizeof(InfoType));
    address P = L.first;
    int i = 0;
    
    while (P != NULL) {
        arr[i++] = P->info;
        P = P->next;
    }
    
    // Bubble sort array 
    for (i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j].nilaiUTS < arr[j + 1].nilaiUTS) {
                InfoType temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    // Print array sorted by score
    printf("%-30s %-10s\n", "Nama", "Nilai UTS SDA");

    for (i = 0; i < count; i++) {
        printf("%-30s %-10d\n", arr[i].nama, arr[i].nilaiUTS);
    }
    printf("----------------------------------------\n");
    
    free(arr);
}

int CountElements(List L) {
    int count = 0;
    address P = L.first;
    
    while (P != NULL) {
        count++;
        P = P->next;
    }
    
    return count;
}

void CopyElementsGreaterThan(List L1, List *L2, int KKM) { // KKM = 70
    address P = L1.first;
    
    CreateEmpty(L2);
    
    while (P != NULL) {
        if (P->info.nilaiUTS > KKM) {
            InsertSorted(L2, P->info);
        }
        P = P->next;
    }
}

void RemoveDuplicatesByName(List *L) {
    if (IsEmpty(*L) || (*L).first->next == NULL) {
        // list kosong atau hanya 1 elemen
        return;
    }
    
    address current = (*L).first;
    
    while (current != NULL && current->next != NULL) {
        address runner = current;
        
        while (runner->next != NULL) {
            if (strcmp(current->info.nama, runner->next->info.nama) == 0) {
                // jika ada duplikat, hapus
                address duplicate = runner->next;
                runner->next = duplicate->next;
                Deallocation(duplicate);
            } else {
                runner = runner->next;
            }
        }
        
        current = current->next;
    }
}