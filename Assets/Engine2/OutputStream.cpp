#include "OutputStream.h"

SpecialCode msgbox = { 1 };
SpecialCode console = { 2 };
OutputStream DebugPrint;

OutputStream & OutputStream::operator<<(SpecialCode finish)
{
	std::string& str = stream.str(); // extends lifetime of temporary 
	std::wstring wsTmp(str.begin(), str.end());
	LPCWSTR p = wsTmp.c_str();

	if (finish.code == msgbox.code) {
		MessageBox(0, p, L"Message:", 0);
	}

	if (finish.code == console.code) {
		OutputDebugString(p);
	}
	stream = std::stringstream("", std::ios_base::app | std::ios_base::out);
	return *this;
}

OutputStream & OutputStream::operator<<(char * data)
{
	return this->operator<<((const char*) data);
}

OutputStream & OutputStream::operator<<(const char * data)
{
	const std::string temp = data;
	stream << temp;
	return *this;
}