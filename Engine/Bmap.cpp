#include "Bmap.h"


Bitmap* Bitmap::GetBitmapPart(int xoff, int yoff, int width, int height) {

	Bitmap* newBitmap = new Bitmap(width, height, this->bkclr);
	newBitmap->data = new Color[pixelcount()];

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			newBitmap->data[y*width + x] = this->data[(y + yoff)* this->width + (x + xoff)];
		}
	}

	return newBitmap;
}

void Bitmap::Load(char * FileName)
{
	Color temp_color = Color();
	int width, height;
	char Header[54] = {};
	unsigned char temp[3] = {};
	int bitmap_align_bytes, size_line;

	int rotation_correct = 0;

	FILE* file_read;
	fopen_s(&file_read, FileName, "rb");

	if (file_read == nullptr) { 
		printerr << "Could not load image: " << FileName << " << FILE NOT FOUND\n";
	}

	int BYTES_TO_READ = File_bytes(file_read);
	if (BYTES_TO_READ < 1) { 
		printerr << "Could not load image: " << FileName << " << EMPTY FILE\n";
	}

	fread_s((void*) Header, 54, sizeof(unsigned char), 54, file_read);

	width = *(int*)&Header[18];
	height = *(int*)&Header[22];
	
	if (height < 0) {
		height = -height;
		rotation_correct = 1;
	}


	Bitmap(width, height, 0x00);

	bitmap_align_bytes = width % 4;
	size_line = width * 3;

	unsigned char * linedata = new unsigned char[size_line];
	for (int i = 0; i < height; i++) {
		fread_s((void*) linedata, size_line, 1, size_line, file_read);

		if (bitmap_align_bytes) {
			fread_s(&temp, bitmap_align_bytes, 1, bitmap_align_bytes, file_read);
		}
		
		for (int j = 0; j < width; j++) {
			unsigned char* datachar = &linedata[j * 3];
			temp_color = Color(*(2 + datachar) ,*(1 + datachar) , *(0 + datachar));
			this->data[i * width + j] = temp_color;
		}
	}

	fclose(file_read);

	if (rotation_correct == 0) {

		for (int y = 0; y <= height / 2; y++) {
			for (int x = 0; x < width; x++) {
				
				temp_color = data[(y)* width + x];
				data[(y)* width + x] = data[((height-1)-y)* width + x];
				data[((height - 1) - y)* width + x] = temp_color;


			}

		}
		
	}

}



Bitmap::Bitmap(int width, int height, Color bkclr)
{
	this->width = width;
	this->height = height;
	this->bkclr = bkclr;
	this->data = new Color[pixelcount()];

	for (int i = 0; i < pixelcount(); i++) {
		this->data[i] = this->bkclr;
	}

}


bool TransparentBitmap::IsColorTransparent(Color color)
{
	int dword = color.dword;

	int r1 = (dword >> 16u) & 0xFFu;
	int g1 = (dword >> 8u) & 0xFFu;
	int b1 = dword & 0xFFu;

	dword = bkclr.dword;

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


TransparentBitmap * TransparentBitmap::GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT)
{
	TransparentBitmap* newBitmap = GetBitmapPart(xoff, yoff, WIDTH, HEIGHT);
	newBitmap->tolerance = this->tolerance;
	return newBitmap;
}



VectorBitmap::VectorBitmap(TransparentBitmap * src)
{
	vector<FPixel*>* created = new vector<FPixel*>;

	int width = src->width;
	int height = src->height;

	for (int yoff = 0; yoff < height; yoff++) {
		for (int xoff = 0; xoff < width; xoff++) {

			Color READ_COLOR = src->data[yoff* width + xoff];

			if (!src->IsColorTransparent(READ_COLOR)) {
				pixels->push_back(new FPixel(xoff, yoff, READ_COLOR));
			}
		}
	}

	this->Load(created);
}

VectorBitmap::~VectorBitmap()
{
	for (std::vector<FPixel*>::iterator it = pixels->begin(); it != pixels->end(); ++it)
	{
		delete *it;
	}
	delete this->pixels;
	pixels = nullptr;
}

void VectorBitmap::Normalise()
{
	int min_x, min_y, max_x, max_y;

	max_x = min_x = (*this->pixels->begin())->x;
	max_y = min_y = (*this->pixels->begin())->y;


	for (std::vector<FPixel*>::iterator it = pixels->begin(); it != pixels->end(); ++it)
	{
		FPixel* current = *it;
		if (current->x < min_x) {
			min_x = current->x;
		}
		else if (current->x > max_x) {
			max_x = current->x;
		}

		if (current->y < min_y) {
			min_y = current->y;
		}

		else if (current->y > max_y) {
			max_y = current->y;
		}
	}

	this->width = max_x - min_x;
	this->height = max_y - min_y;

	int offx = min_x;
	int offy = min_y;

	for (std::vector<FPixel*>::iterator it = pixels->begin(); it != pixels->end(); ++it)
	{
		FPixel* current = *it;
		current->x -= offx;
		current->y -= offy;
	}

	offx = offy = 0;
}

void VectorBitmap::Load(vector<FPixel*>* src)
{
	this->pixels = src;
	this->Normalise();
}



