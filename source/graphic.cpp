#include "pixel.h"
#include "graphic.h"


void Debug(const char *msg)
{
	//FILE *fd = fopen("debug.txt", "w");
	fprintf(stdout, "%s", msg);
	//fclose(fd);
}


int max(int a, int b){
  if(a > b) return a;
   return b;
}


void Window::line(Uint32 pixel, int x0, int y0, int x1, int y1)
{
	int X, Y, dx, dy, step;
	dx = abs(x0 - x1);
	dy = abs(y0 - y1);
	step = max(dx, dy);
	step = !step ? 1 : step;

	for(int i = 0 ; i < step; i++)
	{
		X = x1 + (x0 - x1) * i / step;
		Y = y1 + (y0 - y1) * i / step;
		putpixel(screen, X, Y, pixel);
	}
}

void Window::clean()
{
	if (fliping)
	{
		memset(screen->pixels, 0, screen->pitch * screen->h);
	}
}

void Window::flip()
{
	if (fliping)
	{
		SDL_Flip(screen);
	}
}

void Window::pixel32(Uint32 pixel, int x, int y)
{
	putpixel(screen, x, y, pixel);
}


void Window::rect(int x, int y, int w, int h, Uint32 pixel){
	int i,j;
	for(i=1;i<w;i++){
		for(j=1;j<h;j++){
			putpixel(screen,x+i,y+j,pixel);
		}
	}
}


Window *Init_Window(int w, int h, int bpp, const char *msg)
{
	Window *wd = NULL;
	wd = new Window;
	wd->screen = NULL;
	wd->fliping = false;
	int W, H;
	W = w;
	H = h;
	wd->BPP = bpp;

#if USE_PS2
	printf("iniciando sdl\n");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		printf("error al iniciar sdl\n");
		printf("error: %s\n", SDL_GetError());
		return NULL;
	}
#else
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Debug("error init");
		printf("error: %s\n", SDL_GetError());
		return NULL;
	}
#endif
	printf("inicio sdl\n");
	wd->screen = SDL_SetVideoMode(W, H, wd->BPP, SDL_HWSURFACE);
	if (wd->screen == NULL)
	{
		Debug("pantalla");
		printf("error: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_ShowCursor(false);
	fontsize(8,8);//inica font
	wd->fliping = true;
	return wd;
}

void Window::fps_sincronizar(int FRECUENCIA)
{
	static int t;
	static int tmp;
	static int tl = 0;

	t = SDL_GetTicks();

	if (t - tl >= FRECUENCIA)
	{
		tmp = (t - tl) / FRECUENCIA;
		tl += tmp * FRECUENCIA;
	}
	else
	{
		SDL_Delay(FRECUENCIA - (t - tl));
		tl += FRECUENCIA;
	}
}

void free_Window(Window *w){
  SDL_FreeSurface(w->screen);
  delete w;
}


void Window::draw_text( char *msg, int x, int y, Uint32 pixel){
	print(screen,x,y,msg,pixel);
}


SDL_Surface *load_bmp_fm(char *name, int size){
	SDL_Surface *temp;
	SDL_RWops *rwops = SDL_RWFromConstMem(name,size);
	if(rwops == NULL){
		printf("error: no puede leer memoria %s\n",SDL_GetError());
		return NULL;
	}
	temp = SDL_LoadBMP_RW(rwops, 1);	
	if(temp == NULL){
		printf("erro: %s\n",SDL_GetError());
		return NULL;
	}
	temp = SDL_DisplayFormat(temp);
	printf("load texture\n");
	return temp;
}

SDL_Surface *load_img_fm(char *name, int size){
	SDL_Surface *temp;
	SDL_RWops *rwops = SDL_RWFromConstMem(name,size);
	if(rwops == NULL){
		printf("error: no puede leer memoria %s\n",SDL_GetError());
		return NULL;
	}
	temp = IMG_Load_RW(rwops, 1);
	if(temp == NULL){
		printf("erro: %s\n",SDL_GetError());
		return NULL;
	}
	temp = SDL_DisplayFormat(temp);
	printf("load texture \n");
	return temp;
}