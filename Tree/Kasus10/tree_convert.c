#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nbtrees.h"
#include "tree_convert.h"


// Fungsi untuk membuat Morse Tree berdasarkan data dari Excel
void CreateMorseTree(Isi_Tree X) {
    // Inisialisasi seluruh node
    for (int i = 0; i <= jml_maks; i++) {
        X[i].info = ' ';
        X[i].ps_fs = nil;
        X[i].ps_nb = nil;
        X[i].ps_pr = nil;
    }

    // Membuat tree berdasarkan data dari Excel (Morse Tree.xlsx)
    // Format: Index | info | first son | next brother | parent
    
    // Root (indeks 1)
    X[1].info = ' ';  // Root tidak memiliki karakter
    X[1].ps_fs = 2;   // First son adalah node 2
    X[1].ps_nb = nil;
    X[1].ps_pr = nil;

    // Node 2 (m)
    X[2].info = 'm';
    X[2].ps_fs = 4;
    X[2].ps_nb = 3;
    X[2].ps_pr = 1;

    // Node 3 (3)
    X[3].info = '3';
    X[3].ps_fs = 6;
    X[3].ps_nb = nil;
    X[3].ps_pr = 1;

    // Node 4 (v)
    X[4].info = 'v';
    X[4].ps_fs = 8;
    X[4].ps_nb = 5;
    X[4].ps_pr = 2;

    // Node 5 (i)
    X[5].info = 'i';
    X[5].ps_fs = 10;
    X[5].ps_nb = nil;
    X[5].ps_pr = 2;

    // Node 6 (a)
    X[6].info = 'a';
    X[6].ps_fs = 12;
    X[6].ps_nb = 7;
    X[6].ps_pr = 3;

    // Node 7 (9)
    X[7].info = '9';
    X[7].ps_fs = 14;
    X[7].ps_nb = nil;
    X[7].ps_pr = 3;

    // Node 8 (0)
    X[8].info = '0';
    X[8].ps_fs = 16;
    X[8].ps_nb = 9;
    X[8].ps_pr = 4;

    // Node 9 (spasi)
    X[9].info = ' ';  // Spasi
    X[9].ps_fs = 18;
    X[9].ps_nb = nil;
    X[9].ps_pr = 4;

    // Node 10 (d)
    X[10].info = 'd';
    X[10].ps_fs = 20;
    X[10].ps_nb = 11;
    X[10].ps_pr = 5;

    // Node 11 (z)
    X[11].info = 'z';
    X[11].ps_fs = 22;
    X[11].ps_nb = nil;
    X[11].ps_pr = 5;

    // Node 12 (q)
    X[12].info = 'q';
    X[12].ps_fs = 24;
    X[12].ps_nb = 13;
    X[12].ps_pr = 6;

    // Node 13 (h)
    X[13].info = 'h';
    X[13].ps_fs = 26;
    X[13].ps_nb = nil;
    X[13].ps_pr = 6;

    // Node 14 (x)
    X[14].info = 'x';
    X[14].ps_fs = 28;
    X[14].ps_nb = 15;
    X[14].ps_pr = 7;

    // Node 15 (y)
    X[15].info = 'y';
    X[15].ps_fs = 30;
    X[15].ps_nb = nil;
    X[15].ps_pr = 7;

    // Node 16 (u)
    X[16].info = 'u';
    X[16].ps_fs = 32;
    X[16].ps_nb = 17;
    X[16].ps_pr = 8;

    // Node 17 (0)
    X[17].info = '0';
    X[17].ps_fs = 33;
    X[17].ps_nb = nil;
    X[17].ps_pr = 8;

    // Node 18 (k)
    X[18].info = 'k';
    X[18].ps_fs = nil;
    X[18].ps_nb = 19;
    X[18].ps_pr = 9;

    // Node 19 (4)
    X[19].info = '4';
    X[19].ps_fs = 34;
    X[19].ps_nb = nil;
    X[19].ps_pr = 9;

    // Node 20 (s)
    X[20].info = 's';
    X[20].ps_fs = nil;
    X[20].ps_nb = 21;
    X[20].ps_pr = 10;

    // Node 21 (t)
    X[21].info = 't';
    X[21].ps_fs = 35;
    X[21].ps_nb = nil;
    X[21].ps_pr = 10;

    // Node 22 (r)
    X[22].info = 'r';
    X[22].ps_fs = nil;
    X[22].ps_nb = 23;
    X[22].ps_pr = 11;

    // Node 23 (5)
    X[23].info = '5';
    X[23].ps_fs = nil;
    X[23].ps_nb = nil;
    X[23].ps_pr = 11;

    // Node 24 (e)
    X[24].info = 'e';
    X[24].ps_fs = 36;
    X[24].ps_nb = 25;
    X[24].ps_pr = 12;

    // Node 25 (2)
    X[25].info = '2';
    X[25].ps_fs = nil;
    X[25].ps_nb = nil;
    X[25].ps_pr = 12;

    // Node 26 (8)
    X[26].info = '8';
    X[26].ps_fs = 37;
    X[26].ps_nb = 27;
    X[26].ps_pr = 13;

    // Node 27 (7)
    X[27].info = '7';
    X[27].ps_fs = 38;
    X[27].ps_nb = nil;
    X[27].ps_pr = 13;

    // Node 28 (w)
    X[28].info = 'w';
    X[28].ps_fs = nil;
    X[28].ps_nb = 29;
    X[28].ps_pr = 14;

    // Node 29 (l)
    X[29].info = 'l';
    X[29].ps_fs = nil;
    X[29].ps_nb = nil;
    X[29].ps_pr = 14;

    // Node 30 (1)
    X[30].info = '1';
    X[30].ps_fs = nil;
    X[30].ps_nb = 31;
    X[30].ps_pr = 15;

    // Node 31 (g)
    X[31].info = 'g';
    X[31].ps_fs = nil;
    X[31].ps_nb = nil;
    X[31].ps_pr = 15;

    // Node 32 (b)
    X[32].info = 'b';
    X[32].ps_fs = nil;
    X[32].ps_nb = nil;
    X[32].ps_pr = 16;

    // Node 33 (6)
    X[33].info = '6';
    X[33].ps_fs = nil;
    X[33].ps_nb = nil;
    X[33].ps_pr = 17;

    // Node 34 (c)
    X[34].info = 'c';
    X[34].ps_fs = nil;
    X[34].ps_nb = nil;
    X[34].ps_pr = 19;

    // Node 35 (j)
    X[35].info = 'j';
    X[35].ps_fs = nil;
    X[35].ps_nb = nil;
    X[35].ps_pr = 21;

    // Node 36 (f)
    X[36].info = 'f';
    X[36].ps_fs = nil;
    X[36].ps_nb = nil;
    X[36].ps_pr = 24;

    // Node 37 (n)
    X[37].info = 'n';
    X[37].ps_fs = nil;
    X[37].ps_nb = nil;
    X[37].ps_pr = 26;

    // Node 38 (p)
    X[38].info = 'p';
    X[38].ps_fs = nil;
    X[38].ps_nb = nil;
    X[38].ps_pr = 27;
}

// Fungsi untuk mencari path dari root ke node dengan karakter tertentu
void FindPathToNode(Isi_Tree X, address current, char target, char* path, int level, int* found) {
    if (*found || current == nil) return;
    
    if (X[current].info == target) {
        path[level] = '\0'; // Null-terminate the string
        *found = 1;
        return;
    }
    
    // Cek first son (L)
    if (X[current].ps_fs != nil) {
        path[level] = 'L';
        FindPathToNode(X, X[current].ps_fs, target, path, level + 1, found);
        if (*found) return;
    }
    
    // Cek next brother (R)
    if (X[current].ps_nb != nil) {
        path[level] = 'R';
        FindPathToNode(X, X[current].ps_nb, target, path, level + 1, found);
        if (*found) return;
    }
}

// Fungsi untuk mengkonversi karakter ke kode morse
void CharToMorse(Isi_Tree X, char c, char* morse) {
    if (c == ' ') {
        strcpy(morse, " ");
        return;
    }
    
    // Konversi ke lowercase
    c = tolower(c);
    
    char path[20] = {0};
    int found = 0;
    
    // Mulai pencarian dari root (indeks 1)
    FindPathToNode(X, 1, c, path, 0, &found);
    
    if (!found) {
        strcpy(morse, "?");
        return;
    }
    
    // Konversi path L/R ke kode morse
    int i = 0;
    while (path[i] != '\0') {
        morse[i] = (path[i] == 'L') ? '.' : '-';
        i++;
    }
    morse[i] = '\0';
}

// Fungsi untuk mengkonversi string ke kode morse
void StringToMorse(Isi_Tree X, const char* str, char* morse) {
    morse[0] = '\0';
    int first_char = 1;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            strcat(morse, " / ");
            continue;
        }
        
        char temp[20];
        CharToMorse(X, str[i], temp);
        
        if (!first_char && str[i-1] != ' ') {
            strcat(morse, " ");
        }
        
        strcat(morse, temp);
        first_char = 0;
    }
}

// Fungsi untuk mengkonversi kode morse ke karakter
void MorseToChar(Isi_Tree X, const char* morse, char* c) {
    address current = 1; // Mulai dari root
    
    for (int i = 0; morse[i] != '\0'; i++) {
        if (morse[i] == '.') {
            // L (first son)
            if (X[current].ps_fs != nil) {
                current = X[current].ps_fs;
            } else {
                *c = '?';
                return;
            }
        } else if (morse[i] == '-') {
            // R (next brother)
            if (X[current].ps_nb != nil) {
                current = X[current].ps_nb;
            } else {
                *c = '?';
                return;
            }
        }
    }
    
    *c = X[current].info;
}

// Fungsi untuk mengkonversi string morse ke teks
void MorseToString(Isi_Tree X, const char* morse, char* text) {
    text[0] = '\0';
    char temp_morse[100];
    int temp_index = 0;
    int text_index = 0;
    
    for (int i = 0; morse[i] != '\0'; i++) {
        if (morse[i] == ' ' || morse[i] == '/') {
            if (temp_index > 0) {
                temp_morse[temp_index] = '\0';
                char c;
                MorseToChar(X, temp_morse, &c);
                text[text_index++] = c;
                temp_index = 0;
            }
            
            if (morse[i] == '/') {
                text[text_index++] = ' ';
                i++; // Lewati spasi setelah '/'
            }
        } else {
            temp_morse[temp_index++] = morse[i];
        }
    }
    
    // Handle morse code terakhir
    if (temp_index > 0) {
        temp_morse[temp_index] = '\0';
        char c;
        MorseToChar(X, temp_morse, &c);
        text[text_index++] = c;
    }
    
    text[text_index] = '\0';
}

// Fungsi untuk membaca file dan mengkonversi ke morse
void FileToMorse(Isi_Tree X, const char* input_file, const char* output_file) {
    FILE *in = fopen(input_file, "r");
    FILE *out = fopen(output_file, "w");
    
    if (!in || !out) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), in)) {
        // Hapus newline
        line[strcspn(line, "\n")] = '\0';
        
        char morse[1000];
        StringToMorse(X, line, morse);
        fprintf(out, "%s\n", morse);
    }
    
    fclose(in);
    fclose(out);
}
