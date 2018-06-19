#ifndef __FUNC__H__
#define __FUNC__H__
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <sstream>
#include "Vectors.h"
#include <time.h>
std::string LabelizeVector(Vector2 vec, std::string label);

int CharacterCountInCString(const char* src, char chr, int max);
int File_bytes(FILE* p_file);
wchar_t *CSTR_to_LSTR(const char* charArray);
void Swap(int*a, int*b);


int GetNextLineOffset(FILE* file);
bool HasNextLn(FILE* file);
int File_pos(FILE* p_file);
int File_to_end(FILE* file);
bool Startswith(const char * a, const char * b, int sublen);
void File_Setpos(FILE * p_file, int Pos);
int FindFirstChar(const char * str, char chr);
int FindLastChar(const char * str, char chr);
std::string sprintfToString (const char *fmt, ...);

#endif