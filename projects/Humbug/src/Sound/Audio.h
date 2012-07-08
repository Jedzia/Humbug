#ifndef __AUDIO_H__
#define __AUDIO_H__

//include sdl mixer
#include "sdl_mixer.h"

/*
	==CAudio==
	Allows opening and closing of audio device
*/
class CAudio  
{
public:
	//open audio device
	static bool Open(int chunksize,int frequency=MIX_DEFAULT_FREQUENCY, Uint16 format=MIX_DEFAULT_FORMAT,int channels=MIX_DEFAULT_CHANNELS);
	//close audio device
	static void Close();
	//get frequency
	static int GetFrequency();
	//get format
	static Uint16 GetFormat();
	//get channels
	static int GetChannels();
};

#endif //#ifndef __AUDIO_H__
