#ifndef __OUTPUT_STREAM_H_322__
#define __OUTPUT_STREAM_H_322__
#include <sstream>
#include <Windows.h>

struct SpecialCode { int code; };
extern SpecialCode msgbox ;
extern SpecialCode console;



class OutputStream {
protected:
	std::stringstream stream = std::stringstream("", std::ios_base::app | std::ios_base::out);;
public:
	OutputStream() {}

	OutputStream & OutputStream::operator<<(int data) { stream << data; return *this; }
	OutputStream & OutputStream::operator<<(double data) { stream << data; return *this; }
	OutputStream & OutputStream::operator<<(SpecialCode finish);
	OutputStream & OutputStream::operator<<(char * data);
	OutputStream & OutputStream::operator<<(const char * data);
};

extern OutputStream DebugPrint;

#endif // !__OUTPUT_STREAM_H_322__
