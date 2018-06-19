#include "Static.h"
#include "Bmap.h"



Bitmap* Bitmap::GetBitmapPart(int xoff, int yoff, int width, int height) {
	return GetBitmapPart(xoff, yoff, width, height, 1);
}

Bitmap * Bitmap::GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT, float size)
{
	int n_width = WIDTH * size;
	int n_height = HEIGHT * size;
	Bitmap* newBitmap = new Bitmap(n_width, n_height, this->bckclr);
	newBitmap->keying_enabled = this->keying_enabled;
	newBitmap->tolerance = this->tolerance;
	

	for (int y = 0; y < n_height; y++) {
		int srcy = y / size + yoff;
		for (int x = 0; x < n_width; x++) {
			int srcx = x / size + xoff;
			*newBitmap->GetPixelPointer(x, y) = *this->GetPixelPointer(srcx, srcy);
		}

	}

	return newBitmap;

}

Color * Bitmap::GetPixelPointer(int x, int y)
{
	{ return (x >= 0 && y >= 0 && x < width && y < height) ? &this->data[y * width + x] : nullptr; }
}

float Bitmap::GetBackgroundSimilarity(Color tstclr)
{
	int r1 = (tstclr >> 16u) & 0xFFu; 
	int g1 = (tstclr >>  8u) & 0xFFu; 
	int b1 = (tstclr >>  0u) & 0xFFu;
	int r2 = (bckclr >> 16u) & 0xFFu; 
	int g2 = (bckclr >>  8u) & 0xFFu; 
	int b2 = (bckclr >>  0u) & 0xFFu;

	float distance = pow(r2 - r1, 2) + pow(g2 - g1, 2) + pow(b2 - b1, 2);
	//float percentage = distance / ( 3*(256*256));
	return distance / (3 * (256 * 256));
	
}

Bitmap::Bitmap(const char * FileName)
{
	Color temp_color;
	int width, height;
	char Header[54] = {};
	unsigned char temp[3] = {};
	int bitmap_align_bytes, size_line;
	int rotation_correct = 0;
	unsigned char * linedata;

	FILE* file_read;
	fopen_s(&file_read, FileName, "rb");

	OutputStream output = OutputStream();

	if (file_read == nullptr) {
		output << "ERROR: Could not load image: " << FileName << " FILE NOT FOUND\n" << msgbox;
		return;
	}

	int BYTES_TO_READ = File_bytes(file_read);
	if (BYTES_TO_READ < 1) {
		output << "ERROR: Could not load image: " << FileName << " EMPTY FILE\n" << msgbox;
		goto End;
	}

	fread_s((void*)Header, 54, sizeof(unsigned char), 54, file_read);

	width = *(int*)&Header[18];
	height = *(int*)&Header[22];

	if (height < 0) {
		height = -height;
		rotation_correct = 1;
	}

	this->ReserveMemory(width, height, 0);

	bitmap_align_bytes = width % 4;
	size_line = width * 3;

	linedata = new unsigned char[size_line];

	for (int i = 0; i < height; i++) {
		fread_s((void*)linedata, size_line, 1, size_line, file_read);

		for (int j = 0; j < width; j++) {
			unsigned char* datachar = &linedata[j * 3];
			temp_color = ColorARGB(255,*(2 + datachar), *(1 + datachar), *(0 + datachar));
			Color* data_destination = GetPixelPointer(j, i);
			*data_destination = temp_color;
		}

		if (bitmap_align_bytes) {
			fread_s(&temp, bitmap_align_bytes, 1, bitmap_align_bytes, file_read);
		}


	}

	
	if (!rotation_correct) {
		for (int y = 0; y <= height / 2; y++) {
			for (int x = 0; x < width; x++) {
				temp_color = *this->GetPixelPointer(x, y);
				*this->GetPixelPointer(x, y) = *GetPixelPointer(x, height - y - 1);
				*this->GetPixelPointer(x, height - y - 1) = temp_color;
			}
		}
	}

End:
	fclose(file_read);

}



Bitmap::Bitmap(int width, int height, Color bkclr)
{
	this->ReserveMemory(width, height, bkclr);
}

Bitmap::~Bitmap()
{
	if (!data) return;
	delete[] data;
}

void Bitmap::ReserveMemory(int width, int height, Color bkclr)
{
	this->width = width;
	this->height = height;
	this->bckclr = bkclr;
	this->data = new Color[pixelcount()];

	for (int i = 0; i < pixelcount(); i++) {
		data[i] = bkclr;
	}
}




