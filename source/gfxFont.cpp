#include "gfxFont.hpp"

#include <stdarg.h>		//atexit?
#include <stdlib.h>	
#include <stdio.h>	//atexit?
#include <string>


int short x_shake;
int short y_shake;

// gfxFont
gfxFont::gfxFont()
{
	m_font = NULL;
}

gfxFont::~gfxFont()
{
	if(m_font)
		SFont_FreeFont(m_font);
};

bool gfxFont::init(const char *filename)
{
	if(m_font)
		SFont_FreeFont(m_font);

	printf("\nloading font....\n");

	SDL_Surface *fontsurf = IMG_Load(filename);
	if(fontsurf == NULL)
	{
        printf(" ERROR: Couldn't load file %s\n ",SDL_GetError());
             
		return false;
	}

	m_font = SFont_InitFont(fontsurf);
	if(!m_font)
	{
        printf(" ERROR: an error occurre while loading the font.");
		return false;
	}

    printf("done");
	return true;
}

void gfxFont::draw(SDL_Surface *screen,int x, int y,const char *s)
{
	//if(y + getHeight() < 0)
	//	return;

	SFont_Write(screen, m_font, x, y,s);
}

void gfxFont::drawChopRight(SDL_Surface *screen, int x, int y, int width, const char *s)
{
	//if(y + getHeight() < 0)
	//	return;
		
	SFont_WriteChopRight(screen, m_font, x, y, width, s);
}

void gfxFont::drawChopLeft(SDL_Surface *screen, int x, int y, int width, const char *s)
{
	//if(y + getHeight() < 0)
	//	return;
		
	SFont_WriteChopLeft(screen, m_font, x, y, width, s);
}

void gfxFont::drawCentered(SDL_Surface *screen, int x, int y, const char *text)
{
	//if(y + getHeight() < 0)
	//	return;
		
	SFont_WriteCenter(screen, m_font, x, y, text);
};

void gfxFont::drawChopCentered(SDL_Surface *screen, int x, int y, int width, const char *text)
{
	//if(y + getHeight() < 0)
	//	return;
		
	SFont_WriteChopCenter(screen, m_font, x, y, width, text);
};

void gfxFont::drawRightJustified(SDL_Surface *screen, int x, int y, const char *s, ...)
{
	char buffer[256];

	va_list zeiger;
	va_start(zeiger, s);
	vsprintf(buffer, s, zeiger);
	va_end(zeiger);

	//if(y + getHeight() < 0)
	//	return;
		
	SFont_WriteRight(screen, m_font, x, y, buffer);
};


void gfxFont::drawf(SDL_Surface *screen, int x, int y, const char *s, ...)
{
	char buffer[256];

	va_list zeiger;
	va_start(zeiger, s);
	vsprintf(buffer, s, zeiger);
	va_end(zeiger);

	draw(screen,x,y,buffer);
}

void gfxFont::setalpha(Uint8 alpha)
{
	if( (SDL_SetAlpha(m_font->Surface, SDL_SRCALPHA | SDL_RLEACCEL, alpha)) < 0)
	{
		printf("\n ERROR: couldn't set alpha on sprite: %s\n", SDL_GetError());
	}
}
