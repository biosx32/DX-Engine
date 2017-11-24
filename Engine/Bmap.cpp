#include "Bmap.h"



BitmapData::~BitmapData() {
	if (Data) delete[] Data;
}

BitmapData::BitmapData(int width, int height)
{
	this->width = width;
	this->height = height;
	this->data_count = width*height;
	this->Data = new Color[width* height];
	
	
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



Bitmap* Bitmap::get_sprite(int loc_x, int loc_y, int WIDTH, int HEIGHT) {
	//cache
	int r, g, b, y,x;
    unsigned char * c_ptr,  *ptr;

	if (COLOR_REPLACE_MODE) {
		for (y = 0; y < height; y++) {
			for (x = 0; x < width; x++) {
				ptr = &Data[y* IMG_LINE_SIZE + x * 3];
				r = *ptr++; 
				g = *ptr++; 
				b = *ptr;
				READ_COLOR.dword = (b << 16) + (g << 8) + r;

				if (READ_COLOR.dword == transparent_color.dword);
				else if (COLOR_REPLACE_MODE & ANY_COLOR || READ_COLOR.dword == FROM_REPLACE_KEY.dword) {
					c_ptr = (unsigned char*) &TO_REPLACE_KEY.dword + 2;
					*ptr-- = *c_ptr--; //b
					*ptr-- = *c_ptr--; //g
					*ptr =   *c_ptr;   //r
				}
			}
		}
	}
	
	return new Bitmap(this, loc_x, loc_y, WIDTH, HEIGHT);
}*/

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
	this->Data = new Color[BYTES_TO_READ];

	fread_s((void*) Header, 54, sizeof(unsigned char), 54, file_read);

	this->width = *(int*)&Header[18];
	this->height = *(int*)&Header[22];


	if (this->height < 0) {
		this->height = -height;
		RotationNeeded = 1;
	}

	int IGN_COUNT = this->width % 4;

	unsigned char temp[3] = {};

	int size_line = width * 3;

	for (int i = 0; i < height; i++) {
		fread_s(&Data[i * size_line], size_line, sizeof(unsigned char), size_line, file_read);
		if (IGN_COUNT) {
			fread_s(temp, IGN_COUNT, sizeof(unsigned char), IGN_COUNT, file_read);
		}
	}

	fclose(file_read);

	Color temp_color = Color();

	if (RotationNeeded == 1) {

		for (int y = 0; y <= height / 2; y++) {
			for (int x = 0; x < width; x++) {
				
				temp_color = Data[(y)* width + x];
				Data[(y)* width + x] = Data[((height-1)-y)* width + x];
				Data[((height - 1) - y)* width + x] = temp_color;


			}

		}
		
	}

	return 0;
}


