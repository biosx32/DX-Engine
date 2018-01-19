#include "Func.h"
SpecialCode msgbox = 1;
SpecialCode console = 2;
SpecialCode clear = 3;

OutputStream prints;

int fc=0;
char buff[64];


int chrcnt(char* src, char chr, int max) {
	int counter = 0;
	for (int i = 0; i < max; i++) {
		char* j = &src[i];
		if (*j == chr) counter++;
	}

	return counter;
}
float Radians(float degree){
	float deg = (int)degree % 360 + (degree - (int)degree);
	return M_PI * deg / 180;
}
clock_t begin = 0;




double elapsed_secs = 1000;

float GetSquareDistance1(float a, float b) {
	return a >= b ? (a - b)*(a-b) : (b - a)*(b-a);
}

float GetSquareDistance2(Vector2 v1, Vector2 v2) {

	return GetSquareDistance1(v2.x,v1.x) + GetSquareDistance1(v2.y, v1.y);
}
float GetSquareDistance3(Vector3 v1, Vector3 v2) {

	return GetSquareDistance2(v1,v2) + GetSquareDistance1(v2.z,v1.z);
}




int maximum(float x, float y, float z) {
	return (x > y ? (x > z ? x : z) : (y > z ? y : z));
}

int minimum(float x, float y, float z) {
	return (x < y ? (x < z ? x : z) : (y < z ? y : z));
}

void SwapNumbers(int * x1, int * x0)
{
	if ( 1) {
		int t = *x1;
		*x1 = *x0;
		*x0 = t;
	}
}

char* const getFrameNumber() {

	fc++;
	if (fc > 60) fc = 1;

	if (fc % 15 == 0) {
		clock_t end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		begin = end;
	    
	}

	double FPS = 15 / elapsed_secs;



	sprintf_s(buff, "Frame: %02d\nEPS: %1.3f\nFPS: %2.3f", fc,elapsed_secs, FPS);
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
		std::string& str = stream.str(); // extends lifetime of temporary 
		std::wstring wsTmp(str.begin(), str.end());
		
		LPCWSTR p = wsTmp.c_str();
		MessageBox(0, p, L"Message:", 0);

	}

	if (finish == console) {
		std::string& str = stream.str(); // extends lifetime of temporary 
		std::wstring wsTmp(str.begin(), str.end());

		LPCWSTR p = wsTmp.c_str();
		OutputDebugString(p);
	}

	if (finish == clear) {
		stream = std::stringstream("", std::ios_base::app | std::ios_base::out);
	}

	return *this;
}

OutputStream & OutputStream::operator<<( char * data)
{
	const std::string temp = data;
	stream << temp;
	return *this;
}

