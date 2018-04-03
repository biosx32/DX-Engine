#pragma once
#include "D3DGraphics.h"
#include <string>
#include <GdiPlus.h>
#pragma comment( lib,"gdiplus.lib" )

class Surface
{
public:
	Surface( std::wstring& filename )
	{	
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartup( &gdiplusToken,&gdiplusStartupInput,NULL );

		Gdiplus::Bitmap bitmap( filename.c_str() );
		Gdiplus::Color pixel;

		height = bitmap.GetHeight();
		width = bitmap.GetWidth();
		surface = new D3DCOLOR[ height * width ];

		for( unsigned int y = 0; y < bitmap.GetHeight(); y++ )
		{
			for( unsigned int x = 0; x < bitmap.GetWidth(); x++ )
			{
				bitmap.GetPixel( x,y,&pixel );
				surface[ x + y * bitmap.GetWidth() ] = 
					D3DCOLOR_ARGB( pixel.GetA(),pixel.GetR(),pixel.GetG(),pixel.GetB() );
			}
		}
	}
	~Surface()
	{
		delete [] surface;
	}
	virtual void Draw( int xoff,int yoff,D3DGraphics& gfx ) const
	{		
		const int yStart = max( -yoff, 0 );
		const int xStart = max( -xoff, 0 );
		const int yEnd = min( SCREENHEIGHT - yoff,height );
		const int xEnd = min( SCREENWIDTH - xoff,width );

		for( int y = yStart; y < yEnd; y++ )
		{
			for( int x = xStart; x < xEnd; x++ )
			{
				gfx.PutPixel( x + xoff,y + yoff,surface[ x + y * width ] );
			}
		}
	}

protected:
	unsigned int width;
	unsigned int height;
	D3DCOLOR* surface;
};

class KeyedSurface : public Surface
{
public:
	KeyedSurface( std::wstring& filename,D3DCOLOR key )
		:
	Surface( filename ),
	key( key )
	{}
	virtual void Draw( int xoff,int yoff,D3DGraphics& gfx ) const
	{		
		const int yStart = max( -yoff, 0 );
		const int xStart = max( -xoff, 0 );
		const int yEnd = min( SCREENHEIGHT - yoff,(int)height );
		const int xEnd = min( SCREENWIDTH - xoff,(int)width );

		for( int y = yStart; y < yEnd; y++ )
		{
			for( int x = xStart; x < xEnd; x++ )
			{
				D3DCOLOR c = surface[ x + y * width ];
				if( c != key )
				{
					gfx.PutPixel( x + xoff,y + yoff,c );
				}
			}
		}
	}

private:
	D3DCOLOR key;
};