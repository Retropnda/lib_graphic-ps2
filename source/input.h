#ifndef    INPUT_H_
#define   INPUT_H_

#include <SDL/SDL.h>

#define hat_up  SDL_HAT_UP
#define hat_down SDL_HAT_DOWN
#define hat_left SDL_HAT_LEFT
#define hat_right SDL_HAT_RIGHT

//BUTTONS
#define PS2_SCUARE       0x0000//0
#define PS2_CROSS        0x0001//1
#define PS2_CIRCULE      0X0002//2
#define PS2_TRIANGLE     0x0003//3
#define PS2_SELECT       0x0004//4
#define PS2_START        0x0005//5
#define PS2_L1           0x0006//6
#define PS2_R1           0x0007//7
#define PS2_L2           0x0008//8
#define PS2_R2           0x0009//9


#define PS2_LEFT         0x000A//12
#define PS2_RIGHT        0X000B//13
#define PS2_DOWN         0X000C//14
#define PS2_UP           0x000D//15


typedef struct INPUT{
 	int button_down;
 	int button_up;
 	Uint8 *keys;
 	SDL_Joystick *joystick[4];//dos joysticks
 	void init();
 	void update_event();
 	bool down_press(int event);
 	bool get_hat(int hat);
 	bool get_button(int button);
 	void input_read();
}Input;

#endif//
