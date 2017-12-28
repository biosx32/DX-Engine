#include "Bmap.h"


Bitmap* Bitmap::GetBitmapPart(int xoff, int yoff, int width, int height) {

	Bitmap* newBitmap = new Bitmap(width, height, this->bkclr);
	newBitmap->Reserve(width, height, this->bkclr);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Color* copy = this->GetDataPtr(x + xoff, y + yoff);
			*newBitmap->GetDataPtr(x, y) = Color(*copy);
		}
	}

	return newBitmap;
}





inline Color * Bitmap::GetDataPtr(int x, int y)
{
	if (x >= 0 && y >= 0 && x < width && y < height) {
		return data[y * width + x];
	}
	
	return nullptr;
}

Bitmap::Bitmap(char * FileName)
{
	Color temp_color;
	int width, height;
	char Header[54] = {};
	unsigned char temp[3] = {};
	int bitmap_align_bytes, size_line;
	int rotation_correct = 0;

	FILE* file_read;
	fopen_s(&file_read, FileName, "rb");

	if (file_read == nullptr) {
		prints << "ERROR: Could not load image: " << FileName << " << FILE NOT FOUND\n" << console << msgbox << clear;
		return;
	}

	int BYTES_TO_READ = File_bytes(file_read);
	if (BYTES_TO_READ < 1) {
		prints << "ERROR: Could not load image: " << FileName << " << EMPTY FILE\n" << console << msgbox << clear;
		return;
	}

	fread_s((void*)Header, 54, sizeof(unsigned char), 54, file_read);

	width = *(int*)&Header[18];
	height = *(int*)&Header[22];

	if (height < 0) {
		height = -height;
		rotation_correct = 1;
	}

	this->Reserve(width, height, 0);

	bitmap_align_bytes = width % 4;
	size_line = width * 3;

	unsigned char * linedata = new unsigned char[size_line];

	for (int i = 0; i < height; i++) {
		fread_s((void*)linedata, size_line, 1, size_line, file_read);

		for (int j = 0; j < width; j++) {
			unsigned char* datachar = &linedata[j * 3];
			temp_color = Colors::MakeARGB(255,*(2 + datachar), *(1 + datachar), *(0 + datachar));
			Color* data_destination = GetDataPtr(j, i);
			*data_destination = temp_color;
		}

		if (bitmap_align_bytes) {
			fread_s(&temp, bitmap_align_bytes, 1, bitmap_align_bytes, file_read);
		}


	}

	fclose(file_read);

	if (rotation_correct) {
		return;
	}

	// if it has wrong rotation, then rotate
	for (int y = 0; y <= height / 2; y++) {
		for (int x = 0; x < width; x++) {
			temp_color = *this->GetDataPtr(x, y);
			*this->GetDataPtr(x, y) = *GetDataPtr(x, height - y - 1);
			*this->GetDataPtr(x, height - y - 1) = temp_color;
		}
	}
}

Bitmap::Bitmap(int width, int height, Color bkclr)
{
	this->Reserve(width, height, bkclr);
}

Bitmap::~Bitmap()
{
	if (!data) return;
	for (int i = 0; i < pixelcount(); i++) {
		delete this->data[i];
	}
}

inline void Bitmap::Reserve(int width, int height, Color bkclr)
{
	this->width = width;
	this->height = height;
	this->bkclr = bkclr;
	this->data = new Color*[pixelcount()];
	for (int i = 0; i < pixelcount(); i++) {
		this->data[i] = new Color(this->bkclr);
	}
}


bool TransparentBitmap::IsColorTransparent(Color color)
{
	int r1, g1, b1, r2, g2, b2, temp;
	const int range = (int) (pow(255, 2) + pow(255, 2) + pow(255, 2)); 

	double percentage, distance;

	temp = color;
	r1 = (temp >> 16u) & 0xFFu; g1 = (temp >> 8u) & 0xFFu; b1 = (temp) & 0xFFu;

	temp = bkclr;
	r2 = (temp >> 16u) & 0xFFu; g2 = (temp >> 8u) & 0xFFu; b2 = (temp) & 0xFFu;

	distance = (r2 - r1) *  (r2 - r1) + (g2 - g1) *  (g2 - g1) + (b2 - b1) *  (b2 - b1);
	percentage = distance / range;

	return percentage < (tolerance);
}


TransparentBitmap::TransparentBitmap(Bitmap * bmp):
	Bitmap(*bmp) {}

TransparentBitmap::TransparentBitmap(char * FileName, Color transp): 
	Bitmap(FileName) {
	this->bkclr = transp; 
}

TransparentBitmap::TransparentBitmap(int width, int height, Color transp) : 
	Bitmap(width, height, transp) {}

TransparentBitmap * TransparentBitmap::GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT)
{
	TransparentBitmap* newBitmap = new TransparentBitmap(Bitmap::GetBitmapPart(xoff, yoff, WIDTH, HEIGHT));
	newBitmap->tolerance = this->tolerance;
	return newBitmap;
}





