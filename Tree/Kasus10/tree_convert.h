#ifndef TREE_CONVERT_H
#define TREE_CONVERT_H

#include "nbtrees.h"

typedef struct {
    char character;
    char morse_code[10];
} MorseMapping;

void CreateMorseTree(Isi_Tree X);
void FindPathToNode(Isi_Tree X, address current, char target, char* path, int level, int* found);
void CharToMorse(Isi_Tree X, char c, char* morse);
void StringToMorse(Isi_Tree X, const char* str, char* morse);
void MorseToChar(Isi_Tree X, const char* morse, char* c);
void MorseToString(Isi_Tree X, const char* morse, char* text);
void FileToMorse(Isi_Tree X, const char* input_file, const char* output_file);

#endif 