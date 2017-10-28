#include "Bmap.h"


Bitmap::~Bitmap() {
	delete[] Data;
	delete[] Header;
}

Bitmap::Bitmap(char* FileName) {
	this->IMG_LOADED = false; 
	this->IMG_TOP_DOWN = false;
	this->COLOR_REPLACE_MODE = NO_COLOR;

	FILE* rBMP;
	fopen_s(&rBMP, FileName, "rb");

	if (rBMP == nullptr) {
		goto IOError;
	}

	int BYTES_TO_READ = Get_image_bytes(rBMP, +54);

	if (BYTES_TO_READ < 1) {
		goto Exit;
	}

	this->Header = new unsigned char[54];
	this->Data = new unsigned char[BYTES_TO_READ];

	fread_s((void*)Header, 54, sizeof(unsigned char), 54, rBMP);

	this->IMG_WIDTH = *(int*)&Header[18];
	this->IMG_HEIGHT = *(int*)&Header[22];

	if (this->IMG_HEIGHT < 0) {
		this->IMG_TOP_DOWN = true;
		this->IMG_HEIGHT = -IMG_HEIGHT;
	}

	this->IMG_LINE_SIZE = IMG_WIDTH * COLOR_BSIZE;
	this->IMG_DATA_SIZE = IMG_LINE_SIZE * IMG_HEIGHT;

	int IGN_COUNT = IMG_WIDTH % 4;

	unsigned char temp[3];
	
	for (int i = 0; i < IMG_HEIGHT; i++) {
		fread_s(&Data[i * IMG_LINE_SIZE], IMG_LINE_SIZE, sizeof(unsigned char), IMG_LINE_SIZE, rBMP);
		if (IGN_COUNT) {
			fread_s(temp, IGN_COUNT, sizeof(unsigned char), IGN_COUNT, rBMP);
		}

	}

	fclose(rBMP);

	//cache
	unsigned char *a;
	unsigned char *b;
	unsigned char c;


	if (!IMG_TOP_DOWN) {
		for (int i = 0; i < IMG_DATA_SIZE / 2; i++) {
			int x = i % IMG_LINE_SIZE;
			int y = i / IMG_LINE_SIZE;

			a = &Data[y * IMG_LINE_SIZE + x];
			b = &Data[((IMG_HEIGHT - 1 - y) * IMG_LINE_SIZE) + x];
			c = *a;
			*a = *b;
			*b = c;

		}
	}

	IMG_LOADED = true;
	goto Exit;

IOError:
	//debug
	{}
Exit:
	{}
}
Bitmap::Bitmap(Bitmap* source, int loc_x, int loc_y, int width, int height) {
	this->Header = new unsigned char[0];
	this->Data = new unsigned char[IMG_DATA_SIZE];
	
	this->IMG_LOADED = false; 
	this->IMG_TOP_DOWN = false;
	this->IMG_WIDTH = width;
	this->IMG_HEIGHT = height;
	this->IMG_LINE_SIZE = IMG_WIDTH* COLOR_BSIZE;
	this->IMG_DATA_SIZE = IMG_LINE_SIZE * IMG_HEIGHT;
	
	//cache
	int LN_W, x,y,l_x,l_y;

	for (int i = 0; i < IMG_DATA_SIZE; i++) {
		LN_W = (IMG_WIDTH * COLOR_BSIZE);
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
    unsigned char* c_ptr, ptr;

	if (COLOR_REPLACE_MODE) {
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				ptr = &Data[y* IMG_LINE_SIZE + x * 3];
				r = *ptr++; 
				g = *ptr++; 
				b = *ptr;
				READ_COLOR.dword = (b << 16) + (g << 8) + r;

				if (READ_COLOR.dword == TRANSPARENCY_KEY.dword);
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
}

int Bitmap::Get_image_bytes(FILE* p_file, int offset)
{
	int RESUME = ftell(p_file);
	fseek(p_file, 0, SEEK_END); //seek end
	int size = ftell(p_file) - offset; //get size
	fseek(p_file, 0 + RESUME, SEEK_SET);
	return size;
}
