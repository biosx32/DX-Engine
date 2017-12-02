#include "Bmap.h"


BitmapDS::~BitmapDS() {
	delete[] ptr;
	this->ptr = nullptr;
	
}

BitmapDS::BitmapDS(int width, int height)
{
	this->width = width;
	this->height = height;
	this->ptr = new Color[width* height];
	///////////////////////////////////
}

Bitmap* Bitmap::GetBitmapPart(int xoff, int yoff, int width, int height) {

	Bitmap* cut = this->GetTypeInstance();
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

	if (file_read == nullptr) { 
		printerr << "Could not load image: " << FileName << " << FILE NOT FOUND\n";
		return ERROR_IO_READ;
	}

	int BYTES_TO_READ = File_bytes(file_read);
	if (BYTES_TO_READ < 1) { 
		printerr << "Could not load image: " << FileName << " << EMPTY FILE\n";
		return ERROR_EMPTY_FILE;
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
			temp_color = Color(*(2 + datachar) ,*(1 + datachar) , *(0 + datachar));
			//temp_color = *(Color*) datachar;
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

int Bitmap::SetDataSource(BitmapDS * ptr)
{
	delete BitmapData;
	this->BitmapData = ptr;
	return 0;
}

int Bitmap::IsColorTransparent(Color color)
{
	
	return 0;
}

int Bitmap::GetBitmapType()
{
	return BitmapType::normal;
}

Bitmap * Bitmap::GetTypeInstance()
{
	return new Bitmap();
}

Bitmap::Bitmap() {
	
}

Bitmap::Bitmap(char * FileName)
{
	this->Load(FileName);
}

Bitmap::Bitmap(int width, int height)
{
	this->BitmapData = new BitmapDS(width, height);
}


Bitmap::~Bitmap()
{
	delete this->BitmapData;
	this->BitmapData = nullptr;
}



int TransparentBitmap::IsColorTransparent(Color color)
{
	int dword = color.dword;

	int r1 = (dword >> 16u) & 0xFFu;
	int g1 = (dword >> 8u) & 0xFFu;
	int b1 = dword & 0xFFu;

	dword = transparency.dword;

	int r2 = (dword >> 16u) & 0xFFu;
	int g2 = (dword >> 8u) & 0xFFu;
	int b2 = dword & 0xFFu;

	double distance = (r2 - r1) *  (r2 - r1) + (g2 - g1) *  (g2 - g1) + (b2 - b1) *  (b2 - b1);
	double const range = pow(255, 2) + pow(255, 2) + pow(255, 2);
	double percentage = distance / range;

	if (percentage < tolerance) {
		return 1;
	}
	return 0;
}

int TransparentBitmap::GetBitmapType()
{
	return BitmapType::transparent;
}

Bitmap * TransparentBitmap::GetTypeInstance()
{
	return new TransparentBitmap();
}

Bitmap * TransparentBitmap::GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT)
{
	TransparentBitmap* cut = (TransparentBitmap*) Bitmap::GetBitmapPart(xoff, yoff, WIDTH, HEIGHT);
	cut->tolerance = this->tolerance;
	cut->transparency = this->transparency;
	return (Bitmap*) cut;
}



