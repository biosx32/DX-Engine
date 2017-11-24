#ifndef __FUNC__H__
#define __FUNC__H__

#include <stdio.h>
#include <Windows.h>
#include <string>

int File_bytes(FILE* p_file);

class OutputStream {
public:
	OutputStream& operator<<(char* str);
	OutputStream& operator<<(double chr);
};

extern OutputStream print;



#endif