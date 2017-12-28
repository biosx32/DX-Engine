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
	OutputStream() {
		stream = std::stringstream("", std::ios_base::app | std::ios_base::out);
	}
	
	inline OutputStream & OutputStream::operator<<(int data) { stream << data; return *this;}
	inline OutputStream & OutputStream::operator<<(double data) { stream << data; return *this;}

	OutputStream & OutputStream::operator<<(SpecialCode finish);
	OutputStream & operator<<(char * data);
};


wchar_t *ToLSTR(char* charArray);

extern OutputStream prints;


#endif