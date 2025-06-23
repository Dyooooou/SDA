#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nbtrees.h"
#include "tree_convert.h"
#include "boolean.h"

void CreateMorseTree(Isi_Tree X);
void FindPathToNode(Isi_Tree X, address current, char target, char* path, int level, int* found);
void CharToMorse(Isi_Tree X, char c, char* morse);
void StringToMorse(Isi_Tree X, const char* str, char* morse);
void MorseToChar(Isi_Tree X, const char* morse, char* c);
void MorseToString(Isi_Tree X, const char* morse, char* text);
void FileToMorse(Isi_Tree X, const char* input_file, const char* output_file);

int main() {
    Isi_Tree morseTree;
    CreateMorseTree(morseTree);
    
    printf("Morse Tree telah dibuat.\n");
    
    // 1. Menampilkan semua node hasil traversal secara inorder
    printf("\nInOrder Traversal:\n");
    InOrder(morseTree);
    
    // 2. Mengkonversi string "JTK Politeknik Negeri Bandung" ke morse
    char input[] = "JTK Politeknik Negeri Bandung";
    char morse[1000];
    StringToMorse(morseTree, input, morse);
    printf("\nKode morse untuk \"%s\":\n%s\n", input, morse);
    
    // 3. Mengkonversi kode morse ke teks
    char morse_input[] = ".-- .- ...- .-.. ..-. -... .... .. ... .-";
    char text[100];
    MorseToString(morseTree, morse_input, text);
    printf("\nHasil konversi morse \"%s\":\n%s\n", morse_input, text);
    
    // 4. Membaca file dan mengkonversi ke morse
    printf("\nMengkonversi file input.txt ke morse (output.txt)...\n");
    FileToMorse(morseTree, "input.txt", "output.txt");
    printf("Konversi selesai.\n");
    
    
    return 0;
}