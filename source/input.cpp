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

	key_pad = 0;
}

//update events
void Input::update_event(){
	keys = SDL_GetKeyState(NULL);
 	SDL_JoystickUpdate();
}

bool Input::down_press(int event){
 return false;
}

bool Input::get_hat(int hat){
	if(SDL_JoystickGetHat(joystick[0],0) == hat){return true;}
	return false;
}


void INPUT::input_read(){

	SDL_Event event;
	while(SDL_PollEvent(&event)){

	}
}