/*****************************************************************************
*                                                                            *
* SFX_Sound por Andres Ruiz                                                  *
*                                                                            *
* Desarrollo de Viodeo juegos c++                                            *
*                                                                            *
******************************************************************************/

/*sfx heder*/
#include "sfx.h"

extern bool fResumeMusic;

sfxSound * g_PlayingSoundChannels[NUM_SOUND_CHANNELS];

bool sfx_init()
{
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2, 1024);
	Mix_AllocateChannels(NUM_SOUND_CHANNELS);

	for(short iChannel = 0; iChannel < NUM_SOUND_CHANNELS; iChannel++)
		g_PlayingSoundChannels[iChannel] = NULL;

    return true;
}

void sfx_close()
{
	Mix_CloseAudio();
}

void sfx_stopallsounds()
{
	Mix_HaltChannel(-1);

	for(short iChannel = 0; iChannel < NUM_SOUND_CHANNELS; iChannel++)
		g_PlayingSoundChannels[iChannel] = NULL;
}

void sfx_setmusicvolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void sfx_setsoundvolume(int volume)
{
	Mix_Volume(-1, volume);
}



/***************************/
sfxSound::sfxSound()
{
	paused = false;
	ready = false;
	sfx = NULL;
}

sfxSound::~sfxSound()
{}



bool sfxSound::init(const char *path)
{
	if(sfx)
		reset();

	
	sfx = Mix_LoadWAV(path);
	
	if(sfx == NULL)
	{
		printf(" failed!\n");
		return false;
	}

	channel = -1;
	starttime = 0;
	ready = true;
	instances = 0;

	//Mix_ChannelFinished(&soundfinished);
	
	return true;
}



int sfxSound::play()
{
	int ticks = SDL_GetTicks();

	//Don't play sounds right over the top (doubles volume)
	if(channel < 0 || ticks - starttime > 40)
	{
		instances++;
		channel = Mix_PlayChannel(-1, sfx, 0);

		if(channel < 0)
			return channel;

		starttime = ticks;
		
		if(g_PlayingSoundChannels[channel])
			printf("Error: Sound was played on channel that was not cleared!\n");

		g_PlayingSoundChannels[channel] = this;
	}
	return channel;
}



int sfxSound::playloop(int iLoop)
{
	instances++;
	channel = Mix_PlayChannel(-1, sfx, iLoop);

	if(channel < 0)
		return channel;

	g_PlayingSoundChannels[channel] = this;

	return channel;
}

void sfxSound::stop()
{
	if(channel != -1)
	{
		instances = 0;
		Mix_HaltChannel(channel);
		channel = -1;
	}
}



void sfxSound::sfx_pause()
{
	paused = !paused;

	if(paused)
		Mix_Pause(channel);
	else
		Mix_Resume(channel);
}

void sfxSound::clearchannel()
{
	if(--instances <= 0)
	{
		instances = 0;
		channel = -1;
	}
}

void sfxSound::reset()
{
	Mix_FreeChunk(sfx);
	sfx = NULL;
	ready = false;

	if(channel > -1)
		g_PlayingSoundChannels[channel] = NULL;

	channel = -1;
}

int sfxSound::isplaying()
{
	if(channel == -1)
		return false;

	return Mix_Playing(channel);
}


/*********musicas********/


sfxMusic::sfxMusic()
{
	paused = false;
	ready = false;
	music = NULL;
}

sfxMusic::~sfxMusic()
{}

bool sfxMusic::load(const char *path)
{
	if(music)
		reset();

    
	music = Mix_LoadMUS(path);
	
	if(!music)
	{
	    printf("Error Loading Music: %s\n", Mix_GetError());
		return false;
	}

	//Mix_HookMusicFinished(&musicfinished);

	ready = true;

	return true;
}

void sfxMusic::play()
{
	Mix_PlayMusic(music,0);
	//fResumeMusic = fResume;
}

void sfxMusic::stop()
{
	Mix_HaltMusic();
}

void sfxMusic::sfx_pause()
{
	paused = !paused;

	if(paused)
		Mix_PauseMusic();
	else
		Mix_ResumeMusic();
}

void sfxMusic::reset()
{
	Mix_FreeMusic(music);
	music = NULL;
	ready = false;
}

int sfxMusic::isplaying()
{
	return Mix_PlayingMusic();
}



