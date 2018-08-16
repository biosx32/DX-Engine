#pragma once
#include "Layer0.h"
using std::vector;
class ConfigFile {

public:
	char name[256] = {};
	bool valid = false;
	vector<KeyData> configvalues;
	ConfigFile(const char* config_file) {
		FILE* fread;
		fopen_s(&fread, config_file, "rb");
		OutputStream output = OutputStream();

		int Remaining, toRead;
		char linebuffer[256] = {};

		if (fread == nullptr) {
			output << "ERROR: Could not load config: " << config_file << msgbox;
			return;
		}

		if (!HasNextLn(fread)) {
			goto WrongConfig;
		}

		toRead = GetNextLineOffset(fread);
		if (toRead < 1) {
			goto WrongConfig;
		}

	
		{   //read name
			fread_s(linebuffer, 256, 1, toRead, fread);
			strncpy_s(name, linebuffer, toRead);
			name[toRead] = 0;
			char t[1];
			fread_s(t, 1, 1, 1, fread);
			if (t[0] == '\r') {
				fread_s(t, 1, 1, 1, fread);
			}
		}
		Remaining = File_to_end(fread);

		while (Remaining > 0) {

			if (HasNextLn(fread)) {
				int LineCount = GetNextLineOffset(fread);

				if (LineCount > 255) {
					output << "Line too long, config info" << msgbox;
					goto End;
				}

				fread_s(linebuffer, 255, 1, LineCount, fread);
				char t[1];
				fread_s(t, 1, 1, 1, fread);
				if (t[0] == '\r') {
					fread_s(t, 1, 1, 1, fread);
				}
				linebuffer[LineCount] = 0;
			}

			else {
				if (Remaining > 255) {
					output << "Line too long, font info" << msgbox;
					goto End;
				}
				fread_s(linebuffer, 255, 1, Remaining, fread);
				linebuffer[Remaining] = 0;
			}

			KeyData j = KeyData(linebuffer);
			configvalues.push_back(j);

			Remaining = File_to_end(fread);
		}

		valid = true;
	End:
		fclose(fread);
		return;

	WrongConfig:
		output << "ERROR: Wrong config file: " << config_file << msgbox;
		goto End;

	}

	bool HasKey(const char* key) {
		int len = strlen(key);
		if (len > 0) {
			for (vector<KeyData>::iterator it = configvalues.begin(); it != configvalues.end(); ++it) {
				char* cmp = (*it).keyb;
				int kwlen = strlen(cmp);
				if (strncmp(cmp, key,kwlen) == 0) {
					return true;
				}

			}
		}
		return false;
	}

	char* GetValue(const char* key) {

		for (vector<KeyData>::iterator it = configvalues.begin(); it != configvalues.end(); ++it) {
			char* cmp = (*it).keyb;
			int kwlen = strlen(cmp);
			if (strncmp(cmp, key, kwlen) == 0) {
				return (*it).datab;
			}

		}

		return nullptr;
	}


};