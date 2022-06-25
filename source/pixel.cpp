#include "pixel.h"


int RGB2(SDL_Surface *screen, unsigned char r, unsigned char g, unsigned char b){
	int c = SDL_MapRGB(screen->format,r,g,b);
	return c;
}

// pixel funtion 32
void putpixel(SDL_Surface * s, int x, int y, Uint32 pixel)
{
	
	if (x > 0 && y > 0 && x < s->w && y < s->h)
	{	
		int bpp = s->format->BytesPerPixel; /*conocemos la profundidad de la supeficie 1=8 2=16 3=24 4=32*/
		Uint8 *p = (Uint8 *)s->pixels + y * s->pitch + x * bpp; //esto es el step
		   switch(bpp) {
   	 		case 1:
        		*p = pixel;
        	break;

    		case 2:
        		*(Uint16 *)p = pixel;
        		break;

    		case 3:
        		if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            		p[0] = (pixel >> 16) & 0xff;
            		p[1] = (pixel >> 8) & 0xff;
            		p[2] = pixel & 0xff;
        		} else {
            		p[0] = pixel & 0xff;
            		p[1] = (pixel >> 8) & 0xff;
            		p[2] = (pixel >> 16) & 0xff;
        		}
        	break;

    		case 4:
        		*(Uint32 *)p = pixel;
        	break;
    		}
		
	}
}
