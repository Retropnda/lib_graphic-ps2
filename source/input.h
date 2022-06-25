#ifndef    INPUT_H_
#define   INPUT_H_

#include <SDL/SDL.h>

#define hat_up  SDL_HAT_UP
#define hat_down SDL_HAT_DOWN
#define hat_left SDL_HAT_LEFT
#define hat_right SDL_HAT_RIGHT

//BUTTONS
#define JOY_UP 0x0001
#define JOY_DOWN 0x0002
#define JOY_LWFT 0x0004
#define JOY_RIGHT 0x0006

#define JOY_A 0x0008
#define JOY_B 0x0010
#define JOY_C 0x0012
#define JOY_D 0x0014
#define JOY_L1 0x0016
#define JOY_L2 0x0018
#define JOY_R1 0x0020
#define JOY_R2 0x0022
#define JOY_START 0x0024
#define JOY_SELECT 0x0026

//key 

#define KEY_UP 0x0001
#define KEY_DOWN 0x0002
#define KEY_LWFT 0x0004
#define KEY_RIGHT 0x0006

#define KEY_A 0x0008
#define KEY_B 0x0010
#define KEY_C 0x0012
#define KEY_D 0x0014
#define KEY_L1 0x0016
#define KEY_L2 0x0018
#define KEY_R1 0x0020
#define KEY_R2 0x0022
#define KEY_START 0x0024
#define KEY_SELECT 0x0026



typedef struct INPUT{
 	int key_pad;
 	Uint8 *keys;
 	SDL_Joystick *joystick[4];//dos joysticks
 	void init();
 	void update_event();
 	bool down_press(int event);
 	bool get_hat(int hat);
 	void input_read();
}Input;

#endif//
