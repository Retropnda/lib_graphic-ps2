#include "graphic.h"
#include "sfx.h"



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
static int last_dir = right;
static int count = 0;
Window *w;
gfxFont *my_font;
int x,y;

void draw_personaje(){
	if(joystick->get_hat(hat_down)){y+=1; spr[down]->animate()->draw(w->screen,x,y); last_dir = down;}
	if(joystick->get_hat(hat_up)){y-=1;   spr[up]->animate()->draw(w->screen,x,y);   last_dir = up;}
	if(joystick->get_hat(hat_left)){x-=1; spr[left]->animate()->draw(w->screen,x,y); last_dir = left;}
	if(joystick->get_hat(hat_right)){x+=1;spr[right]->animate()->draw(w->screen,x,y); last_dir = right;}

	spr[last_dir]->draw(w->screen,x,y);

}

int main(int argc, char **argv)
{
	init_logo();
	
	w = new Window;
	w = Init_Window(320, 240,24, "test");
	joystick = new Input;
	joystick->init();
	//sfx_init();
	my_font = new gfxFont;
	my_font->init(large);
	
	x=y=0;
	int done = 0;

	//lee desde memoria 
	SDL_Surface *img = load_img_fm(img_bmp_start,img_bmp_size);
	SDL_Surface *mega = load_img_fm(mega_bmp_start,mega_bmp_size);

	spr[sheet] = new Sprite(img,1,1);
	spr[sheet]->setTransparency(255,0,255);

   	spr[down] = new Sprite(spr[sheet]->getRect(1,1,32*6,32),6,30);
   	spr[up]   = new Sprite(spr[sheet]->getRect(1,32*3,6*32,32),6,30);

   	spr[left] = new Sprite(spr[sheet]->getRect(1,32*2,6*32,32),6,30);
   	spr[left]->reverseAnimation()->flipHorizontal();

   	spr[right] = new Sprite(spr[sheet]->getRect(1,32*2,6*32,32),6,30);
   	//spr[right]->flipHorizontal();

	while (!done)
	{
		
		joystick->input_read();

		SDL_BlitSurface(mega,0,w->screen,0);


		if(joystick->button_up == PS2_CROSS){done =1;}
		if(joystick->button_up == PS2_CIRCULE){x--;}
		if(joystick->button_up == PS2_TRIANGLE){y++;}
		if(joystick->button_up == PS2_SCUARE){y--;}

		//if(joystick->button_down == PS2_CROSS){x++;}
		if(joystick->button_down == PS2_CIRCULE){x--;}
		if(joystick->button_down == PS2_TRIANGLE){y++;}
		if(joystick->button_down == PS2_SCUARE){y--;}
		
		

		
		my_font->draw(w->screen,20,20,"RETROPANDA");
		my_font->drawf(w->screen,20,60,"%d",count);
		draw_personaje();
		w->line(RGB2(w->screen,255,0,0),20,90, 1, 1);
		w->draw_text("hola este es un motor para ps2 v0.01 ", 10, 230, RGB2(w->screen,255,255,255));
		
		w->flip();
		w->clean();
		w->fps_sincronizar(10);
		count++;
	}
	 SDL_Quit();
	 //sfx_close();
     free_Window(w);
     delete joystick;
     delete my_font;
    

	return 0;
}
