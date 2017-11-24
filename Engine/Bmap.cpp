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

/*
Bitmap::Bitmap(Bitmap* source, int loc_x, int loc_y, int width, int height): Bitmap(*source) {
	

	bool _IMG_TOP_DOWN = false;
	this->width = width;
	this->height = height;
	this->IMG_LINE_SIZE = width* COLOR_BSIZE;

	this->IMG_DATA_SIZE = IMG_LINE_SIZE * height;
	
	//cache
	int LN_W, x,y,l_x,l_y;

	for (int i = 0; i < IMG_DATA_SIZE; i++) {
		LN_W = (width * COLOR_BSIZE);
		x = i % LN_W;
		y = i / LN_W;

		l_x = x + loc_x * source->COLOR_BSIZE;
		l_y = y * source->IMG_LINE_SIZE + loc_y * source->IMG_LINE_SIZE;

		this->Data[y * LN_W + x] = source->Data[l_y + l_x];

	}

	this->IMG_LOADED = true;
}


*/
BitmapDS* Bitmap::CutSprite(int xoff, int yoff, int width, int height) {


	BitmapDS* cut = new BitmapDS(width, height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			cut->ptr[y*width + x] = this->BitmapData->ptr[(y + yoff)* this->BitmapData->width + (x + xoff)];
		}
	}


	return cut;
}

int Bitmap::Load(char * FileName)
{
	
	int RotationNeeded = 0;

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
		RotationNeeded = 1;
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

Bitmap::Bitmap() {

}
