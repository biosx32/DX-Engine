#ifndef __COLORS_H__
#define __COLORS_H__

#include <d3d9.h>

typedef D3DCOLOR Color;
#define ColorARGB(a,r,g,b) D3DCOLOR_ARGB(a,r,g,b)
#define ColorRGB(r,g,b) D3DCOLOR_XRGB (r,g,b)

namespace Colors
{
	static constexpr Color White = D3DCOLOR_XRGB(255u, 255u, 255u);
	static constexpr Color Black = D3DCOLOR_XRGB(0u, 0u, 0u);
	static constexpr Color Gray = D3DCOLOR_XRGB(0x80u, 0x80u, 0x80u);
	static constexpr Color LightGray = D3DCOLOR_XRGB(0xABu, 0xABu, 0xABu);
	static constexpr Color LightLightGray = D3DCOLOR_XRGB(0xDFu, 0xDFu, 0xDFu);
	static constexpr Color Red = D3DCOLOR_XRGB(255u, 0u, 0u);
	static constexpr Color Green = D3DCOLOR_XRGB(0u, 255u, 0u);
	static constexpr Color Blue = D3DCOLOR_XRGB(0u, 0u, 255u);
	static constexpr Color Yellow = D3DCOLOR_XRGB(255u, 255u, 0u);
	static constexpr Color Cyan = D3DCOLOR_XRGB(0u, 255u, 255u);
	static constexpr Color Magenta = D3DCOLOR_XRGB(255u, 0u, 255u);
	static constexpr Color DarkGreen = D3DCOLOR_XRGB(50u, 205u, 50u);
	static constexpr Color TKEY = D3DCOLOR_XRGB(177u, 244u, 177u);
}


#endif // !__COLORS_H__
