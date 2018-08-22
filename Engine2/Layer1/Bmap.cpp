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
	

	for (int y = 0; y < n_height; y++) {
		int srcy = y / size + yoff;
		for (int x = 0; x < n_width; x++) {
			int srcx = x / size + xoff;
			*newBitmap->GetPixelPointer(x, y) = *this->GetPixelPointer(srcx, srcy);
		}

	}

	return newBitmap;

}

Bitmap * Bitmap::CreateScreenshot (D3DGraphics * gfx, V2 pos, V2 size, float m)
{
	Bitmap* part = new Bitmap (size.x, size.y, Colors::Black);
	int ymin = pos.y; if (ymin < 0) ymin = 0; if (ymin >= SCREENHEIGHT) ymin = SCREENHEIGHT - 1;
	int xmin = pos.x; if (xmin < 0) xmin = 0; if (xmin >= SCREENWIDTH) xmin = SCREENWIDTH - 1;
	int ymax = pos.y + size.y; if (ymax < 0) ymax = 0; if (ymax >= SCREENHEIGHT) ymax = SCREENHEIGHT - 1;
	int xmax = pos.x + size.x; if (xmax < 0) xmax = 0; if (xmax >= SCREENWIDTH) xmax = SCREENWIDTH - 1;


	for (int y = 0; y < ymax-ymin; y++) {
		for (int x = 0; x < xmax-xmin; x++) {
			*part->GetPixelPointer (x, y) = gfx->GetPixel (x+xmin, y+ymin);
		}

	}
	if (m!=1.0f) {
		Bitmap* ppart = part->GetBitmapPart (0, 0, size.x, size.y, m);
		delete part;
		part = ppart;
	}

	return part;
}

Color * Bitmap::GetPixelPointer(int x, int y)
{
	{ return (x >= 0 && y >= 0 && x < width && y < height) ? &this->data[y * width + x] : nullptr; }
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




