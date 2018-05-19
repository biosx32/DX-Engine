#pragma once
#include <sstream>
#include <Windows.h>

struct SpecialCode { int code; };
extern SpecialCode msgbox ;
extern SpecialCode console;

class OutputStream {
protected:
	std::stringstream stream = std::stringstream("", std::ios_base::app | std::ios_base::out);
public:
	OutputStream();

	OutputStream & operator<<(int data);
	OutputStream & operator<<(double data);
	OutputStream & operator<<(SpecialCode finish);
	OutputStream & operator<<(char * data);
	OutputStream & operator<<(const char * data);
};
