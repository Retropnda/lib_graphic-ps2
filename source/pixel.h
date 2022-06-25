#ifndef PIXEL_H_
#define PIXEL_H_

#include <SDL/SDL.h>


// flag RGB
#if USE_PS2
#define RGB(r,g,b)\
((0<<24)|(b<<16)|(g<<8)|(r))
#else
#define RGB(r,g,b)\
((0<<24)|(r<<16)|(g<<8)|(b))
#endif

int RGB2(SDL_Surface *screen, unsigned char r, unsigned char g, unsigned char b);
// pixel funtion 32
void putpixel(SDL_Surface * s, int x, int y, Uint32 pixel);


#endif
