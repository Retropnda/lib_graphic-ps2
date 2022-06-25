#include "font.h"

     
//COSNTRUCTOR POR DEFECTO DA VALOR A ANCHO Y ALTO 8
void __attribute__((constructor)) SETFONTMODE(void){
    FONTMODE.ancho = 8;
    FONTMODE.alto = 8;
    return;
}

void caracter(SDL_Surface *screen,  int x, int y, const char ascii, unsigned int color ){
	// Los valores de la estructura FONTMODE definen el tamaño de las letras.
    int X,Y,W,H;//variables a usar
    for (Y=0; Y<FONTMODE.ancho; ++Y)//for para abrir ALTO
        for (X=0; X<FONTMODE.alto; ++X){//for para abrir ANCHO
			W = (8 * X / FONTMODE.ancho);//estiramiento calcula cuantos pixeles deveran ser rellenados a lo largo dependiendo el tama�o
            H = (8 * Y / FONTMODE.alto);//estiramiento  calcula cuantos pixeles deveran ser rellenados a lo alto dependiendo el tama�o 
            if ((font_data[ H+(ascii)*8 ]>>W) & 1 ){ putpixel( screen,X+x,Y+y, color ); }//esto no lo entiendo bien
        }
    return;//retornas el control
}

void fontsize( int w, int h ){
    FONTMODE.ancho = w;
    FONTMODE.alto  = h;
    return;
}

void print(SDL_Surface *screen, int x, int y, char *text, unsigned int color_t){
     int i;
     int longitud = strlen(text);//es necesario conocer la longitud?
     for(i=0;i<longitud;i++){//recorreremos la derecha
          caracter(screen,(x+i*(FONTMODE.ancho)),y,(*text++),color_t);
           }
     }

void print_f(SDL_Surface *screen, int x, int y, const char *s, unsigned int color_t, ...){
    
    char buffer[256];

	va_list zeiger;
	va_start(zeiger, s);
	vsprintf(buffer, s, zeiger);
	va_end(zeiger);

    print(screen,x,y,buffer,color_t); 
     }
