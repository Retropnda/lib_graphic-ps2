#include <stdio.h>
#include "input.h"


// inicia el joystick e imprime infoemacion del mismo
void Input::init()
{

	// initializing the joystic subsystem
	SDL_InitSubSystem (SDL_INIT_JOYSTICK);

	int num_joysticks = SDL_NumJoysticks();

	if (num_joysticks == 0)
	{
		fprintf(stderr, "joystick: No joystick found.\n");
	}
	else
	{
		SDL_JoystickEventState (SDL_ENABLE);

		// : FIXME should check if num_joysticks is below 4..
		for (int i = 0; i < num_joysticks; i++)
		{
			joystick[i] = SDL_JoystickOpen (i);
			printf ("  %s\n", SDL_JoystickName(i));
			printf ("  %d-axis %d-buttons %d-balls %d-hats \n",
				SDL_JoystickNumAxes(joystick[i]),
				SDL_JoystickNumButtons(joystick[i]),
				SDL_JoystickNumBalls(joystick[i]),
				SDL_JoystickNumHats(joystick[i]));
		}
	}

	button_down = 0;
	button_up = 0;
}

//update events
void Input::update_event(){

}

bool Input::down_press(int event){
 return false;
}

bool Input::get_hat(int hat){
	if(SDL_JoystickGetHat(joystick[0],0) == hat){return true;}
	return false;
}

bool Input::get_button(int button){
	if(SDL_JoystickGetButton(joystick[0],0) == button){return true;}
	return false;
}


void INPUT::input_read(){
	keys = SDL_GetKeyState(NULL);
 	SDL_JoystickUpdate();
	button_down = -1;
	button_up = -1;
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		//button down
		switch(event.type){
			case SDL_JOYBUTTONDOWN:
				switch(event.jbutton.button){
					case PS2_CROSS:    button_down = PS2_CROSS;    break;
					case PS2_CIRCULE:  button_down = PS2_CIRCULE;  break;
					case PS2_TRIANGLE: button_down = PS2_TRIANGLE; break;
					case PS2_SCUARE:   button_down = PS2_SCUARE;   break;
					case PS2_START:    button_down = PS2_START;    break;
					case PS2_SELECT:   button_down = PS2_SELECT;   break;
					case PS2_L1:       button_down = PS2_L1;       break;
					case PS2_L2:       button_down = PS2_L2;       break;
					case PS2_R1:       button_down = PS2_R2;       break;
					case PS2_UP:       button_down = PS2_UP;       break;
					case PS2_DOWN:     button_down = PS2_DOWN;     break;
					case PS2_LEFT:     button_down = PS2_LEFT;     break;
					case PS2_RIGHT:    button_down = PS2_RIGHT;    break;
					default: button_down = -1;
				}//button down
			case SDL_JOYBUTTONUP:
				switch(event.jbutton.button){
					case PS2_CROSS:    button_up = PS2_CROSS;    break;
					case PS2_CIRCULE:  button_up = PS2_CIRCULE;  break;
					case PS2_TRIANGLE: button_up = PS2_TRIANGLE; break;
					case PS2_SCUARE:   button_up = PS2_SCUARE;   break;
					case PS2_START:    button_up = PS2_START;    break;
					case PS2_SELECT:   button_up = PS2_SELECT;   break;
					case PS2_L1:       button_up = PS2_L1;       break;
					case PS2_L2:       button_up = PS2_L2;       break;
					case PS2_R1:       button_up = PS2_R2;       break;
					case PS2_UP:       button_up = PS2_UP;       break;
					case PS2_DOWN:     button_up = PS2_DOWN;     break;
					case PS2_LEFT:     button_up = PS2_LEFT;     break;
					case PS2_RIGHT:    button_up = PS2_RIGHT;    break;
					default: button_up = -1;
				}//button down

		}//switch
	}//while
}