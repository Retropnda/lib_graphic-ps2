/*****************************************************************************
*                                                                            *
* SFX_Sound por Andres Ruiz                                                  *
*                                                                            *
* Desarrollo de Viodeo juegos c++                                            *
*                                                                            *
******************************************************************************/
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <string>


#define NUM_SOUND_CHANNELS 16

bool sfx_init();
void sfx_close();
void sfx_stopallsounds();
void sfx_setmusicvolume(int volume);
void sfx_setsoundvolume(int volume);

class sfxSound
{
	public:
		sfxSound();
		~sfxSound();

		bool init(const char *path);

		int play();
		int playloop(int iLoop);
		void stop();
		void sfx_pause();

		void resetpause() {paused = false;}

		void reset();
		bool isready() {return ready;}
		int isplaying();

		void clearchannel();
		
	private:
		Mix_Chunk *sfx;
		int channel;
		bool paused;
		bool ready;
		int starttime;
		short instances;
};


/******musicas*****/

class sfxMusic
{
	public:
		sfxMusic();
		~sfxMusic();

		bool load(const char *path);

		void play();
		void stop();
		void sfx_pause();

		void resetpause() {paused = false;}

		void reset();
		bool isready() {return ready;}
		int isplaying();

	private:
		Mix_Music *music;
		bool paused;
		bool ready;
};


