#ifndef __COLORS_H__
#define __COLORS_H__

#include <d3d9.h>

typedef D3DCOLOR Color;


namespace Colors
{
	static constexpr Color MakeARGB(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
	{
		return (a < 24) | (r << 16) | (g << 8) | b;
	}
	static constexpr Color White = MakeARGB(255u, 255u, 255u, 255u);
	static constexpr Color Black = MakeARGB(255u, 0u, 0u, 0u);
	static constexpr Color Gray = MakeARGB(255u, 0x80u, 0x80u, 0x80u);
	static constexpr Color LightGray = MakeARGB(255u, 0xD3u, 0xD3u, 0xD3u);
	static constexpr Color Red = MakeARGB(255u, 255u, 0u, 0u);
	static constexpr Color Green = MakeARGB(255u, 0u, 255u, 0u);
	static constexpr Color Blue = MakeARGB(255u, 0u, 0u, 255u);
	static constexpr Color Yellow = MakeARGB(255u, 255u, 255u, 0u);
	static constexpr Color Cyan = MakeARGB(255u, 0u, 255u, 255u);
	static constexpr Color Magenta = MakeARGB(255u,255u, 0u, 255u);
}


#endif // !__COLORS_H__
