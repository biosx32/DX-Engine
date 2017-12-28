#ifndef __FUNC__H__
#define __FUNC__H__
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <ctime>
#include <sstream>


class SpecialCode {
public:
	SpecialCode(int x) { code = x; }
	bool SpecialCode::operator==(SpecialCode& other) { return this->code == other.code; }
	int code=-1;
};

extern SpecialCode msgbox ;
extern SpecialCode console;
extern SpecialCode clear;

char * const getFrameNumber();

int File_bytes(FILE* p_file);

class OutputStream {
protected:
	std::stringstream stream;
public:

	
	inline OutputStream & OutputStream::operator<<(int data) { stream << data; return *this;}
	inline OutputStream & OutputStream::operator<<(double data) { stream << data; return *this;}

	OutputStream & OutputStream::operator<<(SpecialCode finish);
	OutputStream & operator<<(const wchar_t * data);
	OutputStream & operator<<(const char * data);
};


wchar_t *ToLSTR(char* charArray);

extern OutputStream prints;


#endif