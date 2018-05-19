#pragma once
#include <string>
#include "Func.h"
class KeyData {
public:

	char keyb[256] = {};
	char datab[256] = {};


	KeyData(char* sourceStr) {
		int len, sep_pos, datalen;
		len = strlen(sourceStr);
		if (len <= 0) {
			goto WrongData;
		}

		sep_pos = FindFirstChar(sourceStr, '=');
		
		if (sep_pos < 0 || sep_pos + 1 >= len) {
			goto WrongData;
		}
		datalen = len - (sep_pos + 1);
		strncpy_s(keyb, sourceStr, sep_pos);
		keyb[sep_pos] = 0;
		strcpy_s(datab, &sourceStr[sep_pos + 1]);
		datab[datalen] = 0;
	End:
		return;
	WrongData:
		sprintf_s(keyb, "ERROR");
		sprintf_s(datab, "NULL");

		goto End;

	}
	//compare
	/*
	char keyword[256];
	sprintf_s(keyword, "FONT_INFO");
	if (!strnicmp(linebuffer, keyword, strlen(keyword))) {
	goto End;
	}
	if (strnicmp(linebuffer, keyword, strlen(keyword))) {
	char location[256];
	int kwlen = strlen(keyword);
	int linelen = strlen(linebuffer);
	int datalen = linelen - kwlen;

	strncpy_s(location, &linebuffer[0 + kwlen], datalen);
	printf("jj");
	}
	sprintf_s(keyword, "LOCATION");*/
};