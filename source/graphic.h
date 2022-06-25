/*LIB GRAPHIC ES UNA COLECCIONDE FUNCIONES DE GRAFICOS 
DISAÑADA POR RETROPANDA USE ESTE CODIGO COMO QUIERA */

#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>

#include "font.h"
#include "gfxFont.hpp"
#include "Sprite.h"
#include "pixel.h"
#include "input.h"





int max(int a, int b);

// nueva libreria
// esta estructura contiene toda la informacion
// para un pantalla un pantallaso:)
typedef struct WINDOW
{
	int w;
	int h;
	int BPP;
	bool fliping;
	SDL_Surface *screen;
	// metodos
	void flip();
	void clean();
	void pixel32(Uint32 pixel, int x, int y);
	void line(Uint32 pixel, int x0, int y0, int x1, int y1);
	void rect(int x, int y, int w, int h, Uint32 pixel);
	void fps_sincronizar(int FRECUENCIA);
	void draw_text(char *msg, int x, int y, Uint32 pixel); //esto solo funcionara si la profundidad es de 16 bpp
} Window;

void Debug(const char *msg);
Window *Init_Window(int w, int h, int bpp, const char *msg);
void free_Window(Window *w);
SDL_Surface *load_bmp_fm(char *name, int size);
SDL_Surface *load_img_fm(char *name, int size);


#endif
