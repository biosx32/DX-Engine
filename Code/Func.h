#ifndef __FUNC__H__
#define __FUNC__H__
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <ctime>
#include <sstream>


int chrcnt(char* src, char chr, int max);

float GetDistance1(float a, float b);

float GetDistance1_Square(float a, float b);

float distance_compare(float x0, float y0, float x1, float y1);

float distance_real(float x0, float y0, float x1, float y1);

int maximum(float x, float y, float z);
int minimum(float x, float y, float z);
void SwapNumbers(int* a, int*b);


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