#include "Func.h"

OutputStream print;
Error printerr;

int File_bytes(FILE* p_file)
{
	int RESUME = ftell(p_file);
	fseek(p_file, 0, SEEK_END); //seek end
	int size = ftell(p_file); //get size
	fseek(p_file, 0 + RESUME, SEEK_SET);
	return size;
}

OutputStream & OutputStream::operator<<(char * str)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, str, -1, wString, 4096);
	OutputDebugString(wString);
	return *this;
}

OutputStream & OutputStream::operator<<(double chr)
{
	std::string s = std::to_string(chr);
	char const *pchar = s.c_str();
	wchar_t* wString = new wchar_t[128];
	MultiByteToWideChar(CP_ACP, 0, pchar, -1, wString, 128);
	OutputDebugString(wString);
	return *this;
}


Error & Error::operator<<(char * str)
{
	OutputStream::operator<<("!ERROR: ");
	OutputStream::operator<<(str);
	return *this;
}

Error & Error::operator<<(double chr)
{
	OutputStream::operator<<("!ERROR: ");
	OutputStream::operator<<(chr);
	return *this;
}


