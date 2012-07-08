#ifndef __CHANNEL_H__
#define __CHANNEL_H__

//include sdl mixer stuff
#include "sdl_mixer.h"
//include vector container
#include <vector>
//include CSound stuff
#include "Sound.h"

/*
	==CChannel==
	Abstracts an SDL_mixer channel
*/
class CChannel  
{
private:
	//channel number
	int m_Channel;
	//vector of channels
	static std::vector<CChannel*> s_ChannelList;
	//null channel
	static CChannel s_NullChannel;
public:
	//construct a channel
	CChannel(int channel);
	//destroy a channel
	virtual ~CChannel();
	//play
	bool Play(CSound* pSound,int loops=0,int ticks=-1);
	//fade in
	bool FadeIn(CSound* pSound,int ms,int loops=0,int ticks=-1);
	//pause
	bool Pause();
	//resume
	bool Resume();
	//stop
	bool Stop();
	//fade out
	bool FadeOut(int ms);
	//expire
	bool Expire(int ms);
	//is playing
	bool IsPlaying();
	//is paused
	bool IsPaused();
	//is fading
	bool IsFading();
	//is fading in
	bool IsFadingIn();
	//is fading out
	bool IsFadingOut();
	//allocate channels
	static bool Allocate(int channelcount);
	//determine number of channels
	static int ChannelCount();
	//get a channel
	static CChannel* GetChannel(int channel=-1);
};

#endif //#ifndef __CHANNEL_H__
