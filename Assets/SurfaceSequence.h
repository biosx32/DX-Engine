#pragma once
#include "Surface.h"
#include <string>
#include <sstream>
#include <iomanip>

class SurfaceSequence
{
public:
	SurfaceSequence( std::wstring basename,unsigned int nSurfaces,unsigned int nHoldFrames,D3DCOLOR key = D3DCOLOR_XRGB( 255,255,255 ) )
		:
	nSurfaces( nSurfaces ),
	nHoldFrames( nHoldFrames ),
	iCurSurface( 0 ),
	curHoldCount( 0 )
	{
		surfaces = new KeyedSurface*[ nSurfaces ];
		for( int index = 0; index < nSurfaces; index++ )
		{
			std::wstringstream s;
			s << std::setw( 4 ) << std::setfill( L'0' ) << index;
			surfaces[ index ] = new KeyedSurface( basename + s.str() + std::wstring( L".bmp" ),key );
		}
	}
	~SurfaceSequence()
	{
		for( int index = 0; index < nSurfaces; index++ )
		{
			delete surfaces[ index ];
		}

		delete [] surfaces;
	}
	void Draw( int x,int y,D3DGraphics& gfx ) const
	{
		surfaces[ iCurSurface ]->Draw( x,y,gfx );
	}
	void Advance()
	{
		curHoldCount++;
		if( curHoldCount >= nHoldFrames )
		{
			iCurSurface++;
			iCurSurface %= nSurfaces;
			curHoldCount = 0;
		}
	}

private:
	KeyedSurface** surfaces;
	const unsigned int nSurfaces;
	const unsigned int nHoldFrames;
	unsigned int iCurSurface;
	unsigned int curHoldCount;
};