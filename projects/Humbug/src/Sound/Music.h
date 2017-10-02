#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "sdl_mixer.h"

/*
	==CMusic==
	Abstracts Mix_Music
*/
class CMusic  
{
private:
	//pointer to music
	Mix_Music* m_pMusic;
public:
	//constructor
	CMusic(const char* filename);
	//destructor
	virtual ~CMusic();
	//get music pointer
	Mix_Music* GetMusic();
	//check for validity
	bool IsValid();
	//get music type
	Mix_MusicType GetType();
	//set volume
	static void SetVolume(int volume);
	//get volume
	static int GetVolume();
	//play music
	static void Play(CMusic* pMusic,int loops=-1);
	//fade in
	static void FadeIn(CMusic* pMusic,int ms,int loops=-1);
	//pause
	static void Pause();
	//resume
	static void Resume();
	//rewind
	static void Rewind();
	//stop
	static void Stop();
	//fade out
	static void FadeOut(int ms);
	//is playing?
	static bool IsPlaying();
	//is paused?
	static bool IsPaused();
	//is fading?
	static bool IsFading();
	//is fading out?
	static bool IsFadingOut();
	//is fading in?
	static bool IsFadingIn();
};

#endif //#ifndef __MUSIC_H__
