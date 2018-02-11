#ifndef __FUNC__H__
#define __FUNC__H__
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <sstream>
#include <time.h>


int CharacterCountInCString(char* src, char chr, int max);
int File_bytes(FILE* p_file);
wchar_t *CSTR_to_LSTR(char* charArray);
void Swap(int*a, int*b);


int GetNextLineOffset(FILE* file);
bool HasNextLn(FILE* file);
int File_pos(FILE* p_file);
int File_to_end(FILE* file);
bool Startswith(char * a, char * b, int sublen);
void File_Setpos(FILE * p_file, int Pos);
int FindFirstChar(char * str, char chr);
int FindLastChar(char * str, char chr);
#endif