#include "Func.h"

int File_bytes(FILE* p_file)
{
	int RESUME = ftell(p_file);
	fseek(p_file, 0, SEEK_END); //seek end
	int size = ftell(p_file); //get size
	fseek(p_file, 0 + RESUME, SEEK_SET);
	return size;
}

void print(char * str)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, str, -1, wString, 4096);
	OutputDebugString(wString);
}
void println(char * str)
{
	print(str);
	print("\n");
}
