#ifndef __TVPLAYER_H__
#define __TVPLAYER_H__

#include <vector>
#include "CChannel.h"
#include "tv_types.h"

//typedef std::vector<CChannel*> ChannelVector;

class ITvPlayer
{
public:
	// ITvPlayer() {};
	// virtual ~ITvPlayer() {};

	virtual bool playCur(void) = 0;
	virtual bool playPrev(void) = 0;
	virtual bool playNext(void) = 0;
	virtual bool playBack(void) = 0;
	virtual bool play(unsigned int chIndex) = 0;
	virtual bool pause(bool freeze = true) = 0;
	virtual bool stop(bool freeze = false) = 0;
	virtual bool reset(void) = 0;

	virtual unsigned int getChannelCount(void) = 0;
	virtual CChannel* getCurChannel(void) = 0;
	virtual CChannel* getChannel(unsigned int chIndex) = 0;
};

class TvPlayer : public ITvPlayer
{
public:
	TvPlayer() : _source(SKYTV_INPUT_SOURCE_UNKNOWN), _chIndexCur(0), _chIndexOld(0)   {}
	// TvPlayer(SKYTV_INPUT_SOURCE_TYPE soureInput);
	virtual ~TvPlayer() {};

	virtual bool playCur(void);
	virtual bool playPrev(void);
	virtual bool playNext(void);
	virtual bool playBack(void);
	virtual bool play(unsigned int chIndex);
	virtual bool pause(bool freeze = true);
	virtual bool stop(bool freeze = true);
	virtual bool reset(void);

	virtual unsigned int getChannelCount(void);
	virtual CChannel* getCurChannel(void);
	virtual CChannel* getChannel(unsigned int chIndex);

public:
	virtual unsigned int getLastChannelIndex(void);
	virtual bool swapChannel(unsigned int firstChannelIndex, unsigned int secondChannelIndex);
	virtual bool setChannelStatus(unsigned int chIndex, SKYTV_CHANNEL_OPT_TYPE opt, bool status);

	virtual bool getAllFav(std::vector<CChannel*>& favCh);

protected:
	SKYTV_INPUT_SOURCE_TYPE _source;
	unsigned int _chIndexCur;//channel's index in current vector.
	unsigned int _chIndexOld;//preview channel's index in current vector.
};



#endif // __TVPLAYER_H__

