#include "graphic.h"
#if USE_PS2
#include "file.h"
#else
#include <SDL/SDL.h>
#endif


enum{
	sheet,
	up,
	down,
	left,
	right,
	max_spr
};

Sprite *spr[max_spr];
Input *joystick;

int main(int argc, char **argv)
{
	Window *w;
	w = new Window;
	w = Init_Window(320, 240,24, "test");
	joystick = new Input;
	joystick->init();
	//SDL_InitSubSystem(SDL_INIT_AUDIO);
	int x,y;
	x=y=0;

	//lee desde memoria 
	SDL_Surface *img = load_img_fm(img_bmp_start,img_bmp_size);
	SDL_Surface *mega = load_img_fm(mega_bmp_start,mega_bmp_size);

	spr[sheet] = new Sprite(img,1,1);
	spr[sheet]->setTransparency(255,0,255);

   	spr[down] = new Sprite(spr[sheet]->getRect(1,1,32*6,32),6,30);
   	spr[up]   = new Sprite(spr[sheet]->getRect(1,32*3,6*32,32),6,30);

   	spr[left] = new Sprite(spr[sheet]->getRect(1,32*2,6*32,32),6,30);
   	spr[left]->reverseAnimation();

   	spr[right] = new Sprite(spr[sheet]->getRect(1,32*2,6*32,32),6,30);
   	spr[right]->flipHorizontal();

	while (1)
	{
		joystick->update_event();

		if(joystick->get_hat(hat_down)){y+=1;}
		if(joystick->get_hat(hat_up)){y-=1;}
		if(joystick->get_hat(hat_left)){x-=1;}
		if(joystick->get_hat(hat_right)){x+=1;}

		SDL_BlitSurface(mega,0,w->screen,0);
		spr[right]->animate()->draw(w->screen,x,y);
		w->line(RGB2(w->screen,255,0,0),320,240, 1, 1);
		w->draw_text("hola ", 10, 10, RGB2(w->screen,255,0,0));
		//w->rect(100, 100, 10, 10,RGB(rand()%255, rand()%255, rand()%255));
		w->flip();
		w->clean();
		w->fps_sincronizar(10);
	}
     free_Window(w);
    

	return 0;
}
