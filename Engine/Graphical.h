#ifndef __GRAPHICAL_H__
#define __GRAPHICAL_H__
#include "Interface.h"
#include "Colors.h"

class Interface;

class Draw {
public:
	Interface*  out;

	void setOutInterface(Interface* out);

	void FastVLine( int x0, int y0, int width);
	void FastHLine( int x0, int y0, int height);
	void circle( int x0, int y0, int radius);
	void line( int x0, int y0, int width, int height);
	void rectangle( int x0, int y0, int width, int height);
};


#endif 
