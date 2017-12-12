#include "Bmap.h"


BitmapDS::~BitmapDS() {
	delete[] data;
	this->data = nullptr;
	
}

BitmapDS::BitmapDS(int width, int height)
{
	this->width = width;
	this->height = height;
	this->pixelcount = width * height;
	this->data = new Color[pixelcount];
}

Bitmap* Bitmap::GetBitmapPart(int xoff, int yoff, int width, int height) {

	Bitmap* newBitmap = new Bitmap();
	BitmapDS* newdatagroup = new BitmapDS(width, height);
	newBitmap->datagroup = newdatagroup;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			newdatagroup->data[y*width + x] = this->datagroup->data[(y + yoff)* datagroup->width + (x + xoff)];
		}
	}

	return newBitmap;
}

int Bitmap::Load(char * FileName)
{
	#define ERROR_IO_READ -1
	#define ERROR_EMPTY_FILE -2

	int rotation_correct = 0;

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
		rotation_correct = 1;
	}

	this->datagroup = new BitmapDS(width, height);
	BitmapDS* Data = this->datagroup;

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
			this->datagroup->data[i * width + j] = temp_color;
		}
	}

	fclose(file_read);



	if (rotation_correct == 0) {

		for (int y = 0; y <= height / 2; y++) {
			for (int x = 0; x < width; x++) {
				
				temp_color = Data->data[(y)* width + x];
				Data->data[(y)* width + x] = Data->data[((height-1)-y)* width + x];
				Data->data[((height - 1) - y)* width + x] = temp_color;


			}

		}
		
	}

	return 0;
}






Bitmap::Bitmap() {
	
}

Bitmap::Bitmap(char * FileName)
{
	this->Load(FileName);
}

Bitmap::Bitmap(int width, int height)
{
	this->datagroup = new BitmapDS(width, height);
}


Bitmap::~Bitmap()
{
	delete this->datagroup;
	this->datagroup = nullptr;
}



bool TransparentBitmap::IsColorTransparent(Color color)
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



TransparentBitmap::TransparentBitmap(int width, int height, Color transparency): Bitmap(width, height)
{
	this->transparency = transparency.dword;
	for (int i = 0; i < this->datagroup->pixelcount; i++) {
		this->datagroup->data[i] = this->transparency;
	}
}

TransparentBitmap * TransparentBitmap::GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT)
{
	Bitmap* newBitmap = this->Bitmap::GetBitmapPart(xoff, yoff, WIDTH, HEIGHT);
	TransparentBitmap* newBitmap_T = new TransparentBitmap(newBitmap);
	newBitmap_T->tolerance = this->tolerance;
	newBitmap_T->transparency = this->transparency;
	return newBitmap_T;
}

FPixel::FPixel(int x, int y, Color c)
{
	this->x = x; this->y = y; this->color = c;
}


VectorBitmapDS::VectorBitmapDS(int width, int height)
{
	this->width = width;
	this->height = height;
	this->pixels = new std::vector<FPixel*>;
}

VectorBitmapDS::~VectorBitmapDS()
{
	for (std::vector<FPixel*>::iterator it = pixels->begin(); it != pixels->end(); ++it)
	{
		delete *it;
	}
	delete this->pixels;
	pixels = nullptr;
}

int VectorBitmapDS::Get_pixelcount()
{
	return this->pixels->size();
}


FFPixel::FFPixel(int x, int y, Color c, int state): FPixel(x,y,c)
{
	this->state = state;
}

VectorBitmap::~VectorBitmap()
{
	delete datagroup;
	datagroup = nullptr;
}

VectorBitmap::VectorBitmap()
{
}

VectorBitmap::VectorBitmap(std::vector<FPixel*>* src)
{
	this->Load(src);
}

void VectorBitmap::Load(std::vector<FPixel*>* src)
{

	delete this->datagroup;


}
