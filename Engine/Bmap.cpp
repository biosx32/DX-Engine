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

		for (int j = 0; j < width; j++) {
			unsigned char* datachar = &linedata[j * 3];
			temp_color = Color(*(2 + datachar), *(1 + datachar), *(0 + datachar));
			this->data[i * width + j] = temp_color;
		}

		if (bitmap_align_bytes) {
			fread_s(&temp, bitmap_align_bytes, 1, bitmap_align_bytes, file_read);
		}
		

	}

	fclose(file_read);

	if (rotation_correct) {
		return;
	}

	// if wrong rotaiton, then rotate
	for (int y = 0; y <= height / 2; y++) {
		for (int x = 0; x < width; x++) {
			temp_color = data[(y)* width + x];
			data[(y)* width + x] = data[((height-1)-y)* width + x];
			data[((height - 1) - y)* width + x] = temp_color;
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
	int r1, g1, b1, r2, g2, b2, temp, distance, percentage,
	const range = pow(255, 2) + pow(255, 2) + pow(255, 2); 

	temp = color.dword;
	r1 = (temp >> 16u) & 0xFFu; g1 = (temp >> 8u) & 0xFFu; b1 = (temp) & 0xFFu;

	temp = bkclr.dword;
	r2 = (temp >> 16u) & 0xFFu; g2 = (temp >> 8u) & 0xFFu; b2 = (temp) & 0xFFu;

	distance = (r2 - r1) *  (r2 - r1) + (g2 - g1) *  (g2 - g1) + (b2 - b1) *  (b2 - b1);
	percentage = distance / range;

	return percentage < tolerance;
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

	for (int yoff = 0; yoff < src->height; yoff++) {
		for (int xoff = 0; xoff < src->width; xoff++) {

			Color READ_COLOR = src->data[yoff* width + xoff];

			if (!src->IsColorTransparent(READ_COLOR)) {
				pixels.push_back(new FPixel(xoff, yoff, READ_COLOR));
			}
		}
	}

	this->Load(created);
}

VectorBitmap::~VectorBitmap()
{
	for (std::vector<FPixel*>::iterator it = pixels.begin(); it != pixels.end(); ++it)
	{
		delete *it;
	}
}

void VectorBitmap::Normalise()
{
	int min_x, min_y, max_x, max_y;

	max_x = min_x = (*this->pixels.begin())->x;
	max_y = min_y = (*this->pixels.begin())->y;


	for (std::vector<FPixel*>::iterator it = pixels.begin(); it != pixels.end(); ++it)
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

	for (std::vector<FPixel*>::iterator it = pixels.begin(); it != pixels.end(); ++it)
	{
		FPixel* current = *it;
		current->x -= offx;
		current->y -= offy;
	}

	offx = offy = 0;
}

void VectorBitmap::Load(vector<FPixel*>* src)
{
	this->pixels = vector<FPixel*>(*src);
	this->Normalise();
}



