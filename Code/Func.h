#ifndef __FUNC__H__
#define __FUNC__H__
#include "Types.h"
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <ctime>
#include <sstream>
# define M_PI           3.14159265358979323846

class Vector2;
class Vector3;

int chrcnt(char* src, char chr, int max);
float Radians(float degree);
float GetSquareDistance1(float a, float b);
float GetSquareDistance2(Vector2 v1, Vector2 v2);
float GetSquareDistance3(Vector3 v1, Vector3 v2);

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