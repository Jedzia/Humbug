#ifndef __SOUND_H__
#define __SOUND_H__

#include "sdl_mixer.h"

/*
	==CSound==
	abstracts Mix_Chunk
*/
class CSound  
{
private:
	//chunk pointer
	Mix_Chunk* m_pChunk;
public:
	//constructor
	CSound(char* filename);
	//destructor
	virtual ~CSound();
	//get chunk
	Mix_Chunk* GetChunk();
	//check for a valid chunk
	bool IsValid();
	//set volume
	void SetVolume(int volume);
	//get volume
	int GetVolume();
};

#endif //#ifndef __SOUND_H__
