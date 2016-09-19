#include "Music.h"

//constructor
CMusic::CMusic(const char* filename)
{
	//load the music
	m_pMusic=Mix_LoadMUS(filename);
}

//destructor
CMusic::~CMusic()
{
	//free the music
	if(GetMusic())
	{
		Mix_FreeMusic(m_pMusic);
	}
}

//get music pointer
Mix_Music* CMusic::GetMusic()
{
	//retrieve music pointer
	return(m_pMusic);
}

//check for validity
bool CMusic::IsValid()
{
	//check for non-null music
	return(GetMusic()!=NULL);
}

//get music type
Mix_MusicType CMusic::GetType()
{
	//return the type
	return(Mix_GetMusicType(GetMusic()));
}

//set volume
void CMusic::SetVolume(int volume)
{
	//set the volume
	Mix_VolumeMusic(volume);
}

//get volume
int CMusic::GetVolume()
{
	//return the volume
	return(Mix_VolumeMusic(-1));
}

//play music
void CMusic::Play(CMusic* pMusic,int loops)
{
	//play the music
	Mix_PlayMusic(pMusic->GetMusic(),loops);
}

//fade in
void CMusic::FadeIn(CMusic* pMusic,int ms,int loops)
{
	//fade in the music
	Mix_FadeInMusic(pMusic->GetMusic(),loops,ms);
}

//pause
void CMusic::Pause()
{
	//pause the music
	Mix_PauseMusic();
}

//resume
void CMusic::Resume()
{
	//resume the music
	Mix_ResumeMusic();
}

//rewind
void CMusic::Rewind()
{
	//rewind the music
	Mix_RewindMusic();
}

//stop
void CMusic::Stop()
{
	//halt the music
	Mix_HaltMusic();
}

//fade out
void CMusic::FadeOut(int ms)
{
	//fade out the music
	Mix_FadeOutMusic(ms);
}

//is playing?
bool CMusic::IsPlaying()
{
	//check if music is playing
	return(Mix_PlayingMusic()==1);
}

//is paused?
bool CMusic::IsPaused()
{
	//check for paused state
	return(Mix_PausedMusic()==1);
}

//is fading?
bool CMusic::IsFading()
{
	//check for fading
	return(Mix_FadingMusic()!=MIX_NO_FADING);
}

//is fading out?
bool CMusic::IsFadingOut()
{
	//check for fading out
	return(Mix_FadingMusic()==MIX_FADING_OUT);
}

//is fading in?
bool CMusic::IsFadingIn()
{
	//check for fading in
	return(Mix_FadingMusic()==MIX_FADING_IN);
}

