#include <stdio.h>
#include <stdlib.h>
#include "nbtrees.h"

void Create_tree(Isi_Tree X, int Jml_Node) {
    /* Membuat non-binary tree dengan level order traversal */
    int i;
    infotype info;
    address parent, sibling;
    
    /* Inisialisasi seluruh node */
    for (i = 0; i <= jml_maks; i++) {
        X[i].info = ' ';
        X[i].ps_fs = nil;
        X[i].ps_nb = nil;
        X[i].ps_pr = nil;
    }
    
    /* Jika tidak ada node, return */
    if (Jml_Node <= 0) {
        return;
    }
    
    /* Membuat root (indeks 1) */
    printf("Masukkan nilai root: ");
    scanf(" %c", &info);
    X[1].info = info;
    X[1].ps_fs = nil;
    X[1].ps_nb = nil;
    X[1].ps_pr = nil;
    
    /* Membuat node lainnya secara level order */
    for (i = 2; i <= Jml_Node; i++) {
        printf("Masukkan nilai node %d: ", i);
        scanf(" %c", &info);
        X[i].info = info;
        
        /* Tentukan parent dari node ini */
        printf("Masukkan indeks parent dari node %d: ", i);
        scanf("%d", &parent);
        X[i].ps_pr = parent;
        
        /* Tambahkan sebagai first son jika parent belum memiliki anak */
        if (X[parent].ps_fs == nil) {
            X[parent].ps_fs = i;
        } else {
            /* Temukan sibling terakhir dan tambahkan sebagai next brother */
            sibling = X[parent].ps_fs;
            while (X[sibling].ps_nb != nil) {
                sibling = X[sibling].ps_nb;
            }
            X[sibling].ps_nb = i;
        }
        
        /* Inisialisasi first son dan next brother sebagai nil */
        X[i].ps_fs = nil;
        X[i].ps_nb = nil;
    }
}

boolean IsEmpty(Isi_Tree P) {
    /* Mengirimkan true jika Isi_Tree KOSONG */
    return (P[1].info == ' ');
}

void PreOrderTraversal(Isi_Tree P, address root) {
    /* Fungsi rekursif untuk traversal PreOrder */
    address current;
    
    if (root != nil) {
        /* Cetak parent */
        printf("%c ", P[root].info);
        
        /* Traversal ke first son */
        if (P[root].ps_fs != nil) {
            PreOrderTraversal(P, P[root].ps_fs);
        }
        
        /* Traversal ke next brother */
        if (P[root].ps_nb != nil) {
            PreOrderTraversal(P, P[root].ps_nb);
        }
    }
}

void PreOrder(Isi_Tree P) {
    /* Traversal PreOrder dari root */
    if (IsEmpty(P)) {
        printf("Tree kosong\n");
        return;
    }
    
    printf("PreOrder: ");
    PreOrderTraversal(P, 1);  /* Mulai dari root (indeks 1) */
    printf("\n");
}

void InOrderTraversal(Isi_Tree P, address root) {
    /* Fungsi rekursif untuk traversal InOrder */
    
    if (root != nil) {
        /* Traversal ke first son */
        if (P[root].ps_fs != nil) {
            InOrderTraversal(P, P[root].ps_fs);
        }
        
        /* Cetak parent */
        printf("%c ", P[root].info);
        
        /* Traversal ke next brother */
        if (P[root].ps_nb != nil) {
            InOrderTraversal(P, P[root].ps_nb);
        }
    }
}

void InOrder(Isi_Tree P) {
    /* Traversal InOrder dari root */
    if (IsEmpty(P)) {
        printf("Tree kosong\n");
        return;
    }
    
    printf("InOrder: ");
    InOrderTraversal(P, 1);  /* Mulai dari root (indeks 1) */
    printf("\n");
}

void PostOrderTraversal(Isi_Tree P, address root) {
    /* Fungsi rekursif untuk traversal PostOrder */
    
    if (root != nil) {
        /* Traversal ke first son */
        if (P[root].ps_fs != nil) {
            PostOrderTraversal(P, P[root].ps_fs);
        }
        
        /* Traversal ke next brother */
        if (P[root].ps_nb != nil) {
            PostOrderTraversal(P, P[root].ps_nb);
        }
        
        /* Cetak parent */
        printf("%c ", P[root].info);
    }
}

void PostOrder(Isi_Tree P) {
    /* Traversal PostOrder dari root */
    if (IsEmpty(P)) {
        printf("Tree kosong\n");
        return;
    }
    
    printf("PostOrder: ");
    PostOrderTraversal(P, 1);  /* Mulai dari root (indeks 1) */
    printf("\n");
}

void Level_order(Isi_Tree X, int Maks_node) {
    /* Traversal LevelOrder */
    int i;
    
    if (IsEmpty(X)) {
        printf("Tree kosong\n");
        return;
    }
    
    printf("Level Order: ");
    for (i = 1; i <= Maks_node; i++) {
        if (X[i].info != ' ') {
            printf("%c ", X[i].info);
        }
    }
    printf("\n");
}

void PrintTree(Isi_Tree P) {
    /* Mencetak tree dalam format tabel */
    int i;
    
    if (IsEmpty(P)) {
        printf("Tree kosong\n");
        return;
    }
    
    printf("Indeks\tInfo\tFirst Son\tNext Brother\tParent\n");
    printf("-------------------------------------------------------\n");
    
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info != ' ') {
            printf("%d\t%c\t%d\t\t%d\t\t%d\n", 
                i, P[i].info, P[i].ps_fs, P[i].ps_nb, P[i].ps_pr);
        }
    }
}

boolean Search(Isi_Tree P, infotype X) {
    /* Mengirimkan true jika ada node dari P yang bernilai X */
    int i;
    
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info == X) {
            return true;
        }
    }
    
    return false;
}

int nbElmt(Isi_Tree P) {
    /* Mengirimkan banyak elemen (node) di pohon non biner P */
    int i, count = 0;
    
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info != ' ') {
            count++;
        }
    }
    
    return count;
}

boolean IsDaun(Isi_Tree P, address idx) {
    /* Mengirimkan true jika node dengan indeks idx adalah daun */
    return (P[idx].ps_fs == nil);
}

int nbDaun(Isi_Tree P) {
    /* Mengirimkan banyak daun (node) pohon non biner P */
    int i, count = 0;
    
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info != ' ' && IsDaun(P, i)) {
            count++;
        }
    }
    
    return count;
}

int LevelNode(Isi_Tree P, address idx) {
    /* Menentukan level dari node dengan indeks idx */
    int level = 0;
    address current = idx;
    
    while (P[current].ps_pr != nil) {
        current = P[current].ps_pr;
        level++;
    }
    
    return level;
}

int Level(Isi_Tree P, infotype X) {
    /* Mengirimkan level dari node X yang merupakan salah satu simpul */
    int i;
    
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info == X) {
            return LevelNode(P, i);
        }
    }
    
    /* Jika tidak ditemukan, return -1 */
    return -1;
}

int DepthNode(Isi_Tree P, address idx) {
    /* Rekursif untuk menentukan kedalaman dari subtree dengan root idx */
    int depth_fs = 0, depth_nb = 0;
    
    if (idx == nil) {
        return -1;
    }
    
    /* Hitung kedalaman dari first son */
    if (P[idx].ps_fs != nil) {
        depth_fs = DepthNode(P, P[idx].ps_fs) + 1;
    }
    
    /* Hitung kedalaman dari next brother */
    if (P[idx].ps_nb != nil) {
        depth_nb = DepthNode(P, P[idx].ps_nb);
    }
    
    /* Return nilai terbesar */
    return (depth_fs > depth_nb) ? depth_fs : depth_nb;
}

int Depth(Isi_Tree P) {
    /* Mengirimkan kedalaman dari tree */
    if (IsEmpty(P)) {
        return 0;
    }
    
    return DepthNode(P, 1) + 1;  /* Tambahkan 1 untuk level root */
}

int Max(infotype Data1, infotype Data2) {
    /* Mengirimkan Nilai terbesar dari dua data */
    return (Data1 > Data2) ? Data1 : Data2;
}