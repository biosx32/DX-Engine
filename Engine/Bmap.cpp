#include "Bmap.h"


BitmapDS::~BitmapDS() {
	if (ptr) delete[] ptr;
	
}

BitmapDS::BitmapDS(int width, int height)
{
	this->width = width;
	this->height = height;
	this->ptr = new Color[width* height];
	///////////////////////////////////
}

Bitmap* Bitmap::GetBitmapPart(int xoff, int yoff, int width, int height) {


	Bitmap* cut = new Bitmap();
	BitmapDS* datastruct = new BitmapDS(width, height);
	cut->SetDataSource(datastruct);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			datastruct->ptr[y*width + x] = this->BitmapData->ptr[(y + yoff)* BitmapData->width + (x + xoff)];
		}
	}


	return cut;
}

int Bitmap::Load(char * FileName)
{
	
	int RotationNeeded = 1;

	FILE* file_read;
	fopen_s(&file_read, FileName, "rb");

	if (file_read == nullptr) { return ERROR_IO_READ;
	}

	int BYTES_TO_READ = File_bytes(file_read);
	if (BYTES_TO_READ < 1) { return ERROR_EMPTY_FILE;
	}

	char Header[54] = {};
	

	fread_s((void*) Header, 54, sizeof(unsigned char), 54, file_read);

	int width = *(int*)&Header[18];
	int height = *(int*)&Header[22];
	
	if (height < 0) {
		height = -height;
		RotationNeeded = 0;
	}

	this->BitmapData = new BitmapDS(width, height);
	BitmapDS* Data = this->BitmapData;

	int bitmap_align_bytes = Data->width % 4;
	int size_line = width * 3;
	unsigned char temp[3] = {};
	Color temp_color = Color();
	unsigned char * linedata = new unsigned char[size_line];
	for (int i = 0; i < height; i++) {
		fread_s((void*) linedata, size_line, 1, size_line, file_read);

		if (bitmap_align_bytes) {
			fread_s(&temp, bitmap_align_bytes, 1, bitmap_align_bytes, file_read);
		}
		
		for (int j = 0; j < Data->width; j++) {
			unsigned char* datachar = &linedata[j * 3];
			//temp_color = *(0 + datachar) << 16 | *(1 + datachar) << 8 | *(2 + datachar);
			temp_color = *(Color*) datachar;
			this->BitmapData->ptr[i * width + j] = temp_color;
		}
	}

	fclose(file_read);



	if (RotationNeeded == 1) {

		for (int y = 0; y <= height / 2; y++) {
			for (int x = 0; x < width; x++) {
				
				temp_color = Data->ptr[(y)* width + x];
				Data->ptr[(y)* width + x] = Data->ptr[((height-1)-y)* width + x];
				Data->ptr[((height - 1) - y)* width + x] = temp_color;


			}

		}
		
	}

	return 0;
}

int Bitmap::SetDataSource(BitmapDS * data)
{
	if (this->BitmapData) delete BitmapData;
	this->BitmapData = data;
	return 0;
}

int Bitmap::IsColorVisible(Color color)
{

	return 1;
}

Bitmap::Bitmap() {

}

Bitmap::~Bitmap()
{
	
}

int TransparentBitmap::IsColorVisible(Color color)
{
	if (color.dword == transparency.dword) {
		return 0;
	}
	return 1;
}
