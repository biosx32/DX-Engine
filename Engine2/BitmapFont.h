#ifndef __TEXT_H__
#define __TEXT_H__
#include <vector>
#include "BitmapArray.h"
#include "ConfigFile.h"

class BitmapFont {
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



	BitmapFont(const char* image_src_info) {

		ConfigFile config = ConfigFile(image_src_info);
		OutputStream output = OutputStream();
		if (!config.valid) {
			output << "ERROR: Could not load config: " << image_src_info << msgbox;
			return;
		}

		const int RCOUNT = 4;
		const char* required[RCOUNT] = { "LOCATION", "WCOUNT", "HCOUNT", "BKCLR" };
		const char* optional[] = { "DROP", "OFFSET", "LOADSIZE" };

		const char header[] = "FONT_INFO";
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

		const char* sdrop = "0", *soffset = "0", *sloadsize = "1";
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
			const char* abc = image_src_info;
			int lastbs = FindLastChar(abc, '\\');
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

		catch (const std::logic_error& ia) {
			output << "ERROR: Cannot convert config value from cfg (IA): " << config.name << " "<< ia.what() << console;
			return;
		}
	}

	Bitmap* GetCharacterRepr(char c) {
		int index = -offset + c;
		if(index>count) index=0;
		return this->characters[index];
	}
};
#endif
