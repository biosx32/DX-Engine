#include "Func.h"

int CharacterCountInCString(char* src, char chr, int max) {
	int counter = 0;
	for (int i = 0; i < max; i++) {
		char* j = &src[i];
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

wchar_t *CSTR_to_LSTR(char* charArray)
{
	wchar_t *wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
