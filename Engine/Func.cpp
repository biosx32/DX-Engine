#include "Func.h"
SpecialCode msgbox = 1;
SpecialCode console = 2;
SpecialCode clear = 3;

OutputStream prints;

int fc=0;
char buff[64];



clock_t begin = 0;




double elapsed_secs = 1000;

char* const getFrameNumber() {

	fc++;
	if (fc > 60) fc = 1;

	if (fc % 15 == 0) {
		clock_t end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		begin = end;
	    
	}

	double FPS = 15 / elapsed_secs;



	sprintf_s(buff, "Frame: %02d, EPS: %1.3f, FPS %2.3f", fc,elapsed_secs, FPS);
	return buff;
}

int File_bytes(FILE* p_file)
{
	int RESUME = ftell(p_file);
	fseek(p_file, 0, SEEK_END); //seek end
	int size = ftell(p_file); //get size
	fseek(p_file, 0 + RESUME, SEEK_SET);
	return size;
}

wchar_t *ToLSTR(char* charArray)
{
	wchar_t *wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}



OutputStream & OutputStream::operator<<(SpecialCode finish)
{
	if (finish == msgbox) {
		std::wstring& wstr = stream.str(); // extends lifetime of temporary 
		LPCWSTR p = wstr.c_str();
		MessageBox(0, p, L"Message:", 0);

	}

	if (finish == console) {
		LPCWSTR str = stream.str().c_str();
		OutputDebugStringW(str);
	}

	if (finish == clear) {
		stream = wstringstream();
	}

	return *this;
}

OutputStream & OutputStream::operator<<(const char * data)
{
	stream << data;
	return *this;
}
