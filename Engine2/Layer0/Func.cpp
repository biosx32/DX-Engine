#include "Static.h"
#include "Func.h"

bool IsPrintableCharacter (char p) {
	return p >= 32 && p <= 126;
}
int LongestLineInString (std::string src) {
	int ctr = 0;
	int top = 0;
	int max = src.size ();

	for (int i = 0; i <max; i++) {
		if (src.at(i) != '\n') {
			ctr += 1;
		}
		
	    if (src.at (i) == '\n' || i + 1 == max) {
			if (ctr > top) { top = ctr; }
			ctr = 0;
		}
	

		
	}

	return top;
}

std::string LabelizeVector(Vector2 vec, std::string label)
{

	char buffer[256] = {};
	sprintf_s(buffer, "%s: (%.2f, %.2f)", label.c_str(), vec.x, vec.y);
	std::string temp = buffer;

	return temp;
}
int CharacterCountInCString(const char* src, char chr, int max) {
	int counter = 0;
	for (int i = 0; i < max; i++) {
		const char* j = &src[i];
		if (*j == chr) counter++;
	}

	return counter;
}

std::string FormatString (const char* fmt, ...) {
	va_list args;
	va_start (args, fmt);
	const int size = 32768;
	char buffer[size];
	int rc = vsnprintf (buffer, size - 1, fmt, args);
	std::string text = std::string (buffer);
	va_end (args);
	return text;
}

int NewLineCountInString (std::string src) {
	return CharacterCountInString (src, '\n');
}

int CharacterCountInString (std::string src, char chr) {
	int counter = 0;
	for (int i = 0; i < src.length(); i++) {
		const char* j = &src[i];
		if (*j == chr) counter++;
	}

	return counter;
}

int File_bytes(FILE* p_file)
{
	int RESUME = ftell(p_file);
	fseek(p_file, 0, SEEK_END); //seek end
	int size = ftell(p_file); //get size
	fseek(p_file, 0 + RESUME, SEEK_SET);
	return size;
}
bool HasNextLn(FILE* p_file) {
	return GetNextLineOffset(p_file) >= 0;
}
int File_pos(FILE* p_file)
{
	return ftell(p_file);
}

int File_to_end(FILE * file)
{
	return File_bytes(file) - File_pos(file);
}


bool Startswith(char*a, char*b, int sublen) {
	for (int i = 0; i < sublen; i++) {
		if (*a != *b) {
			return false;
		}
	}
	return true;
}

void File_Setpos(FILE* p_file,int Pos)
{
	fseek(p_file, 0 + Pos, SEEK_SET);
}

int FindFirstChar(const char* str, char chr) {
	int size = strlen(str);
	int Pos = -1;
	if (size <= 0) {
		return -2;
	}

	for (int i = 0; i < size; i++) {
		if (str[i] == chr) {
			Pos = i;
			break;
	
		}
	}

	return Pos;
}

int FindLastChar(const char * str, char chr)
{
	int size = strlen(str);
	int Pos = -1;
	if (size <= 0) {
		return -2;
	}

	for (int i = size-1; i >= 0; i--) {
		if (str[i] == chr) {
			Pos = i;
			break;

		}
	}

	return Pos;
}

std::string sprintfToString (const char * fmt, ...)
{
	va_list args;
	va_start (args, fmt);
	const int size = 32768;
	char buffer[size];
	int rc = vsnprintf (buffer, size - 1, fmt, args);
	std::string text =std::string (buffer);
	va_end (args);

	return text;
}


int GetNextLineOffset(FILE* file) {
	char str[8196]; int Pos = -1;

	int size = File_bytes(file);
	if (size > 8196) {
		size = 8196; //max 8kb file
	}

	int RESUME = ftell(file);

	fread_s(str, 8196, 1, size, file);
	fseek(file, 0 + RESUME, SEEK_SET);

	for (int i = 0; i < size; i++) {
		if (str[i] == '\r') {
			if (i + 1 < size) {
				if (str[i + 1] == '\n') {
					Pos = i;
					break;
				}
			}
			
			
		}
		else if (str[i] == '\n') {
			Pos = i;
			break;
		}
	}

	return Pos;
}

wchar_t *CSTR_to_LSTR(const char* charArray)
{
	wchar_t *wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

void Swap(int*a, int*b) {
	int d = *a;
	*a = *b;
	*b = d;
}

V2 GetCenterOf (V2 pos, V2 size)
{
	return V2 (pos.x + size.x / 2, pos.y + size.y / 2);
}
