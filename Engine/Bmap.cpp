#include "Bmap.h"


Bitmap::~Bitmap() {
	delete[] Data;
	delete[] Header;
}
Bitmap::Bitmap(char* const FileName) {
	IMG_LOADED = false; 
	IMG_TOP_DOWN = false;
	COLOR_REPLACE_MODE = NO_COLOR;

	FILE* rBMP;
	fopen_s(&rBMP, FileName, "rb");

	if (rBMP == nullptr) {
		goto IOError;
	}

	const int BYTES_TO_READ = Get_image_bytes(rBMP, +54);

	if (BYTES_TO_READ < 1) {
		goto Exit;
	}

	this->Header = new unsigned char[54];
	this->Data = new unsigned char[BYTES_TO_READ];

	fread_s((void*)Header, 54, sizeof(unsigned char), 54, rBMP);

	this->IMG_WIDTH = *(int*)&Header[18];
	this->IMG_HEIGHT = *(int*)&Header[22];

	if (IMG_HEIGHT < 0) {
		IMG_TOP_DOWN = true;
		IMG_HEIGHT = -IMG_HEIGHT;
	}

	this->IMG_LINE_DATA = IMG_WIDTH * COLOR_BSIZE;
	this->IMG_DATA_SIZE = IMG_LINE_DATA * IMG_HEIGHT;

	int IGN_COUNT = IMG_WIDTH % 4;

	unsigned char temp[3];
	
	for (int i = 0; i < IMG_HEIGHT; i++) {
		fread_s(&Data[i * IMG_LINE_DATA], IMG_LINE_DATA, sizeof(unsigned char), IMG_LINE_DATA, rBMP);
		if (IGN_COUNT) {
			fread_s(temp, IGN_COUNT, sizeof(unsigned char), IGN_COUNT, rBMP);
		}

	}

	fclose(rBMP);


	if (!IMG_TOP_DOWN) {
		for (int i = 0; i < IMG_DATA_SIZE / 2; i++) {
			int x = i % IMG_LINE_DATA;
			int y = i / IMG_LINE_DATA;

			unsigned char* a = &Data[y * IMG_LINE_DATA + x];
			unsigned char* b = &Data[((IMG_HEIGHT - 1 - y) * IMG_LINE_DATA) + x];
			unsigned char c = *a;
			*a = *b;
			*b = c;

		}
	}




	IMG_LOADED = true;
	IMG_TOP_DOWN = true;
	goto Exit;

IOError:
	//debug
	goto Exit;
Exit:
	{}
}


Bitmap::Bitmap(Bitmap* source, int fromX, int fromY, int width, int height) {
	this->IMG_LOADED = false;
	this->IMG_TOP_DOWN = true;
	this->IMG_PIXEL_COUNT = width * height;
	this->IMG_DATA_SIZE = IMG_PIXEL_COUNT * COLOR_BSIZE;
	
	this->Header = new unsigned char[0];
	this->Data = new unsigned char[IMG_DATA_SIZE];

	this->IMG_WIDTH = width;
	this->IMG_HEIGHT = height;
	this->IMG_LINE_DATA = width * COLOR_BSIZE;


	int xsrc, ysrc, xdest, ydest;

	for (int i = 0; i < source->IMG_DATA_SIZE; i++) {
		xsrc = i % source->IMG_LINE_DATA + fromX * source->COLOR_BSIZE;
		ysrc = i / source->IMG_LINE_DATA + fromY * source->IMG_LINE_DATA;

		xdest = i % source->IMG_LINE_DATA;
		ydest = i / source->IMG_LINE_DATA;

		this->Data[ydest * this->IMG_LINE_DATA + xdest] = source->Data[ysrc * source->IMG_DATA_SIZE + xsrc];

	}

	IMG_LOADED = true;
}



Bitmap* Bitmap::get_sprite(int loc_x, int loc_y, int WIDTH, int HEIGHT) {
	int r, g, b;
	unsigned char* ptr;
    char* c_ptr = (char*) &TO_REPLACE_KEY.dword;

	if (COLOR_REPLACE_MODE) {
		for (int i = 0; i < this->IMG_PIXEL_COUNT; i++) {
			ptr = &this->Data[i * 3];

			b = *ptr; g = *(ptr + 1); r = *(ptr + 2);

			READ_COLOR.dword = b + (g << 8) + (r << 16);

			if (READ_COLOR.dword == TRANSPARENCY_KEY.dword);
			else if (COLOR_REPLACE_MODE & ANY_COLOR || READ_COLOR.dword == FROM_REPLACE_KEY.dword) {
				*ptr = *c_ptr;
				*(ptr + 1) = *(c_ptr + 1);
				*(ptr + 2) = *(c_ptr + 2);

				
			}
		}


		for (int i = 0; i < this->IMG_DATA_SIZE; i++) {
			int x = i % this->IMG_LINE_DATA;
			int y = i / this->IMG_LINE_DATA;

			ptr = &Data[y* IMG_LINE_DATA + x * 3];
			r = *ptr++; g = *ptr++; b = *ptr;
			READ_COLOR.dword = r + (g << 8)  + (b << 16);

			
		}
		
	}
	
	return new Bitmap(this, loc_x, loc_y, WIDTH, HEIGHT);
}

int Bitmap::Get_image_bytes(FILE* p_file, int offset)
{
	const int RESUME = ftell(p_file);
	fseek(p_file, 0, SEEK_END); //seek end
	int size = ftell(p_file) - offset; //get size
	fseek(p_file, 0 + RESUME, SEEK_SET);
	return size;
}
