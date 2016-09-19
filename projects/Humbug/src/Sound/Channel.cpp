#include "Channel.h"

std::vector<CChannel*> CChannel::s_ChannelList;

CChannel CChannel::s_NullChannel(-1);

//construct a channel
CChannel::CChannel(int channel)
{
	//set the channel number
	m_Channel=channel;
}

//destroy a channel
CChannel::~CChannel()
{
	//do nothing
}

//play
bool CChannel::Play(CSound* pSound,int loops,int ticks)
{
	//play the sound
	return(Mix_PlayChannelTimed(m_Channel,pSound->GetChunk(),loops,ticks)!=-1);
}

//fade in
bool CChannel::FadeIn(CSound* pSound,int ms,int loops,int ticks)
{
	//fade in the sound
	return(Mix_FadeInChannelTimed(m_Channel,pSound->GetChunk(),loops,ms,ticks)!=-1);
}

//pause
bool CChannel::Pause()
{
	//pause the channel
	Mix_Pause(m_Channel);
	//return true
	return(true);
}

//resume
bool CChannel::Resume()
{
	//resume the channel
	Mix_Resume(m_Channel);
	//return
	return(true);
}

//stop
bool CChannel::Stop()
{
	//halt the channel
	Mix_HaltChannel(m_Channel);
	//return
	return(true);
}

//fade out
bool CChannel::FadeOut(int ms)
{
	//fade out the channel
	return(Mix_FadeOutChannel(m_Channel,ms)!=0);
}

//expire
bool CChannel::Expire(int ms)
{
	//expire the channel
	return(Mix_ExpireChannel(m_Channel,ms)!=0);
}

//is playing
bool CChannel::IsPlaying()
{
	//return
	return(Mix_Playing(m_Channel)!=0);
}

//is paused
bool CChannel::IsPaused()
{
	//return
	return(Mix_Paused(m_Channel)!=0);
}

//is fading
bool CChannel::IsFading()
{
	//return
	return(Mix_Fading(m_Channel)==MIX_NO_FADING);
}

//is fading in
bool CChannel::IsFadingIn()
{
	//return
	return(Mix_Fading(m_Channel)==MIX_FADING_IN);
}

//is fading out
bool CChannel::IsFadingOut()
{
	//return
	return(Mix_Fading(m_Channel)==MIX_FADING_OUT);
}

//allocate channels
bool CChannel::Allocate(int channelcount)
{
	//allocate new number of channels
	int newchannelcount=Mix_AllocateChannels(channelcount);
	//delete any excess channels
	while(newchannelcount<ChannelCount())
	{
		//grab last channel
		CChannel* pChannel=GetChannel(ChannelCount()-1);
		//delete the channel
		delete pChannel;
		//remove last item in vector list
		s_ChannelList.pop_back();
	}
	//add new channels
	while(newchannelcount>ChannelCount())
	{
		//create a new channel
		CChannel* pChannel=new CChannel(ChannelCount());
		//add channel to list
		s_ChannelList.push_back(pChannel);
	}
	//return
	return(newchannelcount==channelcount);
}

//determine number of channels
int CChannel::ChannelCount()
{
	//return the size of the vector
	return(s_ChannelList.size());
}

//get a channel
CChannel* CChannel::GetChannel(int channel)
{
	//check for -1
	if(channel==-1)
	{
		//look for a channel
		for(int index=0;index<ChannelCount();index++)
		{
			//check for valid channel
			if(GetChannel(index)->IsPlaying()) continue;
			//found one
			return(GetChannel(index));
		}
		//no channel found
		return(&s_NullChannel);
	}
	else
	{
		//check range
		if(channel<ChannelCount())
		{
			//return the channel
			return(s_ChannelList[channel]);
		}
		else
		{
			//not a valid channel
			return(&s_NullChannel);
		}
	}
}

