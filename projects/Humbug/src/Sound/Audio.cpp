#include "Audio.h"

//open audio device
bool CAudio::Open(int chunksize,int frequency, Uint16 format,int channels)
{
	//close the device first
	Close();
	//open the audio device
	return(Mix_OpenAudio(frequency,format,channels,chunksize)==0);
}

//close audio device
void CAudio::Close()
{
	//grab statistics
	int frequency=0;
	Uint16 format=0;
	int channels=0;
	//how many times has the audio device been opened?
	int OpenCount=Mix_QuerySpec(&frequency,&format,&channels);
	//close the audio device that number of times
	while(OpenCount>0)
	{
		//close device
		Mix_CloseAudio();
		//decrease counter
		OpenCount--;
	}
}

//get frequency
int CAudio::GetFrequency()
{
	//grab statistics
	int frequency=0;
	Uint16 format=0;
	int channels=0;
	//query the spec
	Mix_QuerySpec(&frequency,&format,&channels);
	//return the frequency
	return(frequency);
}

//get format
Uint16 CAudio::GetFormat()
{
	//grab statistics
	int frequency=0;
	Uint16 format=0;
	int channels=0;
	//query the spec
	Mix_QuerySpec(&frequency,&format,&channels);
	//return the format
	return(format);
}

//get channels
int CAudio::GetChannels()
{
	//grab statistics
	int frequency=0;
	Uint16 format=0;
	int channels=0;
	//query the spec
	Mix_QuerySpec(&frequency,&format,&channels);
	//return the channels
	return(channels);
}

