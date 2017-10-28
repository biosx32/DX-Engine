#include "Text.h"

Text::operator<<(char* str){
	FILE* log = fopen("LOG.txt", "a");
	if (log==nullptr) return;
	fwrite(log, str);
	fclose(log);
}
