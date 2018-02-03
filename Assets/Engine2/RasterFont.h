#ifndef __TEXT_H__
#define __TEXT_H__
#include <vector>
#include "Spritesheet.h"
#include "ConfigFile.h"

class RasterFont {
public:
	Bitmap * * characters = nullptr;
	int charw;
	int charh;
	int count;
	int offset;


	bool valid = false;

	void LoadFromBMP(Bitmap* src, int wcount, int hcount, float size, Color bkclr) {
		int src_wsize = src->width / wcount;
		int src_hsize = src->height / hcount;
		charw = src_wsize * size;
		charh = src_hsize * size;

		for (int y = 0; y < hcount; y++) {
			for (int x = 0; x < wcount; x++) {

				if (y*wcount + x >= count) {
					break;
				}

				int srcX = x * src_wsize;
				int srcY = y * src_hsize;

				Bitmap* newBitmap = src->GetBitmapPart(srcX, srcY, src_wsize, src_hsize, size);

				this->characters[y*wcount + x] = newBitmap;
			}
		}
	}



	RasterFont(char* image_src_info) {

		ConfigFile config = ConfigFile(image_src_info);
		OutputStream output = OutputStream();
		if (!config.valid) {
			output << "ERROR: Could not load config: " << image_src_info << msgbox;
			return;
		}

		const int RCOUNT = 4;
		char* required[RCOUNT] = { "LOCATION", "WCOUNT", "HCOUNT", "BKCLR" };
		char* optional[] = { "DROP", "OFFSET", "LOADSIZE" };

		char header[] = "FONT_INFO";
		if (strncmp(config.name, header, strlen(header) == 0)) {
			output << "ERROR: Incorrect config."<< image_src_info << "\nConfig for: " << config.name << msgbox;
			return;
		}

		for (int i = 0; i < RCOUNT; i++) {
			if (!config.HasKey(required[i])) {
				output << "ERROR: Config missing required key: " << required[i] << msgbox;
				return;
			}
		}

		char* sdrop = "0", *soffset = "0", *sloadsize = "1";
		char* slocation = config.GetValue(required[0]);
		char* swcount = config.GetValue(required[1]);
		char* shcount = config.GetValue(required[2]);
		char* sbkclr = config.GetValue(required[3]);

		if (config.HasKey(optional[0])) {
			sdrop = config.GetValue(optional[0]);
		}
		if (config.HasKey(optional[1])) {
			soffset = config.GetValue(optional[1]);
		}
		if (config.HasKey(optional[2])) {
			sloadsize = config.GetValue(optional[2]);
		}

		int wcount;
		int hcount;
		Color bkclr;
		float loadsize;

		try {
		 
			wcount = std::stoi(swcount, 0, 10);
			hcount = std::stoi(shcount, 0, 10);
			bkclr = std::stoll(sbkclr, 0, 16);
			int drop = std::stoi(sdrop, 0, 10);
			offset = std::stoi(soffset, 0, 10);
			count = wcount * hcount - drop;
			loadsize = std::stof(sloadsize,0);
			
			char location[512] = {};
			int namelen = strlen(image_src_info);
			int lastbs = FindLastChar(image_src_info, '\\');
			int fullLen;

			if (lastbs == -1) {
				fullLen = strlen(slocation) + 2;
				strcat_s(location, ".\\");
			}
			else {
				fullLen = lastbs + strlen(slocation) + 1;
				strncpy_s(location, image_src_info, lastbs+1);
				
			}
			
			strcat_s(location, slocation);
			location[fullLen] = 0;
		

			this->characters = new Bitmap*[count];
			Bitmap* basebmp = new Bitmap(location, bkclr);
			this->LoadFromBMP(basebmp, wcount, hcount, loadsize, bkclr);
			delete basebmp;
			valid = true;

		}

		catch (const std::invalid_argument& ia) {
			output << "ERROR: Cannot convert config value from cfg (IA): " << config.name << " "<< ia.what() << msgbox;
			return;
		}
	//	catch (...) {
	//		output << "ERROR: Cannot convert config value  from cfg"<<config.name  << msgbox;
	//		return;
	//	}
	
		
	}

	Bitmap* GetCharacterRepr(char c) {
		int index = -offset + c;
		if(index>count) index=0;
		return this->characters[index];
	}
};
/*
class RasterFont {
public:
	FixedSpriteArray* character_map = nullptr;
	int translate[256] = {
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0, // 33 Control characters
	 
	  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 
	  12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 
	  22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 
	  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 
	  42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 
	  52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
	  62, 63, 64, 65, 66, 67, 68, 69, 70, 71,
	  72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 
	  82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
	  92, 93, 94, 95, 96, 97, 98, 99, 100, 101,
	  102, 103, 104, 105, 106, 107, 108, 109, 
	  110, 111, 112, 113, 114, 115, 116, 117,
	  118, 119, 120, 121, 122, 123, 124, 125, 
	  126, 127, 128, 129, 130, 131, 132, 133,
	  134, 135, 136, 137, //VISIBLE CHARACTERS


	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 //unimplemented
	};

public:
	RasterFont(char* image_src,int wcount, int hcount, float size, Color bckclr);
	Bitmap* GetCharacterRepr(char c);
};

*/
#endif
